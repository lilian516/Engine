#include "Entity.h"

Entity::Entity() {

}

void Entity::AddComponents(Component* cComponent) {
	vComponents.push_back(cComponent);
}

vector<Component*> Entity::GetVectorComponents() {
	return vComponents;
}

void Entity::SRT() {
	
}

void Entity::update() {

}

void Entity::render() {

}
