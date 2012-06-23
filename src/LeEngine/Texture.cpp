#include "Texture.h"

#include "Defines.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

Texture::Texture( uint32 TextureTarget, const std::string& FileName )
{
    _textureTarget = TextureTarget;
    _fileName = FileName;
    _imageName = ilGenImage();
    ilBindImage(_imageName);
}

bool Texture::Load()
{
    if (!ilLoadImage((const wchar_t*)_fileName.c_str()))
        throw std::runtime_error("Error loading texture '" + _fileName +"'");

    glGenTextures(1, &_textureObj);
    glBindTexture(_textureTarget, _textureObj);
    glTexImage2D(_textureTarget, 0, GL_RGB,ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), -0.5, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    glTexParameterf(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}


void Texture::Bind( uint32 TextureUnit )
{
    glActiveTexture(TextureUnit);
    glBindTexture(_textureTarget, _textureObj);
}
