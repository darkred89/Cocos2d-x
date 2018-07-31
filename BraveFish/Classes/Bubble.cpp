
#include "Bubble.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

float sceneWidth;
float sceneHeight;

Bubble::Bubble(std::string fileName, int id) :GameObject::GameObject(fileName, id)//Bubble(cocos2d::Scene* scene, cocos2d::Vec2 startPosition, cocos2d::Vec2 maxPosition, int id)
{

}

void Bubble::Init(cocos2d::Vec2 startPos, float startRotation, cocos2d::Vec2 maxPosition, float scale, GameObject* playerFish)
{
	GameObject::Init(startPos, startRotation, scale);
	movingSprite = this;
	//this->playerFish = playerFish;
	this->playerFish=playerFish;
	animatingSprite = this;
	initScale = scale;
	//AnimateScale(GameController::graphicsScale*BUBBLE_SCALE, GameController::graphicsScale*BUBBLE_ANIM_INCREMENT_SCALE, BUBBLE_ANIM_SCALE_PERIOD);

	maxPos = maxPosition;
	initialPos = startPos;

	SetNewPos(startPos, 0, 0);

	active = false;

	//counter = 0;
}

void Bubble::Run(float deltaTime) 
{
	if (!active) return;
	
	Move(deltaTime);
	Animate(deltaTime);

	if (CheckOutScreen()) {
		DeActivate();
	}
}

void Bubble::Activate() 
{
	setScale(initScale);
	SetNewPos(playerFish->getPosition(), playerFish->getRotation() / 180 * M_PI+ M_PI, BUBBLE_SPEED);
	//log("current rotation: %f", playerFish->currentRotation);
	//log("get rotation: %f", playerFish->getRotation());
	TestAnimateAction(BUBBLE_ANIM_MULTIPLY_SCALE, BUBBLE_ANIM_SCALE_PERIOD);
	GameObject::Activate();
}

void Bubble::DeActivate() 
{
	GameObject::DeActivate();
	counter = 0;
	SetNewPos(initialPos,0,0);
}





