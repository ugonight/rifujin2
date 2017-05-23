#pragma  execution_character_set("utf-8")
#include "Script\day0\fieldDef.h"

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
			if (ItemMgr::sharedItem()->getSelectedItem() == "clothes") {
				ItemMgr::sharedItem()->deleteItem("clothes");
				this->runAction(FadeOut::create(0.5f));
				((Esc*)Control::me)->setEndFlag();
			}
			else {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「パジャマから普通の服に着替えよう」");
				novel->addSentence(0, "継「クローゼットは移動すれば見つかるよ」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		tuguru->addCanUseItem("clothes");
		addObject(tuguru, "tuguru", 1, true);

		auto closet = ObjectN::create();
		closet->setArea(Rect(0, 0, 80, 480));
		closet->setCursor(5);
		closet->setFieldChangeEvent("closet");
		addObject(closet, "closet", 2, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void BedRoom::changedField() {

	}

	void Closet::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("closet.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto bed = ObjectN::create();
		bed->setArea(Rect(774, 0, 80, 480));
		bed->setCursor(4);
		bed->setFieldChangeEvent("bedroom");
		addObject(bed, "bed", 2, true);

		auto closet = ObjectN::create();
		closet->setArea(Rect(60, 30, 290, 390));
		closet->setCursor(1);
		closet->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["closet"]->getState() == 0) {
				auto item = ItemMgr::sharedItem();
				item->getItem("clothes", Point(200, 240));
				Esc::me->showMsg("服を手に入れた");
				mObjectList["closet"]->setState(1);
				mObjectList["closet"]->setCursor(2);
			}
			else {
				Esc::me->showMsg("服は手に入れてある");
			}
		}));
		addObject(closet, "closet", 2, true);
	}

	void Closet::changedField() {

	}
}