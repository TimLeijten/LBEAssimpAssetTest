#include "meshexporter.h"
#include <fstream>
#include <iostream>

bool saveTexture2D(std::string path, unsigned int size, unsigned char* pixels, int height, int width)
{
    char version = 1;

    std::ofstream assetfile(path, std::ios::binary);

    assetfile.write((char*)&version, sizeof(version));

    assetfile.write((char*)&size, sizeof(size));
    assetfile.write((char*)&pixels[0], sizeof(unsigned char)*size);

    assetfile.write((char*)&height, sizeof(height));
    assetfile.write((char*)&width, sizeof(width));

    assetfile.close();
    return 1;
}

bool saveMaterial(std::string path, std::string albedo)
{
    char version = 1;

    int albedoSize = albedo.size();

    std::ofstream assetfile(path, std::ios::binary);

    assetfile.write((char*)&version, sizeof(version));

    assetfile.write((char*)&albedoSize, sizeof(albedoSize));
    assetfile.write((char*)&albedo[0], sizeof(char)*albedo.size());

    assetfile.close();

    return 1;
}

bool saveMesh(std::string path, std::string materialPath, std::vector<float> vertices, std::vector<int> indices, std::vector<float> textureCoords)
{
    char version = 1;
    int materialPathCount = materialPath.size();
    int verticesCount = vertices.size();
    int indicesCount = indices.size();
    int textureCoordsCount = textureCoords.size();

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

    std::cout << verticesCount << std::endl;

    return 1;
}
