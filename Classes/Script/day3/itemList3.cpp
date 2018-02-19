#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {

	void ItemMgr::initItem() {
		mItemList["paper"] = new ItemObj("item/paper_i.png");
	}

}