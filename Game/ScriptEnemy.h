#pragma once
#include "App.h"
#include "framework.h"
class ScriptEnemy : public Script
{
public :
	ScriptEnemy();
	void initEnemy(Entity* oEntity);
	void update()override;
	XMFLOAT3 m_DirVect;
};

