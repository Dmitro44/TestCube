#include "cubegeometry.h"

#include <QDebug>

CubeGeometry::CubeGeometry(float size, QVector3D color[6])
{

    initializeOpenGLFunctions();

    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry(size, color);
    initShader();

    prepareModel();
}

CubeGeometry::~CubeGeometry()
{
    vertBuff->destroy();
    indBuff->destroy();
}

void CubeGeometry::initShader()
{
    program = new QOpenGLShaderProgram();
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, "C:/Users/Dima/Documents/RubiksCube/vertexShader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, "C:/Users/Dima/Documents/RubiksCube/fragmentShader.frag");
    program->link();
    if (program->isLinked())
    {
        qDebug() << "program is linked";
    }
    qDebug() << program->log();
    // qDebug() << program->uniformLocation("projection");
    // qDebug() << program->uniformLocation("view");
    // qDebug() << program->uniformLocation("model");
}

void CubeGeometry::prepareModel()
{
    vao = new QOpenGLVertexArrayObject();
    vao->create();
    vao->bind();

    vertBuff = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vertBuff->create();
    vertBuff->bind();
    vertBuff->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertBuff->allocate(&vertices, (int)vertices.size() * sizeof(GLfloat));

    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("aPos");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, 6 * sizeof(GLfloat));

    offset += 3 * sizeof(GLfloat);

    int colorLocation = program->attributeLocation("aColor");
    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, 6 * sizeof(GLfloat));

    indBuff = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    indBuff->create();
    indBuff->bind();
    indBuff->setUsagePattern(QOpenGLBuffer::StaticDraw);
    indBuff->allocate(&indices, (int)indices.size() * sizeof(GLushort));
    vao->release();
    qDebug() << "Model prepared";
}

void CubeGeometry::initCubeGeometry(float size, QVector3D color[6])
{
    vertices = {
        // positions          // colors
        // front side
        -size, -size, -size,  color[0].x(), color[0].y(), color[0].z(),  // front bottom left 0
        size, -size, -size,  color[0].x(), color[0].y(), color[0].z(),  // front bottom right 1
        size,  size, -size,  color[0].x(), color[0].y(), color[0].z(),  // front top right 2
        -size,  size, -size,  color[0].x(), color[0].y(), color[0].z(),  // front top left 3
        // top side
        size,  size, -size,  color[1].x(), color[1].y(), color[1].z(),  // front top right 2
        -size,  size, -size,  color[1].x(), color[1].y(), color[1].z(),  // front top left 3
        -size,  size,  size,  color[1].x(), color[1].y(), color[1].z(),  // back top left 7
        size,  size,  size,  color[1].x(), color[1].y(), color[1].z(),  // back top right 6
        // bottom side
        -size, -size, -size,  color[2].x(), color[2].y(), color[2].z(),  // front bottom left 0
        size, -size, -size,  color[2].x(), color[2].y(), color[2].z(),  // front bottom right 1
        size, -size,  size,  color[2].x(), color[2].y(), color[2].z(),  // back bottom right 5
        -size, -size,  size,  color[2].x(), color[2].y(), color[2].z(),  // back bottom left 4
        // right side
        size, -size, -size,   color[3].x(), color[3].y(), color[3].z(),  // front bottom right 1
        size,  size, -size,   color[3].x(), color[3].y(), color[3].z(),  // front top right 2
        size,  size,  size,   color[3].x(), color[3].y(), color[3].z(),  // back top right 6
        size, -size,  size,   color[3].x(), color[3].y(), color[3].z(),  // back bottom right 5
        // left side
        -size, -size, -size,  color[4].x(), color[4].y(), color[4].z(),  // front bottom left 0
        -size,  size, -size,  color[4].x(), color[4].y(), color[4].z(),  // front top left 3
        -size,  size,  size,  color[4].x(), color[4].y(), color[4].z(),  // back top left 7
        -size, -size,  size,  color[4].x(), color[4].y(), color[4].z(),  // back bottom left 4
        // back side
        -size, -size,  size,  color[5].x(), color[5].y(), color[5].z(),  //   back bottom left 4
        size, -size,  size,  color[5].x(), color[5].y(), color[5].z(),  // back bottom right 5
        size,  size,  size,  color[5].x(), color[5].y(), color[5].z(),  // back top right 6
        -size,  size,  size,  color[5].x(), color[5].y(), color[5].z()  // back top left 7
    };

    indices = {
        0, 1, 2, 2, 3, 0, // front
        4, 5, 6, 6, 7, 4, // top
        8, 9, 10, 10, 11, 8, // bottom
        12, 13, 14, 14, 15, 12, // right
        16, 17, 18, 18, 19, 16, // left
        20, 21, 22, 22, 23, 20 // back
    };
}

void CubeGeometry::drawCubeGeometry(QMatrix4x4 &projection, QMatrix4x4 &view, QMatrix4x4 &model)
{
    QOpenGLContext::currentContext()->makeCurrent(QOpenGLContext::currentContext()->surface());

    program->setUniformValue("model", model);
    program->setUniformValue("view", view);
    program->setUniformValue("projection", projection);

    vao->bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, nullptr);
    vao->release();
}

void CubeGeometry::SetPosition(QVector3D position)
{
    this->position = position;
}

QVector3D CubeGeometry::GetPosition()
{
    return position;
}
