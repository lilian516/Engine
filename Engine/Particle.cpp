#include "Particle.h"

Particle::Particle() {

}
Particle::~Particle() {

}

void Particle::initParticle(float fScale, float fLifeTime, float fVelocity, XMFLOAT3 vDirection, XMFLOAT3 vPosition) {
    XMFLOAT3 scale = { fScale,fScale,fScale };
    m_tTransform.scale(scale);
    m_tTransform.translation(vPosition);
    m_tTransform.updateTransform();
    m_fLifeTime = fLifeTime;
    m_fVelocity = fVelocity;
    m_vDirection = vDirection;
    XMVECTOR vMovement = XMLoadFloat3(&m_vDirection) * m_fVelocity;
    XMStoreFloat3(&m_vMovement, vMovement);
}

void Particle::update(float deltaTime) {
    m_tTransform.translation(m_vMovement);
    m_fLifeTime -= deltaTime;
}

void Particle::buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap)
{
    m_uObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, 1, true);
}