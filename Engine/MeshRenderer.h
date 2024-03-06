#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
class MeshRenderer :public Component
{
public:
	MeshRenderer();
	~MeshRenderer();
	void SetMeshRenderer(Entity* oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh);
	void update()override;
	void render(Graphics* oGraphics)override;
	void buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap);

	std::unique_ptr<UploadBuffer<ObjectConstants>> m_uObjectCB;

	float m_fRadius = 5.0f;
	float m_fTheta = 1.5f * XM_PI;
	float m_fPhi = XM_PIDIV4;

	XMFLOAT4X4 m_fWorld = Identity4x4();
	XMFLOAT4X4 m_fView = Identity4x4();
	XMFLOAT4X4 m_fProj = Identity4x4();

private:
	Shader* m_oShader;
	Mesh* m_oMesh;


protected:
};