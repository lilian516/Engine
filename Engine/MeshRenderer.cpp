#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() {
}

MeshRenderer::~MeshRenderer() {
}
void MeshRenderer::update() {
	
}



void MeshRenderer::render(Graphics *oGraphics, XMMATRIX mWorldViewProj) {

	XMStoreFloat4x4(&m_oObjectConstants.WorldViewProj, XMMatrixTranspose(mWorldViewProj));
	m_uObjectCB->CopyData(0, m_oObjectConstants);
	
	//root signature
	oGraphics->m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);
	//pipeline state
	oGraphics->m_cCommandList->SetPipelineState(m_oShader->m_d3dPipelineState);
	//vertex buffer
	D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_oMesh->m_mMesh.VertexBufferView();
	oGraphics->m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
	//index buffer
	D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_oMesh->m_mMesh.IndexBufferView();
	oGraphics->m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);

	oGraphics->m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(0, m_uObjectCB->Resource()->GetGPUVirtualAddress());

	//draw
	oGraphics->m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(), 1, 0, 0, 0);
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh) {
	initComponent(3, oEntity);
	m_oMesh = oMesh;
	m_oShader = oShader;
	
}

void MeshRenderer::buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap)
{
	m_uObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, 1, true);
}

