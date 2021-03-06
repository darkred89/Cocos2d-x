
#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include "Components.h"

class Fish :public GameObject, public Moving,public Animating
{
public:

	Fish(const std::string& defaultSpriteImege, int id);

	virtual void init(const cocos2d::Vec2& startPos, float startRotation, float scale);
	virtual void die() override;
	void turn(float rotation);
	void fireBubble();
	

private:

	cocos2d::Sprite* fishFireSprite;
	float lookToRotation = 0;
	float deltaRotation = 0;

	float checkAngle(float angle);
	bool turning;

	virtual void update(float delta) override;
	
};

#endif
