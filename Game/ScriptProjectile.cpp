#include "ScriptProjectile.h"
#include "App.h"
#include "ColliderGame.h"

ScriptProjectile::ScriptProjectile() {
	m_oEntity = nullptr;
}

void ScriptProjectile::initProjectile(Entity* oEntity) {
	setScript(oEntity);

	/// le vecteur directeur
	XMVECTOR vForward = App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().getForwardVector();
	XMFLOAT3 fForward;
	XMStoreFloat3(&fForward, vForward);
	m_mDir = { fForward.x,fForward.y,fForward.z };

	/// le mesh renderer
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0], 
		App::Get()->m_oManager.m_vMesh[1], 
		App::Get()->m_oManager.m_vTexture.find("laser")->second);

	

	/// le scale
	oEntity->scale({ 0.15,0.15,0.15 });


	/// le positionnement
	oEntity->translate({ App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.x
		,App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.y - 0.5f
		,App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.z });

	/// le collider
	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptProjectile::update() {
	XMVECTOR vDir = { m_mDir.x,m_mDir.y,m_mDir.z};
	m_oEntity->move(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 10, vDir);
	m_oEntity->getTransform().m_vPosition;

	XMFLOAT4 fPostionProjectile = { m_oEntity->getTransform().m_vPosition.x,
		m_oEntity->getTransform().m_vPosition.y,
		m_oEntity->getTransform().m_vPosition.z, 0.0f };

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

ScriptProjectile::~ScriptProjectile() {

}