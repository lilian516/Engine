#include "ScriptEnemy.h"
#include <iomanip>
#include <iostream>
#include <random>

#include "ColliderGame.h"

ScriptEnemy::ScriptEnemy() {

}

void ScriptEnemy::initEnemy(Entity* oEntity) {
	setScript(oEntity);

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(-2.0f, 2.0f);
	float x = distr(eng);
	float y = distr(eng);
	float z = distr(eng);

	XMFLOAT4 vect{ x,y,z,0.0f };
	oEntity->m_tTransform.translation(vect);

	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0],
		App::Get()->m_oManager.m_vMesh[2],
		App::Get()->m_oManager.m_vTexture[0]);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice, 
		App::Get()->m_oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);

	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);

}

void ScriptEnemy::update() {

}