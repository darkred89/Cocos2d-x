
#define MAX_POS_THRESHOLD 2

#include "Components.h"

USING_NS_CC;


GameObject::GameObject(std::string fileName,int id)
{
	this->id = id;
	Sprite::init();
	this->setTexture(fileName);
}

void GameObject::init(cocos2d::Vec2 startPos, float startRotation, float scale)
{
	this->setPosition(startPos);
	this->setScale(scale);
	this->setRotation(startRotation);	
}

void GameObject::update(float delta)
{

}

void GameObject::activate()
{
	colliding = true;
	active = true;
	this->scheduleUpdate();
}

void GameObject::deActivate()
{
	this->unscheduleUpdate();
	stopAllActions();
	active = false;
	colliding = false;
}

void GameObject::die()
{
	colliding = false;
	this->unscheduleUpdate();
	//active = false;
}

void GameObject::goAway()
{

}

float Moving::lookTo(const cocos2d::Vec2& point)
{
	if (movingSprite == NULL) {
		log("missing movingSprite to move");
		return 0;
	}

	float x = point.x - movingSprite->getPosition().x;
	float y = point.y - movingSprite->getPosition().y;

	return atan2(x, y) * 180 / M_PI;
}

void Moving::setNewPos(cocos2d::Vec2 position, float rotation, int speed) 
{
	currentRotation = rotation * 180 / M_PI;;

	movingSprite->setPosition(position);
	movingSprite->setRotation(rotation);

	currentRotation = currentRotation / 180 * M_PI; // to radians

	movingSpeed = speed;
}

void Moving::move(float deltaTime) 
{
	movingSprite->setPosition(Vec2(movingSprite->getPosition().x + movingSpeed * deltaTime*sin(currentRotation), movingSprite->getPosition().y + movingSpeed * deltaTime*cos(currentRotation)));
}

bool Moving::checkOutScreen() 
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

void Animating::testAnimateAction(Sprite* sprite, float animMultiplyScale, float animScalePeriod)
{
	auto animAction = ScaleBy::create(animScalePeriod/2, animMultiplyScale);
	auto move_ease_in = EaseInOut::create(animAction->clone(),2);
	auto animActionRev = ScaleBy::create(animScalePeriod/2, 1/ animMultiplyScale);
	auto move_ease_out = EaseInOut::create(animActionRev->clone(),2);
	
	auto seq = Sequence::create(move_ease_in, move_ease_out, nullptr);
	auto repeatForever = cocos2d::RepeatForever::create(seq);

	sprite->runAction(repeatForever);
}

void Animating::spriteBlinkAnim(Sprite* sprite, float blinkTime)
{
	auto blinkIn = FadeIn::create(0);
	auto blinkOut = FadeOut::create(0);
	auto delayT = DelayTime::create(blinkTime);

	auto seq = Sequence::create( blinkIn, delayT, blinkOut, nullptr);

	sprite->runAction(seq);
}

void Animating::fishDie(GameObject* fish, float duration)
{
	auto colorChange = TintTo::create(duration / 2, 50, 50, 50);
	auto fadeOut= FadeOut::create(duration);

	auto deactivate = CallFunc::create([fish]() {fish->deActivate(); });

	auto colorBack= TintTo::create(0, 255, 255, 255);
	auto fadeIn= FadeIn::create(0);

	auto seq = Sequence::create(fadeOut,deactivate,colorBack, fadeIn, deactivate, nullptr);

	fish->runAction(colorChange);
	fish->runAction(seq);
}

void PoolHolder::push(GameObject* gameObject)
{
	node = new PoolHolderNode();
	node->gameObject = gameObject;
	node->nextNode = NULL;

	lastNode->nextNode = node;
	lastNode = node;
}

PoolHolder::PoolHolder(GameObject* fisrtGameObject)
{
	node = new PoolHolderNode();
	node->gameObject = fisrtGameObject;
	node->nextNode = NULL;

	firstNode = node;
	lastNode = node;
}

GameObject* PoolHolder::getFreeGameObject()
{
	bool gotGameObject = false;
	PoolHolderNode* currentNode = firstNode;

	while (!gotGameObject)
	{
		if (!currentNode->gameObject->isActive())
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




