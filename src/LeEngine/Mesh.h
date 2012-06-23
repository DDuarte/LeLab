#ifndef MESH_H
#define MESH_H

#include "Defines.h"
#include "Texture.h"

#include <GL/glew.h>
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include <string>
#include <map>
#include <vector>

struct Vertex
{
    Vector3<float> pos;
    Vector2<float> tex;
    Vector3<float> normal;

    Vertex() {}

    Vertex(const Vector3<float>& pos, const Vector2<float>& tex, const Vector3<float>& normal)
    {
        this->pos = pos;
        this->tex = tex;
        this->normal = normal;
    }
};

class Mesh
{
public:
    Mesh() { }
    ~Mesh() { Clear(); }

    Mesh& LoadMesh(const std::string& FileName);

    void Render();

private:
    bool InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(uint32 index, const aiMesh* paiMesh);
    bool InitMaterials(const aiScene* pScene, const std::string& Filename);
    void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry
    {
        MeshEntry();
        ~MeshEntry();

        bool Init(const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices);
        uint32 VB;
        uint32 IB;
        uint32 NumIndices;
        uint32 MaterialIndex;
    };

    std::vector<MeshEntry> _Entries;
    std::vector<Texture*> _Textures;
};





#endif // MESH_H