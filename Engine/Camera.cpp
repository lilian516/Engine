#include "Camera.h"
#include "Component.h"
Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::initCamera(Entity* oEntity,float aspectRatio, ID3D12Device* device) {
    initComponent(9, oEntity);
    camTransform = &oEntity->m_tTransform;
    //m_vUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_fRotationSpeed = 0.1f;
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1000.0f;
    m_mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_mMatrixProj, m_mProjMatrix);

    m_uCamCB = new UploadBuffer<ObjectConstants>(device, 1, true);
}

void Camera::update() {
    //XMMATRIX world = XMLoadFloat4x4(m_oEntity->getTransform().m_mTransform);
    XMMATRIX proj = XMLoadFloat4x4(getProjMatrix());
   XMFLOAT4 pos(0.0f, 0.0f, -0.01f, 0.0f);
   //m_oEntity->getTransform().identify();
   m_oEntity->getTransform().translation(pos);
   m_oEntity->getTransform().updateTransform();
    XMMATRIX view = XMLoadFloat4x4(&m_oEntity->getTransform().m_mTransform);
    view = XMMatrixInverse(nullptr, view);
    XMMATRIX viewProj;
    viewProj = view * proj;
    XMFLOAT4X4 m_fViewProj;
    XMStoreFloat4x4(&m_fViewProj, viewProj);

    ObjectConstants data;
    data.WorldViewProj = m_fViewProj;
    m_uCamCB->CopyData(0, data);
    updateMatrix();
    
}

void Camera::updateMatrix() {
    m_mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_mMatrixProj, m_mProjMatrix);
}

void Camera::change() {

    XMVECTOR pos = XMLoadFloat4(&m_oEntity->getTransform().m_vPosition);
    XMVECTOR dir = XMLoadFloat4(&m_oEntity->getTransform().m_vDirection);
    XMVECTOR up = XMLoadFloat4(&m_oEntity->getTransform().m_vUp);
    //m_vTarget = pos + dir; // Calculez le point que la cam�ra regarde

    //Si crash ici, m_Target doit etre diff�rent de 0
    //m_oEntity->getTransform().m_mTransform = XMMatrixLookAtLH(pos, m_vTarget, up);
}

void Camera::changePos() {
    XMVECTOR pos = XMLoadFloat4(&m_oEntity->getTransform().m_vPosition);
    pos = XMVectorSet(camTransform->m_vPosition.x, camTransform->m_vPosition.y, camTransform->m_vPosition.z, 1.0f);
    XMStoreFloat4(&m_oEntity->getTransform().m_vPosition, pos);
    change();
}


XMFLOAT4X4* Camera::getProjMatrix() {
    return &m_mMatrixProj;
}