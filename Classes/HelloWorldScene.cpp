#include "HelloWorldScene.h"

#include "SynthLevelBitmask.h"

#define LEVEL_WIDTH 1200

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
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

   //background sprite
	Sprite* pBgSprite = Sprite::create("background.png");
	pBgSprite->setAnchorPoint(Point(0, 1));
	pBgSprite->setPosition(Point(0.f, pBgSprite->getContentSize().height));
	this->addChild(pBgSprite, 0);
    
	//hero
	_pHero = new SynthHero();
	_pHero->init(this);

	//physic level
	SynthLevelBitmask* pSLB = new SynthLevelBitmask();
	pSLB->initWithImageFile("background.png");
	pSLB->setAbsolutePosition(pBgSprite->getPosition());
	_pHero->setLevelBitmask(pSLB);

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
	switch(keyCode) {
	case EventKeyboard::KeyCode::KEY_Q:
		_pHero->walkLeft(true);		
		break;

	case EventKeyboard::KeyCode::KEY_D:	
		_pHero->walkRight(true);
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
		_pHero->walkLeft(false);
		break;

	case EventKeyboard::KeyCode::KEY_D:		
		_pHero->walkRight(false);
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
	Node::update(delta);

	_pHero->move(delta);
}