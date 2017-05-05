#include "imagewidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{
DrawWhiteCard(512,512);


}

void ImageWidget::DrawWhiteCard(int x, int y)
{
    image=QImage(x,y,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    resultImage=image;
}

void ImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,resultImage);
}


void ImageWidget::DrawPoint(QRgb color, int x,int y)
{
   QRgb* p=(QRgb*)resultImage.scanLine(y);
   p[x]=color;
}

void ImageWidget::TwoColorGradient(int n, QRgb startColor, QRgb endColor)
{
    int licznik=image.width()/n;
    for(int y=0;y<image.height();y++)
    {
        licznik=ceil(image.width()/(float)n);
        QRgb* pd = (QRgb*)resultImage.scanLine(y);
        QRgb* ps = (QRgb*)image.scanLine(y);

        float r=(float)qRed(startColor);
        float g=(float)qGreen(startColor);
        float b=(float)qBlue(startColor);
        float licznikR=((float)qRed(endColor)-(float)qRed(startColor))/(n-1);
        float licznikG=((float)qGreen(endColor)-(float)qGreen(startColor))/(n-1);
        float licznikB=((float)qBlue(endColor)-(float)qBlue(startColor))/(n-1);

        for(int x=0;x<image.width();x++)
        {
        if(x!=0 && x%licznik==0)
        {
            if(licznikR<0)
            r=max<float>(qRed(endColor),r+licznikR);
            else
            r=min<float>(qRed(endColor),r+licznikR);

            if(licznikG<0)
            g=max<float>(qGreen(endColor),g+licznikG);
            else
            g=min<float>(qGreen(endColor),g+licznikG);

            if(licznikB<0)
            b=max<float>(qBlue(endColor),b+licznikB);
            else
            b=min<float>(qBlue(endColor),b+licznikB);

          //  cout<<"("<<r<<","<<g<<","<<b<<")"<<endl;
        }
       // pd[x]=qRgba(r,g,b,qAlpha(ps[x]);
       DrawPoint(qRgb(r,g,b),x,y);
        }
    }

}


void ImageWidget::DrawLineWithAntialiasing(QRgb color,QPoint startP, QPoint endP)
{
    int w = endP.x() - startP.x() ;
     int h = endP.y() - startP.y();
     int x=startP.x();
     int y=startP.y();
     int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
     if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
     if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
     if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
     int longest = abs(w) ;
     int shortest = abs(h) ;
     if (longest<shortest) {
         longest = abs(h);
         shortest = abs(w);
         if (h<0) dy2 = -1;
         else if (h>0) dy2 = 1;
         dx2 = 0 ;
     }
     int numerator = longest/2 ;
     for (int i=0;i<=longest;i++) {
         DrawPoint(color,x,y) ;
         numerator += shortest ;
         if (numerator>longest) {
             numerator -= longest ;
             x += dx1 ;
             y += dy1 ;
         } else {
             x += dx2 ;
             y += dy2 ;
         }
     }
}
/*
void ImageWidget::DrawCircleBresenham()
{

}

void ImageWidget::DrawCurveCasteljau(QRgb color, QPoint P1, QPoint P2, QPoint P3, QPoint P4)
{

}
void ImageWidget::DrawBSplineWithAsManyPointsAsUWant()
{

}

void ImageWidget::SmithAlgorithm()
{

}
//Transformations
void ImageWidget::Translation()
{

}
void ImageWidget::RotationFromCenter()
{

}
void ImageWidget::ScaleFromCenter()
{

}
void ImageWidget::Lean()
{

}
void ImageWidget::BilinearInterpolation()
{

}
*/

void ImageWidget::keyPressEvent(QKeyEvent * e)
{
    if(e->key()==Qt::Key_G){
        TwoColorGradient(512,qRgb(255,0,0),qRgb(0,255,0));}
    if(e->key()==Qt::Key_N){
        DrawWhiteCard(512,512);
    }
    if(e->key()==Qt::Key_L){
        DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(10,30),QPoint(400,400 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(512,256 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(512,512 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(256,512 ));
    }
    update();
}
