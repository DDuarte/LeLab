#ifndef SHAPES_H
#define SHAPES_H

#include "Vector.h"
#include "Quaternion.h"
#include "VideoUpdate.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <GL/GLFW.h>

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

#endif // SHAPES_H
