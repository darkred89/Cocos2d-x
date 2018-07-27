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


//#include "cocos2d.h"
#include "Components.h"

USING_NS_CC;

void Moving::LookTo(cocos2d::Vec2 point) {

	if (movingSprite == NULL) {
		log("missing movingSprite to move");
		return;
	}

	float x = point.x - movingSprite->getPosition().x;// - sprite->getContentSize().width;
	float y = point.y - movingSprite->getPosition().y;// -sprite->getContentSize().width;



	float angle = atan2(x, y) * 180 / M_PI;

	float currentRotation = angle;

	log("x: %f", x);
	log("y: %f", y);
	log("angle: %f", angle);

	movingSprite->setRotation(angle + 180);
}



