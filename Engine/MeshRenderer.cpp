#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"

MeshRenderer::MeshRenderer() {
}

MeshRenderer::~MeshRenderer() {
	delete m_oShader;
	delete m_oMesh;
	delete m_oTexture;
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh, Texture* oTexture) {
	buildConstantBuffers(device);
	initComponent(3, oEntity);
	m_oMesh = oMesh;
	
	m_oShader = oShader;
	m_oEntity->m_aBox = m_oMesh->m_mMesh.oBox;

	m_oTexture = oTexture;
	
}

void MeshRenderer::update() {

}



void MeshRenderer::render(Graphics* oGraphics) {
	updateConstantBuffer(m_oEntity->getTransform().m_mTransform);

	//root signature
	oGraphics->m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);

	for (int i = 0; i < oGraphics->m_oCamEntity->m_vComponents.size(); i++) {
		if (Camera* cam = dynamic_cast<Camera*>(oGraphics->m_oCamEntity->m_vComponents[i])) {
			oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(2, cam->m_uCamCB->Resource()->GetGPUVirtualAddress());
			break;
		}
	}

	//pipeline state
	oGraphics->m_cCommandList->SetPipelineState(m_oShader->m_d3dPipelineState);
	//vertex buffer
	D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_oMesh->m_mMesh.VertexBufferView();
	oGraphics->m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
	//index buffer
	D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_oMesh->m_mMesh.IndexBufferView();
	oGraphics->m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);

	oGraphics->m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(1, m_uObjectCB->Resource()->GetGPUVirtualAddress());
	

	oGraphics->m_cCommandList->SetGraphicsRootDescriptorTable(0,m_oTexture->getGPUDesc());

	oGraphics->m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(), 1, 0, 0, 0);
}


void MeshRenderer::buildConstantBuffers(ID3D12Device* device)
{
	m_uObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, 1, true);
}

void MeshRenderer::updateConstantBuffer(XMFLOAT4X4 world) {
	
	ObjectConstants data;
	XMStoreFloat4x4(&data.WorldViewProj, XMMatrixTranspose(XMLoadFloat4x4(&world)));
	m_uObjectCB->CopyData(0, data);
}