#include <QWidget>
#include <QImage>


class ImageWidget : public QWidget
{
    QImage image;
    QImage resultImage;
    QImage tempImage;
    int transX,transY,rotateAngle,scaleX,scaleY,shearX,shearY;



protected: //wszelkie funkcje

    void DrawPoint(QRgb color, int x, int y);
    void keyPressEvent(QKeyEvent *e);
    void TwoColorGradient(int n, QRgb startColor, QRgb endColor);
    void paintEvent(QPaintEvent *);

    void DrawWhiteCard(int x, int y);
    void DrawLine(QRgb color, QPoint startP, QPoint endP);
    void IntensifyPixel(QRgb color, int x, int y, double distance);
    void DrawCircleBresenham(QRgb color, QPoint centerP, int r);
    void DrawCurveBezierWithCasteljau(QRgb color, QPoint P1, QPoint P2, QPoint P3, QPoint P4);
    void DrawLabirynth();
    void SmithAlgorithm(QRgb color, QPoint punkt);
    void ProcessImage();

    void translacja(int tx, int ty);
    void manageTempImage();
    void rotacja(int stopnie);
    int *Rotation(int x, int y, double stopnie);
    void skalowanie(double sx, double sy);
    void pochylenie(double ax, double ay);
    int *Shear(int x, int y, double ax, double ay);
public:
    ImageWidget(QWidget *parent = 0);
};

