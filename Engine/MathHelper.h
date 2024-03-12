#pragma once
#include <DirectXMath.h>

using namespace DirectX;

void normalizeVector(XMFLOAT4* vector);

float distanceCalcul(XMFLOAT4 posOne, XMFLOAT4 posTwo);

void identity4x4(XMFLOAT4X4* matrix);

