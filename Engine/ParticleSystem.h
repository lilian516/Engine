#pragma once
#include "Component.h"
#include "Particle.h"
#include "Mesh.h"
#include "Shader.h"

class ParticleSystem : public Component
{
public:
    vector<Particle*> m_vParticle;
    int m_iNbParticle;
    float m_fScaleParticle;
    XMFLOAT3 m_fPosition;
    Mesh* m_mMesh;
    Shader* m_sShader;

    ParticleSystem();
    ~ParticleSystem();

    void setParticleSystem(Entity* oEntity, int iNbParticle, float fScaleParticle, XMFLOAT3 fPosition, Shader* sShader, Mesh* mMesh);
    void createParticle();
    void update()override;
    void render(Graphics* oGraphics)override;
    void setConstantBuffers(ID3D12Device* device, ID3D12DescriptorHeap* dCbvHeap);




    // --TEMPORAIRE-- //
    float m_fRadius = 5.0f;
    float m_fTheta = 1.5f * XM_PI;
    float m_fPhi = XM_PIDIV4;

    XMFLOAT4X4 m_fView = Identity4x4();
    XMFLOAT4X4 m_fProj = Identity4x4();
private:
};