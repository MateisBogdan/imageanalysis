#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QFileInfo>
#include <opencv2/highgui/highgui.hpp>
#include "histoclass.h"
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_verticalSlider_2_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

private:
    Ui::MainWindow *ui; //add global int and make switch tied to radio buttons in interface
    // add cycle option to interface (+-20 values for min to collect data from);
    QString address;
    String path1="D:/facultate/Histo_Image_357/Histo_Image_357/G0/*.jpg";
    String path2="D:/facultate/Histo_Image_357/Histo_Image_357/G1/*.jpg";
    String path3="D:/facultate/Histo_Image_357/Histo_Image_357/G2/*.jpg";
    String path4="D:/facultate/Histo_Image_357/Histo_Image_357/G3/*.jpg";
    bool picks=false,cycle=false,cyclem=false;
   Mat poza,newpoza;
   int min,max,scantype;
};

#endif // MAINWINDOW_H
