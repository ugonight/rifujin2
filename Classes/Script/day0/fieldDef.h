//#pragma  execution_character_set("utf-8")
#pragma once

#include "../../System/field.h"
#include "../../System/control.h"
#include "../../System/item.h"
#include "../../System/object.h"
#include "../../System/novel.h"
#include "define.h"

namespace day0
{

//メンバを追加できるように}は定義しない

CREATE_FIELD(BedRoom)};
CREATE_FIELD(Closet)};

//CREATE_FIELD(AboutItem)
//void setAboutItem(std::string itemName);
//};

class AboutItem : public SAboutItem {
public:
	virtual void initField();
	virtual void changedField();
	CREATE_FUNC(AboutItem);
	void setAboutItem(std::string itemName)override;
};

class Esc : public Control {
public:
	void initField();
};

class ItemMgr : public Item {
public:
	void initItem();
};

}