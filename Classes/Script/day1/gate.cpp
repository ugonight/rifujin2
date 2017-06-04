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

		//auto tuguru = ObjectN::create();
		//tuguru->setTexture("tuguru_s.png");
		//tuguru->setArea(Rect(580, 85, 140, 375));
		//tuguru->setCursor(2);
		//tuguru->setTouchEvent(CallFunc::create([this] {
		//	if (ItemMgr::sharedItem()->getSelectedItem() == "clothes") {
		//		ItemMgr::sharedItem()->deleteItem("clothes");
		//		this->runAction(FadeOut::create(0.5f));
		//		((Esc*)Control::me)->setEndFlag();
		//	}
		//	else {
		//		auto novel = Novel::create();
		//		novel->setCharaR(0, "chara/tuguru2.png");
		//		novel->setFontColor(0, Color3B::BLUE);
		//		novel->addSentence(0, "継「パジャマから普通の服に着替えよう」");
		//		novel->addSentence(0, "継「クローゼットは移動すれば見つかるよ」");
		//		novel->setEndTask(0);
		//		this->addChild(novel, 10, "novel");
		//	}
		//}));
		//tuguru->addCanUseItem("clothes");
		//addObject(tuguru, "tuguru", 1, true);

		//auto closet = ObjectN::create();
		//closet->setArea(Rect(0, 0, 80, 480));
		//closet->setCursor(5);
		//closet->setFieldChangeEvent("closet");
		//addObject(closet, "closet", 2, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void Gate::changedField() {

	}
}