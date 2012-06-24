#include "Mesh.h"

#include "Defines.h"
#include "Log.h"

#include <assert.h>
#include <vector>
#include <algorithm>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <assimp/assimp.hpp>

Mesh::MeshEntry::MeshEntry()
{
    VB = INVALID_OGL_VALUE;
    IB = INVALID_OGL_VALUE;
    NumIndices = 0;
    MaterialIndex = INVALID_MATERIAL;
}

Mesh::MeshEntry::~MeshEntry()
{
    if (VB != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &VB);

    if (IB != INVALID_OGL_VALUE)
        glDeleteBuffers(1, &IB);
}

bool Mesh::MeshEntry::Init( const std::vector<Vertex>& Vertices, const std::vector<uint32>& Indices )
{
    NumIndices = Indices.size();

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32) * NumIndices, &Indices[0], GL_STATIC_DRAW);

    return true;
}

inline void Mesh::Clear()
{
    _Textures.clear();

    for (uint32 i = 0; i < _Textures.size(); i++)
    {
        delete _Textures[i];
        _Textures[i] = NULL;
    }

    //std::for_each(_Textures.begin(), _Textures.end(), SAFE_DELETE<Texture>);
}

Mesh& Mesh::LoadMesh( const std::string& FileName )
{
    Clear();

    
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(FileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (pScene)
        InitFromScene(pScene, FileName);
    else
        throw std::runtime_error("Error parsing '" + FileName + "': +" + importer.GetErrorString() + "'");

    return *this;
}

bool Mesh::InitFromScene( const aiScene* pScene, const std::string& Filename )
{
    _Entries.resize(pScene->mNumMeshes);
    _Textures.resize(pScene->mNumMaterials);

    for (uint32 i = 0; i < _Entries.size(); i++)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

    return InitMaterials(pScene, Filename);
}

void Mesh::InitMesh(uint32 index, const aiMesh* paiMesh)
{
    _Entries[index].MaterialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> vertices;
    std::vector<uint32> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (uint32 i = 0; i < paiMesh->mNumVertices; i++)
    {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = &(paiMesh->mNormals[i]);

        Vertex v(Vector3<float>(pPos->x, pPos->y, pPos->z),
                 Vector2<float>(pTexCoord->x, pTexCoord->y),
                 Vector3<float>(pNormal->x, pNormal->y, pNormal->z));

        vertices.push_back(v);
    }

     for (uint32 i = 0; i < paiMesh->mNumFaces; i++)
     {
         const aiFace& face = paiMesh->mFaces[i];
         assert(face.mNumIndices == 3);
         indices.push_back(face.mIndices[0]);
         indices.push_back(face.mIndices[1]);
         indices.push_back(face.mIndices[2]);
     }

     _Entries[index].Init(vertices, indices);
}

bool Mesh::InitMaterials( const aiScene* pScene, const std::string& Filename )
{
    std::string::size_type slashIndex = Filename.find_last_of("/");
    std::string dir;

    if (slashIndex == std::string::npos)
        dir = ".";
    else if (slashIndex == 0)
        dir = "/";
    else
        dir = Filename.substr(0, slashIndex);

    bool ret = true;

    // Initialize the materials
    for (uint32 i = 0; i < pScene->mNumMaterials; i++)
    {
        const aiMaterial* material = pScene->mMaterials[i];

        _Textures[i] = NULL;

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;
            
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL ,NULL) == AI_SUCCESS)
            {
                std::string fullPath = dir + "/" + path.data;
                _Textures[i] = new Texture(GL_TEXTURE_2D, fullPath.c_str());

                if (_Textures[i]->Load())
                {
                    SAFE_DELETE(_Textures[i]);
                    throw std::runtime_error("Error loading texture '" + fullPath + "'");
                    ret = false;
                }
                else
                    LeLog << LOG_APP << "Loaded texture '" << fullPath.c_str() << "'" << NL;
            }
        }
        // Load a white texture in case the model does not include its own texture
        if (!_Textures[i])
        {
            _Textures[i] = new Texture(GL_TEXTURE_2D, "white.png");

            ret = _Textures[i]->Load();
        }
    }

    return ret;
}

void Mesh::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (uint32 i = 0; i < _Entries.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, _Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (const void*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (const void*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _Entries[i].IB);

        const uint32 materialIndex = _Entries[i].MaterialIndex;

        if (materialIndex < _Textures.size() && _Textures[materialIndex])
        {
            _Textures[materialIndex]->Bind(GL_TEXTURE0);
        }
        
        glDrawElements(GL_TRIANGLES, _Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}


