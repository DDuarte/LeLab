#include "OpenGLTest.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include "InputTask.h"
#include "Kernel.h"
#include "SOIL.h"
#include "Shapes.h"
#include "VideoUpdate.h"


int OpenGLTest::LoadGLTexture()
{
    texture[0] = texture[1] = SOIL_load_OGL_texture("Data/glass.bmp", SOIL_LOAD_AUTO, 
        SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    texture[2] = SOIL_load_OGL_texture("Data/glass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

    if (!texture[0] || !texture[1] || !texture[2])
        return false;

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

bool OpenGLTest::Start()
{
    if (!LoadGLTexture())
        return false;

    VideoUpdate::GetWindow()->SetWindowResizeCallback(WindowResizeHandler);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glEnable(GL_LIGHT1);

    return true;
}

void OpenGLTest::Update()
{
    if (glfwGetKey('L') == GLFW_PRESS && !lp)
    {
        lp = true;
        light = !light;
        (light ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING));
    }
    else if (glfwGetKey('L') != GLFW_PRESS)
        lp = false;

    if (glfwGetKey('F') == GLFW_PRESS && !fp)
    {
        fp = true;
        filter = (filter + 1) % 3;
    }
    else if (glfwGetKey('F') != GLFW_PRESS)
        fp = false;

    if (glfwGetKey('B') == GLFW_PRESS && !bp)
    {
        bp = true;
        blend = !blend;

        if (blend)
        {
            glEnable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
        }
    }
    else if (glfwGetKey('B') != GLFW_PRESS)
        bp = false;

    if (glfwGetKey(GLFW_KEY_PAGEUP) == GLFW_PRESS)
        z -= 0.002f;
    if (glfwGetKey(GLFW_KEY_PAGEDOWN) == GLFW_PRESS)
        z += 0.002f;
    if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
        xspeed -=0.001f;
    if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
        xspeed += 0.001f;
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
        yspeed += 0.001f;
    if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
        yspeed -= 0.001f;

    xrot += xspeed;
    yrot += yspeed;

    Render();
}

void OpenGLTest::Stop()
{

}

void GLFWCALL OpenGLTest::WindowResizeHandler(int width, int height)
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

void OpenGLTest::Render() const
{
    glTranslatef(0,0,z);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture[filter]);

    glBegin(GL_QUADS);
    {
        // Front Face
        glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 1 (Front)
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 2 (Front)
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Front)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 4 (Front)
        // Back Face
        glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Back)
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 2 (Back)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 3 (Back)
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 4 (Back)
        // Top Face
        glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 1 (Top)
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 2 (Top)
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Top)
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 4 (Top)
        // Bottom Face
        glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Bottom)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 2 (Bottom)
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 3 (Bottom)
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 4 (Bottom)
        // Right face
        glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Point 1 (Right)
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Point 2 (Right)
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Point 3 (Right)
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Point 4 (Right)
        // Left Face
        glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Point 1 (Left)
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Point 2 (Left)
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Point 3 (Left)
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Point 4 (Left)
    }
    glEnd();
}
