#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
class MeshRenderer :public Component
{
public:
	MeshRenderer();
	~MeshRenderer();
	void SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh, Texture* oTexture);
	void update()override;
	void render(Graphics* oGraphics)override;
	void buildConstantBuffers(ID3D12Device* device);
	void updateConstantBuffer(XMFLOAT4X4 worldViewProjMatrix);

	std::unique_ptr<UploadBuffer<ObjectConstants>> m_uObjectCB;


	XMFLOAT4X4 m_fWorld = Identity4x4();
	XMFLOAT4X4 m_fView = Identity4x4();
	XMFLOAT4X4 m_fProj = Identity4x4();

private:
	Shader* m_oShader;
	Mesh* m_oMesh;
	Texture* m_oTexture;
	

protected:
};