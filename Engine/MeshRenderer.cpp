#include "MeshRenderer.h"


MeshRenderer::MeshRenderer() {


}

MeshRenderer::~MeshRenderer() {

}
void MeshRenderer::update() {

}

void MeshRenderer::SetMeshRenderer(Entity *oEntity) {
	initComponent(3, *oEntity);
}