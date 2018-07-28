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


#include "Spawner.h"
#include "cocos2d.h"
#include "Game.h"

USING_NS_CC;

//Sprite* EnemyFish::sprite;
//int n;
//Vec2 EnemyFish : :target;

//float angle;

float Spawner::graphicsScale;
Vec2 Spawner::maxCoord;

bool bubbleInitialised = false;
float scaleQuadCoef;

float fishCollideQuadRad;
float bubbleCollideQuadRad;

int bubbleCounter;

Spawner::Spawner(Scene* _scene, float scale)
{
	scene = _scene;
	graphicsScale = scale;
	scaleQuadCoef = graphicsScale * graphicsScale*FISH_SCALE*FISH_SCALE;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maxCoord = Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y);

	bubbleCounter = 0;
}

void Spawner::SpawnFish()
{
	playerFish =  new Fish(scene);
	
}

void Spawner::SpawnEnemyFish()
{
	enemyFish = new EnemyFish(scene);
	//enemyFish->LookTo(playerFish->sprite->getPosition());
	
	enemyFish->SetTarget(playerFish->sprite->getPosition());
	enemyFish->Activate();
}

void Spawner::SpawnBubble()
{
	//return;

	if (!bubbleInitialised) 
	{
		bubble = new Bubble(scene, Vec2(INITIAL_POS_X,INITIAL_POS_Y), maxCoord, bubbleCounter);
		//bubble->id = bubbleCounter;
		bubbleCounter++;
		bubbleInitialised = true;		
	}

	bubble->SetNewPos(playerFish->sprite->getPosition(), playerFish->currentRotation, BUBBLE_SPEED);
	bubble->Activate();
	
}

void Spawner::Run(float deltaTime) 
{
	if (bubbleInitialised) 
	{
		bubble->Run(deltaTime);
		CheckBubbleCollide();
	}
	
	//if (enemyFish->active) 
	{
		enemyFish->Run(deltaTime);
	}
	
	CheckFishCollide();
	
}

void Spawner::CheckFishCollide() {
	if (CollisionDetection(playerFish->sprite, enemyFish->sprite))
	{
		Game::gameOver = true;
	}
}

void Spawner::CheckBubbleCollide() {
	if (CollisionDetection(bubble->sprite, enemyFish->sprite))
	{
		//enemyFish->enemyFishSprite->setPosition(enemyFish->GetRandomCoord());
		//enemyFish->LookTo(playerFish->sprite->getPosition());
		enemyFish->DeActivate();
		enemyFish->Activate();
		bubble->DeActivate();
	}
}

void Spawner::TurnPlayerFish(Vec2 lookPos)
{
	playerFish->LookTo(lookPos);
}

bool Spawner::CollisionDetection(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2) {

	Rect rect1 = sprite1->getBoundingBox();
	Rect rect2 = sprite2->getBoundingBox();

	float xA = sprite1->getPosition().x;
	float yA = sprite1->getPosition().y;

	float xB = sprite2->getPosition().x;
	float yB = sprite2->getPosition().y;

	float rA = sprite1->getContentSize().width / 2;
	float rB = sprite2->getContentSize().width / 2;

	if ((xA - xB)*(xA - xB) + (yA - yB)*(yA - yB) < ((rA + rB)*(rA + rB))*scaleQuadCoef)
	{
		log("Collided");
		return true;
	}

	return false;
}


