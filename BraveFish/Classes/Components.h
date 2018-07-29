
#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "cocos2d.h"
//All game objects
class GameObject: public cocos2d::Sprite
{
public:

	GameObject(std::string fileName,cocos2d::Scene* scene,int id);

	virtual void Init(cocos2d::Vec2 startPos, float startRotation, float scale);

	virtual void Run(float);
	virtual void Activate();
	virtual void DeActivate();
	//
	bool active;
	int id;
};

///Basic moving
class Moving
{
public:

	float movingSpeed;
	float turningSpeed;
	cocos2d::Vec2 initialPos;
	cocos2d::Vec2 maxPos;

	float currentRotation;
	GameObject* movingSprite;

	virtual void LookTo(cocos2d::Vec2 point);
	void SetNewPos(cocos2d::Vec2 position, float rotation, int speed);
	void Move(float deltaTime);
	bool CheckOutScreen();
		
};

//Basic animating
class Animating
{
public:
	float counter;

	GameObject * animatingSprite;
	

	virtual void Animate(float deltaTime);

	virtual void AnimateScale(float currentScale, float animIncrementScale, float animScalePeriod);
	virtual void AnimateSprite(std::string defaultSprite, std::string nextSprite, float duration);
	//virtual void Run(float deltaTime) {};

private:
	std::string defaultSprite;

	float currentScale;
	float animIncrementScale;
	float animScalePeriod;

	float setAnimSpriteTime;

	bool animScale=false;
	bool animSprite=false;
	virtual void RunAnimateScale();
};


struct PoolHolderNode
{
	GameObject* gameObject;
	PoolHolderNode* nextNode;
};

class PoolHolder
{
public:
	PoolHolderNode* node;

	PoolHolderNode* FirstNode;
	PoolHolderNode* LastNode;

	PoolHolder(GameObject* fisrtGameObject);
	void Push(GameObject* gameObject);
	void RunObjects(float deltaTime);
	GameObject* GetFreeGameObject();
};

#endif 
