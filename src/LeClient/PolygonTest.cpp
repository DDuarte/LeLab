#include "PolygonTest.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include <LeEngine/InputTask.h>
#include <LeEngine/Kernel.h>
#include <SOIL.h>
#include <LeEngine/Shapes.h>
#include <LeEngine/VideoUpdate.h>
#include <LeEngine/Window.h>
#include <LeEngine/Vertex.h>

#include <vector>
#include <map>
#include <string>
#include <fstream>

bool PolygonTest::Start()
{
    VideoUpdate::GetWindow()->SetWindowResizeCallback(WindowResizeHandler);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    _polygons.resize(6);

    std::vector<Vertex> v(4);

    v[0] = Vertex(Vector3f(0.0f, 0.0f, 0.0f));
    v[1] = Vertex(Vector3f(1.0f, 0.0f, 0.0f));
    v[2] = Vertex(Vector3f(1.0f, 1.0f, 0.0f));
    v[3] = Vertex(Vector3f(0.0f, 1.0f, 0.0f));

    _polygons[0].AddVertices(v);

    v[0] = Vertex(Vector3f(0.0f, 0.0f, 0.0f));
    v[1] = Vertex(Vector3f(1.0f, 0.0f, 0.0f));
    v[2] = Vertex(Vector3f(1.0f, 0.0f, 1.0f));
    v[3] = Vertex(Vector3f(0.0f, 0.0f, 1.0f));

    _polygons[1].AddVertices(v);

    v[0] = Vertex(Vector3f(1.0f, 0.0f, 0.0f));
    v[1] = Vertex(Vector3f(1.0f, 0.0f, 1.0f));
    v[2] = Vertex(Vector3f(1.0f, 1.0f, 1.0f));
    v[3] = Vertex(Vector3f(1.0f, 1.0f, 0.0f));

    _polygons[2].AddVertices(v);

    v[0] = Vertex(Vector3f(0.0f, 0.0f, 0.0f));
    v[1] = Vertex(Vector3f(0.0f, 0.0f, 1.0f));
    v[2] = Vertex(Vector3f(0.0f, 1.0f, 1.0f));
    v[3] = Vertex(Vector3f(0.0f, 1.0f, 0.0f));

    _polygons[3].AddVertices(v);

    v[0] = Vertex(Vector3f(0.0f, 0.0f, 1.0f));
    v[1] = Vertex(Vector3f(1.0f, 0.0f, 1.0f));
    v[2] = Vertex(Vector3f(1.0f, 1.0f, 1.0f));
    v[3] = Vertex(Vector3f(0.0f, 1.0f, 1.0f));

    _polygons[4].AddVertices(v);

    v[0] = Vertex(Vector3f(0.0f, 1.0f, 0.0f));
    v[1] = Vertex(Vector3f(1.0f, 1.0f, 0.0f));
    v[2] = Vertex(Vector3f(1.0f, 1.0f, 1.0f));
    v[3] = Vertex(Vector3f(0.0f, 1.0f, 1.0f));

    _polygons[5].AddVertices(v);

    return true;
}

void PolygonTest::Update()
{
    Render();
}

void PolygonTest::Stop()
{

}

void GLFWCALL PolygonTest::WindowResizeHandler(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //float aspectRatio = ((float)height) / width;
    //glFrustum(.5, -.5, -.5 * aspectRatio, .5 * aspectRatio, 1, 50);
    gluPerspective(45.0f, float(width)/float(height), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void PolygonTest::Render() const
{
    glTranslatef(0.0f, 0.0f, -5.0f);

    for (std::vector<Polygon<Vertex>>::const_iterator polygon = _polygons.cbegin(); polygon != _polygons.cend(); polygon++)
    { polygon->Render(); }
}