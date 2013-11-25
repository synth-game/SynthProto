#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SynthHero.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	HelloWorld();
	~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
	//keyboard handling
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;

	//update
	void update(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	SynthHero* _pHero;
};

#endif // __HELLOWORLD_SCENE_H__
