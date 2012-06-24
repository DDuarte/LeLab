#include "Technique.h"

#include <cstdio>
#include <string>
#include <GL/glew.h>

Technique::Technique()
{
    _shaderProg = 0;
}

Technique::~Technique()
{
    // Delete the intermediate shader objects that have been added to the program
    // the list will only contain something if shaders were compiled but the object itself
    // was destroyed prior to linking
    for (ShaderObjList::iterator it = _shaderObjList.begin(); it != _shaderObjList.end(); it++)
        glDeleteShader(*it);

    if (_shaderProg != 0)
    {
        glDeleteProgram(_shaderProg);
        _shaderProg = 0;
    }
}

bool Technique::Init()
{
    _shaderProg = glCreateProgram();

    if (_shaderProg == 0)
        throw std::runtime_error("Error creating shader program.");

    return true;
}

//! Use this method to add shaders to the program. When finished - call finalize()
bool Technique::AddShader(uint32 shaderType, const char* shaderText)
{
    uint32 shaderObj = glCreateShader(shaderType);

    if (shaderObj == 0)
        throw std::runtime_error("Error creating shader type " + ToStringA(shaderType) + ".");

    _shaderObjList.push_back(shaderObj);

    const char* p[1];
    p[0] = shaderText;
    int32 Lengths[1];
    Lengths[0] = strlen(shaderText);
    glShaderSource(shaderObj, 1, p, Lengths);

    glCompileShader(shaderObj);

    int32 success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
        throw std::runtime_error("Error compiling shader type " + ToStringA(shaderType) + ": '" + InfoLog + "'.");
    }
}
