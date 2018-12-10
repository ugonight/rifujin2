#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day4 {
	void Prison::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "牢屋";

		auto bg = Sprite::create("prison.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");


		auto blanket = ObjectN::create();
		blanket->setArea(Rect(550, 400, 120, 80));
		blanket->setCursor(Cursor::INFO);
		blanket->setFieldChangeEvent("aisle");
		addObject(blanket, "blanket", 1, true);

		{
			auto searchPoint = ObjectN::create();
			searchPoint->setArea(Rect(0, 100, 100, 270));
			searchPoint->setCursor(Cursor::INFO);
			searchPoint->setMsg("鎖が垂れ下がっている");
			addObject(searchPoint, "kusari", 1, true);
		}

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

	}

	void Prison::changedField() {
	}

	void Aisle::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（牢屋）";

		auto bg = Sprite::create("aisle.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(460, 380, 160, 70));
		entrance->setCursor(Cursor::INFO);
		entrance->setFieldChangeEvent("prison");
		addObject(entrance, "prison", 1, true);

		auto remon = ObjectN::create();
		remon->setArea(Rect(95, 200, 100, 170));
		remon->setTexture("aisle_remon.png");
		remon->setCursor(Cursor::INFO);
		remon->setTouchEvent(CallFunc::create([this]() {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/remon1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "早く牢のカギを持ってきてちょうだいね");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(remon, "remon", 2, true);

		auto b2f = ObjectN::create();
		b2f->setArea(Rect(100, 430, 320, 50));
		b2f->setCursor(Cursor::BACK);
		b2f->setFieldChangeEvent("aisle2");
		addObject(b2f, "b2f", 1, true);


		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void Aisle::changedField() {

	}
}