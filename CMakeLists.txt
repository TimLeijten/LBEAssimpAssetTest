cmake_minimum_required(VERSION 3.5)

include_directories(LBE_ModelToAsset "Libraries/assimp/include" "src" "/home/tim/Documents/GitProjects/build-LBEAssimpAssetTest-Imported_Kit-Release/Libraries/assimp/include")

add_subdirectory(Libraries/assimp)

file(GLOB ModelToAssetSOURCES
"src/*.cpp" "src/*.h"
)

project(LBE_ModelToAsset)
add_executable(LBE_ModelToAsset ${ModelToAssetSOURCES})
target_link_libraries(LBE_ModelToAsset assimp)
