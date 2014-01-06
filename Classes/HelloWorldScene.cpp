#include "HelloWorldScene.h"

#include "SynthLevelBitmask.h"

#include "Actor.h"

USING_NS_CC;

HelloWorld::HelloWorld()
	: LayerColor()
	, _pHero(NULL)
{

}

HelloWorld::~HelloWorld()
{
	if(_pHero)
	{
		delete _pHero;
		_pHero = NULL;
	}
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
	//Layer properties
	this->setKeyboardEnabled(true);
	this->scheduleUpdate();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...
    _hero = new Actor();
    _hero->addComponent(MovementComponent::create());
    CCLOG("HERO ID = %d", _hero->getActorID());
    
	// decor sprite
	Sprite* pDecorSprite = Sprite::create("decor.jpg");
	pDecorSprite->setAnchorPoint(Point(0,1));
	pDecorSprite->setPosition(Point(0.f, pDecorSprite->getContentSize().height));
	this->addChild(pDecorSprite, 0, 2);

    //background sprite
	Sprite* pBgSprite = Sprite::create("background.png");
	pBgSprite->setAnchorPoint(Point(0, 1));
	pBgSprite->setPosition(Point(0.f, pBgSprite->getContentSize().height));
	this->addChild(pBgSprite, 0, 1);

	//set background sprite shaders
	GLProgram* pBgProgram = new GLProgram();
	pBgProgram->initWithVertexShaderFilename("shaders/synthTestShader.vs", "shaders/synthTestShader.fs");
	pBgProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	pBgProgram->addAttribute(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	pBgProgram->link();
	pBgProgram->updateUniforms();
	pBgProgram->use();
	pBgProgram->setUniformLocationWith2f(pBgProgram->getUniformLocationForName("uTexSize"), pBgSprite->getContentSize().width, pBgSprite->getContentSize().height);
	pBgSprite->setShaderProgram(pBgProgram);
    
	/*//hero
	_pHero = new SynthHero();
	_pHero->init(this);

	//physic level
	SynthLevelBitmask* pSLB = new SynthLevelBitmask();
	pSLB->initWithImageFile("background.png");
	pSLB->setAbsolutePosition(pBgSprite->getPosition());
	_pHero->setLevelBitmask(pSLB);*/

    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    Actor* hero2 = new Actor();
    hero2->addComponent(MovementComponent::create());
	CCLOG("KEY PRESSED");
    ActorMoveEvent* moveEvent = new ActorMoveEvent(hero2);
    //ActorMoveEvent* moveEvent2 = new ActorMoveEvent(hero2);
    //CCLOG("EVENT SOURCE IN ON KEY PRESSED IS NULL ? %d", moveEvent->getSource() == NULL);
    auto dispatcher = EventDispatcher::getInstance();
    switch(keyCode) {
	case EventKeyboard::KeyCode::KEY_Q:
		//_pHero->walkLeft(true);
        CCLOG("Dispatching ActorMoveEvent");
        dispatcher->dispatchEvent(moveEvent);
		break;

	case EventKeyboard::KeyCode::KEY_D:
        //CCLOG("Dispatching ActorMoveEvent2");
        //dispatcher->dispatchEvent(moveEvent2);
		//_pHero->walkRight(true);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		if(!_pHero->isJumping() && !_pHero->isFalling())
		{
			_pHero->jump();
		}
		break;

	default:
		break;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch(keyCode) {
	case EventKeyboard::KeyCode::KEY_Q:
		//_pHero->walkLeft(false);
		break;

	case EventKeyboard::KeyCode::KEY_D:		
		//_pHero->walkRight(false);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		if(_pHero->isJumping())
		{
			_pHero->fall();
		}
		break;

	default:
		break;
	}
}

void HelloWorld::update(float delta)
{
    _hero->update(delta);
	//_pHero->move(delta);
}