#include "Component.h"

Component::Component() {

}

void Component::initComponent(int iId, Entity* oEntity) {
	m_iId = iId;
	m_oEntity = oEntity;

}

void Component::update() {

}

void Component::render(Graphics* oGraphics, XMFLOAT4X4* mWorldViewProj) {

}

int Component::getId() {
	return m_iId;
}


