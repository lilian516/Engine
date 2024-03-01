#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {
	m_oEntity.m_tTranform->rotate( 0.0f, 0.0f, XM_PI / 3.0f);
	m_oEntity.m_tTranform->updateTransform();
}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device) {
	initComponent(3, *oEntity);
	

	
}