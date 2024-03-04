#pragma once
#include "Mesh.h"
class PyramidMesh :public Mesh
{
public:
    PyramidMesh();
    ~PyramidMesh();
    void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
};

