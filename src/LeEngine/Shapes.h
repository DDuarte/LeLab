#ifndef SHAPES_H
#define SHAPES_H

#include "Vector.h"
#include "Quaternion.h"
#include "VideoUpdate.h"
#include "Renderer.h"
#include "Vertex.h"

#include <GL/glew.h>
#include <GL/GLFW.h>

#include <vector>

/*
class Cube : public IRenderable
{
private:
    Vector<3> _position;
    Quaternion _rotations;
    float _size;

public:
    Cube(double size) : _size(size) {}

    void Render() const
    {

    }
};
*/

class Cylinder : public IRenderable
{
private:
    Vector<3, double> _position;
    Quaternion _rotations;
    double _radius;
    double _height;

    GLUquadricObj* _cylinder;

public:
    Cylinder(double radius, double height)
        : _radius(radius), _height(height)
    {
        _cylinder = gluNewQuadric();
         assert(_cylinder != NULL);
    }

    void Render() const
    {
        glColor3f(0.5,0.5,0.5);
        glPushMatrix();
        glRotatef(_rotations.GetW(), _rotations.GetX(), _rotations.GetY(), _rotations.GetZ());
        glTranslatef(0, -1, 0); // ?
        gluCylinder(_cylinder, _radius, _radius, _height, 100, 100);
        glPopMatrix();
    }
};

template<class V = Vertex>
class Polygon : public IRenderable
{
private:
    std::vector<V> _vertices;
public:
	Polygon()
    {
        _vertices.resize(0);
    }

    void Render() const
    {
        GLenum face_mode;
        switch (_vertices.size())
        {
        case 0: return;
        case 1: face_mode = GL_POINTS; break;
        case 2: face_mode = GL_LINES; break;
        case 3: face_mode = GL_TRIANGLES; break;
        case 4: face_mode = GL_QUADS; break;
        default: face_mode = GL_POLYGON; break;
        }
        glBegin(face_mode);
        {
            for (std::vector<V>::const_iterator it = _vertices.cbegin(); it != _vertices.cend(); it++)
            {
                it->Render();
            }
        }
        glEnd();
    }

    void SetVertices(std::vector<V> vert)
    {
        _vertices = vert;
    }

    void AddVertex(V vert)
    {
        _vertices.push_back(vert);
    }

    void AddVertices(std::vector<V> vert)
    {
        _vertices.insert(_vertices.end(), vert.begin(), vert.end());
    }
};
#endif // SHAPES_H
