#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
class MeshRenderer :public Component
{
public:
	MeshRenderer();
	~MeshRenderer();
	void SetMeshRenderer(Entity *oEntity, ID3D12Device* device);
	void update()override;
	

private:

protected:
};

