#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {

	void ItemMgr::initItem() {
		mItemList["fruit"] = new ItemObj("item/fruit_i.png");
		mItemList["net"] = new ItemObj("item/net_i.png");
		mItemList["pepper"] = new ItemObj("item/pepper_i.png");
		mItemList["camera"] = new ItemObj("item/camera_i.png");
		mItemList["magazine"] = new ItemObj("item/magazine_i.png");
		mItemList["picture"] = new ItemObj("item/picture_i.png");
	}

}