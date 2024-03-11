#include "BoxMesh.h"

BoxMesh::BoxMesh() {

}

BoxMesh::~BoxMesh() {

}

void BoxMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(-0.5, 0.5f, -0.5f), XMFLOAT4(m_cColor) }),//0
		Vertex({ XMFLOAT3(0.5, 0.5f, -0.5f), XMFLOAT4(m_cColor) }),//1
		Vertex({ XMFLOAT3(0.5, -0.5f, -0.5f), XMFLOAT4(m_cColor) }),//2
		Vertex({ XMFLOAT3(-0.5, -0.5, -0.5f), XMFLOAT4(m_cColor) }),//3
		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.5f), XMFLOAT4(m_cColor) }),//4
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.5f), XMFLOAT4(m_cColor) }),//5
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.5f), XMFLOAT4(m_cColor) }),//6
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.5f), XMFLOAT4(m_cColor) }),//7

	};
	m_mMesh.oBox.pCenter = { 0.0f,0.0f,0.0f };
	m_mMesh.oBox.vRadius = { 0.5f,0.5f,0.5f };
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// front face
		0, 1, 2,
		2, 3, 0,

		//// back face
		4, 5, 6,
		6, 7, 4,

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
		7, 6, 2,
		2, 3, 7,
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}