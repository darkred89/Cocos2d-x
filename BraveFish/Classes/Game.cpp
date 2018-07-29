
#include "Game.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);

    return scene;
}

Label label;
int counter=0;
Sprite target;

bool Game::gameOver;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Game::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	InitialSetup();

	srand(time(NULL));

	spawner =new Spawner(this,graphicsScale);
	spawner->SpawnEnemyFish();
	
	this->scheduleUpdate();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	gameOver = false;
    return true;
}

void Game::InitialSetup() 
{
	auto director = cocos2d::Director::getInstance();
	auto width = cocos2d::Size(director->getOpenGLView()->getFrameSize()).width;
	auto height = cocos2d::Size(director->getOpenGLView()->getFrameSize()).height;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	graphicsScale = 1.0 *width / 960;

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		closeItem->setScale(graphicsScale);
		float x = origin.x + visibleSize.width - graphicsScale*closeItem->getContentSize().width / 2;
		float y = origin.y + graphicsScale*closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	label = Label::createWithTTF("Kill them!", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
		this->addChild(label, 2);
	}

	auto sprite = Sprite::create("background.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		sprite->setScale(graphicsScale);
		this->addChild(sprite, 0);
	}
}

void Game::update(float delta)
{
	spawner->Run(delta);
	
	if (gameOver) 
	{
		GameOver();
		return;
	}
}

void GotoMainMenu() 
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));
}

void Game::GameOver() 
{
	label->setString("GameOver");
	float delay = 2.0f;
	auto delayAction = DelayTime::create(delay);  // For 2 Seconds of Delay
	auto funcCallback = CallFunc::create([]() {GotoMainMenu(); });
	this->runAction(Sequence::create(delayAction, funcCallback, NULL));
}

bool Game::onTouchBegan(Touch* touch, Event* event)
{
	if (gameOver) return true;
	//spawner->TurnPlayerFish(touch->getLocation());
	spawner->SetTouch(touch->getLocation());
	return true;
}

void Game::onTouchEnded(Touch* touch, Event* event)
{
	//spawner->SpawnBubble();
	spawner->TouchEnded();
}

void Game::onTouchMoved(Touch* touch, Event* event)
{
	if (gameOver) return;
	spawner->SetTouch(touch->getLocation());
	//spawner->TurnPlayerFish(touch->getLocation());
}

void Game::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}

void Game::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}
