#pragma once
#include "Mesh.h"

class Skybox: public Mesh
{
public:
	Skybox();
	~Skybox();
	void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
};

