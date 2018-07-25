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

#include "Bubble.h"
#include "Spawner.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Bubble::Bubble(cocos2d::Scene* scene, cocos2d::Vec2 position, float rotation, int speed) {
	sprite = Sprite::create("bubble.png");
	if (sprite == nullptr)
	{
		//
	}
	else
	{
		
		sprite->setScale(BUBBLE_SCALE*Spawner::graphicsScale);

		angle = rotation;

		sprite->setPosition(position);
		sprite->setRotation(rotation);

		angle = angle / 180 * M_PI; // to radians

		this->speed = speed;

		log("Bubble speed %f", this->speed);

		// add the sprite as a child to this layer
		scene->addChild(sprite, 1);
	}
	counter = 0;
}

void Bubble::SetNewPos(cocos2d::Vec2 position, float rotation, int speed) {

		angle = rotation;

		sprite->setPosition(position);
		sprite->setRotation(rotation);

		angle = angle / 180 * M_PI; // to radians

		this->speed = speed;

		log("Bubble speed %f", this->speed);

		// add the sprite as a child to this layer
	counter = 0;
}



void Bubble::Run(float deltaTime) {
	counter += deltaTime;
	sprite->setPosition(Vec2(sprite->getPosition().x + speed * deltaTime*sin(angle), sprite->getPosition().y + speed * deltaTime*cos(angle)));
	//enemyFishSprite->setScale(2);
	sprite->setScale((TARGET_SCALE*(1 - sin(5.99*counter)) / 4 + TARGET_SCALE)*Spawner::graphicsScale);
}




