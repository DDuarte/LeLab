#ifndef OPENGLTEST2_H
#define OPENGLTEST2_H

#include <LeEngine/ITask.h>

#include <GL/glew.h>
#include <GL/glfw.h>

class OpenGLTest2 : public ITask
{
public:
    OpenGLTest2() : ITask("OpenGLTest")
    {
        // materials
        mat1_shininess[0] = 128.0f;

        mat1_specular[0] = 0.3f; //{ 0.3, 0.3, 0.3, 1.0 };
        mat1_specular[1] = 0.3f;
        mat1_specular[2] = 0.3f;
        mat1_specular[3] = 1.0f;

        mat1_diffuse[0] = 0.7f; //   =    { 0.7, 0.7, 0.7, 1.0 };
        mat1_diffuse[1] = 0.7f;
        mat1_diffuse[2] = 0.7f;
        mat1_diffuse[3] = 1.0f;

        mat1_ambient[0] = 0.7f; //  =    { 0.7, 0.7, 0.7, 1.0 };
        mat1_ambient[1] = 0.7f;
        mat1_ambient[2] = 0.7f;
        mat1_ambient[3] = 1.0f;

        // LIGHT0
        //light0_position  =  {4.0, 6.0, 3.0, 1.0};

        light0_position[0] = 4.0f; //{ 0.3, 0.3, 0.3, 1.0 };
        light0_position[1] = 6.0f;
        light0_position[2] = 3.0f;
        light0_position[3] = 1.0f;

        light0_ambient[0] = light0_ambient[1] = light0_ambient[2] =  0.0f; light0_ambient[3] = 1.0f;
        light0_diffuse[0] = light0_diffuse[1] = light0_diffuse[2] =  0.8f; light0_diffuse[3] = 1.0f;
        light0_specular[0] = light0_specular[1] = light0_specular[2] =  0.8f; light0_specular[3] = 1.0f;
        light0_kc = 1.0f;
        light0_kl = 0.0f;
        light0_kq = 0.0f;

        // Ambient light source
        light_ambient[0] = light_ambient[1] = light_ambient[2] =  0.2f; light_ambient[3] = 1.0f;
    }

    bool Start();
    void Update();
    void Render() const;
    void Stop() { }


    static void GLFWCALL WindowResizeHandler(int width, int height);
private:

    // materials
    float mat1_shininess[1]; /* = { 128.0 } */
    float mat1_specular[4];  /* = {0.3, 0.3, 0.3, 1.0}; */	/* specular reflection. */
    float mat1_diffuse[4];   /* =  {0.7, 0.7, 0.7, 1.0}; */	/* diffuse reflection. */
    float mat1_ambient[4];   /* =  {0.7, 0.7, 0.7, 1.0}; */	/* ambient reflection. */

    // LIGHT0
    float light0_position[4];   /* =  {4.0, 6.0, 3.0, 1.0}; */ // posicao da fonte de luz
    float light0_ambient[4];    /* =  {0.0, 0.0, 0.0, 1.0}; */ // sem componente ambiente
    float light0_diffuse[4];    /* =  {0.8, 0.8, 0.8, 1.0}; */ 
    float light0_specular[4];   /* =  {0.8, 0.8, 0.8, 1.0}; */ 
    float light0_kc; /* = 1.0; */
    float light0_kl; /* = 0.0; */
    float light0_kq; /* = 0.0; */

    // Ambient light source
    float light_ambient[4]; /* = {0.2, 0.2, 0.2, 1.0}; */
};

#endif // OPENGLTEST2_H
