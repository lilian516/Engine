#pragma once
#include "framework.h"
class ScriptProjectile : public Script
{
public : 
	ScriptProjectile();
	~ScriptProjectile();
	void initProjectile(Entity* oEntity);
	void update()override;
	XMFLOAT3 m_mDir;
};

