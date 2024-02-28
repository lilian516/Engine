#include "Component.h"

Component::Component() {

}

void Component::SetComponent(int id) {
	m_iId = id;
}

int Component::GetId() {
	return m_iId;
}
