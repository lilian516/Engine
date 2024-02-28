#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {

}

void MeshRenderer::SetMeshRenderer(Entity *oEntity, ID3D12Device* device) {
	initComponent(3, *oEntity);
	

	
}