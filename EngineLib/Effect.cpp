#include "pch.h"
#include "Effect.h"

Effect::Effect() {

}

Effect::~Effect() {

}

void Effect::setEffect(Entity *oEntity) {
	initComponent(2,oEntity);
}