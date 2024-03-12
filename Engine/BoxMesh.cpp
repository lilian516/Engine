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

		Vertex({ XMFLOAT3(-0.5, 0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,0) }),//4
		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) }),//5
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.5f), XMFLOAT4(Colors::Black) ,XMFLOAT2(0,1)}),//6
		Vertex({ XMFLOAT3(-0.5, -0.5f, -0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) }),//7

		Vertex({ XMFLOAT3(-0.5, -0.5f, 0.5f), XMFLOAT4(Colors::White), XMFLOAT2(0,1)}),//8
		Vertex({ XMFLOAT3(0.5, -0.5, 0.5f), XMFLOAT4(Colors::White), XMFLOAT2(1,1)}),//9
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.5f), XMFLOAT4(Colors::Black), XMFLOAT2(1,0)}),//10
		Vertex({ XMFLOAT3(-0.5, 0.5, 0.5f), XMFLOAT4(Colors::Black), XMFLOAT2(0,0)}),//11

		Vertex({ XMFLOAT3(0.5, 0.5, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(1,0) }),//12
		Vertex({ XMFLOAT3(0.5, 0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) }),//13
		Vertex({ XMFLOAT3(0.5, -0.5f, -0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(0,1) }),//14
		Vertex({ XMFLOAT3(0.5, -0.5, 0.5f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//15

		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) }),//16
		Vertex({ XMFLOAT3(-0.5, 0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//17
		Vertex({ XMFLOAT3(0.5, 0.5, -0.5f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//18
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//19

		Vertex({ XMFLOAT3(-0.5, -0.5f, 0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) }),//20
		Vertex({ XMFLOAT3(-0.5, -0.5f, -0.5f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) }),//21
		Vertex({ XMFLOAT3(0.5, -0.5, -0.5f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1)}),//22
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.5f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) }),//23

	};
	m_mMesh.vertices = std::move(vertices);

	std::vector<std::uint16_t> indices =
	{
		// front face
		 0, 1, 2,
		 2, 3, 0,

		 //// left face
		 6, 5, 4,
		 4, 7, 6,

		 //// back face
		 9, 10, 11,
		 11, 8, 9,

		 //////// right face
		 14, 13, 12,
		 12, 15, 14,

		 //////// top face
		 18, 17, 16,
		 16, 19, 18,

		 //////// bottom face
		 20, 21, 22,
		 22, 23, 20,
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh, device, commandList);
}