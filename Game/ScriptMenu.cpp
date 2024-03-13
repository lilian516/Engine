#include "ScriptMenu.h"
#include <iomanip>
#include <iostream>
#include <random>

#include "ColliderGame.h"
#include "ScriptProjectile.h"

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
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		createProjectile();

	}
	if (App::Get()->m_oManager.m_oTimer.m_fDifflTime > 5.0f) {
		App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	}

	/*if (App::Get()->m_oManager.m_oInputManager.isKey(65)) {

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({0.0f,0.0f,0.001f});

	}*/
	if (App::Get()->m_oManager.m_oInputManager.isKey(81)) {  //gauche
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ -0.005f,0.0f,0.0f });
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(-0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(83)) { // bas

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(0.5f), 0.0f, 0.0f);

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(68)) {  //droite
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ 0.005f,0.0f,0.0f });
		//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-10.f), 0.0f, 0.0f);
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(90)) {  //haut
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-0.5f), 0.0f, 0.0f);


	}
	if (App::Get()->m_oManager.m_oInputManager.isKey(87)) {
		m_oScriptManager->updateState();
	}
}
void ScriptMenu::createProjectile() {
	Entity* pProjectile = App::Get()->m_oManager.createEntity();

	ScriptProjectile* pScript = pProjectile->addComponent<ScriptProjectile>();
	pScript->initProjectile(pProjectile);
}

void ScriptMenu::setScriptManager(ScriptManager* oScriptManager) {
	m_oScriptManager = oScriptManager;
}
