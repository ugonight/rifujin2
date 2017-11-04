#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		//胡椒の実
		auto ai = ObjectN::create();
		ai->setTexture("item/fruit_a.png");
		ai->setMsg("コショウの実だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "fruit", 1, false);

		//網
		ai = ObjectN::create();
		ai->setTexture("item/net_a.png");
		ai->setMsg("美術で使うぼかし網だ");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "fruit") {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ごしごしごし…");
				novel->setCharaR(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "あーつぐるんがまた奇行に走ってるー！");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->deleteItem("fruit");
					ItemMgr::sharedItem()->deleteItem("net");
					ItemMgr::sharedItem()->getItem("pepper", Director::getInstance()->getVisibleSize() / 2);
					Control::me->showMsg("コショウを手に入れた");
				}));
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "できた");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "は、はっくしょん！…なんでコショウなんて作ってるのよー！");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		ai->addCanUseItem("fruit");
		addObject(ai, "net", 1, false);

		//コショウ
		ai = ObjectN::create();
		ai->setTexture("item/pepper_a.png");
		ai->setMsg("コショウだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "pepper", 1, false);

		//カメラ
		ai = ObjectN::create();
		ai->setTexture("item/camera_a.png");
		ai->setMsg("宇沢から渡されたカメラだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "camera", 1, false);

		//雑誌
		ai = ObjectN::create();
		ai->setTexture("item/magazine_a.png");
		ai->setMsg("恋巳から渡されたオカルト雑誌だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "magazine", 1, false);

		//写真
		ai = ObjectN::create();
		ai->setTexture("item/picture_a.png");
		ai->setMsg("UFOの写真だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "picture", 1, false);

		//紙切れ
		ai = ObjectN::create();
		ai->setTexture("item/paper_a.png");
		ai->setMsg("誰かが落としたメモだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "paper", 1, false);
	}
	void AboutItem::changedField() {}
	void AboutItem::setAboutItem(std::string itemName) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		this->removeAllChildren();

		this->scheduleUpdate();
		for (auto it : this->getChildren()) {
			it->scheduleUpdate();
		}

		//ここにAboutItemの処理を書いていく
		//同時に二つ以上表示する場合はitemName == で書く
		if (itemName == "letter") {
			if (mObjectList["letter_"]->getState() == 1) {
				addChild(mObjectList["letter_"], 2, "letter_");
			}
			else {
				addChild(mObjectList["letter"], 1, "letter");
			}
		}
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}