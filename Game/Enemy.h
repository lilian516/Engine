#pragma once
#include "pch.h"
class Enemy : public Entity 
{
public :
	Enemy();
	void initEnemy(Graphics* oGraphics, Shader* oShader, Mesh* oMesh);
	MeshRenderer m_oMeshRenderer;
	void update()override;
	void render(Graphics* oGraphics)override;
};

