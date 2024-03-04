#pragma once
#include "Entity.h"
#include "Graphics.h"
#include <memory>

#include "ObjectConstants.h"

class Component : public Entity
{
private :
	int m_iId;
public :
	Entity m_oEntity;

	Component();
	void initComponent(int iId, Entity* oEntity);
	virtual void update();
	virtual void render(Graphics* oGraphics);
	int getId();
	
};

