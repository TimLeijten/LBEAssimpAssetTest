#include <iostream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

int main()
{
	std::cout << "Hi!" << std::endl;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( "a.fbx",
          aiProcess_CalcTangentSpace       |
          aiProcess_Triangulate            |
          aiProcess_JoinIdenticalVertices  |
          aiProcess_SortByPType);
    if( !scene)
    {
      std::cout << "Failed to load model!" << std::endl;
      return false;
    }

    return true;
}
