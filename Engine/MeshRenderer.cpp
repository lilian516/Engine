#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {

}

void MeshRenderer::render(Graphics *oGraphics) {
	oGraphics->m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);
	oGraphics->m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);

	oGraphics->m_cCommandList->SetPipelineState(m_oShader->m_d3dPipelineState);

	D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_oMesh->m_mMesh.VertexBufferView();
	oGraphics->m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
	D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_oMesh->m_mMesh.IndexBufferView();
	oGraphics->m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);
	oGraphics->m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(0, m_oShader->m_uObjectCB->Resource()->GetGPUVirtualAddress());
	oGraphics->m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(), 1, 0, 0, 0);
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh) {
	initComponent(3, *oEntity);
	m_oMesh = oMesh;
	m_oShader = oShader;
	
}