#include "Camera.h"
#include "Component.h"
Camera::Camera() {
}

Camera::~Camera() {

}

void Camera::initCamera(Entity* oEntity,float aspectRatio, ID3D12Device* device) {
    initComponent(4, oEntity);
    camTransform = &oEntity->m_tTransform;
    //m_vUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_fRotationSpeed = 0.1f;
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1000.0f;
    DirectX::XMMATRIX mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_mMatrixProj, mProjMatrix);

    m_uCamCB = new UploadBuffer<ObjectConstants>(device, 1, true);
}

void Camera::update() {
    XMMATRIX proj = XMLoadFloat4x4(getProjMatrix());
    /*XMFLOAT3 pos(0.0f, 0.0f, -0.01f);
    m_oEntity->getTransform().identify();
    m_oEntity->getTransform().translation(pos);*/
    //m_oEntity->getTransform().updateTransform();


 
    //XMStoreFloat4x4(&m_fView, view);

    /*float x = m_fRadius * sinf(m_fPhi) * cosf(m_fTheta);
    float z = m_fRadius * sinf(m_fPhi) * sinf(m_fTheta);
    float y = m_fRadius * cosf(m_fPhi);*/

    // Build the view matrix.
    XMVECTOR pos = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    //XMVECTOR target = XMLoadFloat4(&m_oEntity->getTransform().m_vDirection);
    XMVECTOR vPosition = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    XMVECTOR target = XMVectorAdd(vPosition, m_oEntity->getTransform().getForwardVector());
    //XMStoreFloat3(&m_oEntity->m_tTransform.m_fTarget, target);
    //XMVECTOR up = XMLoadFloat4(&m_oEntity->getTransform().m_vUp);
    //XMVECTOR target = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);  // lui il bouge pas

    

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
    //XMMATRIX view = XMLoadFloat4x4(&m_oEntity->getTransform().m_mTransform);
   //view = XMMatrixInverse(nullptr, view);

    //XMMATRIX view = XMLoadFloat4x4(&m_oEntity->getTransform().m_mTransform);
    //view = XMMatrixInverse(nullptr, view);
    XMMATRIX viewProj = view * proj;
    XMFLOAT4X4 m_fViewProj;
    XMStoreFloat4x4(&m_fViewProj, XMMatrixTranspose(viewProj));

    ObjectConstants data;
    data.WorldViewProj = m_fViewProj;
    m_uCamCB->CopyData(0, data);
    updateMatrix();
    
}

void Camera::updateMatrix() {
    XMMATRIX mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);
    DirectX::XMStoreFloat4x4(&m_mMatrixProj, mProjMatrix);
    /*XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.14, m_AspectRatio, 1.0f, 1000.0f);
    XMStoreFloat4x4(&m_mMatrixProj, P);*/
}

void Camera::change() {

    XMVECTOR pos = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    XMVECTOR dir = XMLoadFloat4(&m_oEntity->getTransform().m_vDirection);
    XMVECTOR up = XMLoadFloat4(&m_oEntity->getTransform().m_vUp);
    //m_vTarget = pos + dir; // Calculez le point que la caméra regarde

    //Si crash ici, m_Target doit etre différent de 0
    //m_oEntity->getTransform().m_mTransform = XMMatrixLookAtLH(pos, m_vTarget, up);
}

void Camera::changePos() {
    XMVECTOR pos = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    pos = XMVectorSet(camTransform->m_vPosition.x, camTransform->m_vPosition.y, camTransform->m_vPosition.z, 1.0f);
    XMStoreFloat3(&m_oEntity->getTransform().m_vPosition, pos);
    change();
}


XMFLOAT4X4* Camera::getProjMatrix() {
    return &m_mMatrixProj;
}

