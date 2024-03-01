#include "pch.h"
#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::initCamera(Entity *oEntity) {
    initComponent(0, *oEntity);
    XMVECTOR position = XMVectorSet(m_fPosition.x, m_fPosition.y, m_fPosition.z, 0.0f);
    XMVECTOR lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMStoreFloat4x4(&m_mViewMatrix, XMMatrixLookAtLH(position, lookAt, up));
}

void Camera::update() {
    m_yaw += m_fMouseX * m_fRotationSpeed;
    m_pitch += m_fMouseY * m_fRotationSpeed;

    // Update the view matrix
    m_tTransform.rotate(m_pitch, 0.0f, m_yaw);
    m_tTransform.updateTransform();
    XMMATRIX rotation = XMLoadFloat4x4(&m_tTransform.m_mRotation);
    XMVECTOR position = XMVectorSet(m_fPosition.x, m_fPosition.y, m_fPosition.z, 0.0f);
    XMVECTOR direction = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotation);
    XMVECTOR up = XMVector3TransformCoord(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
    XMVECTOR target = position + direction;
    XMStoreFloat4x4(&m_mViewMatrix, XMMatrixLookAtLH(position, target, up));

}