#include "PenMesh.h"

PenMesh::PenMesh() {

}

PenMesh::~PenMesh() {

}

void PenMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		 Vertex({ XMFLOAT3(-0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//0
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//1
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.0f), XMFLOAT4(Colors::Black) }),//2
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.0f), XMFLOAT4(Colors::Black) }),//3
		Vertex({ XMFLOAT3(-0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//4
		Vertex({ XMFLOAT3(0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//5
		Vertex({ XMFLOAT3(0.5, -0.5f, 1.0f), XMFLOAT4(Colors::Black) }),//6
		Vertex({ XMFLOAT3(-0.5, -0.5, 1.0f), XMFLOAT4(Colors::Black) }),//7
		Vertex({ XMFLOAT3(0.0, 1.5f, 0.5f), XMFLOAT4(Colors::Blue) }),//8

	};
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
        // front face
        0, 1, 2,
        2, 3, 0,

        //// back face
        6, 5, 4,
        4, 7, 6,

        //// left face
        4, 0, 3,
        3, 7, 4,

        //////// right face
        1, 5, 6,
        6, 2, 1,

        //////// top face
        4, 5, 1,
        1, 0, 4,

        //////// bottom face
        2, 6, 7,
        7, 3, 2,

        0, 8, 1,
        5, 8, 4,

        4, 8, 0,
        1, 8, 5,
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}
