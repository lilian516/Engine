#include "ScriptEnemy.h"
#include <iomanip>
#include <iostream>
#include <random>

#include "ColliderGame.h"

ScriptEnemy::ScriptEnemy() {

}

void ScriptEnemy::initEnemy(Entity* oEntity) {
	setScript(oEntity);

	float x = rand() % 61 + (-30);
	float y = rand() % 61 + (-30);
	float z = rand() % 61 + (-30);

	XMFLOAT3 vect{ x,y,z};

	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0],
		App::Get()->m_oManager.m_vMesh[1],
		App::Get()->m_oManager.m_vTexture.find("apognan")->second);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	oEntity->translate(vect);
	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptEnemy::update() {

}