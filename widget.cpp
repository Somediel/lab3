#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    countOfPointInLine = sqrt(10000);
    countOfIndex = pow(countOfPointInLine - 1, 2) * 6;
    makeIndex();
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);
    glLoadIdentity();

    if (typeOfView == "Ортогональная")
    {
        glOrtho(-1 , 1, -1, 1, -1, 1);
    }
    else if (typeOfView == "Перспективная")
    {
        glFrustum(-1, 1, -1, 1, 1, 3);
        glTranslatef(0, 0, -2);
    }

    scalingGraph();
    rotateGraph();

    DrawSurface();

    update();
}

void Widget::initializeGL()
{
        this->setMouseTracking(true);
        QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(51.0 / 255, 51.0 / 255, 51.0 / 255, 1);
        glMatrixMode(GL_PROJECTION);
        glEnable(GL_DEPTH_TEST);
        glEnableClientState(GL_VERTEX_ARRAY);
}

void Widget::resizeGL(int w, int h)
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
        f->glViewport(0, 0, w, h);
}

void Widget::DrawSurface()
{
     glVertexPointer(3, GL_DOUBLE, 0, surface.arrayOfPoint);
     glColor3f(0.8f,0.8f, 0.2f);
     if (typeOfRendering == "Точки")
     {
         glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
     }
     else if (typeOfRendering == "Треугольники")
     {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

     }
     else if (typeOfRendering == "Линии")
     {
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     }
     glDrawElements(GL_TRIANGLES, countOfIndex, GL_UNSIGNED_INT, indexArray);
}

void Widget::makeIndex()
{
        indexArray = new GLuint[countOfIndex];
        int j = 0;
        for (size_t i = 0; i < countOfIndex; i += 6)
        {
            indexArray[i] = j;
            indexArray[i + 1] = j + countOfPointInLine;
            indexArray[i + 2] = j + 1;

            indexArray[i + 4] = j + countOfPointInLine;
            indexArray[i + 3] = j + 1;
            indexArray[i + 5] = j + 1 + countOfPointInLine;
            (j + 1) % countOfPointInLine == countOfPointInLine - 1 ? j += 2 : j++;
        }
}


void Widget::rotateGraph()
{
    glRotated(rotateX, 1, 0, 0);
    glRotated(rotateY, 0, 1, 0);
}

void Widget::scalingGraph()
{
    if (wheelScroll > 0)
            glScaled(wheelScroll, wheelScroll, wheelScroll);
        else
            glScaled(1 / -wheelScroll, 1 / -wheelScroll, 1 / -wheelScroll);
}

void Widget::setTypeOfView(const QString &value)
{
    typeOfView = value;
}

void Widget::setTypeOfRendering(const QString &value)
{
    typeOfRendering = value;
}

double Widget::coordinateScale(double value)
{
    if (wheelScroll < 0)
        return value * -wheelScroll;
        else if (wheelScroll > 0)
            return  value / wheelScroll;
}

void Widget::wheelEvent(QWheelEvent *event)
{
    event->accept();
    int delta = event->angleDelta().y() / 32;
    wheelScroll += delta;
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
        if (event->buttons() & Qt::LeftButton)
        {
            qreal mouseMove = mousePosition.y() - event->localPos().y();
            rotateX += 1 / M_PI * (mouseMove);

            mouseMove = mousePosition.x() - event->localPos().x();
            rotateY += 1 / M_PI * (mouseMove);

            mousePosition = event->localPos();
        }
        update();
}
void Widget::mousePressEvent(QMouseEvent* event)
{
    event->accept();
    mousePosition = event->localPos();
    update();
}



