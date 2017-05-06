#include "imagewidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stack>
#include <conio.h>
using namespace std;

ImageWidget::ImageWidget(QWidget *parent): QWidget(parent)
{

DrawWhiteCard(512,512);
//DrawLabirynth();

}

void ImageWidget::DrawWhiteCard(int x, int y)
{
    image=QImage(x,y,QImage::Format_RGB32);
    image.fill(qRgb(255,255,255));
    resultImage=image;
}
void ImageWidget::DrawLabirynth()
{
    image=QImage("Labirynt.png");
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
       // QRgb* pd = (QRgb*)resultImage.scanLine(y);
       // QRgb* ps = (QRgb*)image.scanLine(y);

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
/*
QRgb* p=(QRgb*)resultImage.scanLine(y);
QRgb ImageColor=p[0];
//cout<<qRed(ImageColor)<<qGreen(ImageColor)<<qBlue(ImageColor);
QRgb newColor1=min<QRgb>(qRgb(255,255,255),qRgb(1.0/2*(qRed(ImageColor)+qRed(color)),1.0/2*(qGreen(ImageColor)+qGreen(color)),1.0/2*(qBlue(ImageColor)+qBlue(color))));
QRgb newColor2=min<QRgb>(qRgb(255,255,255),qRgb(2.0/3*(qRed(ImageColor)+qRed(color)),1.0/2*(qGreen(ImageColor)+qGreen(color)),1.0/2*(qBlue(ImageColor)+qBlue(color))));
  */
  int numerator = longest>>1 ;
     for (int i=0;i<=longest;i++) {
         DrawPoint(color,x,y) ;
      //   DrawPoint(newColor1,x+1,y);
      //   DrawPoint(newColor1,x-1,y);
      //   DrawPoint(newColor2,x+2,y);
      //   DrawPoint(newColor2,x-2,y);
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

void ImageWidget::DrawCircleBresenham(QRgb color, QPoint centerP, int r)
{
    int xm=centerP.x();
    int ym=centerP.y();

    int x=-r,y=0,dd=2-2*r;
      do {
         DrawPoint(color,xm-x, ym+y);
         DrawPoint(color,xm-y, ym-x);
         DrawPoint(color,xm+x, ym-y);
         DrawPoint(color,xm+y, ym+x);
         r = dd;
         if (r<=y) dd+=++y*2+1;
         if (r>x || dd>y) dd += ++x*2+1;
      } while(x<0);
}

void ImageWidget::DrawCurveBezierWithCasteljau(QRgb color, QPoint P1, QPoint P2, QPoint P3, QPoint P4)
{
QPoint P5,P6,P7,P8,P9,P10=P1,Ptemp;
for(double t=0;t<=1;t+=0.05)
{
P5=P1+(P2-P1)*t;
P6=P2+(P3-P2)*t;
P7=P3+(P4-P3)*t;
P8=P5+(P6-P5)*t;
P9=P6+(P7-P6)*t;
Ptemp=P10;
P10=P8+(P9-P8)*t;
DrawLineWithAntialiasing(color,Ptemp,P10);
DrawPoint(color,P10.x(),P10.y());
cout<<P10.x()<<" "<<P10.y()<<endl;
}


}

class Segment{
public:
    int x;
    int y;
    int len;
    Segment(){}
};
void ImageWidget::SmithAlgorithm(QRgb color, QPoint punkt)
{
    stack <Segment> stacker;
    Segment s;
    int len=0;
    QRgb colorTemp=qRgb(255,255,255);//biale
    QRgb colorTemp2=qRgb(0,0,0);
   // cout<<punkt.x()<<punkt.y()<<endl;
    int x=punkt.x(),y=punkt.y();
    while(image.pixelColor(QPoint(x,y)) == colorTemp)
    {
        x--;
 //cout<<x<<y<<endl;
    }
    s.x=x;
    s.y=y;
 //   cout<<"  "<<x<<y<<endl;
    while(image.pixelColor(QPoint(x+1,y)) == colorTemp)
    {
        x++;
        len++;
        DrawPoint(color,x,y);
    }
    s.len=len;
    stacker.push(s);

    Segment SegmentToStack;
    while(!stacker.empty())
    {
        //cout<<s.x<<s.y<<endl;
        s=stacker.top();
        stacker.pop();
        int TempX=s.x;
        while(TempX+s.len>=s.x)
        {
            //down
            if(resultImage.pixelColor(s.x,s.y-1) == colorTemp && resultImage.pixelColor(s.x,s.y-1)!=color)
            {
                SegmentToStack.len=0;
                SegmentToStack.y=s.y-1;
                x=s.x;
                while(resultImage.pixelColor(x-1,SegmentToStack.y)==colorTemp)
                    x--;
                SegmentToStack.x=x;
                while(resultImage.pixelColor(x, SegmentToStack.y)==colorTemp)
                {
                    DrawPoint(color, x,SegmentToStack.y);
                    SegmentToStack.len++;
                    x++;
                }
                stacker.push(SegmentToStack);
            }
            //Up
            if(resultImage.pixelColor(s.x,s.y+1) == colorTemp && resultImage.pixelColor(s.x,s.y+1)!=color)
            {
                SegmentToStack.len=0;
                SegmentToStack.y=s.y+1;
                x=s.x;
                while(resultImage.pixelColor(x-1,SegmentToStack.y)==colorTemp)
                    x--;
                SegmentToStack.x=x;
                while(resultImage.pixelColor(x, SegmentToStack.y)==colorTemp)
                {
                    DrawPoint(color, x,SegmentToStack.y);
                    SegmentToStack.len++;
                    x++;
                }
                stacker.push(SegmentToStack);
            }
            s.x++;
        }

    }

}

//Transformations
/*
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
        DrawLineWithAntialiasing(qRgb(0,0,0),QPoint(20,30),QPoint(400,35 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(512,256 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(512,512 ));
      //  DrawLineWithAntialiasing(qRgb(255,0,0),QPoint(0,0),QPoint(256,512 ));
    }
    if(e->key()==Qt::Key_O){
        DrawCircleBresenham(qRgb(255,0,0),QPoint(255,255),50);
    }
    if(e->key()==Qt::Key_C){
        DrawCurveBezierWithCasteljau(qRgb(255,0,0),QPoint(50,400),QPoint(125,200),QPoint(200,250),QPoint(300,450));
    }
    if(e->key()==Qt::Key_S){
      DrawLabirynth();
    }
    if(e->key()==Qt::Key_A){
        //Aby użyć Algorytmu Smitha potrzebne jest coś do wypełnienia, proszę użyć funkcji wyżej :)
               SmithAlgorithm(qRgb(255,0,0),QPoint(279,371));
    }
    update();
}
