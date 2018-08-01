
#include "EnemyFish.h"
#include "GameController.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

USING_NS_CC;

EnemyFish::EnemyFish(std::string fileName, int id):GameObject::GameObject(fileName, id)
{
	
}

void EnemyFish::init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	GameObject::init(startPos, startRotation, scale);
	movingSprite = this;
	initialPos = startPos;
	setNewPos(startPos, 0, 0);
}

void EnemyFish::activate() 
{	
	GameObject::activate();
	setNewPos(getRandomCoord(), 0, FISH_SPEED+ rand() % FISH_SPEED);
	setCurrentRotation(lookTo(target));
	setCurrentRotationToRadians();
}

void EnemyFish::deActivate() 
{
	GameObject::deActivate();
	setNewPos(initialPos, 0, 0);
	lookTo(target);
	
}

void EnemyFish::goAway()
{
	setNewPos(initialPos, 0, 0);
}

void EnemyFish::die()
{
	GameObject::die();
	fishDie(this, 1.0f);
}

Vec2 EnemyFish::getRandomCoord() 
{
	int side = rand() % 4;
	Vec2 randomPos = Vec2(0, 0);
	switch (side)
	{
		case 0: //TOP
			randomPos.y = GameController::maxCoord.y;
			randomPos.x= rand() % static_cast<int>(GameController::maxCoord.x);
			break;
		case 1: //RIGH
			randomPos.y = rand() % static_cast<int>(GameController::maxCoord.y);
			randomPos.x = GameController::maxCoord.x;
			break;
		case 2: //BOTTOM
			randomPos.y = 0;// origin.y;
			randomPos.x = rand() % static_cast<int>(GameController::maxCoord.x);
			break;
		case 3: //LEFT
			randomPos.y = rand() % static_cast<int>(GameController::maxCoord.y);
			randomPos.x = 0;
			break;
	}
	//log("pos x: %f", randomPos.x);
	return randomPos;
}

void EnemyFish::setTarget(Vec2 point) 
{
	target = point;
	Moving::lookTo(point);
}

void EnemyFish::update(float delta)
{
	move(delta);
}



