#pragma  execution_character_set("utf-8")

#include "fieldDef.h"

USING_NS_CC;

void AboutItem::initField() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//オブジェクトを作っておく
	//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

	//クレヨン（緑）
	//auto crayon = ObjectN::create();
	//crayon->setTexture("item/crayon_g.png");
	//crayon->setMsg("緑のクレヨンだ");
	//crayon->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//crayon->setArea(crayon->getBoundingBox());
	//addObject(crayon, "crayon_g", 1, false);

}
void AboutItem::changedField(){}
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
		addChild(mObjectList[itemName]);	//基本的に登録名と同じオブジェクトを表示
	}
}