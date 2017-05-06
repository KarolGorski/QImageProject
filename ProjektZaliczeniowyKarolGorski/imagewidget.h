#include <QWidget>
#include <QImage>


class ImageWidget : public QWidget
{
    QImage image;
    QImage resultImage;



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
public:
    ImageWidget(QWidget *parent = 0);
};

