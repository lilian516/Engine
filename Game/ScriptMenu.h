#pragma once
#include "framework.h"
class ScriptMenu : public Script
{
public:
	ScriptMenu();
	void initMenu(Entity* oEntity);
	void update()override;
};

