#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "meshexporter.h"

int iy = 0;
void processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "Found mesh named: " << std::string(mesh->mName.C_Str())+"_"+std::to_string(iy)+".mesh" << " Vertices: " << mesh->mNumVertices*3 << std::endl;
        std::vector<float> vertices;
        for (unsigned int ii = 0; ii < mesh->mNumVertices; ii++)
        {
            vertices.push_back(mesh->mVertices[ii].x);
            vertices.push_back(mesh->mVertices[ii].y);
            vertices.push_back(mesh->mVertices[ii].z);
        }
        std::vector<int> indices;
        std::vector<float> textureCoords;
        for (unsigned int ii = 0; ii < mesh->mNumVertices; ii++)
        {
            textureCoords.push_back(mesh->mTextureCoords[0][ii].x);
            textureCoords.push_back(mesh->mTextureCoords[0][ii].y);
            textureCoords.push_back(mesh->mTextureCoords[0][ii].z);
        }
        saveMesh("/home/tim/Documents/Random/TestBin/"+std::string(mesh->mName.C_Str())+"_"+std::to_string(iy)+".mesh", "/materials/defaultMat.material", vertices, indices, textureCoords);
        iy++;
        //meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

int main()
{
    Assimp::Importer importer;
    //const aiScene* scene = importer.ReadFile( "Gasebo.fbx",
    //const aiScene* scene = importer.ReadFile( "Cup_Made_By_Tyro_Smith.obj",
    const aiScene* scene = importer.ReadFile( "/home/tim/Downloads/velaroobj/untitled.obj",
    //const aiScene* scene = importer.ReadFile( "cube.fbx",
          aiProcess_CalcTangentSpace       |
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          aiProcess_SortByPType);
    if( !scene)
    {
      std::cout << "Failed to load model: " << importer.GetErrorString() << std::endl;
      return false;
    }
    else
    {
        std::cout << "Loading model succeded!" << std::endl;
    }

    std::cout << "Meshes in model: " << scene->mNumMeshes << std::endl;
    std::cout << "Textures in model: " << scene->mNumTextures << std::endl;
    std::cout << "Materials in model: " << scene->mNumMaterials << std::endl;
    processNode(scene->mRootNode, scene);

    std::vector<float> testVertices = {-1, 1, -0.5f, 0, 1, -1, 0.5f, 0, 1};
    std::vector<int> testIndices = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<float> testTextureCoords = {-1, -1, 0, -0.5f, 1, -1, 0, 0.5f, 1};

    saveMesh("/home/tim/Documents/Random/TestBin/test.bin", "/Materials/TestMat.mat", testVertices, testIndices, testTextureCoords);

    return true;
}
