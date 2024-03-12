#include "Skybox.h"

Skybox::Skybox() {

}

Skybox::~Skybox() {

}

void Skybox::buildGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(-500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,0) }),//0
		Vertex({ XMFLOAT3(500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//1
		Vertex({ XMFLOAT3(500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) }),//2
		Vertex({ XMFLOAT3(-500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//3

		Vertex({ XMFLOAT3(-500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,0) }),//4
		Vertex({ XMFLOAT3(-500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//5
		Vertex({ XMFLOAT3(-500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//6
		Vertex({ XMFLOAT3(-500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//7

		Vertex({ XMFLOAT3(-500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black), XMFLOAT2(0,0)}),//8
		Vertex({ XMFLOAT3(500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black), XMFLOAT2(0,1)}),//9
		Vertex({ XMFLOAT3(500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black), XMFLOAT2(1,1)}),//10
		Vertex({ XMFLOAT3(-500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black), XMFLOAT2(1,0)}),//11

		Vertex({ XMFLOAT3(500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,0) }),//12
		Vertex({ XMFLOAT3(500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//13
		Vertex({ XMFLOAT3(500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) }),//14
		Vertex({ XMFLOAT3(500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,0)}),//15

		Vertex({ XMFLOAT3(-500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,0) }),//16
		Vertex({ XMFLOAT3(-500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//17
		Vertex({ XMFLOAT3(500.0f, 500.0f, -500.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//18
		Vertex({ XMFLOAT3(500.0f, 500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//19

		Vertex({ XMFLOAT3(-500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,0) }),//20
		Vertex({ XMFLOAT3(-500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//21
		Vertex({ XMFLOAT3(500.0f, -500.0f, -500.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//22
		Vertex({ XMFLOAT3(500.0f, -500.0f, 500.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//23

	};
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// front face
		 0, 2, 1,
		 2, 0, 3,

		 //// left face
		 6, 4, 5,
		 4, 6, 7,

		 //// back face
		 9, 11, 10,
		 11, 9, 8,

		 //////// right face
		 14, 12, 13,
		 12, 14, 15,

		 //////// top face
		 18, 16, 17,
		 16, 18, 19,

		 //////// bottom face
		 20, 22, 21,
		 22, 20, 23,
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}
