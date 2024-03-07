#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {

}
ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::setParticleSystem(int iNbParticle, float fScaleParticle, XMFLOAT3 fPosition) {
	m_iNbParticle = iNbParticle;
	m_fScaleParticle = fScaleParticle;
	m_fPosition = fPosition;
}

void ParticleSystem::createParticle(){
	float fScale;
	float fLifeTime;
	float fVelocity;
	XMFLOAT3 fDirection;
	XMVECTOR vDirection;
	for (int i = 0 ; i < m_iNbParticle ; i++){
		Particle particle;
		fScale = rand() % 1 / 100 + 1 / 1000;
		fLifeTime = rand() % 1 / 2 + 2;
		fVelocity = rand() % 1 / 100 + 1 / 1000;
		vDirection = { static_cast<float>(rand() % (-1) + 1), static_cast<float>(rand() % (-1) + 1) , static_cast<float>(rand() % (-1) + 1) };
		XMStoreFloat3(&fDirection,XMVector3Normalize(vDirection));
		particle.initParticle(fScale, fLifeTime, fVelocity, fDirection,m_fPosition);
		m_vParticle.push_back(&particle);
	}
}
void ParticleSystem::update(){
	for (int i = 0 ; i < m_vParticle.size() ; i++){
		if (m_vParticle[i]->m_fLifeTime <=0){
			delete m_vParticle[i];
		}
		m_vParticle[i]->update(2.f);
	}
	for (int i = 0; i < m_vParticle.size(); i++){
		if (m_vParticle[i]->m_fLifeTime <= 0) {
			delete m_vParticle[i];
		}
	}
	
}