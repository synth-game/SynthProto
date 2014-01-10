#include "HelloWorldScene.h"

#include "SynthLevelBitmask.h"

#include "Actor.h"
#include "GeometryComponent.h"
#include "MovementComponent.h"
#include "AnimatedSpriteComponent.h"
#include "CollisionComponent.h"
#include "ActorStartMoveEvent.h"
#include "ActorJumpEvent.h"

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
	/////////////////////////////

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

	//physic level
	SynthLevelBitmask* pSLB = new SynthLevelBitmask();
	pSLB->initWithImageFile("background.png");
	pSLB->setAbsolutePosition(pBgSprite->getPosition());
    
    _hero = new Actor();
	_hero->addComponent(GeometryComponent::create(Point(200.f, 190.f), Size(74.f, 74.f), 0.f, Point(0.5f, 0.5f)));
	_hero->addComponent(CollisionComponent::create(pSLB));
	_hero->addComponent(MovementComponent::create(Point(0.f, 0.f), Point(0.f, 0.f), Point(20.f, 20.f), Point(0.f, -5.f)));
    _hero->addComponent(AnimatedSpriteComponent::create(this, "sprites/megaman.pvr", "sprites/megaman.plist", "walk_3.png"));

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
	_pHero->init(this);*/

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
	CCLOG("KEY PRESSED");
	ActorStartMoveEvent* moveEvent = nullptr;
	ActorJumpEvent* jumpEvent = nullptr;
    auto dispatcher = EventDispatcher::getInstance();
    switch(keyCode) {
	case EventKeyboard::KeyCode::KEY_Q:
		moveEvent = new ActorStartMoveEvent(_hero);
		moveEvent->_direction = Point(-1., 0.f);
		moveEvent->_bChangeX = true;
		moveEvent->_bChangeY = false;
		moveEvent->_bStart = true;
        CCLOG("Dispatching ActorStartMoveEvent LEFT");
        dispatcher->dispatchEvent(moveEvent);
		break;

	case EventKeyboard::KeyCode::KEY_D:
		moveEvent = new ActorStartMoveEvent(_hero);
		moveEvent->_direction = Point(1.f, 0.f);
		moveEvent->_bChangeX = true;
		moveEvent->_bChangeY = false;
		moveEvent->_bStart = true;
        CCLOG("Dispatching ActorStartMoveEvent RIGHT");
        dispatcher->dispatchEvent(moveEvent);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		jumpEvent = new ActorJumpEvent(_hero);
		jumpEvent->_bStart = true;
		CCLOG("Dispatching ActorStartMoveEvent JUMP");
		dispatcher->dispatchEvent(jumpEvent);
		break;

	default:
		break;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    CCLOG("KEY RELEASED");
    auto dispatcher = EventDispatcher::getInstance();
	ActorStartMoveEvent* stopMovingEvent = nullptr;
	ActorJumpEvent* jumpEvent = nullptr;
    switch(keyCode) {
    case EventKeyboard::KeyCode::KEY_Q:
		stopMovingEvent = new ActorStartMoveEvent(_hero);
		stopMovingEvent->_direction = Point(1.f, 0.f);
		stopMovingEvent->_bChangeX = true;
		stopMovingEvent->_bChangeY = false;
		stopMovingEvent->_bStart = false;
        dispatcher->dispatchEvent(stopMovingEvent);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		stopMovingEvent = new ActorStartMoveEvent(_hero);
		stopMovingEvent->_direction = Point(-1.f, 0.f);
		stopMovingEvent->_bChangeX = true;
		stopMovingEvent->_bChangeY = false;
		stopMovingEvent->_bStart = false;
        dispatcher->dispatchEvent(stopMovingEvent);
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		jumpEvent = new ActorJumpEvent(_hero);
		jumpEvent->_bStart = false;
		dispatcher->dispatchEvent(jumpEvent);
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