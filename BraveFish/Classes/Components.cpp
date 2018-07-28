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

#define MAX_POS_THRESHOLD 2

//#include "cocos2d.h"
#include "Components.h"

USING_NS_CC;

#pragma region Moving

void Moving::LookTo(cocos2d::Vec2 point) {

	if (movingSprite == NULL) {
		log("missing movingSprite to move");
		return;
	}

	float x = point.x - movingSprite->getPosition().x;// - sprite->getContentSize().width;
	float y = point.y - movingSprite->getPosition().y;// -sprite->getContentSize().width;

	currentRotation = atan2(x, y) * 180 / M_PI;

	//log("x: %f", x);
	//log("y: %f", y);
	//log("angle: %f", currentRotation);

	movingSprite->setRotation(currentRotation + 180);

	currentRotation = currentRotation / 180 * M_PI; // to radians
}

void Moving::SetNewPos(cocos2d::Vec2 position, float rotation, int speed) {

	currentRotation = rotation * 180 / M_PI;;

	movingSprite->setPosition(position);
	movingSprite->setRotation(rotation);

	currentRotation = currentRotation / 180 * M_PI; // to radians

	movingSpeed = speed;

	//log("Speed is %f", movingSpeed);

}

void Moving::Move(float deltaTime) {

	movingSprite->setPosition(Vec2(movingSprite->getPosition().x + movingSpeed * deltaTime*sin(currentRotation), movingSprite->getPosition().y + movingSpeed * deltaTime*cos(currentRotation)));
}

bool Moving::CheckOutScreen() {
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

void Animating::AnimateScale(float deltaTime) {
	counter += deltaTime;
	animatingSprite->setScale(animIncrementScale*(1 - sin(animScalePeriod*counter)) + currentScale);
	log("bubble scale %f",animatingSprite->getScale());
}

#pragma endregion




