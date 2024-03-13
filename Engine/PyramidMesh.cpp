#include "PyramidMesh.h"

PyramidMesh::PyramidMesh() {

}

PyramidMesh::~PyramidMesh() {

}

void PyramidMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1)}),//0
		Vertex({ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,0) }),//1
		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//2
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//3
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(0,0) }),//4



		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//5
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//6
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(1,0) }),//7

	};
	m_mMesh.oBox.pCenter = { 0.0f,0.0f,0.0f };
	m_mMesh.oBox.vRadius = { 0.5f,0.5f,0.5f };
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// right front face
		1, 4, 0,
		// left front face
		2, 4, 1,
		// right back face
		6, 7, 5,
		// left back face
		0, 4, 3,

		// bottom face
		2, 1, 0,
		0, 3, 2
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}