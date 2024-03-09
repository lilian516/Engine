#include "ScriptGame.h"
#include "App.h"
#include "framework.h"
#include "ScriptProjectile.h"
ScriptGame::ScriptGame() {

}

void ScriptGame::initGame(Entity* oEntity) {
	setScript(oEntity);
	Entity* pCube = App::Get()->m_oManager.createEntity();
	Shader* pShader = App::Get()->m_oManager.createShader();
	Texture* pTexture = App::Get()->m_oManager.createTexture("test",L"Texture/image.dds");
	Sprite* pMesh = App::Get()->m_oManager.createMesh<Sprite>();
	PyramidMesh* pPyramid = App::Get()->m_oManager.createMesh<PyramidMesh>();
	MeshRenderer* pMeshRenderer = pCube->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(pCube, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, pShader, pMesh, pTexture);
	pMeshRenderer->buildConstantBuffers(App::Get()->m_oManager.m_oGraphics.m_d3dDevice, App::Get()->m_oManager.m_oGraphics.m_dConstantBufferViewHeapDescriptor);
}

void ScriptGame::update() {

	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(1)) {
		createProjectile();
	}
	if (App::Get()->m_oManager.m_oInputManager.isKeyDown(2)) {
		App::Get()->m_oManager.m_vEntity.pop_back();
	}
}

void ScriptGame::createProjectile() {
	Entity* pProjectile = App::Get()->m_oManager.createEntity();

	ScriptProjectile* pScript = pProjectile->addComponent<ScriptProjectile>();
	pScript->initProjectile(pProjectile);
}