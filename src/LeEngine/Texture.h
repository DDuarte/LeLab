#ifndef TEXTURE_H
#define TEXTURE_H

#include "Defines.h"

#include <string>

#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

class Texture
{
public:

    Texture(uint32 TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(uint32 TextureUnit);

    uint32 GettT() { return _textureTarget; }

private:
    std::string _fileName;
    uint32 _textureTarget;
    uint32 _textureObj;
    uint32 _imageName;
};




#endif // TEXTURE_H