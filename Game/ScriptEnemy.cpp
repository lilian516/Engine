#include "ScriptEnemy.h"
#include <iomanip>
#include <iostream>
#include <random>

#include "ColliderGame.h"

ScriptEnemy::ScriptEnemy() {

}

void ScriptEnemy::initEnemy(Entity* oEntity) {
	setScript(oEntity);

	float x = rand() % 50 + (-50);
	float y = rand() % 10 + (-10);
	float z = rand() % 20 + (-20);

	XMFLOAT3 vect{ x,y,z};

	m_DirVect = { App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.x - vect.x,
	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.y - vect.y,
	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->getTransform().m_vPosition.z - vect.z };

	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0],
		App::Get()->m_oManager.m_vMesh[3],
		App::Get()->m_oManager.m_vTexture.find("enemy")->second);
	
	oEntity->translate(vect);
	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptEnemy::update() {
	XMVECTOR vDir = {m_DirVect.x,m_DirVect.y,m_DirVect.z};
	XMVECTOR vDirNormalize = XMVector3Normalize(vDir);
	m_oEntity->move(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 2.0f, vDirNormalize);

	
}