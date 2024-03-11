#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::setParticleSystem(Entity* oEntity, int iNbParticle, float fScaleParticle, XMFLOAT3 fPosition, Shader* sShader, Mesh* mMesh) {
	m_iNbParticle = iNbParticle;
	m_fScaleParticle = fScaleParticle;
	m_fPosition = fPosition;
	m_sShader = sShader;
	m_mMesh = mMesh;
	createParticle();
}

void ParticleSystem::createParticle(){
	float fScale;
	float fLifeTime;
	float fVelocity;
	XMFLOAT3 fDirection;
	XMVECTOR vDirection;
	for (int i = 0 ; i < m_iNbParticle ; i++){
		Particle* particle = new Particle();
		fScale =  1 / static_cast<float>(rand() % 90 + 10) ;
		fLifeTime = 1 / static_cast<float>(rand() % 50 + 1);
		fVelocity = 1 / static_cast<float>(rand() % 50 + 5);
		vDirection = {1 / static_cast<float>(rand() % 11 - 5), 1 / static_cast<float>(rand() % 11 - 5) , 1 / static_cast<float>(rand() % 11 - 5) };
		XMStoreFloat3(&fDirection,XMVector3Normalize(vDirection));
		particle->initParticle(fScale, fLifeTime, fVelocity, fDirection,m_fPosition);
		m_vParticle.push_back(particle);
	}
}

void ParticleSystem::render(Graphics* oGraphics) {
	for (int i = 0; i < m_vParticle.size(); i++) {
		//root signature
		oGraphics->m_cCommandList->SetGraphicsRootSignature(m_sShader->m_d3dRootSignature);

		//pipeline state
		oGraphics->m_cCommandList->SetPipelineState(m_sShader->m_d3dPipelineState);
		//vertex buffer
		D3D12_VERTEX_BUFFER_VIEW meshVertexBufferView = m_mMesh->m_mMesh.VertexBufferView();
		oGraphics->m_cCommandList->IASetVertexBuffers(0, 1, &meshVertexBufferView);
		//index buffer
		D3D12_INDEX_BUFFER_VIEW meshIndexBufferView = m_mMesh->m_mMesh.IndexBufferView();
		oGraphics->m_cCommandList->IASetIndexBuffer(&meshIndexBufferView);

		oGraphics->m_cCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		oGraphics->m_cCommandList->SetGraphicsRootConstantBufferView(1, m_vParticle[i]->m_uObjectCB->Resource()->GetGPUVirtualAddress());

		//draw
		oGraphics->m_cCommandList->DrawIndexedInstanced(m_mMesh->m_mMesh.indices.size(), 1, 0, 0, 0);
	}
}

void ParticleSystem::update() {

	for (int i = 0; i < m_vParticle.size(); i++) {
		m_vParticle[i]->update(0.001f);

		
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

		XMMATRIX world = XMLoadFloat4x4(&m_vParticle[i]->m_tTransform.m_mTransform);
		XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
		XMMATRIX worldViewProj = world * view * proj;

		// Update the constant buffer with the latest worldViewProj matrix.
		ObjectConstants objConstants;
		XMStoreFloat4x4(&objConstants.WorldViewProj, XMMatrixTranspose(worldViewProj));
		m_vParticle[i]->m_uObjectCB->CopyData(0, objConstants);

		XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, static_cast<float>(800) / 600, 1.0f, 1000.0f);
		XMStoreFloat4x4(&m_fProj, P);
		if (m_vParticle[i]->m_fLifeTime <= 0) {
			delete m_vParticle[i];
			m_vParticle.erase(m_vParticle.begin() + i);
			i--;
		}
	}
}


void ParticleSystem::setConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap){
	for (int i = 0 ; i < m_vParticle.size() ; i++){
		m_vParticle[i]->buildConstantBuffers(device, dCbvHeap);
	}
}