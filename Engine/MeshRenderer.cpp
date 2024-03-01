#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {
	
	//Convert Spherical to Cartesian coordinates.
	float x = m_fRadius * sinf(m_fPhi) * cosf(m_fTheta);
	float z = m_fRadius * sinf(m_fPhi) * sinf(m_fTheta);
	float y = m_fRadius * cosf(m_fPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
	XMStoreFloat4x4(&m_fView, view);
	
	XMMATRIX world = XMLoadFloat4x4(&m_oEntity.m_tTransform.m_mTransform);
	XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	m_uObjectCB->CopyData(0, objConstants);

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, static_cast<float>(800) / 600, 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_fProj, P);
}



void MeshRenderer::render(Graphics *oGraphics) {
	
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
	initComponent(3, *oEntity);
	m_oMesh = oMesh;
	m_oShader = oShader;
	
}

void MeshRenderer::buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap)
{
	m_uObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, 1, true);


}