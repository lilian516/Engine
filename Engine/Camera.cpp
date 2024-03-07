#include "Camera.h"
Camera::Camera() {

}

Camera::~Camera() {

}

void Camera::initCamera(Entity *oEntity, HWND *hWnd) {
    initComponent(0, oEntity);
    XMVECTOR position = XMVectorSet(m_fPosition.x, m_fPosition.y, m_fPosition.z, 0.0f);
    XMVECTOR lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMStoreFloat4x4(&m_mViewMatrix, XMMatrixLookAtLH(position, lookAt, up));
    m_fRotationSpeed = 0.1f;
    m_hWnd = hWnd;
    RECT rClientRect;
    if (GetClientRect(*m_hWnd, &rClientRect)) {
        // Calculate the center of the client area
        m_pCenter.x = rClientRect.left + (rClientRect.right - rClientRect.left) / 2;
        m_pCenter.y = rClientRect.top + (rClientRect.bottom - rClientRect.top) / 2;
    }
}

void Camera::update() {
    if ((ClientToScreen(*m_hWnd, &m_pCenter))) {
        m_yaw += m_fMouseX * m_fRotationSpeed;
        m_pitch += m_fMouseY * m_fRotationSpeed;

        // Update the view matrix
        m_oEntity->m_tTransform.rotate(m_pitch, 0.0f, m_yaw);
        m_oEntity->m_tTransform.updateTransform();
        XMMATRIX rotation = XMLoadFloat4x4(&m_oEntity->m_tTransform.m_mRotation);
        XMVECTOR position = XMVectorSet(m_fPosition.x, m_fPosition.y, m_fPosition.z, 0.0f);
        XMVECTOR direction = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotation);
        XMVECTOR up = XMVector3TransformCoord(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
        XMVECTOR target = position + direction;
        XMStoreFloat4x4(&m_mViewMatrix, XMMatrixLookAtLH(position, target, up));
    }
}

void Camera::updateMatrix() {
    m_mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_MatrixProj, m_ProjMatrix);
}

XMFLOAT4X4* Camera::getViewMatrix() {
    return &m_mViewMatrix;
}