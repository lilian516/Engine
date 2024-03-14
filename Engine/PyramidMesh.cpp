#include "PyramidMesh.h"

PyramidMesh::PyramidMesh() {

}

PyramidMesh::~PyramidMesh() {

}

void PyramidMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0)}),//0
		Vertex({ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,0) }),//1
		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//2
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//3
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(0,0) }),//4



		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//5
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//6
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(1,0) }),//7

		Vertex({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(1,1)}),//8
		Vertex({ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//9
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(1,0) }),//10

		Vertex({ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//11
		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//12
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(0,0) }),//13

		Vertex({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1)}),//14
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,1) }),//15
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue),XMFLOAT2(0,0) }),//16
	};
	m_mMesh.oBox.pCenter = { 0.0f,0.0f,0.0f };
	m_mMesh.oBox.vRadius = { 0.5f,0.5f,0.5f };
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// right front face
		9, 10, 8,
		// left front face
		12, 13, 11,
		// right back face
		6, 7, 5,
		// left back face
		14, 16, 15,

		// bottom face
		2, 1, 0,
		0, 3, 2
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}