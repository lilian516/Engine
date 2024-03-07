#pragma once
#include "Component.h"
#include "Particle.h"

class ParticleSystem : public Component
{
public:
	vector<Particle*> m_vParticle;
	int m_iNbParticle;
	float m_fScaleParticle;
	XMFLOAT3 m_fPosition;

	ParticleSystem();
	~ParticleSystem();

	void setParticleSystem(int iNbParticle, float fScaleParticle, XMFLOAT3 fPosition);
	void createParticle();
	void update()override;
private:
};