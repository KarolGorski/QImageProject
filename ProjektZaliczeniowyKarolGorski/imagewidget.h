#include <QWidget>
#include <QImage>


class ImageWidget : public QWidget
{
    QImage image;
    QImage resultImage;
    int transX,transY,rotateAngle,scaleX,scaleY,shearX,shearY;



protected: //wszelkie funkcje

    void DrawPoint(QRgb color, int x, int y);
    void keyPressEvent(QKeyEvent *e);
    void TwoColorGradient(int n, QRgb startColor, QRgb endColor);
    void paintEvent(QPaintEvent *);

    void DrawWhiteCard(int x, int y);
    void DrawLineWithAntialiasing(QRgb color, QPoint startP, QPoint endP);
    void IntensifyPixel(QRgb color, int x, int y, double distance);
    void DrawCircleBresenham(QRgb color, QPoint centerP, int r);
    void DrawCurveBezierWithCasteljau(QRgb color, QPoint P1, QPoint P2, QPoint P3, QPoint P4);
    void DrawLabirynth();
    void SmithAlgorithm(QRgb color, QPoint punkt);
    void ProcessImage();
    int *Translation(int x, int y, int tx, int ty);
    int *Rotation(int x, int y, double angle);
    int *Shear(int x, int y, double ax, double ay);
    int *Scale(int x, int y, double sx, double sy);
public:
    ImageWidget(QWidget *parent = 0);
};

