#pragma once
#include "pch.h"
class Projectile : public Entity
{
public :
	Projectile();
	void initProjectile(Manager* oManager, Shader* oShader, Mesh* oMesh);
	MeshRenderer m_oMeshRenderer;
};

