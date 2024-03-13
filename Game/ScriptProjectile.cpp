#include "ScriptProjectile.h"
#include "App.h"
#include "ColliderGame.h"

ScriptProjectile::ScriptProjectile() {
	m_oEntity = nullptr;
}

void ScriptProjectile::initProjectile(Entity* oEntity) {
	setScript(oEntity);
	XMVECTOR vForward = App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().getForwardVector();
	XMFLOAT3 fForward;
	XMStoreFloat3(&fForward, vForward);
	m_mDir = { fForward.x,
		fForward.y,
		fForward.z };

	/*m_mDir = { App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vRotation.x,
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vRotation.y,
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vRotation.z };*/

	
	
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0], 
		App::Get()->m_oManager.m_vMesh[2], 
		App::Get()->m_oManager.m_vTexture.find("apognan")->second);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	oEntity->translate({ App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.x
		,App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.y - 1.0f
		,App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.z });
	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptProjectile::update() {
	XMVECTOR vDir = { m_mDir.x,m_mDir.y,m_mDir.z};
	m_oEntity->move(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 10, vDir);
	m_oEntity->getTransform().m_vPosition;
	XMFLOAT4 fPostionProjectile = { m_oEntity->getTransform().m_vPosition.x, 
		m_oEntity->getTransform().m_vPosition .y, 
		m_oEntity->getTransform().m_vPosition .z, 0.0f};
	XMFLOAT4 fPostionCamera = { App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.x,
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.y,
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.z, 0.0f };
	float distance = distanceCalcul(fPostionProjectile, fPostionCamera);
	int collideState;
	for (int i = 0; i < m_oEntity->getVectorComponents().size(); i++) {
		if (Collider* collider = dynamic_cast<Collider*>(m_oEntity->getVectorComponents()[i])) {
			collideState = collider->m_cCollision;
		}
	}
	if (distance > 40.0f && collideState != 1) {
		App::Get()->m_oManager.deleteEntity(m_oEntity);
	}
	
}