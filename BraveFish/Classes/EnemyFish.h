
#ifndef __ENEMY_FISH_H__
#define __ENEMY_FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include <stdlib.h> 
#include "Components.h"

class EnemyFish:public GameObject, public Moving, public Animating
{
public:

	EnemyFish(const std::string& fileName, int id);
	
	virtual void init(const cocos2d::Vec2& startPos, float startRotation, float scale) override;
	virtual void die() override;
	virtual void activate() override;
	virtual void deActivate() override;

	void setTarget(cocos2d::Vec2);
	
private:

	virtual void update(float delta) override;
	cocos2d::Vec2 target;
	cocos2d::Vec2 getRandomCoord();
};

#endif
