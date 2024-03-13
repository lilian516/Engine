#include "ScriptMenu.h"
#include <iomanip>
#include <iostream>
#include <random>

#include "ColliderGame.h"

ScriptMenu::ScriptMenu() {

}

void ScriptMenu::initMenu(Entity* oEntity) {
	setScript(oEntity);

	/*std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(10.0f, 20.0f);
	double x = distr(eng);
	double y = distr(eng);
	double z = distr(eng);

	XMFLOAT3 vect{ float(x),float(y),float(z) };
	oEntity->m_tTransform.translation(vect);*/
	MeshRenderer* pMeshRenderer = oEntity->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(oEntity, App::Get()->m_oManager.m_oGraphics.m_d3dDevice,
		App::Get()->m_oManager.m_vShader[0],
		App::Get()->m_oManager.m_vMesh[2],
		App::Get()->m_oManager.m_vTexture[0]);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);

	ColliderGame* pCollider = oEntity->addComponent<ColliderGame>();
	App::Get()->m_oManager.addCollideEntity(oEntity);
	pCollider->setCollider(oEntity, App::Get()->m_oManager.m_vCollideEntity);
}

void ScriptMenu::update() {

}