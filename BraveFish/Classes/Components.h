
#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "cocos2d.h"
//All game objects
class GameObject: public cocos2d::Sprite
{
public:

	//GameObject(std::string fileName,cocos2d::Scene* scene,int id);
	GameObject(std::string fileName, int id);
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

	cocos2d::Vec2 initialPos;
	cocos2d::Vec2 maxPos;
	
	GameObject* movingSprite;

	virtual float LookTo(const cocos2d::Vec2& point);
	void SetNewPos(cocos2d::Vec2 position, float rotation, int speed);
	void Move(float deltaTime);
	bool CheckOutScreen();

	float getCurrentRotation()
	{
		return currentRotation;
	}

	void setCurrentRotation(float rotation)
	{
		currentRotation = rotation;
		movingSprite->setRotation(currentRotation+ initialRotation);
	}

	void setCurrentRotationToRadians()
	{
		currentRotation = currentRotation / 180 * M_PI;
	}

private:
	float initialRotation=180;
	float currentRotation=0;
	float movingSpeed=0;
	float turningSpeed=0;

};

//Basic animating
class Animating
{
public:
	float counter;

	GameObject * animatingSprite;
	
	virtual void TestAnimateAction(float animMultiplyScale, float animScalePeriod);

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
	void RunAnimateScale();
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
