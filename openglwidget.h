#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include <QQuaternion>

#include "cubegeometry.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void setElementsOfCube(QVector<CubeGeometry> &cubes, QVector<QVector3D> &colors);

private:
    QVector<CubeGeometry> cubes;
    QVector<QVector3D> colors;

    QMatrix4x4 projection;
    //QQuaternion rotation;
};

#endif // OPENGLWIDGET_H
