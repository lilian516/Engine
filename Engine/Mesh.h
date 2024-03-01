#pragma once
#include <vector>
#include "Entity.h"
using namespace DirectX;

struct Vertex {
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct MeshData {
	std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;
	ID3D12Resource* vertexBuffer;
	ID3D12Resource* indexBuffer;

	ID3D12Resource* vertexBufferGPU = nullptr;
	ID3D12Resource* indexBufferGPU = nullptr;

	UINT vertexByteStride = 0;
	UINT vertexByteSize = 0;
	UINT indexBufferByteSize = 0;
	DXGI_FORMAT indexFormat = DXGI_FORMAT_R16_UINT;


	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;
};

class Mesh
{
public:

	Mesh();
	~Mesh();
	void update();
	void buildBoxGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void buildPyramidGeometry(ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	void uploadMeshToBuffers(MeshData mesh, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);
	ID3D12Resource* CreateDefaultBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, const void* initData, UINT64 byteSize, ID3D12Resource*& uploadBuffer);
	
	MeshData m_mMesh;
private:
	

protected:


};

