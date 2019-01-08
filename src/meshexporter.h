#ifndef MESHEXPORTER_H
#define MESHEXPORTER_H
#include <vector>
#include <string>

struct Texture2DAsset
{

};

struct MaterialAsset
{

};

struct MeshAsset
{
    int version;

};
bool saveMaterial(std::string path, std::string albedo);
bool saveTexture2D(std::string path, unsigned int size, unsigned char* pixels, int height, int width);
bool saveMesh(std::string path, std::string materialPath, std::vector<float> vertices, std::vector<int> indices, std::vector<float> textureCoords);

#endif // MESHEXPORTER_H
