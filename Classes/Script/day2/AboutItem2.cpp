#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

USING_NS_CC;

namespace day2 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		//メモ1
		auto ai = ObjectN::create();
		ai->setTexture("item/memo1_a.png");
		ai->setMsg("数字の書かれたメモだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "memo1", 1, false);

		// 塩
		ai = ObjectN::create();
		ai->setTexture("item/solt_a.png");
		ai->setMsg("塩だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "solt", 1, false);

		// ぬめぬめ
		ai = ObjectN::create();
		ai->setTexture("item/nume_a.png");
		ai->setMsg("ヒルが溶けて出てきたヌメヌメだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "nume", 1, false);

		// 救急箱
		ai = ObjectN::create();
		ai->setTexture("item/fak_a.png");
		ai->setMsg("包帯や消毒薬などが入っている");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "fak", 1, false);
		// 救急箱 - 注射
		ai = ObjectN::create();
		ai->setTexture("item/fak_s.png");
		//ai->setMsg("注射器を手に入れた");
		ai->setItemGetEvent("syringe");
		ai->setCursor(Cursor::NEW);
		ai->setArea(Rect(854 / 2 - 150 + 80, 480 / 2 - 150 + 145, 30, 25));
		ai->setTouchEvent(CallFunc::create([this] {
			mObjectList["fak_s"]->setState(1);  Control::me->showMsg("注射器を手に入れた"); 
			Control::me->getField("prison")->addChild(Control::me->getField("prison")->getObject("lizard"), 3, "lizard");
		}));
		addObject(ai, "fak_s", 2, false);

		// 注射器
		ai = ObjectN::create();
		ai->setTexture("item/syringe_a.png");
		ai->setMsg("注射器だ。解毒薬の材料を入れていこう。");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this] (){
			if (ItemMgr::sharedItem()->getSelectedItem() == "nume") {
				Control::me->showMsg("注射器にヒルの体液を入れた");
				mObjectList["syringe_h"]->setState(1);
				mObjectList["syringe_h"]->setOpacity(0.0f);
				mObjectList["syringe_h"]->runAction(FadeIn::create(1.0f));
				addChild(mObjectList["syringe_h"], 3, "syringe_h");
				ItemMgr::sharedItem()->deleteItem("nume");
			}
			else if (mObjectList["syringe_w"]->getState() == 1 && mObjectList["syringe_b"]->getState() == 1 && mObjectList["syringe_h"]->getState() == 1 && mObjectList["syringe_r"]->getState() == 1) {
				if (mObjectList["syringe"]->getState() == 0) {
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::BLUE);
					novel->setCharaR(0, "chara/tuguru1.png");
					novel->addSentence(0, "継", "これで解毒薬の完成だ");
					novel->addSentence(0, "継", "急いでバンダナの元へ向かおう");
					mObjectList["syringe"]->setState(1);
					novel->setEndTask(0);
					addChild(novel, 10, "novel");
				}
				else {
					Control::me->showMsg("解毒薬が完成した");
				}
			}
		}));
		addObject(ai, "syringe", 5, false);
		ai = ObjectN::create();	// 水
		ai->setTexture("item/syringe_w.png");
		addObject(ai, "syringe_w", 1, false);
		ai = ObjectN::create(); // 血清
		ai->setTexture("item/syringe_b.png");
		addObject(ai, "syringe_b", 2, false);
		ai = ObjectN::create(); // 体液
		ai->setTexture("item/syringe_h.png");
		addObject(ai, "syringe_h", 3, false);
		ai = ObjectN::create(); // しっぽ
		ai->setTexture("item/syringe_r.png");
		addObject(ai, "syringe_r", 4, false);
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
		if (itemName == "fak") {
			addChild(mObjectList["fak"], 1, "fak");
			if (mObjectList["fak_s"]->getState() == 0) {
				addChild(mObjectList["fak_s"], 2, "fak_s");
			}
		}
		else if (itemName == "syringe") {
			addChild(mObjectList["syringe"], 5, "syringe");
			if (mObjectList["syringe_w"]->getState() == 1) addChild(mObjectList["syringe_w"], 1, "syringe_w");
			if (mObjectList["syringe_b"]->getState() == 1) addChild(mObjectList["syringe_b"], 2, "syringe_b");
			if (mObjectList["syringe_h"]->getState() == 1) addChild(mObjectList["syringe_h"], 3, "syringe_h");
			if (mObjectList["syringe_r"]->getState() == 1) addChild(mObjectList["syringe_r"], 4, "syringe_r");
		}
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}