#include "ColliderGame.h"


ColliderGame::ColliderGame() {

}

void ColliderGame::enterCollision() {
	Entity* particle = App::Get()->m_oManager.createEntity();
	ParticleSystem* system = particle->addComponent<ParticleSystem>();
	system->setParticleSystem(particle, 1000, 0.1, m_oEntity->getTransform().m_vPosition, App::Get()->m_oManager.m_vShader[0], App::Get()->m_oManager.m_vMesh[0], App::Get()->m_oManager.m_vTexture[0]);

	App::Get()->m_oManager.deleteEntity(m_oEntity);
}