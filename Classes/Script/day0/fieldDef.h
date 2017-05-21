#pragma once

#include "../../System/field.h"

namespace day0
{

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 
//�����o��ǉ��ł���悤��}�͒�`���Ȃ�

CREATE_FIELD(BedRoom)};
CREATE_FIELD(Closet)};

CREATE_FIELD(AboutItem)
void setAboutItem(std::string itemName);
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