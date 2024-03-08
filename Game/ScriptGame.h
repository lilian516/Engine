#pragma once
#include "framework.h"
class ScriptGame : public Script 
{
public :
	ScriptGame();
	void initGame(Entity* oEntity);
	void update()override;
	void createProjectile();
};

