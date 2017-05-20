#pragma  execution_character_set("utf-8")
#include "fieldDef.h"

USING_NS_CC;

namespace day0 {
	void BedRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("bedroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto tuguru = ObjectN::create();
		tuguru->setTexture("tuguru_s.png");
		tuguru->setArea(Rect(580, 85, 140, 375));
		tuguru->setCursor(2);
		tuguru->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaR(0,"chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0,"継「パジャマから普通の服に着替えよう」");
			novel->addSentence(0, "継「クローゼットは移動すれば見つかるよ」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addChild(tuguru, 1, "tuguru");

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void BedRoom::changedField() {

	}
}