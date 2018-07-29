
#include "Fish.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Fish::Fish(std::string defaultSpriteImege, cocos2d::Scene* scene, int id):GameObject::GameObject(defaultSpriteImege, scene, id)
{

}

void Fish::Init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	GameObject::Init(startPos, startRotation, scale);
	movingSprite = this;
	SetNewPos(startPos, 0, 0);
	animatingSprite = this;
	counter = 0;
	currentRotation = 0;
	lookToRotation = 0;
	turning = false;
}

void Fish::Turn(float rotation) 
{
	lookToRotation = rotation;

	float clockR = lookToRotation - currentRotation;
	float aClockR = currentRotation + (360 - lookToRotation);

	CheckAngleOuntOfBounds(&clockR);
	CheckAngleOuntOfBounds(&aClockR);

	//log("fish current rotation %f", currentRotation);
	//log("fish look rotation %f", lookToRotation);
	//log("fish clockR rotation %f", clockR);
	//log("fish aClockR rotation %f", aClockR);

	if (clockR > aClockR)
	{
		deltaRotation = -FISH_TURN_RATE;
	}
	else
	{
		deltaRotation=FISH_TURN_RATE;
	}
	turning = true;
}

void Fish::Run(float deltaTime)
{
	Animate(deltaTime);
	
	if (!turning) return;

	CheckAngleOuntOfBounds(&currentRotation);

	if (abs(currentRotation - lookToRotation) < FISH_TURN_RATE*deltaTime)
	{
		currentRotation = lookToRotation;
		turning = false;
	}
	else
	{
		currentRotation += deltaRotation*deltaTime;
	}

	setRotation(currentRotation);
}

void Fish::CheckAngleOuntOfBounds(float* angle)
{
	if (*angle < 0)
	{
		*angle += 360;
	}

	if (*angle > 360.0f)
	{
		*angle -= 360;
	}
}




