#include "Entity.h"
#include "Component.h"
#include "Graphics.h"
#include "Transform.h"
#include "Camera.h"
Entity::Entity() {

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

void Entity::updateBox() {
	m_aBox.pCenter = m_tTransform.m_vPosition;
	XMVECTOR vRadius = XMLoadFloat4(&m_aBox.vRadius);
	XMVECTOR vScaling = XMLoadFloat4(&m_tTransform.m_vScaling);
	vRadius *= vScaling;
	XMStoreFloat4(&m_aBox.vRadius,vRadius);
}

void Entity::update() {
	updateBox();
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->update();
	}
	
	
}

void Entity::translate(XMFLOAT4 vTranslation) {
	m_tTransform.translation(vTranslation);
	m_tTransform.updateTransform();
	m_aBox.pCenter = m_tTransform.m_vPosition;
}

void Entity::rotate(float pitch, float roll, float yaw){
	m_tTransform.rotate(pitch, roll, yaw);
	m_tTransform.updateTransform();
}

void Entity::scale(XMFLOAT3 ratio) {
	m_tTransform.scale(ratio);
	m_tTransform.updateTransform();
	XMVECTOR vScale = XMLoadFloat4(&m_tTransform.m_vScaling);
	XMVECTOR vRadius = XMLoadFloat4(&m_aBox.vRadius);
	vRadius *= vScale;
	XMStoreFloat4(&m_aBox.vRadius, vRadius);
}

void Entity::render(Graphics* oGraphics, XMFLOAT4X4* mWorldViewProj) {
	temporaire();
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->render(oGraphics, mWorldViewProj);

	}
	
}

Transform& Entity::getTransform() {
	return m_tTransform;
}

void Entity::temporaire() {
	//Convert Spherical to Cartesian coordinates.
	float x = m_fRadius * sinf(m_fPhi) * cosf(m_fTheta);
	float z = m_fRadius * sinf(m_fPhi) * sinf(m_fTheta);
	float y = m_fRadius * cosf(m_fPhi);

	// Build the view matrix.
	XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX view;
	XMFLOAT4X4 viewTemp = Identity4x4();
	view = XMLoadFloat4x4(&viewTemp);

	for (int i = 0; i < m_vComponents.size(); i++) {
		if (dynamic_cast<Camera*>(m_vComponents[i])) {
			Camera* camera = dynamic_cast<Camera*>(m_vComponents[i]);
			view = XMLoadFloat4x4(camera->getViewMatrix()) ;
		}
	}

	XMMATRIX world = XMLoadFloat4x4(&m_tTransform.m_mTransform);
	XMMATRIX proj = XMLoadFloat4x4(&m_fProj);
	XMMATRIX WorldViewProj = world * view * proj;
	XMStoreFloat4x4(&m_mWorldViewProj, WorldViewProj);
	
	// Update the constant buffer with the latest worldViewProj matrix.

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, static_cast<float>(800) / 600, 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_fProj, P);
}

XMFLOAT4X4* Entity::getWorldViewProj() {
	return &m_mWorldViewProj;
}