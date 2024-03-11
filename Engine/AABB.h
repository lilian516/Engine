#pragma once

#include <DirectXMath.h>

using namespace DirectX;

struct AABB {
	XMFLOAT3 pCenter;
	XMFLOAT3 vRadius;
};