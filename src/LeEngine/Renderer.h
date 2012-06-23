#ifndef RENDERER_H
#define RENDERER_H

#include "Defines.h"
#include "Mesh.h"
#include "Material.h"

#include <vector>
#include <string>
#include <map>

#include <assimp/assimp.hpp>

class Renderer
{
public:
    std::vector<Mesh> meshes;
    std::vector<float *> matrixStack;

    Import(std::string name);

    float modelMatrix[16];
private:
    uint8 vertexLoc = 0, normalLoc = 1, textCoordLoc = 2;
    uint8 matricesUniLoc = 1, materialUniLoc = 2;
    uint8 textUnit = 0;
};

Renderer::Import( std::string name )
{
    Assimp::Importer importer;

    float scaleFactor;

    std::map<std::string, uint32> textureIdMap;
}

#endif // RENDERER_H