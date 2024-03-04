#pragma once
#include "Mesh.h"
class BoxMesh :public Mesh
{
public:
    BoxMesh();
    ~BoxMesh();
    void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)override;
};
