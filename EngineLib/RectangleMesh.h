#pragma once
#include "Mesh.h"
class RectangleMesh : public Mesh
{
public :
	RectangleMesh();
	~RectangleMesh();
	void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList)override;
};

