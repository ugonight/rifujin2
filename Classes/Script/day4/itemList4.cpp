﻿#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {

	void ItemMgr::initItem() {
		mItemList["sulfate"] = new ItemObj("item/sulfate_i.png");
		mItemList["thorn"] = new ItemObj("item/thorn_i.png");
		mItemList["memo2"] = new ItemObj("item/memo2_i.png");
		mItemList["skeleton"] = new ItemObj("item/skeleton_i.png");
		mItemList["key_broken"] = new ItemObj("item/key_broken_i.png");
		mItemList["key"] = new ItemObj("item/key_i.png");
		mItemList["memories"] = new ItemObj("item/memories_i.png");
		mItemList["suama"] = new ItemObj("item/suama_report_i.png");
		mItemList["bowgun"] = new ItemObj("item/bowgun_i.png");
		mItemList["doll"] = new ItemObj("item/straw_doll_i.png");
		mItemList["key_remon"] = new ItemObj("item/key_remon_i.png");
		mItemList["diary"] = new ItemObj("item/diary_i.png");
		mItemList["candle"] = new ItemObj("item/candle_i.png");
		mItemList["key2"] = new ItemObj("item/key2_i.png");

	}

}