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
};

class Mesh
{
public:

	Mesh();
	~Mesh();
	void update();
	void init(ID3D12Device* device);
	void buildBoxGeometry();
	void buildPyramidGeometry();
	void uploadMeshToBuffers(MeshData mesh);
	MeshData m_mMesh;
private:
	ID3D12Device* m_d3dDevice;
	

protected:


};

