#include "ScriptLoose.h"

ScriptLoose::ScriptLoose() {

}

void ScriptLoose::initScriptLoose(Entity* oEntity) {
	setScript(oEntity);
	m_pButtonLoose = App::Get()->m_oManager.createEntity();
	Texture* pTexture = App::Get()->m_oManager.createTexture("start", L"Texture/start.dds");
	MeshRenderer* pMeshRenderer = m_pButtonLoose->addComponent<MeshRenderer>();
	pMeshRenderer->SetMeshRenderer(m_pButtonLoose, App::Get()->m_oManager.m_oGraphics.m_d3dDevice, 
		App::Get()->m_oManager.m_vShader[0], App::Get()->m_oManager.m_vMesh[0], pTexture);
	m_pButtonLoose->translate({900,900,900});
}

void ScriptLoose::update() {

}