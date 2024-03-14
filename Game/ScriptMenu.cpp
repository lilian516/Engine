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

	// bouton start
	m_pButtonStart = App::Get()->m_oManager.createEntity();
	Shader* pShader = App::Get()->m_oManager.createShader();
	Texture* pTexture = App::Get()->m_oManager.createTexture("start",L"Texture/start.dds");
	Sprite* pSprite = App::Get()->m_oManager.createMesh<Sprite>();
	MeshRenderer* pMeshRenderer = m_pButtonStart->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(m_pButtonStart, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSprite, pTexture);	
	m_pButtonStart->m_tTransform.translation({0.0f,2.0f,-2.0f});
	m_pButtonStart->m_tTransform.scale({ 1.5f,1.0f,0.0f });

	//affichage menu
	m_pMenu = App::Get()->m_oManager.createEntity();
	Texture* pTextureVaisseau = App::Get()->m_oManager.createTexture("menu", L"Texture/vaisseau.dds");
	MeshRenderer* pMeshRenderer2 = m_pMenu->addComponent<MeshRenderer>();
	pMeshRenderer2->SetMeshRenderer(m_pMenu, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pSprite, pTextureVaisseau);
	m_pMenu->m_tTransform.translation({ 0.0f,2.5f,-1.0f });
	m_pMenu->m_tTransform.scale({ 7.5f,7.5f,0.0f });

}

void ScriptMenu::update() {
	if (App::Get()->m_oManager.m_oInputManager.isKey(13)) {
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
