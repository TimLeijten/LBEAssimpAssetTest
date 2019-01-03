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

bool saveMesh(std::string path, std::string materialPath, std::vector<float> vertices, std::vector<int> indices, std::vector<float> textureCoords);

#endif // MESHEXPORTER_H
