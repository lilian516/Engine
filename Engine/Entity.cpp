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

void Entity::move(float fDeltaTime, float fSpeed, XMVECTOR vDir) {
	float fSpeedTime = fDeltaTime * fSpeed;
	//XMVECTOR vDirection = XMLoadFloat4(&m_tTransform.m_vDirection);
	XMVECTOR vDirection = vDir * fSpeedTime;
	XMFLOAT3 fDirection;
	XMStoreFloat3(&fDirection, vDirection);

	translate(fDirection);
	
}

void Entity::translate(XMFLOAT3 vDir) {
	m_tTransform.translation(vDir);
	m_tTransform.updateTransform();
	m_aBox.pCenter = m_tTransform.m_vPosition;
}

void Entity::rotate(float fDeltaTime, float fSpeed, float pitch, float roll, float yaw) {
	float fpitch = fDeltaTime * fSpeed * pitch;
	float froll = fDeltaTime * fSpeed * roll;
	float fyaw = fDeltaTime * fSpeed * yaw;

	m_tTransform.rotate(fpitch, froll, fyaw);
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
		// Lib�rer la m�moire allou�e pour chaque pointeur
		delete ptr;
	}

	// Effacer tous les �l�ments du vecteur
	m_vComponents.clear();
}