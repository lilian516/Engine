#pragma once
#include "Component.h"
class MeshRenderer :public Component
{
public:
	MeshRenderer();
	~MeshRenderer();
	void SetMeshRenderer(Entity *oEntity);
	void update()override;

private:

protected:
};

