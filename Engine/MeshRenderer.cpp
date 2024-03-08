#include "MeshRenderer.h"
#include "Transform.h"

MeshRenderer::MeshRenderer() {
}

MeshRenderer::~MeshRenderer() {
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device, Mesh* oMesh, Texture* oTexture) {
	buildConstantBuffers(device);
	initComponent(3, oEntity);
	m_oMesh = oMesh;
	m_oShader = new Shader();
	m_oShader->init(device);
	m_oEntity->m_aBox = m_oMesh->m_mMesh.oBox;

	m_oTexture = oTexture;
	
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

	XMMATRIX world = XMLoadFloat4x4(&m_oEntity->m_tTransform.m_mTransform);
	XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
	XMMATRIX worldViewProj = world * view * proj;

	// Update the constant buffer with the latest worldViewProj matrix.
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
	m_uObjectCB->CopyData(0, objConstants);

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, static_cast<float>(800) / 600, 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_fProj, P);
}



void MeshRenderer::render(Graphics* oGraphics) {
	oGraphics->updateCam(this);
	updateConstantBuffer(oGraphics->m_worldViewProj);
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

	oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(1, m_uObjectCB->Resource()->GetGPUVirtualAddress());

	oGraphics->m_cCommandList->SetGraphicsRootDescriptorTable(0,m_oTexture->getGPUDesc());

	//draw
	oGraphics->m_cCommandList->DrawIndexedInstanced(m_oMesh->m_mMesh.indices.size(), 1, 0, 0, 0);
}


void MeshRenderer::buildConstantBuffers(ID3D12Device* device)
{
	m_uObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, 1, true);
}

void MeshRenderer::updateConstantBuffer(XMMATRIX worldViewProjMatrix) {
	CD3DX12_RANGE readRange(0, 0);
	m_uObjectCB->Resource()->Map(0, &readRange, reinterpret_cast<void**>(&m_uObjectCB));

	memcpy(m_uObjectCB->Resource(), &worldViewProjMatrix, sizeof(worldViewProjMatrix));
	m_uObjectCB->Resource()->Unmap(0, nullptr);
}