#pragma once
#include "Entity.h"
class Component : public Entity
{
private :
	int m_iId;
public :
	Entity m_oEntity;

	Component();
	void initComponent(int iId, Entity oEntity);
	virtual void update();
	virtual void render();
	int getId();
};

