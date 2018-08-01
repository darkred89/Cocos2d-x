
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

    return scene;
}

bool GameScene::gameOverFlag =false;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	gameOverFlag = false;

	srand(time(NULL));

	initialSetup();

	auto gameNode = Node::create();
	this->addChild(gameNode);

	gameController =new GameController(gameNode,graphicsScale);

	this->scheduleUpdate();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	Director::getInstance()->getScheduler()->scheduleUpdate(gameController, 0, false);

    return true;
}

//Labels and menu
void GameScene::initialSetup()
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
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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

	mainLabel = Label::createWithTTF("Kill them!", "fonts/Marker Felt.ttf", 24);
	if (mainLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mainLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - mainLabel->getContentSize().height));
		this->addChild(mainLabel, 2);
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

void GameScene::update(float delta)
{
	if (gameOverFlag) 
	{
		gameOver();
		return;
	}
}

void gotoMainMenu() 
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));
}

void GameScene::gameOver()
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(gameController);
	mainLabel->setString("GameOver");
	float delay = 2.0f;
	auto delayAction = DelayTime::create(delay);  // For 2 Seconds of Delay
	auto funcCallback = CallFunc::create([]() {gotoMainMenu(); });
	this->runAction(Sequence::create(delayAction, funcCallback, NULL));
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	if (gameOverFlag) return true;
	gameController->setTouch(touch->getLocation());
	return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	gameController->touchEnded();
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	if (gameOverFlag) return;
	gameController->setTouch(touch->getLocation());
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(gameController);

	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
	#endif
}
