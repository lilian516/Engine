#pragma once
#include "framework.h"
class ScriptProjectile : public Script
{
public : 
	ScriptProjectile();
	void initProjectile(Entity* oEntity);
	void update()override;
};

