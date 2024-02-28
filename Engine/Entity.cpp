#include "Entity.h"

Entity::Entity() {

}

void Entity::initEntity() {
	m_tTranform = new Transform();
	m_tTranform->Identify();

}

void Entity::AddComponents(Component* cComponent) {
	m_vComponents.push_back(cComponent);

vector<Component*> Entity::GetVectorComponents() {
	return vComponents;
}

void Entity::SRT() {
	
}

void Entity::update() {

}

void Entity::render() {

}
