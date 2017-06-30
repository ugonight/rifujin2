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
				if (mObjectList["renji"]->getState() == 0) {
					novel->addSentence(0, "恋巳「御早う、諸君。」");
					novel->addSentence(0, "恋巳「俺は、神北　恋巳（かみきた　れんじ）。以後、お見知り置きを。」");
					novel->addSentence(0, "継「うん、おはよう。神北くん」");
					mObjectList["renji"]->setState(1);
				}
				else if (mObjectList["renji"]->getState() == 1) {
					novel->addSentence(0, "恋巳「御早う、諸君。」");
				}
				else if (mObjectList["renji"]->getState() == 2){
					novel->addSentence(0, "恋巳「ちょっと待ちたまえ、君たち。」");
					novel->addSentence(0, "継「ん？どうしたのかな、神北くん」");
					novel->addSentence(0, "恋巳「諸君らはオカルトに、興味はあるか？」");
					novel->addSentence(0, "継「オカルト…？うーん、特には」");
					novel->addSentence(0, "恋巳「オカルトはいいぞ…いつまでも俺の知的好奇心を刺激してくれる」");
					novel->addEvent(0, CallFunc::create([this] {
						ItemMgr::sharedItem()->getItem("magazine", Director::getInstance()->getVisibleSize() / 2);
						Control::me->showMsg("雑誌を手に入れた");
						mObjectList["renji"]->setState(1);
						mObjectList["renji"]->setCursor(Cursor::INFO);
					}));
					novel->addSentence(0, "恋巳「これをあげるから、諸君らも是非読んで興味を持ってくれると嬉しい。」");
					novel->addSentence(0, "継「ありがとう、神北くん。」");
				}
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
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

		auto ufo = ObjectN::create();
		ufo->setArea(Rect(650, 0, 100, 100));
		ufo->setTexture("ufo.png");
		ufo->setCursor(Cursor::INFO);
		ufo->setMsg("UFOが飛んでいる");
		ufo->addCanUseItem("camera");
		ufo->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "camera") {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "継「UFOをカメラで撮影してみよう」");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->getItem("picture", Director::getInstance()->getVisibleSize() / 2);
					Control::me->showMsg("写真を手に入れた");
					removeChildByName("ufo");
				}));
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "パシャッ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「よし、写真が撮れたよ」");
				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(ufo, "ufo", 3, false);

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