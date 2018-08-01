
#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "cocos2d.h"

class GameObject: public cocos2d::Sprite
{
public:

	GameObject(const std::string& fileName, int id);
	virtual void init(const cocos2d::Vec2& startPos, float startRotation, float scale);

	virtual void activate();
	virtual void deActivate();
	virtual void die();

	bool isActive()
	{
		return active;
	}
	bool isColliding()
	{
		return colliding;
	}

protected:
	virtual void update(float delta);

private:
	bool active=false;
	bool colliding = false;
	int id=0;
};


class Moving
{
public:
	
	virtual float lookTo(const cocos2d::Vec2& point);
	void setNewPos(const cocos2d::Vec2& position, float rotation, int speed);

	float getCurrentRotation()
	{
		return currentRotation;
	}
	void setCurrentRotation(float rotation)
	{
		currentRotation = rotation;
		movingSprite->setRotation(currentRotation+ initialRotation);
	}	

protected:

	GameObject* movingSprite;
	cocos2d::Vec2 initialPos;
	cocos2d::Vec2 maxPos;

	void setCurrentRotationToRadians()
	{
		currentRotation = currentRotation / 180 * M_PI;
	}
	void move(float deltaTime);
	bool checkOutScreen();
	
private:

	float initialRotation=180;
	float currentRotation=0;
	float movingSpeed=0;
	float turningSpeed=0;

};


class Animating
{	
protected:

	virtual void testAnimateAction(cocos2d::Sprite* sprite,float animMultiplyScale, float animScalePeriod);
	virtual void spriteBlinkAnim(cocos2d::Sprite* sprite, float blinkTime);
	virtual void fishDie(GameObject* fish,float duration);

private:

	float currentScale;
	float setAnimSpriteTime;

};


struct PoolHolderNode
{
	GameObject* gameObject;
	PoolHolderNode* nextNode;
};

class PoolHolder
{
public:

	PoolHolderNode* firstNode;
	PoolHolderNode* lastNode;

	PoolHolder(GameObject* fisrtGameObject);
	void push(GameObject* gameObject);
	
	GameObject* getFreeGameObject();

private:
	PoolHolderNode* node;
};

#endif 
