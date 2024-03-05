#pragma once
#include "Entity.h"
#include "Mesh.h"
class Sprite : public Mesh
{
public:
	Sprite();
	~Sprite();
	void buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
};

