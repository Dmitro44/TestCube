#ifndef CUBEGEOMETRY_H
#define CUBEGEOMETRY_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class CubeGeometry : protected QOpenGLFunctions
{
public:
    CubeGeometry(float size, QVector3D color[6]);
    virtual ~CubeGeometry();

    void initShader();
    void prepareModel();
    void drawCubeGeometry(QMatrix4x4 &projection, QMatrix4x4 &view, QMatrix4x4 &model);
    void SetPosition(QVector3D position);
    QVector3D GetPosition();

private:
    void initCubeGeometry(float size, QVector3D color[6]);

    QOpenGLShaderProgram *program;
    QOpenGLBuffer *vertBuff;
    QOpenGLBuffer *indBuff;
    QOpenGLVertexArrayObject *vao = nullptr;

    QVector3D position;

    QVector<GLfloat> vertices;
    QVector<GLushort> indices;
};

#endif // CUBEGEOMETRY_H
