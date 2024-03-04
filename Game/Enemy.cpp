#include "Enemy.h"

Enemy::Enemy() {

}

void Enemy::initEnemy(Graphics* oGraphics,Shader *oShader,Mesh *oMesh) {
	initEntity();
	
	
	m_oMeshRenderer.SetMeshRenderer(this, oGraphics->m_d3dDevice, oShader, oMesh);
	m_oMeshRenderer.buildConstantBuffers(oGraphics->m_d3dDevice, oGraphics->m_dConstantBufferViewHeapDescriptor);
	addComponent(&m_oMeshRenderer);
	
}


void Enemy::update() {
	Entity::update();
}

void Enemy::render(Graphics* oGraphics) {
	Entity::render(oGraphics);
}