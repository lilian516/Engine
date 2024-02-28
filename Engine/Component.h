#pragma once
#include "Entity.h"
class Component : public Entity
{
private :
	int m_iId;
	Entity m_oEntity;
public :
	Component();
	void initComponent(int iId, Entity oEntity);
	virtual void update();
	virtual void render();
	int getId();
};

