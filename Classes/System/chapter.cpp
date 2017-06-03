#pragma execution_character_set("utf-8")

#include "chapter.h"
#include "novel.h"
#include "control.h"
//#include "System/cursor.h"
//#include "Script\Chapter1\fieldDef.h"

//#include "audio/include/AudioEngine.h"
//using namespace cocos2d::experimental;
USING_NS_CC;

Chapter::Chapter() : mFuncNum(0) {};

//Scene* Chapter::createScene()
//{
//	auto scene = Scene::create();
//	auto layer = Chapter::create();
//	scene->addChild(layer);
//	return scene;
//}

bool Chapter::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initChapter();

	mFuncList[mFuncNum]();

	return true;
}

void Chapter::initChapter() {
	//継承先で実装
}

void Chapter::update(float delta) {
	if (mFuncNum < mFuncList.size()-1) {
		if (mFuncType == 1) {
			auto control = (Control*)getChildByName("control");
			if (control) {
				if (control->getEndFlag()) {
					mFuncType = mFuncList[++mFuncNum]();
				}
			}
		}
		else if (mFuncType == 0) {
			Novel* novel = (Novel*)(this->getChildByName("novel"));
			if (novel) {
				if (novel->getEndFlag()) {
					mFuncType = mFuncList[++mFuncNum]();
					this->removeChild(novel);
				}
			}
		}
		else {
			funcOtherEnd();
		}
	}
}

void Chapter::funcOtherEnd(){/*継承先で定義*/}