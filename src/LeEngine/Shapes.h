#ifndef SHAPES_H
#define SHAPES_H

#include "Vector.h"
#include "Quaternion.h"
#include "VideoUpdate.h"

#include <GL/glew.h>
#include <GL/GLFW.h>

class IRenderable
{
public:
    virtual void Render() const = 0;
};

class Cylinder : public IRenderable
{
private:
    Vector<3, double> _position;
    Quaternion _rotations;
    double _radius;
    double _height;

    GLUquadricObj* _cylinder;

public:
    Cylinder(double radius, double height, Vector<3, double> position, Quaternion rotations)
        : _position(position), _rotations(rotations), _radius(radius), _height(height)
    {
        _cylinder = gluNewQuadric();
         assert(_cylinder != NULL);
    }

    void Render() const
    {
        glColor3f(0.5,0.5,0.5);
        glPushMatrix();
        glRotatef(_rotations.GetW(), _rotations.GetX(), _rotations.GetY(), _rotations.GetZ());
        glTranslatef(0, -1, InputTask::Wheel);
        gluCylinder(_cylinder, _radius, 0, _height, 100, 100);
        glPopMatrix();
    }
};

#endif // SHAPES_H
