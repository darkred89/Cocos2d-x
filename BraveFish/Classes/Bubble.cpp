
#include "Bubble.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

float sceneWidth;
float sceneHeight;

Bubble::Bubble(std::string fileName, int id) :GameObject::GameObject(fileName, id)//Bubble(cocos2d::Scene* scene, cocos2d::Vec2 startPosition, cocos2d::Vec2 maxPosition, int id)
{

}

void Bubble::init(cocos2d::Vec2 startPos, float startRotation, cocos2d::Vec2 maxPosition, float scale, GameObject* playerFish)
{
	GameObject::init(startPos, startRotation, scale);
	movingSprite = this;
	this->playerFish=playerFish;
	//animatingSprite = this;
	initScale = scale;

	maxPos = maxPosition;
	initialPos = startPos;

	setNewPos(startPos, 0, 0);
}

void Bubble::update(float delta)
{
	GameObject::update(delta);
	move(delta);

	if (checkOutScreen()) {
		deActivate();
	}
}

void Bubble::activate() 
{
	setScale(initScale);
	setNewPos(playerFish->getPosition(), playerFish->getRotation() / 180 * M_PI+ M_PI, BUBBLE_SPEED);
	testAnimateAction(this,BUBBLE_ANIM_MULTIPLY_SCALE, BUBBLE_ANIM_SCALE_PERIOD);
	GameObject::activate();
}

void Bubble::deActivate() 
{
	GameObject::deActivate();
	//counter = 0;
	setNewPos(initialPos,0,0);
}





