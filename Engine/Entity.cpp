#include "Entity.h"
#include "Component.h"
#include "Graphics.h"
#include "Transform.h"
Entity::Entity() {

}

Entity::~Entity() {
	while (m_vComponents.size() != 0) {
		delete m_vComponents.back();
		m_vComponents.pop_back();
	}
}

void Entity::initEntity() {
	//m_tTranform = new Transform();
	m_tTransform.identify();

}

void Entity::addComponents(Component* cComponent) {
	m_vComponents.push_back(cComponent);
}

vector<Component*> Entity::getVectorComponents() {
	return m_vComponents;
}

void Entity::SRT() {

}

void Entity::update() {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->update();
	}

}

void Entity::translate(XMFLOAT3 vTranslation) {
	m_tTransform.translation(vTranslation);
	m_tTransform.updateTransform();
	m_aBox.pCenter = m_tTransform.m_vPosition;
}

void Entity::rotate(float pitch, float roll, float yaw) {
	m_tTransform.rotate(pitch, roll, yaw);
	m_tTransform.updateTransform();
}

void Entity::scale(XMFLOAT3 ratio) {
	m_tTransform.scale(ratio);
	m_tTransform.updateTransform();
	XMVECTOR vScale = XMLoadFloat3(&m_tTransform.m_vScaling);
	XMVECTOR vRadius = XMLoadFloat3(&m_aBox.vRadius);
	vRadius *= vScale;
	XMStoreFloat3(&m_aBox.vRadius, vRadius);
}

void Entity::render(Graphics* oGraphics) {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->render(oGraphics);

	}
}

Transform& Entity::getTransform() {
	return m_tTransform;
}