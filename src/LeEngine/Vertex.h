#ifndef VERTEX_H
#define VERTEX_H

#include "Vector.h"
#include "Color.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <GL/glfw.h>

class Vertex : public IRenderable
{
public:
    Vector3f Position;

    Vertex() : Position(Vector3f()) { }
    Vertex(const Vector3f& pos) : Position(pos) { }

    void Render() const
    {
        glVertex3f(Position[0], Position[1], Position[2]);
    }
};

class RGBVertex : public Vertex
{
public:
    ColorRGB Color;

    RGBVertex() : Vertex(), Color(ColorRGB::WHITE) { }
    RGBVertex(const Vector3f& pos, ColorRGB color = ColorRGB::WHITE) : Vertex(pos), Color(color) { }

    void Render() const
    {
        glColor3f(Color.R(), Color.G(), Color.B());
        glVertex3f(Position[0], Position[1], Position[2]);
    }
};

class RGBAVertex : public Vertex
{
public:
    ColorRGBA Color;

    RGBAVertex() : Vertex(), Color(ColorRGB::WHITE) { }
    RGBAVertex(Vector3f pos, ColorRGB color = ColorRGB::WHITE) : Vertex(pos), Color(color) { }

    void Render() const
    {
        glColor4f(Color.R(), Color.G(), Color.B(), Color.A());
        glVertex3f(Position[0], Position[1], Position[2]);
    }
};

class UVVertex : public Vertex
{
public:
    Vector<2,float> UV;

    UVVertex() : Vertex(), UV(Vector<2,float>()) { }
    UVVertex(Vector3f pos, Vector<2,float> uv = Vector<2,float>()) : Vertex(pos), UV(uv) { }

    void Render() const
    {
        glTexCoord2f(UV[0], UV[1]);
        glVertex3f(Position[0], Position[1], Position[2]);
    }
};


#endif // VERTEX_H
