#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::SetCamera(Entity *oEntity) {
	initComponent(0, *oEntity);
}