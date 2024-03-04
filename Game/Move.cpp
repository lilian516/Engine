#include "Move.h"

Move::Move() {

}

void Move::update() {
	XMFLOAT4 vect = { 0.0f,0.0f,0.001f,0.0f };
	m_oEntity->m_tTransform.translation(vect);
	m_oEntity->m_tTransform.updateTransform();
	
}
