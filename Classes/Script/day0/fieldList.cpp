#include "System/control.h"

#include "fieldDef.h"

USING_NS_CC;

namespace day0 {

	void Esc::initField() {
		//�t�B�[���h�ꗗ
		mFieldList["bedroom"] = BedRoom::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//�ŏ��ɕ\��������t�B�[���h
		this->addChild(mFieldList["bedroom"], 0, "field");

		//�A�C�e���̏�����
		auto item = ItemMgr::create();
		this->addChild(item, 2, "item");

	}

	void Esc::showAI(std::string itemName) {
		auto ai = (AboutItem*)mFieldList["AboutItem"];
		ai->setAboutItem(itemName);
		addChild(ai, 3, "AboutItem");
	}
}