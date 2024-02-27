#include "Mesh.h"
#include "Graphics.h"

using namespace DirectX;


struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texCoord;
};

Mesh::Mesh() {

}

Mesh::~Mesh() {

}