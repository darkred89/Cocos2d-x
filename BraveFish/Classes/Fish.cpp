
#include "Fish.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Fish::Fish(std::string defaultSpriteImege, int id):GameObject::GameObject(defaultSpriteImege, id)
{

}

void Fish::Init(const cocos2d::Vec2& startPos, float startRotation, float scale)
{
	GameObject::Init(startPos, startRotation, scale);
	movingSprite = this;
	SetNewPos(startPos, 0, 0);
	animatingSprite = this;
	counter = 0;
	//currentRotation = 0;
	setCurrentRotation(0);
	lookToRotation = 0;
	turning = false;
	this->scheduleUpdate();
}

void Fish::Turn(float rotation) 
{
	lookToRotation = rotation;

	lookToRotation= CheckAngleOuntOfBounds(lookToRotation);

	float clockR = lookToRotation - getCurrentRotation();
	float aClockR = getCurrentRotation() + (360 - lookToRotation);

	clockR=CheckAngleOuntOfBounds(clockR);
	aClockR=CheckAngleOuntOfBounds(aClockR);

	//log("fish current rotation %f", getCurrentRotation());
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

void Fish::update(float delta)
{
	log("fish update");
}


void Fish::Run(float deltaTime)
{
	Animate(deltaTime);
	
	if (!turning) return;

	setCurrentRotation(CheckAngleOuntOfBounds(getCurrentRotation()));

	if (abs(getCurrentRotation() - lookToRotation) < FISH_TURN_RATE*deltaTime)
	{
		setCurrentRotation(lookToRotation);
		turning = false;
	}
	else
	{
		//getCurrentRotation() += deltaRotation*deltaTime;
		setCurrentRotation(getCurrentRotation() + deltaRotation*deltaTime);
	}

	//setRotation(currentRotation);
}

float Fish::CheckAngleOuntOfBounds(float angle)
{
	if (angle < 0)
	{
		angle += 360;
	}

	if (angle > 360.0f)
	{
		angle -= 360;
	}
	return angle;
}




