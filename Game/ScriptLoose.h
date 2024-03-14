#pragma once
#include "App.h"
#include "framework.h"
class ScriptLoose : public Script
{
public :
	ScriptLoose();
	void initScriptLoose(Entity* oEntity);
	void update()override;
	Entity* m_pButtonLoose;
};

