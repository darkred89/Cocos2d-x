/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef SPAWNER_H
#define SPAWNER_H

#pragma once

#define INITIAL_POS_X -100
#define INITIAL_POS_Y -100

#define FISH_SCALE 0.15

#define BUBBLE_SCALE 0.15
#define BUBBLE_ANIM_INCREMENT_SCALE 0.05
#define BUBBLE_ANIM_SCALE_PERIOD 1 //in seconds

#define TARGET_SCALE 0.15
#define FISH_SPEED 20
#define BUBBLE_SPEED 50

#define RELOAD_TIME 2

#define FISH_COUNT 100
#define BUBBLE_COUNT 100


#include "Fish.h"
#include "EnemyFish.h"
#include "Bubble.h"

#include <cmath> 
#include <stdlib.h> 
#include <cstdlib>
#include <ctime>

class Spawner
{
public:

	static float graphicsScale;
	static cocos2d::Vec2 maxCoord;

	Spawner(cocos2d::Scene* _scene, float scale);

	void Run(float deltaTime);

	void SpawnFish();
	void SpawnEnemyFish();
	void SpawnBubble();

	void TurnPlayerFish(cocos2d::Vec2 lookPos);
	bool CollisionDetection(cocos2d::Sprite*, cocos2d::Sprite*);
	
	Bubble* bubble;
	Fish* playerFish;
	EnemyFish* enemyFish;

	

private:
	//Bubble* bubbleList[FISH_COUNT];
	void CheckFishCollide();
	void CheckBubbleCollide();

	float fireCounter;
	bool canFire;
	
	cocos2d::Scene* scene;
};


class EnemyFishHolder
{
public:
	Fish* fishList[FISH_COUNT];

};

struct BubbleNode
{
	Bubble* bubble;
	Bubble* nextBubble;
	//Bubble*	
};

class BubbleHolder
{
public:
	BubbleNode FirstBubble;
	BubbleNode LastBubble;

	void Push(Bubble* bubble);
};




#endif // __HELLOWORLD_SCENE_H__
