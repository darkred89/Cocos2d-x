
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameController.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	static bool gameOverFlag;

private:

	cocos2d::Label* mainLabel;
	GameController* gameController;
	float graphicsScale;

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void initialSetup();
	void update(float) override;

	void gameOver();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	CREATE_FUNC(GameScene);
};

#endif
