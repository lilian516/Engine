#pragma once
#include "pch.h"
#include "GameManager.h"
#include <iomanip>
#include <iostream>
#include <random>
class EnemyManager
{
public :
	EnemyManager();
	void initEnemyManager(Manager* oManager);
	void createEnemy(Manager* oManager);
	Shader *m_oShader;
	BoxMesh* m_oMesh;
	vector<Enemy*> m_vEnemy;
	
};

