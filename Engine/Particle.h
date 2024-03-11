#pragma once

#include "Transform.h"
#include "ObjectConstants.h"

#include "UploadBuffer.h"

class Particle
{
public:
    float m_fVelocity;
    float m_fLifeTime;
    Transform m_tTransform;
    XMFLOAT3 m_vDirection;
    XMFLOAT3 m_vMovement;
    std::unique_ptr<UploadBuffer<ObjectConstants>> m_uObjectCB;

    XMFLOAT4X4 m_fWorld = Identity4x4(); //|\\ TEMPORAIRE //|\\

    Particle();
    ~Particle();
    void initParticle(float fScale, float fLifeTime, float fVelocity, XMFLOAT3 vDirection, XMFLOAT3 vPosition);
    void update(float deltaTime);

    void buildConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap);

private:
};