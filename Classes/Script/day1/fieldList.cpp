#include "System/control.h"

#include "fieldDef.h"

void Day1::initField() {



	//�ŏ��ɕ\��������t�B�[���h
	this->addChild(mFieldList["forest1"], 0, "field");
}

void Day1::showAI(std::string itemName) {
	auto ai = (AboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}