#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day2 {
	void Aisle2::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（B2F-1）";

		auto bg = Sprite::create("aisle2.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto prison = ObjectN::create();
		prison->setArea(Rect(490, 50, 110, 220));
		prison->setCursor(Cursor::ENTER);
		prison->setFieldChangeEvent("aisle");
		addObject(prison, "prison", 1, true);
	}

	void Aisle2::changedField() {

	}
}