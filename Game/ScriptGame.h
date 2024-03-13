#pragma once
#include "framework.h"
class ScriptGame : public Script 
{
public :
	enum stateGame{apagnan,menu,start,stop};
	stateGame m_sGame = apagnan;
	ScriptGame();
	void initGame(Entity* oEntity);
	void update()override;
	void createProjectile();
	void createEnemy();
	
};

