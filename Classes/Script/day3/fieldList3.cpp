#pragma  execution_character_set("utf-8")
//#include "System/control.h"

#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	Control* Esc::createControl() {
		return Esc::create();
	}

	void Esc::initField() {
		//フィールド一覧
		mFieldList["gate"] = Gate::create();
		mFieldList["entrance"] = Entrance::create();
		mFieldList["corridor"] = Corridor::create();
		mFieldList["classroom"] = ClassRoom::create();
		mFieldList["artroom"] = ArtRoom::create();
		mFieldList["backyard"] = Backyard::create();

		mFieldList["AboutItem"] = AboutItem::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//最初に表示させるフィールド
		mFirstField = "classroom";
		this->addChild(mFieldList[mFirstField], 0, "field");

		//アイテムの初期化
		auto item = (ItemMgr*)ItemMgr::create();
		item->initItem();
		this->addChild(item, 2, "item");

		//ヒントの初期化
		auto hint = HintMgr::create();
		this->addChild(hint, 2, "hint");

		mEndFlag = false;
	}
}