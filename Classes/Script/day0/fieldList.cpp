#include "System/control.h"

#include "fieldDef.h"

USING_NS_CC;

namespace day0 {

	void Esc::initField() {
		//フィールド一覧
		mFieldList["bedroom"] = BedRoom::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//最初に表示させるフィールド
		this->addChild(mFieldList["bedroom"], 0, "field");

		//アイテムの初期化
		auto item = ItemMgr::create();
		this->addChild(item, 2, "item");

	}

	void Esc::showAI(std::string itemName) {
		auto ai = (AboutItem*)mFieldList["AboutItem"];
		ai->setAboutItem(itemName);
		addChild(ai, 3, "AboutItem");
	}
}