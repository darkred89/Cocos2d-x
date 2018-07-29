
#include "Spawner.h"
#include "cocos2d.h"
#include "Game.h"

USING_NS_CC;

float Spawner::graphicsScale;
Vec2 Spawner::maxCoord;

bool bubbleInitialised = false;
float scaleQuadCoef;

float fishCollideQuadRad;
float bubbleCollideQuadRad;

int bubbleCounter;
int enemyFishCounter;
int spawnCounter;
int spawnAmount;
float spawnCooldown;

float reloadingTime;

bool touching;

Spawner::Spawner(Scene* _scene, float scale)
{
	reloadingTime = 0;
	bubbleCounter = 0;
	enemyFishCounter = 0;
	spawnCounter = 0;
	spawnAmount = 1;
	spawnCooldown = 0;

	touching = false;
	touchPos = Vec2(0, 0);

	scene = _scene;
	graphicsScale = scale;
	scaleQuadCoef = graphicsScale * graphicsScale*FISH_SCALE*FISH_SCALE;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maxCoord = Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y);

	SpawnFish();

	Bubble* newBubble = new Bubble(BUBBLE_IMAGE, scene, bubbleCounter);
	newBubble->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale,playerFish);
	bubbleCounter++;
	bubbleHolder = new BubbleHolder(newBubble);	

	EnemyFish* newEnemyFish = new EnemyFish("badFish.png", scene, enemyFishCounter);
	newEnemyFish->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, FISH_SCALE*graphicsScale);
	newEnemyFish->SetTarget(playerFish->getPosition());
	enemyFishCounter++;
	enemyFishHolder = new EnemyFishHolder(newEnemyFish);

	target = new GameObject(BUBBLE_IMAGE, scene, 0);
	target->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, BUBBLE_SCALE*graphicsScale*0.3);
	target->setOpacity(0);
}

void Spawner::SpawnFish()
{
	//return;
	playerFish =  new Fish(FISH_IMAGE,scene,1);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 centrCoord = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	playerFish->Init(centrCoord, 0, FISH_SCALE*graphicsScale);
	playerFish->Activate();
}

void Spawner::SpawnEnemyFish()
{
	//enemyFish =  new EnemyFish("badFish.png", scene, 1);
	//enemyFish->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, FISH_SCALE*graphicsScale);
	//enemyFish->SetTarget(playerFish->getPosition());
	//enemyFish->Activate();

	GameObject* newEnemyFish = enemyFishHolder->GetFreeGameObject();

	if (newEnemyFish != NULL) {
		newEnemyFish->Activate();
	}
	else
	{
		EnemyFish* nextEnemyFish = new EnemyFish("badFish.png", scene, 1);
		nextEnemyFish->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, FISH_SCALE*graphicsScale);
		enemyFishCounter++;
		enemyFishHolder->Push(nextEnemyFish);
		nextEnemyFish->SetTarget(playerFish->getPosition());
		nextEnemyFish->Activate();
	}
}

void Spawner::SetTouch(Vec2 touchPos)
{	
	touching = true;
	TurnPlayerFish(touchPos);
	this->touchPos = touchPos;
}

void Spawner::TouchEnded()
{
	touching = false;
}

void Spawner::CheckTouch()
{
	if (!CheckEnemyFishTouched(touchPos)) return;	
	SpawnBubble();	
}

bool Spawner::CheckEnemyFishTouched(Vec2 touchPos)
{
	target->setPosition(touchPos);

	if (CheckFishCollide(target, false))
	{
		return true;
	}
	return false;
}

void Spawner::SpawnBubble()
{
	if (reloadingTime > 0) return;

	if(playerFish->active) 
		playerFish->AnimateSprite(FISH_IMAGE, FISH_BUBBLE_IMAGE, FISH_FIREANIM_TIME);

	reloadingTime = RELOAD_TIME;

	GameObject* newBubble = bubbleHolder->GetFreeGameObject();

	if (newBubble != NULL) {
		newBubble->Activate();
	}
	else 
	{
		Bubble* nextBubble = new Bubble("bubble.png", scene, bubbleCounter);
		nextBubble->Init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale, playerFish);
		bubbleCounter++;
		bubbleHolder->Push(nextBubble);
		nextBubble->Activate();
	}	
}

void Spawner::Run(float deltaTime) 
{
	SpawnDecide(deltaTime);
	playerFish->Run(deltaTime);
	RunBubbles(deltaTime);
	RunEnemyFishes(deltaTime);
	
	CheckBubbleCollide();

	if (CheckFishCollide(playerFish,false))
	{
		playerFish->DeActivate();
		Game::gameOver = true;
	}

	if (reloadingTime > 0) {
		reloadingTime -= deltaTime;
	}

	if (touching)
	{
		CheckTouch();
	}
}

void Spawner::SpawnDecide(float deltaTime)
{
	if (spawnCooldown <= 0)
	{
		for (int i = 0; i < spawnAmount; i++) 
		{
			SpawnEnemyFish();
		}
		spawnCounter++;
		if (spawnCounter > FISH_SPAWN_COUNTER_INCREASE)
		{
			spawnCounter = - spawnAmount* FISH_SPAWN_COUNTER_INCREASE/2;
			spawnAmount++;
		}
		spawnCooldown = FISH_SPAWN_DELAY;
	}
	spawnCooldown -= deltaTime;
}

void Spawner::RunEnemyFishes(float deltaTime)
{
	enemyFishHolder->RunObjects(deltaTime);
}

void Spawner::RunBubbles(float deltaTime)
{	
	bubbleHolder->RunObjects(deltaTime);
}

bool Spawner::CheckFishCollide(GameObject* gameObject, bool deactivateFish) 
{
	bool runFishCollide = true;
	enemyFishNode = enemyFishHolder->FirstNode;
	while (runFishCollide)
	{
		if (enemyFishNode->gameObject->active)
		{
			if (CollisionDetection(enemyFishNode->gameObject, gameObject))
			{
				if (deactivateFish) enemyFishNode->gameObject->DeActivate();
				return true;
			}
		}
		if (enemyFishNode->nextNode == NULL)
		{
			runFishCollide = false;
		}
		else
		{
			enemyFishNode = enemyFishNode->nextNode;
		}
	}
	return false;
}

void Spawner::CheckBubbleCollide() 
{
	
	bool runBubbles = true;
	bubbleNode = bubbleHolder->FirstNode;
	while (runBubbles)
	{
		if (bubbleNode->gameObject->active)
		{
			if(CheckFishCollide(bubbleNode->gameObject,true))
			{
				bubbleNode->gameObject->DeActivate();
				return;
			}
		}	
		if (bubbleNode->nextNode == NULL)
		{
			runBubbles = false;
		}
		else
		{
			bubbleNode = bubbleNode->nextNode;
		}
	}
	
}

void Spawner::TurnPlayerFish(Vec2 lookPos)
{
	if (!playerFish->active) return;
	playerFish->Turn(playerFish->LookTo(lookPos) +180);
}

bool Spawner::CollisionDetection(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2) 
{
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
		//log("Collided");
		return true;
	}

	return false;
}


BubbleHolder::BubbleHolder(GameObject* fisrtBubble):PoolHolder::PoolHolder(fisrtBubble){}

EnemyFishHolder::EnemyFishHolder(GameObject* fisrtEnemyFish) : PoolHolder::PoolHolder(fisrtEnemyFish) {}



