#include "Script.h"

Script::Script() {


}

Script::~Script() {

}

void Script::setScript(Entity *oEntity) {
	initComponent(4, *oEntity);
}