
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#pragma once

#define ENEMY_COUNT 3

#include "cocos2d.h"
#include "Spawner.h"

class Game : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	static bool gameOver;

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
	void InitialSetup();
	void update(float) override;
	void GameOver();

	cocos2d::Label* label;
	int counter;

	cocos2d::Sprite* target;
	Spawner* spawner;
	
	

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	

    // implement the "static create()" method manually
    CREATE_FUNC(Game);

private:
	float graphicsScale;	
};

#endif // __HELLOWORLD_SCENE_H__
