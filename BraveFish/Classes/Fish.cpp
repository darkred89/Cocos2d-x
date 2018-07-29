
#include "Fish.h"
#include "Spawner.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Fish::Fish(std::string fileName, cocos2d::Scene* scene, int id):GameObject::GameObject(fileName, scene, id) 
{

}

void Fish::Init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	GameObject::Init(startPos, startRotation, scale);
	movingSprite = this;
	SetNewPos(startPos, 0, 0);
}

void Fish::Turn() 
{
	currentRotation += FISH_TURN_RATE;
	sprite->setRotation(currentRotation);
}

void Fish::Run(float deltaTime)
{

}




