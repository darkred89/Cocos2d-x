
#include "Fish.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


Fish::Fish(const std::string& defaultSpriteImege, int id):GameObject::GameObject(defaultSpriteImege, id)
{

}

void Fish::init(const cocos2d::Vec2& startPos, float startRotation, float scale)
{
	GameObject::init(startPos, startRotation, scale);
	movingSprite = this;
	setNewPos(startPos, 0, 0);
	setCurrentRotation(0);
	lookToRotation = 0;
	turning = false;
	
	fishFireSprite = Sprite::create(FISH_BUBBLE_IMAGE);
	fishFireSprite->setAnchorPoint(Vec2(0, 0));
	fishFireSprite->setRotation(startRotation);
	this->addChild(fishFireSprite);
	fishFireSprite->setPosition(Vec2(0, 0));
	fishFireSprite->setOpacity(0);

}

void Fish::die()
{
	GameObject::die();
	fishDie(this, 3);
}

void Fish::fireBubble()
{
	spriteBlinkAnim(fishFireSprite, FISH_FIREANIM_TIME);
}

void Fish::turn(float rotation) 
{
	lookToRotation = rotation;

	lookToRotation= checkAngle(lookToRotation);

	float clockR = lookToRotation - getCurrentRotation();
	float aClockR = getCurrentRotation() + (360 - lookToRotation);

	clockR= checkAngle(clockR);
	aClockR= checkAngle(aClockR);

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
	GameObject::update(delta);

	if (!turning) return;

	setCurrentRotation(checkAngle(getCurrentRotation()));

	if (abs(getCurrentRotation() - lookToRotation) < FISH_TURN_RATE*delta)
	{
		setCurrentRotation(lookToRotation);
		turning = false;
	}
	else
	{
		setCurrentRotation(getCurrentRotation() + deltaRotation*delta);
	}
}

float Fish::checkAngle(float angle)
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




