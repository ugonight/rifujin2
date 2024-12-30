#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

class Ending : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Ending);

private:
	static const int mFuncCount = 2;

	std::function<void()> mFunc[mFuncCount];
	int mFuncNum;

	int mBgmId = 0;
	float mVolume = 1, mVolumeDefault = 1;
	bool mEndingLast = false, mToTitle = false;
	int mSkip = 0;
};

