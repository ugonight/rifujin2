#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void Gate::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("gate.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto renji = ObjectN::create();
		renji->setTexture("renji.png");
		renji->setArea(Rect(50, 110, 120, 370));
		renji->setCursor(Cursor::INFO);
		renji->setTouchEvent(CallFunc::create([this] {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/renji1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳「御早う、諸君。」");
				if (mObjectList["renji"]->getState() == 0) novel->addSentence(0, "恋巳「我こそは、神北　恋巳（かみきた　れんじ）。以後、お見知り置きを。」");
				novel->addSentence(0, "継「うん、おはよう。神北くん」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["renji"]->setState(1);
		}));
		//renji->addCanUseItem("clothes");
		addObject(renji, "renji", 1, true);

		auto cenotaph = ObjectN::create();
		cenotaph->setArea(Rect(700, 100, 100, 180));
		cenotaph->setCursor(Cursor::INFO);
		cenotaph->setMsg("初代学長の慰霊碑がある");
		addObject(cenotaph, "cenotaph", 3, true);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(300, 140, 270, 100));
		entrance->setCursor(Cursor::FORWARD);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void Gate::changedField() {

	}

	void Entrance::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("entrance.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto fruit = ObjectN::create();
		fruit->setArea(Rect(270, 230, 100, 100));
		fruit->setCursor(Cursor::NEW);
		fruit->setItemGetEvent("fruit");
		fruit->setMsg("枯れた植物の実を手に入れた");
		addObject(fruit, "fruit", 3, true);

		auto gate = ObjectN::create();
		gate->setArea(Rect(780, 0, 74, 480));
		gate->setCursor(Cursor::RIGHT);
		gate->setFieldChangeEvent("gate");
		addObject(gate, "gate", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(0, 0, 80, 480));
		corridor->setCursor(Cursor::LEFT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void Entrance::changedField() {

	}
}