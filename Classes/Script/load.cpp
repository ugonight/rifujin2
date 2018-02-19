#include "System/record.h"
#include "define.h"

//全てのchapterのfieldDefをinclude
#include "day1\fieldDef.h"
#include "day2\fieldDef.h"
#include "day3\fieldDef.h"

#pragma execution_character_set("utf-8")

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

void Record::load() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Chapter *chapter;
	std::stringstream str;
	resetStr(str);
	str << FileUtils::getInstance()->getWritablePath() << mSelectNum << "/";
	auto path = str.str();
	auto file = path + "saveData.plist";
	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);

	if (data["chapter"].asInt() > 0) {	//ロードするchapterを記述
		switch (data["chapter"].asInt())
		{
		case 1:
			chapter = day1::Day::create();
			break;
		case 2:
			chapter = day2::Day::create();
			break;
		case 3:
			chapter = day3::Day::create();
			break;
		default:

			break;
		}
		
		this->runAction(Sequence::create(EaseSineIn::create(MoveBy::create(0.2, Vec3(0, visibleSize.height, 0)))
			,RemoveSelf::create(), NULL));
		auto scene = Scene::create();
		scene->addChild(chapter, 0,"chapter");
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::WHITE));
		((Chapter*)scene->getChildByName("chapter"))->load(mSelectNum);

		//基準時間の初期化
		UserDefault *userDef = UserDefault::getInstance();
		userDef->setIntegerForKey("startTime", (int)time(NULL));
		userDef->setIntegerForKey("totalTime", data["totalTime"].asInt());
		userDef->flush();
	}

}