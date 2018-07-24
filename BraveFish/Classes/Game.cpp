/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#define TARGET_SCALE 0.2


#include "Game.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"

#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

//#define SSTR( x ) static_cast< std::ostringstream & >( \
//        ( std::ostringstream() << std::dec << x ) ).str()

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
Fish* fish;
EnemyFish* enemyFish[ENEMY_COUNT];
Sprite target;
float Game::graphicsScale;

bool gameOver;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	InitialSetup();

	fish = new Fish(this);

	srand(time(NULL));


	for (int i = 0; i < ENEMY_COUNT; i++) {
		enemyFish[i] = new EnemyFish(this);
		enemyFish[i]->LookTo(fish->sprite->getPosition());
	}

	
	

	

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

void Game::InitialSetup() {

	auto director = cocos2d::Director::getInstance();
	auto width = cocos2d::Size(director->getOpenGLView()->getFrameSize()).width;
	auto height = cocos2d::Size(director->getOpenGLView()->getFrameSize()).height;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	graphicsScale = 1.0 *width / 960;

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
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

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	label = Label::createWithTTF("Kill them!", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("background.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


		sprite->setScale(graphicsScale);
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}

	target = Sprite::create("bubble.png");
	if (target == nullptr)
	{
		problemLoading("'bubble.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		target->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		target->setScale(TARGET_SCALE*graphicsScale);
		// add the sprite as a child to this layer
		this->addChild(target, 0);
	}


	//label->setString("rrr");

}

void Game::update(float delta)
{

	for (int i = 0; i < ENEMY_COUNT; i++) {
		enemyFish[i]->Run(delta);
	}
	
	if (gameOver) 
	{
		GameOver();

		return;
	}
	//test update	

	counter++;
	int i = 42;
	//std::string s = SSTR("Frames passed: " << counter);

	//label->setString(s);
	
	//fish->Turn();

	CollisionDetection(fish->sprite, enemyFish[0]->enemyFishSprite);

	//Bubble bubble
	target->setScale((TARGET_SCALE*(1-sin(0.99*counter/10))/4 + TARGET_SCALE)*graphicsScale);
}

void GotoMainMenu() {
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));
}

void Game::GameOver() {

	//log("GameOver");
	label->setString("GameOver");
	//CallFunc *runCallback = CallFunc::create(this, callfunc_selector(GotoMainMenu));
	float delay = 2.0f;
	auto delayAction = DelayTime::create(delay);  // For 2 Seconds of Delay
	auto funcCallback = CallFunc::create([]() {GotoMainMenu(); });
	this->runAction(Sequence::create(delayAction, funcCallback, NULL));

}



bool Game::onTouchBegan(Touch* touch, Event* event)
{
	if (gameOver) return true;

	target->setPosition(touch->getLocation());
	return true;
}

void Game::onTouchEnded(Touch* touch, Event* event)
{
	cocos2d::log("touch ended");
	
	//fish->LookTo(touch->getLocation());
}

void Game::onTouchMoved(Touch* touch, Event* event)
{
	if (gameOver) return;

	fish->LookTo(touch->getLocation());
	target->setPosition(touch->getLocation());
	//cocos2d::log("touch moved");
}

void Game::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}

bool Game::CollisionDetection(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2) {

	Rect rect1 = sprite1->getBoundingBox();
	Rect rect2 = sprite2->getBoundingBox();

	float xA = sprite1->getPosition().x;
	float yA = sprite1->getPosition().y;

	float xB = sprite2->getPosition().x;
	float yB = sprite2->getPosition().y;

	float rA = sprite1->getContentSize().width / 2;
	float rB = sprite2->getContentSize().width / 2;

	//log("rA: %f", rA);
	//log("radius sum: %f", ((rA + rB)*(rA + rB)) * graphicsScale * graphicsScale * 0.15* 0.15);
	//log("dist: %f", (xA - xB)*(xA - xB) + (yA - yB)*(yA - yB));
	//if (rect1.intersectsRect(rect2))
	if ((xA - xB)*(xA - xB) + (yA - yB)*(yA - yB) < ((rA + rB)*(rA + rB))*graphicsScale*graphicsScale*0.15*0.15)
	{
		log("Collided");
		//Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));
		gameOver = true;
	}
	else
	{
		//log("Not collided");
	}

	return false;
}


void Game::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene(), Color3B(255, 255, 255)));

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
