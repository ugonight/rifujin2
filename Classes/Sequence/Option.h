#pragma once
#include "cocos2d.h"

class Option :
	public cocos2d::Scene
{
public:
	Option();
	~Option();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Option);

private:
	bool slideBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void slideMove(cocos2d::Touch* touch, cocos2d::Event* event);
	void slideEnd(cocos2d::Touch* touch, cocos2d::Event* event);
	bool lineBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	int mBGM;
	int mReset;
};

