#include "Entity.h"
#include "Component.h"
#include "Graphics.h"
#include "Transform.h"
Entity::Entity() {

}

void Entity::initEntity() {
	//m_tTranform = new Transform();
	m_tTransform.identify();

}

void Entity::AddComponents(Component* cComponent) {
	m_vComponents.push_back(cComponent);
}

vector<Component*> Entity::GetVectorComponents() {
	return m_vComponents;
}

void Entity::SRT() {
	
}

void Entity::update() {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->update();
	}
	
}

void Entity::render(Graphics* oGraphics) {
	for (int i = 0; i < m_vComponents.size(); i++) {
		m_vComponents[i]->render(oGraphics);

	}
}

Transform& Entity::getTransform() {
	return m_tTransform;
}