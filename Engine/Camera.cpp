#include "Camera.h"
#include "Component.h"
Camera::Camera() {
}

Camera::~Camera() {
    delete camTransform;
}

void Camera::initCamera(Entity* oEntity,float aspectRatio, ID3D12Device* device) {
    initComponent(4, oEntity);
    camTransform = &oEntity->m_tTransform;
    //m_vUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_fRotationSpeed = 0.1f;
    m_AspectRatio = aspectRatio;
    m_FovAngleY = DirectX::XMConvertToRadians(70.0f);
    m_NearZ = 0.1f;
    m_FarZ = 1500.0f;
    DirectX::XMMATRIX mProjMatrix = DirectX::XMMatrixPerspectiveFovLH(m_FovAngleY, m_AspectRatio, m_NearZ, m_FarZ);

    // Stocker la matrice de projection dans une variable mProj (par exemple)
    XMStoreFloat4x4(&m_mMatrixProj, mProjMatrix);

    m_uCamCB = new UploadBuffer<ObjectConstants>(device, 1, true);
}

void Camera::update() {
    XMMATRIX proj = XMLoadFloat4x4(getProjMatrix());
 

    // Build the view matrix.
    XMVECTOR pos = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    
    XMVECTOR vPosition = XMLoadFloat3(&m_oEntity->getTransform().m_vPosition);
    XMVECTOR target = XMVectorAdd(vPosition, m_oEntity->getTransform().getForwardVector());
    
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);  

    

    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);
   
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
    
}




XMFLOAT4X4* Camera::getProjMatrix() {
    return &m_mMatrixProj;
}

