#pragma once
//#pragma  execution_character_set("utf-8")
//↑prologueでリンクエラー出るときはここのコメントいじって

#include "../../System/field.h"
#include "../../System/control.h"
#include "../../System/item.h"
#include "../../System/object.h"
#include "../../System/novel.h"
#include "define.h"

namespace day0
{
	//メンバを追加できるように}は定義しない

	class AboutItem : public SAboutItem {
	public:
		virtual void initField();
		virtual void changedField();
		CREATE_FUNC(AboutItem);
		void setAboutItem(std::string itemName)override;
	};

	class Esc : public Control {
	public:
		static Control* createControl();
		void initField();
		CREATE_FUNC(Esc);
	};

	class ItemMgr : public Item {
	public:
		void initItem();
	};

	//CREATE_FIELD(BedRoom)};
	//CREATE_FIELD(Closet)};

	class BedRoom : public Field {
	public: 
			virtual void initField(); 
			virtual void changedField(); 
			CREATE_FUNC(BedRoom);
	};
	class Closet : public Field {
	public:
		virtual void initField();
		virtual void changedField();
		CREATE_FUNC(Closet);
	};
}

