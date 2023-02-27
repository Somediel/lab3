#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QWheelEvent>

#include "surface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void DrawSurface();
    void makeIndex();
    void rotateGraph();
    void scalingGraph();
    QString typeOfRendering = "Точки";
    QString typeOfView = "Ортогоналная";

    double coordinateScale(double value);

    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    void paintGL() override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;

    void setTypeOfRendering(const QString &value);
    void setTypeOfView(const QString &value);

private:
    Surface surface;
    QPointF mousePosition;

    GLuint* indexArray;

    int countOfPointInLine;
    int countOfIndex;
    double wheelScroll = 1.0;
    double rotateX = 0;
    double rotateY = 0;

};
#endif // WIDGET_H
