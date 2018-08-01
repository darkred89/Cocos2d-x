
#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include "cocos2d.h"
#include "Components.h"

class Bubble:public GameObject, public Moving, public Animating
{
public:

	cocos2d::Sprite* sprite;
	Bubble(const std::string& fileName, int id);
	virtual void init(const cocos2d::Vec2& startPos, float startRotation, const cocos2d::Vec2& maxPosition, float scale, GameObject* playerFish);

	virtual void activate();
	virtual void deActivate();

	GameObject* playerFish;

private:
	virtual void update(float delta) override;
	float initScale=0;
};

#endif
