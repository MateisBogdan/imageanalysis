#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(255);
    ui->verticalSlider_2->setMinimum(0);
    ui->verticalSlider_2->setMaximum(255);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open image")
                                                    ,"D:/",tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    poza = imread(fileName.toLatin1().data(),0);
    address=fileName;

    QImage img= QImage((uchar*) poza.data,poza.cols,poza.rows,
                       poza.step,QImage::Format_Grayscale8);
    ui->label_3->setPixmap(QPixmap::fromImage(img));
   ui->label_3->resize(ui->label_3->pixmap()->size());
}

void MainWindow::on_pushButton_2_clicked()
{
    vector<vector<Point> > contours;
      vector<Vec4i>hierarchy;

       Mat tempoza= Mat::zeros(poza.size(),CV_8UC3);

    vector<String> paths1;
    glob(path1,paths1,false);

    vector<String> paths2;
    glob(path2,paths2,false);

    vector<String> paths3;
    glob(path3,paths3,false);


    vector<String> paths4;
    glob(path4,paths4,false);

    RNG rng(12345);

    threshold(poza,tempoza,min,max,THRESH_BINARY_INV);

    findContours(tempoza,contours,hierarchy,scantype,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

QString minimu;
String cvstring;
    for(size_t i=0;i<paths1.size();i++){
        cvstring+=Histograma::scrieContururi(paths1[i],min,max,"a",scantype,picks)+"\n";



    }
    for(size_t i=0;i<paths2.size();i++){
        cvstring+=Histograma::scrieContururi(paths2[i],min,max,"b",scantype,picks)+"\n";



    }
    for(size_t i=0;i<paths3.size();i++){
        cvstring+=Histograma::scrieContururi(paths3[i],min,max,"c",scantype,picks)+"\n";



    }
    for(size_t i=0;i<paths4.size();i++){
        cvstring+=Histograma::scrieContururi(paths4[i],min,max,"d",scantype,picks)+"\n";



    }
    minimu=QString::fromStdString(cvstring);
    QString filename;
    if(picks){
    filename= "D:/programming/R/data/threshtest"+QString::number(min)+"scan"+QString::number(scantype)+"ms.txt";
    }
    else{
        filename= "D:/programming/R/data/threshtest"+QString::number(min)+"scan"+QString::number(scantype)+".txt";
    }
       QFile fisier(filename);
       QFileInfo check_file(filename);

       if(fisier.open((QIODevice::ReadWrite | QIODevice::Text))){
       QTextStream stream (&fisier);

       stream<<"nrContururi   minimPerim   maximPerim   deviatiePerim    mediePerim   minimArie   maximArie   deviatieArie    medieArie  tip \n"<<minimu<<endl;
       }
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    QString s ="Max "+ QString::number(ui->verticalSlider_2->value());
     ui->label_2->setText(s);
    max = ui->verticalSlider_2->value();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    vector<vector<Point> > contours;
      vector<Vec4i>hierarchy;

    QString s ="Min "+ QString::number(ui->verticalSlider->value());
     ui->label->setText(s);
    min = ui->verticalSlider->value();
    Mat tempoza= Mat::zeros(poza.size(),CV_8UC3);


      Mat temppoza= imread(address.toLatin1().data());



    threshold(poza,tempoza,min,max,THRESH_BINARY_INV);
    findContours(tempoza,contours,hierarchy,scantype,CV_CHAIN_APPROX_SIMPLE,Point(0,0));

    for(size_t i=0;i<contours.size();i++){
        Scalar color = Scalar(144,245,0);
        drawContours(temppoza,contours,i,color,2,8,hierarchy,0,Point());


    }
    QImage img= QImage((uchar*) temppoza.data,temppoza.cols,temppoza.rows,
                       temppoza.step,QImage::Format_RGB888);
    ui->label_4->setPixmap(QPixmap::fromImage(img));
   ui->label_4->resize(ui->label_4->pixmap()->size());
}


void MainWindow::on_radioButton_clicked()
{
    scantype=0;
}

void MainWindow::on_radioButton_2_clicked()
{
    scantype=1;
}

void MainWindow::on_radioButton_3_clicked()
{
    scantype=3;
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    picks=ui->checkBox->checkState();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    cycle=ui->checkBox_2->checkState();

}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    cyclem=ui->checkBox_3->checkState();

}
