
#include "EnemyFish.h"
#include "Spawner.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

USING_NS_CC;

EnemyFish::EnemyFish(std::string fileName, cocos2d::Scene* scene, int id):GameObject::GameObject(fileName, scene, id)
{
	
}

void EnemyFish::Init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	GameObject::Init(startPos, startRotation, scale);
	movingSprite = this;
	initialPos = startPos;
	SetNewPos(startPos, 0, 0);
	active = false;
}

void EnemyFish::Activate() 
{	
	GameObject::Activate();
	SetNewPos(GetRandomCoord(), 0, FISH_SPEED+ rand() % FISH_SPEED);
	currentRotation = LookTo(target);
	setRotation(currentRotation+180);
	currentRotation= currentRotation / 180 * M_PI;
}

void EnemyFish::DeActivate() 
{
	GameObject::DeActivate();
	SetNewPos(initialPos, 0, 0);
	LookTo(target);
}

Vec2 EnemyFish::GetRandomCoord() 
{
	int side = rand() % 4;
	Vec2 randomPos = Vec2(0, 0);
	switch (side)
	{
		case 0: //TOP
			randomPos.y = Spawner::maxCoord.y;
			randomPos.x= rand() % static_cast<int>(Spawner::maxCoord.x);
			break;
		case 1: //RIGH
			randomPos.y = rand() % static_cast<int>(Spawner::maxCoord.y);
			randomPos.x = Spawner::maxCoord.x;
			break;
		case 2: //BOTTOM
			randomPos.y = 0;// origin.y;
			randomPos.x = rand() % static_cast<int>(Spawner::maxCoord.x);
			break;
		case 3: //LEFT
			randomPos.y = rand() % static_cast<int>(Spawner::maxCoord.y);
			randomPos.x = 0;
			break;
	}
	//log("pos x: %f", randomPos.x);
	return randomPos;
}

void EnemyFish::SetTarget(Vec2 point) 
{
	target = point;
	Moving::LookTo(point);
}

void EnemyFish::Run(float deltaTime) 
{
	if (!active) return;
	Move(deltaTime);
}




