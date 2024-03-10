#include "Camera.h"
#include "Component.h"
Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::initCamera(Entity* oEntity,float aspectRatio) {
    initComponent(9, oEntity);
    camTransform = &oEntity->m_tTransform;
    m_vUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_fRotationSpeed = 0.1f;
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1000.0f;
    m_mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_mMatrixProj, m_mProjMatrix);
}

void Camera::update() {
   
}

void Camera::updateMatrix() {
    m_mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_mMatrixProj, m_mProjMatrix);
}

void Camera::change() {

    m_vTarget = m_vPosition + m_vForward; // Calculez le point que la caméra regarde

    //Si crash ici, m_Target doit etre différent de 0
    m_mViewMatrix = XMMatrixLookAtLH(m_vPosition, m_vTarget, m_vUp);
    XMStoreFloat4x4(&m_mMatrixView, m_mViewMatrix);
}

void Camera::changePos() {
    m_vPosition = XMVectorSet(camTransform->m_vPosition.x, camTransform->m_vPosition.y, camTransform->m_vPosition.z, 1.0f);
    change();
}

XMFLOAT4X4* Camera::getViewMatrix() {
    return &m_mMatrixView;
}
XMFLOAT4X4* Camera::getProjMatrix() {
    return &m_mMatrixProj;
}