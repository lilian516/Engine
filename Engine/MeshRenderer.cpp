#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {

}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device) {
	initComponent(3, *oEntity);
	m_oMesh = new Mesh();
	m_oMesh->init(device);
	m_oShader = new Shader();

	m_oShader->initializeRootSignature(device);
	m_oShader->initializeShader();
	m_oMesh->buildBoxGeometry();
	m_oShader->initializePipelineState(device);
}