
#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "cocos2d.h"
#include "Components.h"

class Bubble:public GameObject, public Moving, public Animating
{
public:

	cocos2d::Sprite* sprite;
	Bubble(std::string fileName, cocos2d::Scene* scene, int id);
	virtual void Init(cocos2d::Vec2 startPos, float startRotation, cocos2d::Vec2 maxPosition, float scale, GameObject* playerFish);

	virtual void Run(float);
	virtual void Activate();
	virtual void DeActivate();

	//virtual void AnimateScale(float deltaTime) override;

	GameObject* playerFish;
};

#endif
