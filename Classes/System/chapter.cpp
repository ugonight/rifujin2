#pragma execution_character_set("utf-8")

#include "chapter.h"
#include "novel.h"
#include "control.h"
#include "record.h"
#include "define.h"
//#include "System/cursor.h"
//#include "Script\Chapter1\fieldDef.h"

#include <time.h>
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Chapter::Chapter() : mFuncNum(0), mChapterNum(0), mSituation("") {};

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

	//mFuncType = mFuncList[mFuncNum]();

	//セーブ
	auto save = MenuItemImage::create(
		"save.png",
		"save2.png",
		CC_CALLBACK_1(Chapter::save, this));
	save->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	save->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y));
	auto menu = Menu::create(save, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5, "save");
	//setVisibleWithTouch(menu, mFuncType == 0);

	return true;
}

void Chapter::playFirst() {
	mFuncType = mFuncList[mFuncNum]();
}

void Chapter::initChapter() {
	//継承先で実装
}

void Chapter::update(float delta) {
	if (mFuncNum < mFuncList.size()-1) {
		//場面終了処理
		if (mFuncType == 1) {	//探索
			auto control = (Control*)getChildByName("control");
			if (control) {
				if (control->getEndFlag()) {
					mFuncType = mFuncList[++mFuncNum]();
				}
			}
		}
		else if (mFuncType == 0) {	//ノベル
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

		//セーブのオン・オフ←常に表示させておく
		//Novel* novel = (Novel*)(this->getChildByName("novel"));
		//auto save = getChildByName("save");
		//if (mFuncType == 0) {	//ノベル
		//	if (novel) {
		//		setVisibleWithTouch(save,true);
		//	}
		//}
		//else {
		//	setVisibleWithTouch(save, false);
		//}
	}
}

void Chapter::funcOtherEnd(){/*継承先で定義*/}

void Chapter::save(cocos2d::Ref* pSender) {
	std::function< void(int)> func = [this](int i) {
		std::stringstream str;
		str << FileUtils::getInstance()->getWritablePath() << i << "/";
		auto path = str.str();
		auto file = path + "saveData.plist";
		ValueMap data;

		data["chapter"] = mChapterNum;
		data["funcNum"] = mFuncNum;
		data["situation"] = mSituation;

		//セーブ時間
		int t = (int)time(NULL);
		UserDefault *userDef = UserDefault::getInstance();
		//struct tm* date = localtime(&t);
		//char str2[256];
		//sprintf_s(str2, 256, "%d/%02d/%02d %02d:%02d", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday, date->tm_hour, date->tm_min);
		data["startTime"] = t;
		data["totalTime"] = userDef->getIntegerForKey("totalTime") + (t - userDef->getIntegerForKey("startTime"));

		if (mFuncType == 1) {	//探索モード
			auto control = (Control*)getChildByName("control");
			if (control) {
				control->save(i, data);	//	saveDataへの保存は託す
			}
		}
		else {
			FileUtils::getInstance()->writeToFile(data, file);
		}
		CCLOG("saved");
	};

	auto record = Record::create();
	record->save(func);
	addChild(record, 10, "record");
}

void Chapter::load(int i) {
	std::stringstream str;
	str << FileUtils::getInstance()->getWritablePath() << i << "/" ;
	auto path = str.str();

	auto file = path + "saveData.plist";

	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);
	mFuncNum = data["funcNum"].asInt();
	
	AudioEngine::stopAll();	//一度BGMを止める
	mFuncType = mFuncList[mFuncNum]();

	if (mFuncType == 1) {	//探索モード
		auto control = (Control*)getChildByName("control");
		if (control) {
			control->load(i);
		}
	}
	else {

	}


}