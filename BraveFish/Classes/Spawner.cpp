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

float reloadingTime;

Spawner::Spawner(Scene* _scene, float scale)
{
	//GameObject* testObject =new  GameObject("fish.png", _scene, Vec2(50, 50));

	reloadingTime = 0;
	bubbleCounter = 0;

	scene = _scene;
	graphicsScale = scale;
	scaleQuadCoef = graphicsScale * graphicsScale*FISH_SCALE*FISH_SCALE;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maxCoord = Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y);

	//bubble = new Bubble(scene, Vec2(INITIAL_POS_X, INITIAL_POS_Y), maxCoord, bubbleCounter);
	Bubble* newBubble = new Bubble("bubble.png", scene, bubbleCounter);
	newBubble->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale);
	bubbleCounter++;

	bubbleHolder = new BubbleHolder(newBubble);

	
}

void Spawner::SpawnFish()
{
	//return;
	playerFish =  new Fish("fish.png",scene,1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 centrCoord = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	playerFish->Init(centrCoord, 0, FISH_SCALE*graphicsScale);
	playerFish->Activate();
}

void Spawner::SpawnEnemyFish()
{
	enemyFish =  new EnemyFish("badFish.png", scene, 1);
	//enemyFish->LookTo(playerFish->sprite->getPosition());
	enemyFish->Init(Vec2(-100, -100), 0, FISH_SCALE*graphicsScale);
	//enemyFish->SetTarget(playerFish->sprite->getPosition());
	//enemyFish->SetTarget(Vec2(200, 200));
	enemyFish->SetTarget(playerFish->getPosition());
	enemyFish->Activate();
}

void Spawner::SpawnBubble()
{
	//return;
	playerFish->setTexture("fishBubble.png");

	if (reloadingTime > 0) return;
	//return;

	/*
	if (!bubbleInitialised) 
	{
		bubble = new Bubble(scene, Vec2(INITIAL_POS_X,INITIAL_POS_Y), maxCoord, bubbleCounter);
		//bubble->id = bubbleCounter;
		bubbleCounter++;
		bubbleInitialised = true;		
	}

	bubble->SetNewPos(playerFish->sprite->getPosition(), playerFish->currentRotation, BUBBLE_SPEED);
	bubble->Activate();
	*/
	reloadingTime = RELOAD_TIME;

	bool gotBubble = false;

	BubbleNode* currentBubbleNode = bubbleHolder->FirstBubbleNode;

	while (!gotBubble) {
		
		if (!currentBubbleNode->bubble->active) {

			currentBubbleNode->bubble->SetNewPos(playerFish->getPosition(), playerFish->currentRotation, BUBBLE_SPEED);
			currentBubbleNode->bubble->Activate();
			gotBubble = true;
			log("Fired bubble %d", currentBubbleNode->bubble->id);
		}
		else if (currentBubbleNode->nextBubbleNode != NULL) {
			currentBubbleNode = currentBubbleNode->nextBubbleNode;
			continue;
		}
		else
		{
			BubbleNode* newBubbleNode = new BubbleNode();
			
			//Bubble* newBubble =new Bubble(scene, Vec2(INITIAL_POS_X, INITIAL_POS_Y), maxCoord, bubbleCounter);
			Bubble* newBubble = new Bubble("bubble.png", scene, bubbleCounter);
			newBubble->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale);
			bubbleCounter++;

			newBubbleNode->bubble = newBubble;
			newBubbleNode->nextBubbleNode = NULL;

			bubbleHolder->Push(newBubble);

			currentBubbleNode = newBubbleNode;
			continue;
		}
		//bubbleHolder.FirstBubbleNode->bubble

	}
	
}

void Spawner::Run(float deltaTime) 
{
	//if (bubbleInitialised) 
	//{
	//	bubble->Run(deltaTime);
	//	CheckBubbleCollide();
	//}
	
	RunBubbles(deltaTime);
	//if (enemyFish->active) 
	{
		enemyFish->Run(deltaTime);
	}
	
	CheckBubbleCollide();
	CheckFishCollide();
	

	if (reloadingTime > 0) {
		reloadingTime -= deltaTime;
	}
}

void Spawner::RunBubbles(float deltaTime)
{
	bool runBubbles = true;

	bubbleNode = bubbleHolder->FirstBubbleNode;

	while (runBubbles)
	{
		if (bubbleNode->bubble->active) bubbleNode->bubble->Run(deltaTime);

		if (bubbleNode->nextBubbleNode == NULL)
		{
			runBubbles = false;
		}
		else
		{
			bubbleNode = bubbleNode->nextBubbleNode;
		}
	}
}

void Spawner::CheckFishCollide() {
	if (CollisionDetection(playerFish, enemyFish))
	{
		Game::gameOver = true;
	}
}

void Spawner::CheckBubbleCollide() {

	bool runBubbles = true;

	bubbleNode = bubbleHolder->FirstBubbleNode;

	while (runBubbles)
	{
		if (bubbleNode->bubble->active)
		{
			//bubbleNode->bubble->Run(deltaTime);
			if (CollisionDetection(bubbleNode->bubble, enemyFish))
			{
				//enemyFish->enemyFishSprite->setPosition(enemyFish->GetRandomCoord());
				//enemyFish->LookTo(playerFish->sprite->getPosition());
				enemyFish->DeActivate();
				enemyFish->Activate();
				bubbleNode->bubble->DeActivate();
			}
		}

		if (bubbleNode->nextBubbleNode == NULL)
		{
			runBubbles = false;
		}
		else
		{
			bubbleNode = bubbleNode->nextBubbleNode;
		}
	}

	
}

void Spawner::TurnPlayerFish(Vec2 lookPos)
{
	if (!playerFish->active) return;
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

void BubbleHolder::Push(Bubble* bubble) {

	bubbleNode = new BubbleNode();

	bubbleNode->bubble = bubble;
	bubbleNode->nextBubbleNode = NULL;

	LastBubbleNode->nextBubbleNode =  bubbleNode;

	LastBubbleNode = bubbleNode;
}

BubbleHolder::BubbleHolder(Bubble* firstBubble) {
	bubbleNode = new BubbleNode();
	bubbleNode->bubble = firstBubble;
	bubbleNode->nextBubbleNode = NULL;

	FirstBubbleNode = bubbleNode;
	LastBubbleNode = bubbleNode;
}


