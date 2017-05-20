#include "System/control.h"

#include "fieldDef.h"

void Day1::initField() {



	//最初に表示させるフィールド
	this->addChild(mFieldList["forest1"], 0, "field");

	//アイテムの初期化
	auto item = Item1::create();
	this->addChild(item, 2, "item");
}

void Day1::showAI(std::string itemName) {
	auto ai = (AboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}