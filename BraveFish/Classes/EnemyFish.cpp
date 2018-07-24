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

#define FISH_SCALE 0.1
#define FISH_SPEED 20

#include "EnemyFish.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

//Sprite* EnemyFish::sprite;
//int n;
//Vec2 EnemyFish : :target;
float angle;

EnemyFish::EnemyFish(Scene* scene) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	sprite = Sprite::create("badFish.png");
	if (sprite == nullptr)
	{
		//
	}
	else
	{

		sprite->setScale(FISH_SCALE);

		sprite->setPosition(GetRandomCoord());

		// add the sprite as a child to this layer
		scene->addChild(sprite, 0);
	}
}

Vec2 EnemyFish::GetRandomCoord() {


	Vec2 coord = Vec2(0, 0);
	return coord;
}

void EnemyFish::LookTo(Vec2 point) {

	log("Begin look to");

	float x = point.x - sprite->getPosition().x;;
	float y = point.y - sprite->getPosition().y;

	target = new Vec2(sprite->getPosition().x, sprite->getPosition().y);

	angle = atan2(x, y) * 180 / M_PI;
	
	cocos2d::log("x: %f", x);
	cocos2d::log("y: %f", y);
	cocos2d::log("angle: %f", angle);

	sprite->setRotation(angle+180);
	angle = angle / 180 * M_PI; // to radians
}

void EnemyFish::Run(float deltaTime) {

	sprite->setPosition(Vec2(sprite->getPosition().x + FISH_SPEED * deltaTime*sin(angle), sprite->getPosition().y + FISH_SPEED * deltaTime*cos(angle)));
}




