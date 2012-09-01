#include "OpenGLTest2.h"

#include <GL/glew.h>
#include <GL/glfw.h>


void GLFWCALL OpenGLTest2::WindowResizeHandler( int width, int height )
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspectRatio = ((float)width) / height;
    glFrustum(.5, -.5, -.5 * aspectRatio, .5 * aspectRatio, .1, 50);
    //gluPerspective(45.0f, float(width)/float(height), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool OpenGLTest2::Start()
{
    /* -- Depth and Culling functions -- */

    glDepthFunc(GL_LEQUAL);     // Depth function, default value GL_LESS
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);     // Use face culing to improve speed

    // glClearColor(1.0,1.0,1.0,1.0);   // Default back color is black. Uncomment this line to have white background.

    /* -- Light -- */

    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient); // ambient light definition

    // ilumination parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);        // GL_FLAT / GL_SMOOTH

    glPolygonMode(GL_FRONT, GL_FILL);

    return true;
}

void OpenGLTest2::Update()
{
    Render();
}

void OpenGLTest2::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // initialization of the model view matrix
    glMatrixMode(GL_MODELVIEW);

    glTranslated(0.0,0.0,-5.0);
    glRotated(20.0, 1.0,0.0,0.0 );		// 20 graus em torno de X
    glRotated(-45.0, 0.0,1.0,0.0 );		//-45 graus em torno de Y

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glDisable(GL_COLOR_MATERIAL);

    glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat1_specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat1_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat1_ambient);

    glPushMatrix();

    glTranslated(3, 0, 2);
    glRotated(30.0, 0.0, 1.0, 0.0);
    glScaled(4.0, 2.0 ,1.0);

    glBegin(GL_POLYGON);
    glNormal3d(0.0,0.0,1.0);
    glVertex3d(0,0,0);
    glVertex3d(2,0,0);
    glVertex3d(0,5,0);
    glEnd();

    glPopMatrix();

    glScaled(2.0, 2.0 ,2.0);

    glBegin(GL_POLYGON);
    glNormal3d(1.0,1.0,1.0);
    glVertex3d(1,0,0);
    glVertex3d(0,1,0);
    glVertex3d(0,0,1);
    glEnd();


}
