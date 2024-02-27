#pragma once
#include "d3d12.h"
#include <vector>

struct Vertex;


class Mesh
{
public:

	Mesh();
	~Mesh();

private:
    struct MeshData {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        ID3D12Resource* vertexBuffer;
        ID3D12Resource* indexBuffer;
    };
protected:


};

