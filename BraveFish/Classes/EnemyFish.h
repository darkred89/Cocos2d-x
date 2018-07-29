
#ifndef __ENEMY_FISH_H__
#define __ENEMY_FISH_H__

#include "cocos2d.h"
#include <cmath> 
#include <stdlib.h> 
#include "Components.h"

class EnemyFish:public GameObject, public Moving, public Animating
{
public:

	EnemyFish(std::string fileName, cocos2d::Scene* scene, int id);
	
	virtual void Init(cocos2d::Vec2 startPos, float startRotation, float scale) override;
	virtual void Run(float) override;
	virtual void Activate() override;
	virtual void DeActivate() override;

	void SetTarget(cocos2d::Vec2);
	
private:

	cocos2d::Vec2 target;
	cocos2d::Vec2 GetRandomCoord();
};

#endif
