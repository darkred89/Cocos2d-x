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

//#define FISH_SCALE 0.15
//#define FISH_SPEED 20

#include "EnemyFish.h"
#include "Spawner.h"
//#include "Game.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

USING_NS_CC;

//Sprite* EnemyFish::sprite;
//int n;
//Vec2 EnemyFish : :target;

//float angle;

EnemyFish::EnemyFish(Scene* scene) {
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//srand(seed);
	sprite = Sprite::create("badFish.png");
	if (sprite == nullptr)
	{
		//
	}
	else
	{

		sprite->setScale(FISH_SCALE*Spawner::graphicsScale);
		sprite->setPosition(GetRandomCoord());

		movingSprite = sprite;
		SetNewPos(GetRandomCoord(), 0, 0);

		//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		scene->addChild(sprite, 1);
	}
}

void EnemyFish::Activate() {
	
	//enemyFishSprite->setPosition(GetRandomCoord());
	
	SetNewPos(GetRandomCoord(), 0, FISH_SPEED);
	LookTo(target);

	active = true;
}

void EnemyFish::DeActivate() {
	active = false;
	SetNewPos(GetRandomCoord(), 0, 0);
	LookTo(target);
}

Vec2 EnemyFish::GetRandomCoord() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	int side = rand() % 4;

	//speed = FISH_SPEED + rand() % FISH_SPEED;
	//srand(time(0));

	Vec2 randomPos = Vec2(0, 0);
	switch (side)
	{
		case 0: //TOP
			randomPos.y = Spawner::maxCoord.y;// visibleSize.height + origin.y;
			randomPos.x= rand() % static_cast<int>(Spawner::maxCoord.x);
			break;
		case 1: //RIGH
			randomPos.y = rand() % static_cast<int>(Spawner::maxCoord.y);
			randomPos.x = Spawner::maxCoord.x;// visibleSize.width + origin.x;
			break;
		case 2: //BOTTOM
			randomPos.y = 0;// origin.y;
			randomPos.x = rand() % static_cast<int>(Spawner::maxCoord.x);
			break;
		case 3: //LEFT
			randomPos.y = rand() % static_cast<int>(Spawner::maxCoord.y);
			randomPos.x = 0;// origin.x;
			break;
	}

	log("pos x: %f", randomPos.x);

	return randomPos;
}


void EnemyFish::SetTarget(Vec2 point) {

	/*
	target = Vec2(point.x, point.y);

	//log("Begin look to");

	float x = point.x - enemyFishSprite->getPosition().x;;
	float y = point.y - enemyFishSprite->getPosition().y;



	angle = atan2(x, y) * 180 / M_PI;
	
	//cocos2d::log("x: %f", x);
	//cocos2d::log("y: %f", y);
	//cocos2d::log("angle: %f", angle);

	enemyFishSprite->setRotation(angle+180);
	angle = angle / 180 * M_PI; // to radians
	*/
	target = point;
	Moving::LookTo(point);
}


void EnemyFish::Run(float deltaTime) {

	if (!active) return;
	//enemyFishSprite->setPosition(Vec2(enemyFishSprite->getPosition().x + speed * deltaTime*sin(angle), enemyFishSprite->getPosition().y + speed * deltaTime*cos(angle)));
	//enemyFishSprite->setScale(2);
	Move(deltaTime);
}




