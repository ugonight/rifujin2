#pragma once

#include "cocos2d.h"

class Prologue : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Prologue);

private:
	std::function<void()> mFunc[5];
	int mFuncNum;
};