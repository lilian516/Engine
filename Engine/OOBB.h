#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct OOBB {
	XMFLOAT4 p_MaxCoordinate;
	XMFLOAT4 p_MinCoordinate;
};