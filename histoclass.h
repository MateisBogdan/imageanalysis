#ifndef HISTOCLASS_H
#define HISTOCLASS_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <math.h>
#include <QVector>

using namespace cv;
using namespace std;
class Histograma{

private:



public:
    static double minim(double *a ,int size){
         double minimum=a[0];
       for(int i =0;i<size;i++){
           if(minimum>a[i] || minimum==0)
               minimum=a[i];
       }
       return minimum;
     }
    static double maxim(double *a ,int size){
         double maximum=a[0];
       for(int i =0;i<size;i++){
           if(maximum<a[i])
               maximum=a[i];
       }
       return maximum;
     }
    static double average(double *a ,int size){
         double mean=0;
       for(int i =0;i<size;i++){

               mean+=a[i];
       }
       return mean/size;
     }
    static double deviation(double *a,int size){
    double med= average(a,size);
    double sum=0;
    for(int i=0;i<size;i++){
        sum+=pow(fabs(a[i]-med),2);
    }
    return sqrt(sum/size);
    }
    static double* adunaContururi(vector<double> contururi){
        int size=contururi.size();
        double *marime=new double[size];
        for (size_t i=0;i<contururi.size();i++)
        {
            marime[i]=contururi[i];
        }
        return marime;
    }



    static String scrieContururi(String path,int min,int max, String type,int scan,bool pick){
        vector<vector<Point> > contours;
          vector<Vec4i>hierarchy;
       QVector<double> sortare;
        QVector<double> sortares;
        Mat pict= imread(path,0);
        String values;
        Mat tempoza= Mat::zeros(pict.size(),CV_8UC3);
        threshold(pict,tempoza,min,max,THRESH_BINARY_INV);

        findContours(tempoza,contours,hierarchy,scan,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
      unsigned int size= contours.size();
       double *marime=new double[size];
       double *marimi= new double[size]; //after i find contours, verific daca conturul este final, adica nu are descendent, daca nu are il introduc in lista

       for(size_t i=0;i<contours.size();i++){
        if(hierarchy[i][2]==-1){
           sortare.append(contourArea(contours[i]));
           sortares.append(arcLength(contours[i],1));

        }
          marime[i]=arcLength(contours[i],1);
          marimi[i]=contourArea(contours[i]);
       }
       double *val= new double[sortare.size()];
       double *vall=new double[sortares.size()];
       for(size_t i=0;i<sortare.size();i++){
           val[i]=sortare[i];
           vall[i]=sortares[i];
       }
       if(pick){
       values=std::to_string(contours.size())+ makeStrings(vall,sortares.size())+ makeStrings(val,sortare.size())+"     "+type;
}
       else{
          values=std::to_string(contours.size())+ "   "+makeStrings(marime,contours.size())+ makeStrings(marimi,contours.size())+"     "+type;
       }
       delete[] marime;
       delete[] marimi;
        delete[] val;
       delete[]vall;
       return values;

       }
    static String makeStrings(double *values,int size){
        double minP=Histograma::minim(values,size);
        double maxP= Histograma::maxim(values,size);
        double deviationP= Histograma::deviation(values,size);
        double averageP = Histograma::average(values,size);
        String vals= std::to_string(minP)+"     "+ std::to_string(maxP)+"     "+ std::to_string(deviationP)+"     "+ std::to_string(averageP)+"     ";

        return vals;
    }

   static String loopContururi(vector<String> imgpaths,int min,int max,int loopcount,int scantype,bool pick){
       String ret;

       for(size_t i=0;i<imgpaths.size();i++){
          ret+=Histograma::scrieContururi(imgpaths[i],min,max,"a",scantype,pick)+"\n";



       }

       return ret;
   }
};
#endif // HISTOCLASS_H
