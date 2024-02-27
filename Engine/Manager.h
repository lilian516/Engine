#pragma once
#include "Graphics.h"
#include "Entity.h"
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <iostream>

using namespace std;


class Manager
{
public :
	Manager();
	void initManager();
	void mainLoop();
	void update();
	void render();

	Graphics *m_oGraphics;
	vector<Entity> m_vEntity;
	vector<Shader> m_vShader;
	vector<Mesh> m_vMesh;
};

