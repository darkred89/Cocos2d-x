
#ifndef SPAWNER_H
#define SPAWNER_H

#pragma once

#define INITIAL_POS_X -100
#define INITIAL_POS_Y -100

#define FISH_SCALE 0.15
#define FISH_IMAGE "fish.png"
#define FISH_BUBBLE_IMAGE "fishBubble.png"
#define FISH_TURN_RATE 220 //in grads
#define ENEMY_FISH_IMAGE "badFish.png"
#define RELOAD_TIME 0.3
#define FISH_FIREANIM_TIME RELOAD_TIME*0.6

#define BUBBLE_SCALE 0.15
#define BUBBLE_ANIM_INCREMENT_SCALE 0.05
#define BUBBLE_ANIM_MULTIPLY_SCALE 1.5
#define BUBBLE_ANIM_SCALE_PERIOD 1 //in seconds

#define TARGET_SCALE 0.15
#define FISH_SPEED 15
#define BUBBLE_SPEED 100
#define BUBBLE_IMAGE "bubble.png"


#define FISH_SPAWN_DELAY 2
#define FISH_SPAWN_COUNTER_INCREASE 3
#define FISH_COUNT 100
#define BUBBLE_COUNT 100


#include "Fish.h"
#include "EnemyFish.h"
#include "Bubble.h"

#include <cmath> 
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>

class BubbleHolder :public PoolHolder
{
public:
	BubbleHolder(GameObject* fisrtBubble);
};

class EnemyFishHolder :public PoolHolder
{
public:
	EnemyFishHolder(GameObject* fisrtEnemyFish);
};


class GameController
{
public:
	static float graphicsScale;
	static cocos2d::Vec2 maxCoord;

	GameController(cocos2d::Node* _scene, float scale);

	void Run(float deltaTime);

	void SpawnFish();
	void SpawnEnemyFish();
	void SpawnBubble();

	void SetTouch(cocos2d::Vec2 touchPos);
	void TouchEnded();
	
	void update(float);

	GameObject* target;

	Fish* playerFish;

	BubbleHolder* bubbleHolder;
	PoolHolderNode* bubbleNode;
	
	EnemyFishHolder* enemyFishHolder;
	PoolHolderNode* enemyFishNode;

private:
	void TurnPlayerFish(cocos2d::Vec2 lookPos);
	bool CollisionDetection(cocos2d::Sprite*, cocos2d::Sprite*);	

	void CheckTouch();
	bool CheckFishCollide(GameObject* gameObject, bool deactivateFish);
	void CheckBubbleCollide();
	bool CheckEnemyFishTouched(cocos2d::Vec2 touchPos);

	void RunBubbles(float deltaTime);
	void RunEnemyFishes(float deltaTime);
	void SpawnDecide(float deltaTime);

	float fireCounter;
	bool canFire;
	int currentSpawnQuantity;

	cocos2d::Vec2 touchPos;

	cocos2d::Node* scene;
};

#endif
