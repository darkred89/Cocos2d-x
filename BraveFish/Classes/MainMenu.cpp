
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	menuSetup();

    return true;
}

void MainMenu::menuSetup() {
	auto director = cocos2d::Director::getInstance();
	auto width = cocos2d::Size(director->getOpenGLView()->getFrameSize()).width;
	auto height = cocos2d::Size(director->getOpenGLView()->getFrameSize()).height;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float scaleMultilier = width / 960;
	////CloseButton
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		closeItem->setScale(scaleMultilier);
		float x = origin.x + visibleSize.width - scaleMultilier*closeItem->getContentSize().width / 2;
		float y = origin.y + scaleMultilier*closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	//Game
	auto gameItem = MenuItemImage::create(
		"buttonRed.png",
		"buttonRedPressed.png",
		CC_CALLBACK_1(MainMenu::gotoGameScene, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = visibleSize.width / 2 + origin.x;
		float y = visibleSize.height / 2 + origin.y;
		gameItem->setPosition(Vec2(x, y));
		gameItem->setScaleX(60 * scaleMultilier);
		gameItem->setScaleY(4 * scaleMultilier);
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, gameItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	
	auto label = Label::createWithTTF("Fish Game", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 2);
	}


	auto btnLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", 24);
	if (btnLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		btnLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the label as a child to this layer
		this->addChild(btnLabel, 2);
	}

	//testing of action
	//Sprite* testSprite = Sprite::create("fish.png");
	//
	//this->addChild(testSprite);
	//testSprite->setPosition(0, 0);
	//
	//auto animAction = ScaleBy::create(2.0f, 2.0f);
	////auto moveAction = MoveBy::create()
	//auto repeatForever = cocos2d::RepeatForever::create(animAction);
	//testSprite->runAction(animAction);

}

void MainMenu::gotoGameScene(Ref* pSender) {
	auto sceneGame = GameScene::createScene();
	Director::getInstance()->replaceScene(sceneGame);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{   
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
