#pragma once
#include "Mesh.h"
class PenMesh :public Mesh
{
public:
	PenMesh();
	~PenMesh();
	void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
};

