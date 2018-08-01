
#include "GameController.h"
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

float GameController::graphicsScale;
Vec2 GameController::maxCoord;

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

GameController::GameController(Node* playNode, float scale)
{
	reloadingTime = 0;
	bubbleCounter = 0;
	enemyFishCounter = 0;
	spawnCounter = 0;
	spawnAmount = 1;
	spawnCooldown = 0;

	touching = false;
	touchPos = Vec2(0, 0);

	this->playNode = playNode;
	graphicsScale = scale;
	scaleQuadCoef = graphicsScale * graphicsScale*FISH_SCALE*FISH_SCALE;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maxCoord = Vec2(visibleSize.width + origin.x, visibleSize.height + origin.y);

	spawnFish();

	Bubble* newBubble = new Bubble(BUBBLE_IMAGE, bubbleCounter);
	newBubble->init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale,playerFish);
	bubbleCounter++;
	bubbleHolder = new BubbleHolder(newBubble);	
	this->playNode->addChild(newBubble,0);

	EnemyFish* newEnemyFish = new EnemyFish("badFish.png", enemyFishCounter);
	newEnemyFish->init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, FISH_SCALE*graphicsScale);
	newEnemyFish->setTarget(playerFish->getPosition());
	enemyFishCounter++;
	enemyFishHolder = new EnemyFishHolder(newEnemyFish);
	this->playNode->addChild(newEnemyFish,0);

	target = new GameObject(BUBBLE_IMAGE, 0);
	target->init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, BUBBLE_SCALE*graphicsScale*0.3);
	target->setOpacity(0);
	
}



void GameController::spawnFish()
{
	//return;
	playerFish =  new Fish(FISH_IMAGE,1);
	playNode->addChild(playerFish);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 centrCoord = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	playerFish->init(centrCoord, 0, FISH_SCALE*graphicsScale);
	playerFish->activate();

}

void GameController::spawnEnemyFish()
{
	GameObject* newEnemyFish = enemyFishHolder->getFreeGameObject();
	

	if (newEnemyFish != NULL) {
		newEnemyFish->activate();
	}
	else
	{
		EnemyFish* nextEnemyFish = new EnemyFish(ENEMY_FISH_IMAGE, 1);
		playNode->addChild(nextEnemyFish,0);
		nextEnemyFish->init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, FISH_SCALE*graphicsScale);
		
		enemyFishCounter++;
		enemyFishHolder->push(nextEnemyFish);
		nextEnemyFish->setTarget(playerFish->getPosition());
		nextEnemyFish->activate();
		
	}
}

void GameController::setTouch(const Vec2& touchPos)
{	
	touching = true;
	turnPlayerFish(touchPos);
	this->touchPos = touchPos;
}

void GameController::touchEnded()
{
	touching = false;
}

void GameController::checkTouch()
{
	if (!checkEnemyFishTouched(touchPos)) return;	
	spawnBubble();	
}

void GameController::turnPlayerFish(const Vec2& lookPos)
{
	playerFish->turn(playerFish->lookTo(lookPos));
}

bool GameController::checkEnemyFishTouched(const Vec2& touchPos)
{
	target->setPosition(touchPos);

	if (checkFishCollide(target, false))
	{
		return true;
	}
	return false;
}

void GameController::spawnBubble()
{
	if (reloadingTime > 0) return;

	if (playerFish->isActive())
	{
		playerFish->fireBubble();
	}

	reloadingTime = RELOAD_TIME;

	GameObject* newBubble = bubbleHolder->getFreeGameObject();

	if (newBubble != NULL) {
		newBubble->activate();
	}
	else 
	{
		Bubble* nextBubble = new Bubble(BUBBLE_IMAGE, bubbleCounter);
		playNode->addChild(nextBubble,0);
		nextBubble->init(Vec2(INITIAL_POS_X, INITIAL_POS_Y), 0, maxCoord, BUBBLE_SCALE*graphicsScale, playerFish);
		bubbleCounter++;
		bubbleHolder->push(nextBubble);
		nextBubble->activate();
		
	}	
}

void GameController::update(float delta)
{
	spawnDecide(delta);
	checkBubbleCollide();

	if (checkFishCollide(playerFish, false))
	{
		playerFish->die();
		GameScene::gameOverFlag = true;
	}

	if (reloadingTime > 0) {
		reloadingTime -= delta;
	}

	if (touching)
	{
		checkTouch();
	}
}

void GameController::spawnDecide(float deltaTime)
{
	//return;
	if (spawnCooldown <= 0)
	{
		for (int i = 0; i < spawnAmount; i++) 
		{
			spawnEnemyFish();
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


bool GameController::checkFishCollide(GameObject* gameObject, bool deactivateFish)
{
	bool runFishCollide = true;
	enemyFishNode = enemyFishHolder->firstNode;
	while (runFishCollide)
	{
		if (enemyFishNode->gameObject->isColliding())
		{
			if (collisionDetection(enemyFishNode->gameObject, gameObject))
			{
				if (deactivateFish) enemyFishNode->gameObject->die();
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

void GameController::checkBubbleCollide()
{	
	bool runBubbles = true;
	bubbleNode = bubbleHolder->firstNode;
	while (runBubbles)
	{
		if (bubbleNode->gameObject->isColliding())
		{
			if(checkFishCollide(bubbleNode->gameObject,true))
			{
				bubbleNode->gameObject->deActivate();
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


bool GameController::collisionDetection(cocos2d::Sprite* sprite1, cocos2d::Sprite* sprite2)
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



