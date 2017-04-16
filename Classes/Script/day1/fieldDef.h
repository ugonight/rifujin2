#pragma once

#include "../../System/field.h"

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 
//メンバを追加できるように}は定義しない

//CREATE_FIELD(Field1)};
//CREATE_FIELD(Field2)};
//CREATE_FIELD(Forest2)};

CREATE_FIELD(AboutItem)
	void setAboutItem(std::string itemName);
};

class Day1 : public Control {
protected:
	virtual void initField();
public:
	virtual void showAI(std::string itemName);
};

class Item1 : public Item {
protected:
	virtual void initItem();
};