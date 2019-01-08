#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H
#include <vector>
#include <string>
#include <iostream>


struct Mesh
{
    std::string assetPath;

    std::string materialPath;
    std::vector<float> vvertices;
    std::vector<int> vindices;
    std::vector<float> vtextureCoords;

    /*float* vertices;
    int* indices;
    float* textureCoords;*/
};

Mesh loadMesh(std::string path);

template<class T> void printArray(T* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
}

#endif // MESHIMPORTER_H
