#pragma  execution_character_set("utf-8")
//#include "System/control.h"

#include "Script\day0\fieldDef.h"
USING_NS_CC;

namespace day0 {
	Control* Esc::createControl() {
		return Esc::create();
	}

	void Esc::initField() {
		//フィールド一覧
		mFieldList["bedroom"] = BedRoom::create();
		mFieldList["closet"] = Closet::create();

		mFieldList["AboutItem"] = AboutItem::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//最初に表示させるフィールド
		this->addChild(mFieldList["bedroom"], 0, "field");

		//アイテムの初期化
		auto item = (ItemMgr*)ItemMgr::create();
		item->initItem();
		this->addChild(item, 2, "item");

		//チュートリアルではセーブしない
		getChildByName("save")->setVisible(false);
		getChildByName("save")->pause();

		mEndFlag = false;
	}

}