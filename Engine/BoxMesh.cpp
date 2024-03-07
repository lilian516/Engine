#include "BoxMesh.h"

BoxMesh::BoxMesh() {

}

BoxMesh::~BoxMesh() {

}

void BoxMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(-0.5, 0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,0) }),//0
		Vertex({ XMFLOAT3(0.5, 0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) }),//1
		Vertex({ XMFLOAT3(0.5, -0.5f, -0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//2
		Vertex({ XMFLOAT3(-0.5, -0.5, -0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) }),//3
		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//4
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//5
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//6
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.5f), XMFLOAT4(Colors::Black) ,XMFLOAT2(0,0)}),//7

	};
	m_mMesh.oBox.pCenter = { 0.0f,0.0f,0.0f,0.0f };
	m_mMesh.oBox.vRadius = { 0.5f,0.5f,0.5f,0.0f };
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
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}