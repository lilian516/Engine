#include "Mesh.h"
#include "Graphics.h"
#include <stdexcept>

using namespace DirectX;


Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::init(ID3D12Device* device) {
	m_d3dDevice = device;
}

void Mesh::uploadMeshToBuffers(MeshData mesh) {

	D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC vertexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mesh.vertices.size() * sizeof(Vertex));
	HRESULT hresult = m_d3dDevice->CreateCommittedResource(&heapProperties,D3D12_HEAP_FLAG_NONE,&vertexBufferDesc,D3D12_RESOURCE_STATE_GENERIC_READ,nullptr,IID_PPV_ARGS(&mesh.vertexBuffer));
	if (FAILED(hresult)) {
		throw std::runtime_error("Failed to create vertex buffer.");
	}

	UINT8* pVertexDataBegin;
	D3D12_RANGE readRange = { 0, 0 };
	hresult = mesh.vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
	if (FAILED(hresult)) {
		throw std::runtime_error("Failed to map vertex buffer.");
	}
	memcpy(pVertexDataBegin, mesh.vertices.data(), mesh.vertices.size() * sizeof(Vertex));
	mesh.vertexBuffer->Unmap(0, nullptr);

	D3D12_RESOURCE_DESC indexBufferDesc = CD3DX12_RESOURCE_DESC::Buffer(mesh.indices.size() * sizeof(uint16_t));
	hresult = m_d3dDevice->CreateCommittedResource(&heapProperties,D3D12_HEAP_FLAG_NONE,&indexBufferDesc,D3D12_RESOURCE_STATE_GENERIC_READ,nullptr,IID_PPV_ARGS(&mesh.indexBuffer));
	if (FAILED(hresult)) {
		throw std::runtime_error("Failed to create index buffer.");
	}

	UINT8* pIndexDataBegin;
	hresult = mesh.indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin));
	if (FAILED(hresult)) {
		throw std::runtime_error("Failed to map index buffer.");
	}
	memcpy(pIndexDataBegin, mesh.indices.data(), mesh.indices.size() * sizeof(uint16_t));
	mesh.indexBuffer->Unmap(0, nullptr);
}

void Mesh::buildBoxGeometry() {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(-0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//0
		Vertex({ XMFLOAT3(0.5, 0.5f, 0.0f), XMFLOAT4(Colors::White) }),//1
		Vertex({ XMFLOAT3(0.5, -0.5f, 0.0f), XMFLOAT4(Colors::White) }),//2
		Vertex({ XMFLOAT3(-0.5, -0.5, 0.0f), XMFLOAT4(Colors::Black) }),//3
		Vertex({ XMFLOAT3(-0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//4
		Vertex({ XMFLOAT3(0.5, 0.5f, 1.0f), XMFLOAT4(Colors::White) }),//5
		Vertex({ XMFLOAT3(0.5, -0.5f, 1.0f), XMFLOAT4(Colors::White) }),//6
		Vertex({ XMFLOAT3(-0.5, -0.5, 1.0f), XMFLOAT4(Colors::Black) }),//7

	};
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
		6, 2, 5,

		//////// top face
		4, 5, 1,
		1, 0, 4,

		//////// bottom face
		7, 6, 2,
		2, 3, 7
	};
	m_mMesh.indices = std::move(indices);
	uploadMeshToBuffers(m_mMesh);
}

void Mesh::buildPyramidGeometry() {
	std::vector<Vertex> vertices =
	{
		Vertex({ XMFLOAT3(0.5f, 0.0f, 0.0f), XMFLOAT4(Colors::White) }),//0
		Vertex({ XMFLOAT3(0.0f, 0.0f, -0.5f), XMFLOAT4(Colors::White) }),//1
		Vertex({ XMFLOAT3(-0.5f, 0.0f, 0.0f), XMFLOAT4(Colors::White) }),//2
		Vertex({ XMFLOAT3(0.0f, 0.0f, 0.5f), XMFLOAT4(Colors::Black) }),//3
		Vertex({ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(Colors::Blue) }),//4

	};
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
	uploadMeshToBuffers(m_mMesh);
}