#include "PyramidMesh.h"

PyramidMesh::PyramidMesh() {

}

PyramidMesh::~PyramidMesh() {

}

void PyramidMesh::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White) }),//0
		Vertex({ XMFLOAT3(0.0f, -0.5f, -0.5f), XMFLOAT4(Colors::White) }),//1
		Vertex({ XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT4(Colors::White) }),//2
		Vertex({ XMFLOAT3(0.0f, -0.5f, 0.5f), XMFLOAT4(Colors::White) }),//3
		Vertex({ XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(Colors::Blue) }),//4

	};
	m_mMesh.oBox.pCenter = { 0.0f,0.0f,0.0f,0.0f };
	m_mMesh.oBox.vRadius = { 0.5f,0.5f,0.5f,0.0f };
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// right front face
		1, 4, 0,
		// left front face
		2, 4, 1,
		// right back face
		3, 4, 2,
		// left back face
		0, 4, 3,

		// bottom face
		2, 1, 0,
		0, 3, 2
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}