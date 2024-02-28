#pragma once
#include "Entity.h"
class Component : public Entity
{
private :
	int m_iId;
public :
	Component();
	void setComponent(int iId);
	virtual void update();
	virtual void render();
	int getId();
};

