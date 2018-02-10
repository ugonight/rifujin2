#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

class Control;

class Chapter : public cocos2d::Layer
{
public:
	Chapter();
	//static cocos2d::Scene* createScene(); //継承先で記述

	virtual bool init();
	virtual void update(float delta);

	void playFirst();	//最初の場面を実行
	void load(int saveNum);
	
	CREATE_FUNC(Chapter);

protected:
	int mFuncType;	// 0:ノベル 1:探索パート 3~:別途定義
	Control* mControl;	//initでEscクラスを代入

	virtual void funcOtherEnd();	// ノベルと探索以外の終了処理
	virtual void updateChapter();	// 任意update処理

	int mFuncNum, mChapterNum;
	std::vector<std::function<int()>> mFuncList;
	std::string mSituation;

	virtual void initChapter();
	void save(cocos2d::Ref* pSender);

};