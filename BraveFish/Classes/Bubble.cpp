
#include "Bubble.h"
#include "Spawner.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

float sceneWidth;
float sceneHeight;

Bubble::Bubble(cocos2d::Scene* scene, cocos2d::Vec2 startPosition, cocos2d::Vec2 maxPosition, int id)
{
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->id = id;
	maxPos = maxPosition;

	sprite = Sprite::create("bubble.png");
	if (sprite == nullptr)
	{
		//
	}
	else
	{
		
		sprite->setScale(BUBBLE_SCALE*Spawner::graphicsScale);
		sprite->setPosition(startPosition);

		//Moving settings
		initialPos = startPosition;
		movingSprite = sprite;
		
		//Animation settings
		animatingSprite = sprite;

		currentScale = Spawner::graphicsScale*BUBBLE_SCALE;
		animIncrementScale = Spawner::graphicsScale*BUBBLE_ANIM_INCREMENT_SCALE;
		animScalePeriod =2* M_PI/ BUBBLE_ANIM_SCALE_PERIOD;

		//SettingUp map borders


		//sprite->setRotation(rotation);

		//angle = angle / 180 * M_PI; // to radians

		//this->speed = speed;

		//log("Bubble speed %f", this->speed);

		// add the sprite as a child to this layer
		scene->addChild(sprite, 1);
	}
	counter = 0;
}

/*
void Bubble::SetNewPos(cocos2d::Vec2 position, float rotation, int speed) 
{

		angle = rotation;

		sprite->setPosition(position);
		sprite->setRotation(rotation);

		angle = angle / 180 * M_PI; // to radians

		this->speed = speed;

		log("Bubble speed %f", this->speed);

		// add the sprite as a child to this layer
	counter = 0;
}

*/

void Bubble::Run(float deltaTime) 
{
	//counter += deltaTime;
	//sprite->setPosition(Vec2(sprite->getPosition().x + speed * deltaTime*sin(angle), sprite->getPosition().y + speed * deltaTime*cos(angle)));
	//enemyFishSprite->setScale(2);
	//sprite->setScale((TARGET_SCALE*(1 - sin(5.99*counter)) / 4 + TARGET_SCALE)*Spawner::graphicsScale);
	if (!active) return;
	
	Move(deltaTime);
	AnimateScale(deltaTime);

	if (CheckOutScreen()) {
		DeActivate();
	}
}

//override test - not working on android
//void Bubble::AnimateScale(float deltaTime) 
//{
//	Animating::AnimateScale(deltaTime);
//	//sprite->setScale(sprite->getScale() * 2);
//}


void Bubble::Activate() 
{
	active = true;
}

void Bubble::DeActivate() 
{
	active = false;
	SetNewPos(initialPos,0,0);
}





