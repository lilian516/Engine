#include "Projectile.h"
#include "Move.h"
Projectile::Projectile() {

}

void Projectile::initProjectile(Manager* oManager, Shader* oShader, Mesh* oMesh) {
	initEntity();
	m_oMeshRenderer.SetMeshRenderer(this, oManager->m_oGraphics->m_d3dDevice, oShader, oMesh);
	m_oMeshRenderer.buildConstantBuffers(oManager->m_oGraphics->m_d3dDevice, oManager->m_oGraphics->m_dConstantBufferViewHeapDescriptor);

	addComponent(&m_oMeshRenderer);
	Move* oMove = new Move();
	oMove->setScript(this);
	addComponent(oMove);
	
	oManager->addEntity(this);
}