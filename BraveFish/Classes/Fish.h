
#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include "Components.h"

class Fish :public GameObject, public Moving,public Animating
{
public:

	//cocos2d::Sprite* sprite;
	Fish(std::string defaultSpriteImege, int id);

	//virtual void run(float deltaTime);	
	virtual void init(const cocos2d::Vec2& startPos, float startRotation, float scale);
	void turn(float rotation);
	void fireBubble();
	

private:

	cocos2d::Sprite* fishFireSprite;
	float lookToRotation = 0;
	float deltaRotation = 0;
	float ñheckAngleOutOfBounds(float angle);
	bool turning;

	virtual void update(float delta) override;
	
};

#endif
