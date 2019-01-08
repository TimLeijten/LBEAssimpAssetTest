#include "meshimporter.h"
#include <fstream>
#include <iostream>
#include <cstring>

std::string charpointerToString(char* chars, int size)
{
    std::string newString;
    for (int i = 0; i < size; i++)
    {
        newString.push_back(chars[i]);
    }
    return newString;
}



Mesh loadMesh(std::string path)
{
    //std::cout << "Loading mesh: " << path << std::endl;
    Mesh newmesh;

    char version;

    int materialPathLength;
    char* materialPath;

    int verticesCount;
    float* vertices;

    int indicesCount;
    int* indices;

    int textureCoordsCount;
    float* textureCoords;

    std::ifstream meshfile(path, std::ios::binary);
    if (meshfile.good())
    {
        meshfile.read(&version, sizeof(version));

        meshfile.read((char*)&materialPathLength, sizeof(int));
        materialPath = new char[materialPathLength];
        meshfile.read(materialPath, materialPathLength);

        meshfile.read((char*)&verticesCount, sizeof(int));
        vertices = new float[verticesCount];
        meshfile.read((char*)vertices, sizeof(float)*verticesCount );

        meshfile.read((char*)&indicesCount, sizeof(int));
        indices = new int[indicesCount];
        meshfile.read((char*)indices, sizeof(int)*indicesCount );

        meshfile.read((char*)&textureCoordsCount, sizeof(int));
        textureCoords = new float[textureCoordsCount];
        meshfile.read((char*)textureCoords, sizeof(float)*textureCoordsCount );

        meshfile.close();
    }
    else
    {
        std::cout << "Can't open file: " << std::endl;
        std::cout << "Reason: " << std::strerror(errno) << std::endl;
    }

    newmesh.materialPath = charpointerToString(materialPath, materialPathLength);

    newmesh.assetPath = path;

    newmesh.vvertices = std::vector<float>(vertices, vertices+verticesCount);
    newmesh.vindices = std::vector<int>(indices, indices+indicesCount);
    newmesh.vtextureCoords = std::vector<float>(textureCoords, textureCoords+textureCoordsCount);

    /*newmesh.vertices = vertices;
    newmesh.indices = indices;
    newmesh.textureCoords = textureCoords;*/

    /*std::cout << "version: " << (int)version << std::endl;
    std::cout << "materialPathLength: " << materialPathLength << std::endl;
    std::cout << "materialPath: " << charpointerToString(materialPath, materialPathLength) << std::endl;
    std::cout << "verticesCount: " << verticesCount << std::endl;
    //std::cout << "vertices: "; printArray<float>(vertices, verticesCount);
    std::cout << "indicesCount: " << indicesCount << std::endl;
    //std::cout << "indices: "; printArray<int>(indices, indicesCount);
    std::cout << "textureCoordsCount: " << textureCoordsCount << std::endl;
    //std::cout << "textureCoords: "; printArray<float>(textureCoords, textureCoordsCount);
    std::cout << "Finished loading!" << std::endl;*/
    return newmesh;
}
