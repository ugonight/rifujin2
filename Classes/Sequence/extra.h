#pragma once

#include "cocos2d.h"
#include "System/novel.h"

class Extra : public cocos2d::Scene {

private:
	std::vector<std::string> mStillList;
	int mPage;
	const double ratio;

	void menu();
	void character();
	void music();
	void still();

	void transition(cocos2d::CallFunc *func);

	void turnPage();

public:
	Extra();

	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(Extra);
};