#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    //setFocusPolicy(Qt::StrongFocus);
    colors = {
        QVector3D(1.0f, 0.0f, 0.0f),
        QVector3D(0.0f, 1.0f, 0.0f),
        QVector3D(0.0f, 0.0f, 1.0f),
        QVector3D(1.0f, 1.0f, 0.0f),
        QVector3D(1.0f, 0.5f, 0.0f),
        QVector3D(1.0f, 1.0f, 1.0f)
    };
}

void OpenGLWidget::initializeGL()
{
    makeCurrent();

    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    setElementsOfCube(cubes, colors);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    makeCurrent();
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 50.0, field of view 45 degrees
    const qreal zNear = 0.1, zFar = 100.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void OpenGLWidget::paintGL()
{
    makeCurrent();
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 view;

    // Camera setup
    QVector3D cameraPos(3.0f, 3.0f, 3.0f);
    QVector3D cameraFront = QVector3D(-0.525f, -0.525f, 0.525f) - cameraPos;
    cameraFront.normalize();
    QVector3D cameraUp(0.0f, 1.0f, 0.0f);

    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    // view.translate(30.0f, 30.0f, 30.0f);
    // view.rotate(30.0f, QVector3D(1.0f, 0.0f, 0.0f)); // Rotate 30 degrees around the x-axis
    // view.rotate(-45.0f, QVector3D(0.0f, 1.0f, 0.0f)); // Rotate -45 degrees around the y-axis

    QMatrix4x4 model;


    // Draw cube geometry
    for (auto &cube : cubes)
    {
        model.translate(cube.GetPosition());

        cube.drawCubeGeometry(projection, view, model);
    }
    update();
}

void OpenGLWidget::setElementsOfCube(QVector<CubeGeometry> &cubes, QVector<QVector3D> &colors)
{
    makeCurrent();
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                QVector3D cubeColors[6];
                for (int i = 0; i < 6; ++i)
                {
                    cubeColors[i] = QVector3D(0.3f, 0.3f, 0.3f);
                }
                // Assign colors based on the position of the cube
                if (x == 0) cubeColors[4] = colors[0]; // Red - left
                if (x == 2) cubeColors[3] = colors[4]; // Orange - right
                if (y == 0) cubeColors[2] = colors[3]; // Yellow - bottom
                if (y == 2) cubeColors[1] = colors[5]; // White - top
                if (z == 0) cubeColors[0] = colors[2]; // Blue - front
                if (z == 2) cubeColors[5] = colors[1]; // Green - back
                CubeGeometry cube(0.25f, cubeColors);
                QVector3D position(x * 0.525f - 0.525f, y * 0.525f - 0.525f, z * 0.525f - 0.525f);
                cube.SetPosition(position);
                cubes.push_back(cube);
            }
        }
    }
}
