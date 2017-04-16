#include "System/control.h"

#include "fieldDef.h"

void Day1::initField() {



	//最初に表示させるフィールド
	this->addChild(mFieldList["forest1"], 0, "field");
}

void Day1::showAI(std::string itemName) {
	auto ai = (AboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}