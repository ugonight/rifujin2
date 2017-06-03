#pragma once
#include "cocos2d.h"

class Control;

class Chapter : public cocos2d::Layer
{
public:
	Chapter();
	//static cocos2d::Scene* createScene(); //継承先で記述

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Chapter);

protected:
	int mFuncType;	// 0:ノベル 1:探索パート 3~:別途定義
	Control* mControl;	//initでEscクラスを代入

	virtual void funcOtherEnd();	//ノベルと探索以外の終了処理

	int mFuncNum;
	std::vector<std::function<int()>> mFuncList;

	virtual void initChapter();
};