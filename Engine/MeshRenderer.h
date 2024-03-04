#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
class MeshRenderer :public Component
{
public:
	MeshRenderer();
	~MeshRenderer();
	void SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader *oShader, Mesh *oMesh);
	void update()override;
	void render(Graphics* oGraphics, XMMATRIX mWorldViewProj)override;
	void buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap);
	
	ObjectConstants m_oObjectConstants;
	std::unique_ptr<UploadBuffer<ObjectConstants>> m_uObjectCB;



	
private:
	Shader* m_oShader;
	Mesh* m_oMesh;
	

protected:
};

