#pragma once
#include "framework.h"
class ScriptGame : public Script 
{
public :
	
	ScriptGame();
	void initGame(Entity* oEntity);
	void update()override;
	void createProjectile();
	void createEnemy();
	void inputCamera();
	void setCursorPos();
	bool m_bSetCursor;
	
};

