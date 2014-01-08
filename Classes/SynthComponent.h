#ifndef __SYNTH_COMPONENT_H__
#define __SYNTH_COMPONENT_H__

#include "cocos2d.h"

 // virtuel pur, completement abstraite ne peut pas être instanciée
class SynthComponent : public cocos2d::Component {

public :
	
	// Methods
	SynthComponent() : Component() {}
	virtual bool init(const char* componentType);

protected:
	
	// Methods
	virtual void initListeners() = 0;
	virtual void addListeners()  = 0;

};




#endif