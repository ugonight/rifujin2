#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		//メモ1
		//auto ai = ObjectN::create();
		//ai->setTexture("item/memo1_a.png");
		//ai->setMsg("数字の書かれたメモだ");
		//ai->setArea(ai->getBoundingBox());
		//addObject(ai, "memo1", 1, false);

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
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}