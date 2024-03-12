#include "ScriptProjectile.h"
#include "App.h"
#include "ColliderGame.h"

ScriptProjectile::ScriptProjectile() {
	m_oEntity = nullptr;
}

void ScriptProjectile::initProjectile(Entity* oEntity) {
	setScript(oEntity);
	oEntity->m_tTransform.translation({ 0.f, 0.f, -5.f });
	
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0], 
		App::Get()->m_oManager.m_vMesh[1], 
		App::Get()->m_oManager.m_vTexture[0]);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptProjectile::update() {
	m_oEntity->move(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 2);
	if (m_oEntity->m_tTransform.m_vPosition.z > 5) {
		App::Get()->m_oManager.deleteEntity(m_oEntity);
	}
	
}