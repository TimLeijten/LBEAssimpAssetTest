#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags


void processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        std::cout << "Found mesh named: " << mesh->mName.C_Str() << std::endl;
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
    const aiScene* scene = importer.ReadFile( "Cup_Made_By_Tyro_Smith.obj",
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

    return true;
}
