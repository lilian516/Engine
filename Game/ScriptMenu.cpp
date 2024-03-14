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

	// boutton start
	m_pButtonStart = App::Get()->m_oManager.createEntity();
	Shader* pShader = App::Get()->m_oManager.createShader();
	Texture* pTexture = App::Get()->m_oManager.createTexture("start",L"Texture/start.dds");
	Sprite* pSprite = App::Get()->m_oManager.createMesh<Sprite>();
	MeshRenderer* pMeshRenderer = m_pButtonStart->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(m_pButtonStart, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSprite, pTexture);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	m_pButtonStart->m_tTransform.translation({0.0f,2.0f,-2.0f});
	m_pButtonStart->m_tTransform.scale({ 1.5f,1.0f,0.0f });



	m_pMenu = App::Get()->m_oManager.createEntity();
	Texture* pTextureVaisseau = App::Get()->m_oManager.createTexture("menu", L"Texture/vaisseau.dds");
	MeshRenderer* pMeshRenderer2 = m_pMenu->addComponent<MeshRenderer>();
	pMeshRenderer2->SetMeshRenderer(m_pMenu, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSprite, pTextureVaisseau);
	pMeshRenderer2->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice);
	m_pMenu->m_tTransform.translation({ 0.0f,2.5f,-1.0f });
	m_pMenu->m_tTransform.scale({ 7.5f,7.5f,0.0f });
	/*std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<> distr(10.0f, 20.0f);
	double x = distr(eng);
	double y = distr(eng);
	double z = distr(eng);

	XMFLOAT3 vect{ float(x),float(y),float(z) };
	oEntity->m_tTransform.translation(vect);*/
	
}

void ScriptMenu::update() {
	//if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
	//	POINT cursorPos;
	//	GetCursorPos(&cursorPos);

	//	createProjectile();

	//}
	//if (App::Get()->m_oManager.m_oTimer.m_fDifflTime > 5.0f) {
	//	App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	//}

	///*if (App::Get()->m_oManager.m_oInputManager.isKey(65)) {

	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({0.0f,0.0f,0.001f});

	//}*/
	//if (App::Get()->m_oManager.m_oInputManager.isKey(81)) {  //gauche
	//	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ -0.005f,0.0f,0.0f });
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(-0.5f));

	//}
	//if (App::Get()->m_oManager.m_oInputManager.isKey(83)) { // bas

	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(0.5f), 0.0f, 0.0f);

	//}
	//if (App::Get()->m_oManager.m_oInputManager.isKey(68)) {  //droite
	//	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.translation({ 0.005f,0.0f,0.0f });
	//	//App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-10.f), 0.0f, 0.0f);
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(0.0f, 0.0f, XMConvertToRadians(0.5f));

	//}
	//if (App::Get()->m_oManager.m_oInputManager.isKey(90)) {  //haut
	//	App::Get()->m_oManager.m_oGraphics.m_oCamEntity->m_tTransform.rotate(XMConvertToRadians(-0.5f), 0.0f, 0.0f);


	//}
	if (App::Get()->m_oManager.m_oInputManager.isKey(65)) {
		App::Get()->m_oManager.deleteEntity(m_pButtonStart);
		App::Get()->m_oManager.deleteEntity(m_pMenu);
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
