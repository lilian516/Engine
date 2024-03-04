#include "pch.h"
#include "RectangleMesh.h"

RectangleMesh::RectangleMesh() {

}

RectangleMesh::~RectangleMesh() {

}

void RectangleMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
    std::vector<Vertex> vertices =
    {
        Vertex({ XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT4(Colors::Red) }),//0
        Vertex({ XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT4(Colors::Red) }),//1
        Vertex({ XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT4(Colors::Red) }),//2
        Vertex({ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT4(Colors::Red) }),//3
        //Vertex({ XMFLOAT3(-0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//4
        //Vertex({ XMFLOAT3(0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//5
        //Vertex({ XMFLOAT3(0.5, -0.5f, 1.0f), XMFLOAT4(Colors::Black) }),//6
        //Vertex({ XMFLOAT3(-0.5, -0.5, 1.0f), XMFLOAT4(Colors::Black) }),//7

    };
    m_mMesh.vertices = std::move(vertices);

    std::vector<std::uint16_t> indices =
    {
        // front face
        0, 1, 2,
        2, 3, 0,

        //// back face
        //4, 5, 6,
        //6, 7, 4,

        ////// left face
        //4, 0, 3,
        //3, 7, 4,

        ////////// right face
        //1, 5, 6,
        //6, 2, 1,

        ////////// top face
        //4, 5, 1,
        //1, 0, 4,

        ////////// bottom face
        //7, 6, 2,
        //2, 3, 7,
    };
    m_mMesh.indices = std::move(indices);
    uploadMeshToBuffers(m_mMesh, device, commandList);
}
