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

#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__

#include "cocos2d.h"
//All game objects
class GameObject: public cocos2d::Sprite
{
public:

	GameObject(std::string fileName,cocos2d::Scene* scene,int id);

	virtual void Init(cocos2d::Vec2 startPos, float startRotation, float scale);

	virtual void Run(float);
	virtual void Activate();
	virtual void DeActivate();
	//
	bool active;
	int id;
};

///Basic moving
class Moving
{
public:

	float movingSpeed;
	float turningSpeed;
	cocos2d::Vec2 initialPos;
	cocos2d::Vec2 maxPos;

	float currentRotation;

	//cocos2d::Sprite* movingSprite;
	GameObject* movingSprite;

	virtual void LookTo(cocos2d::Vec2 point);
	void SetNewPos(cocos2d::Vec2 position, float rotation, int speed);
	void Move(float deltaTime);
	bool CheckOutScreen();

};

//Basic animating
class Animating
{
public:

	cocos2d::Sprite* animatingSprite;

	float currentScale;
	float animIncrementScale;
	float animScalePeriod;
	virtual void AnimateScale(float deltaTime);
	float counter;
private:

	
	//virtual void Run(float deltaTime) {};

};
#endif // __HELLOWORLD_SCENE_H__
