#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

USING_NS_CC;

namespace day2 {

	void ItemMgr::initItem() {
		mItemList["memo1"] = new ItemObj("item/memo1_i.png");
		mItemList["solt"] = new ItemObj("item/solt_i.png");
		mItemList["nume"] = new ItemObj("item/nume_i.png");
		mItemList["fak"] = new ItemObj("item/fak_i.png");
		mItemList["syringe"] = new ItemObj("item/syringe_i.png");


	}

}