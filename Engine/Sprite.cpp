#include "Sprite.h"
#include <string>



Sprite::Sprite() {

}

Sprite::~Sprite() {

}

void Sprite::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//0
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//1
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.0f), XMFLOAT4(Colors::Black) }),//2
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.0f), XMFLOAT4(Colors::Black) }),//3
	};
		m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// front face
		0, 1, 2,
		2, 3, 0,
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}

