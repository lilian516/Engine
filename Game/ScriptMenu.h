#pragma once
#include "framework.h"
class ScriptMenu : public Script
{
public:
	ScriptMenu();
	void initMenu(Entity* oEntity);
	void update()override;
	void setScriptManager(ScriptManager* oScriptManager);
	void createProjectile();

	ScriptManager* m_oScriptManager;
	Entity* m_pButtonStart;
	Entity* m_pMenu;
};

