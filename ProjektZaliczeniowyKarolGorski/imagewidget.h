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
public:
    ImageWidget(QWidget *parent = 0);
};

