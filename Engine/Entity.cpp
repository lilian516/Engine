#include "Entity.h"
#include "Component.h"
#include "Graphics.h"
#include "Transform.h"
Entity::Entity() {

}

void Entity::initEntity() {
	
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

void Entity::move(float fDeltaTime, float fSpeed) {
	float fSpeedTime = fDeltaTime * fSpeed;
	XMVECTOR vDirection = XMLoadFloat4(&m_tTransform.m_vDirection);
	vDirection = vDirection * fSpeedTime;
	XMFLOAT3 fDirection;
	XMStoreFloat3(&fDirection, vDirection);

	m_tTransform.translation(fDirection);
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

Entity::~Entity() {
	for (Component* ptr : m_vComponents) {
		// Libérer la mémoire allouée pour chaque pointeur
		delete ptr;
	}

	// Effacer tous les éléments du vecteur
	m_vComponents.clear();
}