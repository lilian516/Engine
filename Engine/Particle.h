#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Timer.h"

class Particle
{
public:
	float m_fVelocity;
	float m_fLifeTime;
	Transform m_tTransform;
	XMFLOAT3 m_vDirection;
	XMFLOAT3 m_vMovement;

	Particle();
	~Particle();
	void initParticle(float fScale, float fLifeTime, float fVelocity, XMFLOAT3 vDirection,XMFLOAT3 vPosition);
	void update(float deltaTime);

private:
};

