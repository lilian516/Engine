#include "pch.h"
#include "MathHelper.h"

void normalizeVector(XMFLOAT4* vector) {
	XMFLOAT4 temp = *vector;
	temp.x /= static_cast<float>(sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z));
	temp.y /= static_cast<float>(sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z));
	temp.z /= static_cast<float>(sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z));
	*vector = temp;
}
float distanceCalcul(XMFLOAT4 posOne, XMFLOAT4 posTwo) {
	float xPos = pow((posOne.x - posTwo.x), 2);
	float yPos = pow((posOne.y - posTwo.y), 2);
	float zPos = pow((posOne.z - posTwo.z), 2);
	float distance = static_cast<float>(sqrt(xPos + yPos + zPos));
	return round(distance * 1000.0f) / 1000.0f;
}