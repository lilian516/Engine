#pragma once
#include "Component.h"
class Script : public Component
{
public:
	Script();
	~Script();
	void setScript(Entity *oEntity);
	virtual void update()override;
private:

protected:

};

