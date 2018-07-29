
#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include "Components.h"

class Fish :public GameObject, public Moving,public Animating
{
public:

	cocos2d::Sprite* sprite;
	Fish(std::string defaultSpriteImege, cocos2d::Scene* scene, int id);

	virtual void Run(float deltaTime);
	virtual void Init(cocos2d::Vec2 startPos, float startRotation, float scale);
	void Turn(float rotation);

	float lookToRotation;
	float deltaRotation;
private:

	bool turning;
	void CheckAngleOuntOfBounds(float* angle);
};

#endif
