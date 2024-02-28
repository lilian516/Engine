#include "Component.h"

Component::Component() {

}

void Component::setComponent(int iId) {
	m_iId = iId;
}

void Component::update() {

}

void Component::render() {

}

int Component::GetId() {
	return m_iId;
}
