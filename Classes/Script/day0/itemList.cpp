#include "System/item.h"
#include "Script\day0\fieldDef.h"

USING_NS_CC;

namespace day0 {

	void ItemMgr::initItem() {
		mItemList["clothes"] = new ItemObj("item/clothes_i.png");

	}

}