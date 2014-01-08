#include "SynthComponent.h"

bool SynthComponent::init(const char* componentType) {
	setName(componentType);
	initListeners();
	addListeners();
	return true;
}