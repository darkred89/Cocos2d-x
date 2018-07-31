
#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include "Components.h"

class Fish :public GameObject, public Moving,public Animating
{
public:

	cocos2d::Sprite* sprite;
	Fish(std::string defaultSpriteImege, int id);

	virtual void Run(float deltaTime);
	
	virtual void Init(const cocos2d::Vec2& startPos, float startRotation, float scale);
	void Turn(float rotation);
	void update(float);

	float lookToRotation=0;
	float deltaRotation=0;
private:

	bool turning;
	float CheckAngleOuntOfBounds(float angle);
};

#endif
