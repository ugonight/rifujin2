#include "System/control.h"

#include "fieldDef.h"

void Day1::initField() {



	//�ŏ��ɕ\��������t�B�[���h
	this->addChild(mFieldList["forest1"], 0, "field");

	//�A�C�e���̏�����
	auto item = Item1::create();
	this->addChild(item, 2, "item");
}

void Day1::showAI(std::string itemName) {
	auto ai = (AboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}