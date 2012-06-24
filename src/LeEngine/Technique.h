#ifndef TECHNIQUE_H
#define TECHNIQUE_H

#include "Defines.h"

#include <list>

#include <GL/glew.h>

class Technique
{
public:

    Technique();
    ~Technique();
    virtual bool Init();
    void Enabled();

protected:

    bool AddShader(uint32 shaderType, const char* shaderText);
    bool Finalize();
    int32 GetUniformLocation(const char* uniformName);

private:

    uint32 _shaderProg;

    typedef std::list<uint32> ShaderObjList;
    ShaderObjList _shaderObjList;
};

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF


#endif // TECHNIQUE_H
