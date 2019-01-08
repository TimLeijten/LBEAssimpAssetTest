#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "meshexporter.h"
#include "meshimporter.h"
#include "testing.h"

int iy = 0;

struct CompMesh
{
    std::string path;
    std::string matPath;
    std::vector<float> vertices;
    std::vector<int> indices;
    std::vector<float> textureCoords;
};

std::vector<CompMesh> Meshes;

bool testMeshLoading()
{
    std::vector<Mesh> loadedMeshes;
    std::cout << "Testloading meshes..." << std::endl;
    for (int i = 0; i < Meshes.size(); i++)
    {
        loadedMeshes.push_back(loadMesh(Meshes[i].path));
    }
    std::cout << "Done testloading meshes!" << std::endl;

    std::cout << "Comparing meshes..." << std::endl;
    if (loadedMeshes.size() != Meshes.size())
    {
        std::cout << "ERROR! Mesh count not equal!" << std::endl;
        return 0;
    }
    for (int i = 0; i < loadedMeshes.size(); i++)
    {
        if (loadedMeshes[i].assetPath != Meshes[i].path)
        {
            std::cout << "WARNING! Asset path not equal![" << i << "]" << loadedMeshes[i].assetPath << "vs" << Meshes[i].path << std::endl;
        }
        if (loadedMeshes[i].vvertices.size() != Meshes[i].vertices.size())
        {
            std::cout << "ERROR! Vertices Count in mesh not equal![" << i << "]" << loadedMeshes[i].vvertices.size() << "vs" << Meshes[i].vertices.size() << " MeshPath: " << loadedMeshes[i].assetPath << std::endl;
            return 0;
        }
        for (int ii = 0; ii < loadedMeshes[i].vvertices.size(); ii++)
        {
            if (loadedMeshes[i].vvertices[ii] != Meshes[i].vertices[ii])
            {
                std::cout << "ERROR! Vertice not equal![" << i << "][" << ii << "]" << loadedMeshes[i].vvertices[ii] << "vs" << Meshes[i].vertices[ii] << " MeshPath: " << loadedMeshes[i].assetPath << std::endl;
                return 0;
            }
        }
        if (loadedMeshes[i].materialPath != Meshes[i].matPath)
        {
            std::cout << "ERROR! Material Path not equal![" << i << "]" << loadedMeshes[i].materialPath << "vs" << Meshes[i].matPath << " MeshPath: " << loadedMeshes[i].assetPath << std::endl;
        }
    }
    std::cout << "Done comparing meshes! All is ok." << std::endl;
}


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
        std::vector<int> indices = {0, 1, 2, 0, 4};
        std::vector<float> textureCoords;
        if (mesh->HasTextureCoords(0))
        {
            for (unsigned int ii = 0; ii < mesh->mNumVertices; ii++)
            {
                textureCoords.push_back(mesh->mTextureCoords[0][ii].x);
                textureCoords.push_back(mesh->mTextureCoords[0][ii].y);
                textureCoords.push_back(mesh->mTextureCoords[0][ii].z);
            }
        }
        //std::string _tmpn(mesh->mName.C_Str(), 2);
        saveMesh("/home/tim/Documents/Random/TestBin/_"+std::to_string(iy)+".mesh", "/materials/defaultMat.material", vertices, indices, textureCoords);
        CompMesh newMesh;
        newMesh.path = "/home/tim/Documents/Random/TestBin/_"+std::to_string(iy)+".mesh";
        newMesh.matPath = "/materials/defaultMat.material";
        newMesh.vertices = vertices;
        newMesh.indices = indices;
        newMesh.textureCoords = textureCoords;
        Meshes.push_back(newMesh);
        iy++;
        //meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void printTree(aiNode *node, const aiScene *scene, std::string depth)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[ node->mMeshes[i] ];
        //std::cout << "/" << node->mMeshes[i] << std::endl;
        std::cout << "Found mesh named: " << depth+""+std::string(mesh->mName.C_Str()) << " Vertices: " << mesh->mNumVertices*3 << std::endl;
    }
    //std::cout << node->mNumMeshes << std::endl;
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        //std::cout << node->mName.C_Str() << "-/-" << node->mNumChildren << std::endl;
        printTree(node->mChildren[i], scene, depth+std::string(node->mName.C_Str())+std::string("/"));

    }
}

int main()
{
    Assimp::Importer importer;
    //const aiScene* scene = importer.ReadFile( "Gasebo.fbx",
    //const aiScene* scene = importer.ReadFile( "/home/tim/Downloads/velaroobj/untitled.obj",
    const aiScene* scene = importer.ReadFile( "/home/tim/Downloads/velaroobj/Velaro_E_DB_OBJ.obj",
    //const aiScene* scene = importer.ReadFile( "cube.fbx",
          aiProcess_CalcTangentSpace       |
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          aiProcess_OptimizeMeshes         |
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
    //processNode(scene->mRootNode, scene);
    unsigned char* pixels = new unsigned char[4*4]{122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122};
    saveTexture2D("/home/tim/Documents/Random/TestBin/tex1.tex", 4*4, pixels, 2, 2);


    return testMeshLoading();
}
