#include "meshexporter.h"
#include <fstream>
#include <iostream>

bool saveTexture2D()
{

    return 1;
}

bool saveMaterial()
{

    return 1;
}

bool saveMesh(std::string path, std::string materialPath, std::vector<float> vertices, std::vector<int> indices, std::vector<float> textureCoords)
{
    char version = 1;
    int verticesCount = vertices.size();
    int indicesCount = indices.size();
    int textureCoordsCount = textureCoords.size();
    int materialPathCount = materialPath.size();

    std::ofstream assetfile(path, std::ios::binary);
    assetfile.write((char*)&version, sizeof(version));// Version

    assetfile.write((char*)&materialPathCount, sizeof(materialPathCount));// Material Name Length
    assetfile.write((char*)&materialPath[0], sizeof(char)*materialPath.size());// Material Name

    assetfile.write((char*)&verticesCount, sizeof(verticesCount));// Vertices Count
    assetfile.write((char*)&vertices[0], sizeof(float)*vertices.size());// Vertices

    assetfile.write((char*)&indicesCount, sizeof(indicesCount));// Indices Count
    assetfile.write((char*)&indices[0], sizeof(int)*indices.size());// Indices

    assetfile.write((char*)&textureCoordsCount, sizeof(textureCoordsCount));// TextureCoords Count
    assetfile.write((char*)&textureCoords[0], sizeof(float)*textureCoords.size());// TextureCoords

    assetfile.close();
    return 1;
}
