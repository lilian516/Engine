#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {

}

void MeshRenderer::render() {
	/*m_cCommandList->SetGraphicsRootSignature(m_oShader->m_d3dRootSignature);

	m_cCommandList->SetPipelineState(m_oShader->m_d3dPipelineState);

	D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_oMesh->m_mMesh.VertexBufferView();
	m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
	D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_oMesh->m_mMesh.IndexBufferView();
	m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);
	m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_cCommandList->SetGraphicsRootConstantBufferView(0, m_oShader->m_uObjectCB->Resource()->GetGPUVirtualAddress());
	m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(), 1, 0, 0, 0);*/
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Shader* oShader, Mesh* oMesh) {
	initComponent(3, *oEntity);
	m_oMesh = oMesh;
	m_oShader = oShader;
	
}