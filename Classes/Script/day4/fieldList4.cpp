#pragma  execution_character_set("utf-8")
//#include "System/control.h"

#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {
	Control* Esc::createControl() {
		return Esc::create();
	}

	void Esc::initField() {
		//フィールド一覧
		mFieldList["prison"] = Prison::create();
		mFieldList["aisle"] = Aisle::create();
		mFieldList["aisle2"] = Aisle2::create();
		mFieldList["aisle3"] = Aisle3::create();
		mFieldList["aisle4"] = Aisle4::create();
		mFieldList["torture"] = Torture::create();
		mFieldList["lab"] = Lab::create();
		mFieldList["library"] = Library::create();
		mFieldList["baking"] = Baking::create();
		mFieldList["panel"] = Panel::create();
		mFieldList["rroom"] = RRoom::create();
		mFieldList["rart"] = RArt::create();
		mFieldList["dangeon1"] = Dangeon1::create();
		mFieldList["remains"] = Remains::create();
		mFieldList["dangeon2"] = Dangeon2::create();
		mFieldList["deadend"] = DeadEnd::create();

		mFieldList["AboutItem"] = AboutItem::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//最初に表示させるフィールド
		mFirstField = "aisle";
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