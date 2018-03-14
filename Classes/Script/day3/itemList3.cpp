#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {

	void ItemMgr::initItem() {
		mItemList["paper"] = new ItemObj("item/paper_i.png");
		mItemList["whistle"] = new ItemObj("item/whistle_i.png");
		mItemList["chisel"] = new ItemObj("item/chisel_i.png");
		mItemList["hatpin"] = new ItemObj("item/hatpin_i.png");
		mItemList["memories"] = new ItemObj("item/memories_i.png");
	}

}