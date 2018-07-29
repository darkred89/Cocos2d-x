
#define MAX_POS_THRESHOLD 2

#include "Components.h"

USING_NS_CC;

#pragma region GameObject

GameObject::GameObject(std::string fileName, Scene* scene,int id)
{
	this->id = id;
	//this->initWithSpriteFrameName(fileName);
	//this = dynamic_cast<GameObject*>(Sprite::create(fileName));
	this->init();
	this->setTexture(fileName);
	//this->setPosition
	scene->addChild(this, 1);
}

void GameObject::Init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	this->setPosition(startPos);
	this->setScale(scale);
	this->setRotation(startRotation);
}

void GameObject::Run(float deltaTime) {}
void GameObject::Activate()
{
	active = true;
}

void GameObject::DeActivate()
{
	active = false;
}

#pragma endregion

#pragma region Moving

float Moving::LookTo(cocos2d::Vec2 point) 
{
	if (movingSprite == NULL) {
		log("missing movingSprite to move");
		return 0;
	}

	float x = point.x - movingSprite->getPosition().x;// - sprite->getContentSize().width;
	float y = point.y - movingSprite->getPosition().y;// -sprite->getContentSize().width;

	//currentRotation = atan2(x, y) * 180 / M_PI;

	return atan2(x, y) * 180 / M_PI;
	//log("current rotation: %f", currentRotation);

	//movingSprite->setRotation(currentRotation + 180);

	//currentRotation = currentRotation / 180 * M_PI; // to radians
}

void Moving::SetNewPos(cocos2d::Vec2 position, float rotation, int speed) 
{
	currentRotation = rotation * 180 / M_PI;;

	movingSprite->setPosition(position);
	movingSprite->setRotation(rotation);

	currentRotation = currentRotation / 180 * M_PI; // to radians

	movingSpeed = speed;
}

void Moving::Move(float deltaTime) 
{
	movingSprite->setPosition(Vec2(movingSprite->getPosition().x + movingSpeed * deltaTime*sin(currentRotation), movingSprite->getPosition().y + movingSpeed * deltaTime*cos(currentRotation)));
}

bool Moving::CheckOutScreen() 
{
	Vec2 currentPos = movingSprite->getPosition();
	if (currentPos.x > maxPos.x + MAX_POS_THRESHOLD || currentPos.x<-MAX_POS_THRESHOLD || currentPos.y > maxPos.y + MAX_POS_THRESHOLD || currentPos.y < -MAX_POS_THRESHOLD) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

#pragma endregion

#pragma region Animating

void Animating::AnimateScale(float currentScale, float animIncrementScale, float animScalePeriod)
{
	animScale = true;
	this->animScalePeriod =  2* M_PI / animScalePeriod;
	this->currentScale = currentScale;
	this->animIncrementScale = animIncrementScale;
}

void Animating::RunAnimateScale()
{	
	animatingSprite->setScale(animIncrementScale*(1 - sin(animScalePeriod*counter)) + currentScale);
	//log("bubble scale %f",animatingSprite->getScale());
}

void Animating::Animate(float deltaTime)
{
	counter += deltaTime;
	if(animScale) RunAnimateScale();

	if (animSprite)
	{
		if (counter > setAnimSpriteTime)
		{
			animatingSprite->setTexture(defaultSprite);
			animSprite = false;
		}
	}
}

void Animating::AnimateSprite(std::string defaultSprite,std::string nextSprite, float duration)
{
	if (animSprite) return;

	this->defaultSprite = defaultSprite;
	animSprite = true;
	setAnimSpriteTime = counter+ duration;
	animatingSprite->setTexture(nextSprite);
}

#pragma endregion

#pragma region Pool
void PoolHolder::Push(GameObject* gameObject)
{
	node = new PoolHolderNode();
	node->gameObject = gameObject;
	node->nextNode = NULL;

	LastNode->nextNode = node;
	LastNode = node;
}

PoolHolder::PoolHolder(GameObject* fisrtGameObject)
{
	node = new PoolHolderNode();
	node->gameObject = fisrtGameObject;
	node->nextNode = NULL;

	FirstNode = node;
	LastNode = node;
}

GameObject* PoolHolder::GetFreeGameObject()
{
	bool gotGameObject = false;
	PoolHolderNode* currentNode = FirstNode;

	while (!gotGameObject)
	{
		if (!currentNode->gameObject->active)
		{
			gotGameObject = true;
			return(currentNode->gameObject);
		}
		else if (currentNode->nextNode != NULL)
		{
			currentNode = currentNode->nextNode;
			continue;
		}
		else
		{
			return NULL;
		}
	}
}

void PoolHolder::RunObjects(float deltaTime)
{
	bool runObjects = true;
	PoolHolderNode* currentNode = FirstNode;
	while (runObjects)
	{
		if (currentNode->gameObject->active) currentNode->gameObject->Run(deltaTime);
		if (currentNode->nextNode == NULL)
		{
			runObjects = false;
		}
		else
		{
			currentNode = currentNode->nextNode;
		}
	}
}

#pragma endregion



