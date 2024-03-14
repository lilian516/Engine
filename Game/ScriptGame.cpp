#include "ScriptGame.h"
#include "App.h"
#include "framework.h"
#include "ScriptProjectile.h"
#include "ScriptEnemy.h"
#include "ScriptMenu.h"
ScriptGame::ScriptGame() {

}

void ScriptGame::initGame(Entity* oEntity) {
	setScript(oEntity);
	ShowCursor(FALSE);

	//création de la caméra
	App::Get()->m_oManager.m_oGraphics.createCam();
	App::Get()->m_oManager.addEntity(App::Get()->m_oManager.m_oGraphics.m_oCamEntity);

	PyramidMesh* pPyramid = App::Get()->m_oManager.createMesh<PyramidMesh>();
	PenMesh* pPen = App::Get()->m_oManager.createMesh<PenMesh>();
	BoxMesh* pBox = App::Get()->m_oManager.createMesh<BoxMesh>();
	
	Texture* pTextureLaser = App::Get()->m_oManager.createTexture("laser",L"Texture/Laser2.dds");
	Texture* pTextureEnemy = App::Get()->m_oManager.createTexture("enemy", L"Texture/Enemy.dds");

	/// création de la Skybox
	Skybox* pSky = App::Get()->m_oManager.createMesh<Skybox>();
	Texture* pTextureSkybox = App::Get()->m_oManager.createTexture("sky", L"Texture/sky.dds");
	Entity* pCubeSky = App::Get()->m_oManager.createEntity();
	MeshRenderer* pMeshRendererSky = pCubeSky->addComponent<MeshRenderer>();
	pCubeSky->scale({ 800.0f,800.0f,800.0f });
	pMeshRendererSky->SetMeshRenderer(pCubeSky, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, App::Get()->m_oManager.m_vShader[0], pSky, pTextureSkybox);
	
	m_bSetCursor = true;

	
}

void ScriptGame::update() {
	
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		createProjectile();
		
	}
	if (App::Get()->m_oManager.m_oTimer.m_fDifflTime  > 5.0f) {
		createEnemy();
		App::Get()->m_oManager.m_oTimer.m_fDifflTime = 0.0f;
	}

	inputCamera();

	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(27)) {
		ShowCursor(TRUE);
		m_bSetCursor = false;
	}

	if (m_bSetCursor) {
		setCursorPos();
	}

	
}

void ScriptGame::createProjectile() {
	Entity* pProjectile = App::Get()->m_oManager.createEntity();

	ScriptProjectile* pScript = pProjectile->addComponent<ScriptProjectile>();
	pScript->initProjectile(pProjectile);
}

void ScriptGame::createEnemy() {
	Entity* pEnemy = App::Get()->m_oManager.createEntity();

	ScriptEnemy* pScript = pEnemy->addComponent<ScriptEnemy>();
	pScript->initEnemy(pEnemy);
}

void ScriptGame::inputCamera() {
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX < 0) {  //gauche
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(),270,0.0f, 0.0f, XMConvertToRadians(-0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY > 0) { // bas

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 270, XMConvertToRadians(0.5f), 0.0f, 0.0f);

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaX > 0) {  //droite

		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 270, 0.0f, 0.0f, XMConvertToRadians(0.5f));

	}
	if (App::Get()->m_oManager.m_oInputManager.m_iDeltaY < 0) {  //haut
		App::Get()->m_oManager.m_oGraphics.m_oCamEntity->rotate(App::Get()->m_oManager.m_oTimer.getDeltaTime(), 270, XMConvertToRadians(-0.5f), 0.0f, 0.0f);
	}
}

void ScriptGame::setCursorPos() {
	SetCursorPos(App::Get()->m_oManager.m_oGraphics.m_iClientWidth / 2, App::Get()->m_oManager.m_oGraphics.m_iClientHeight / 2);
	App::Get()->m_oManager.m_oInputManager.m_pLastMousePos.x = App::Get()->m_oManager.m_oGraphics.m_iClientWidth / 2;
	App::Get()->m_oManager.m_oInputManager.m_pLastMousePos.y = App::Get()->m_oManager.m_oGraphics.m_iClientHeight / 2;
}

