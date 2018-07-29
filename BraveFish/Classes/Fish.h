
#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include "Components.h"

class Fish :public GameObject, public Moving
{
public:

	cocos2d::Sprite* sprite;
	Fish(std::string fileName, cocos2d::Scene* scene, int id);

	virtual void Run(float deltaTime);
	virtual void Init(cocos2d::Vec2 startPos, float startRotation, float scale);
	void Turn();

};

#endif
