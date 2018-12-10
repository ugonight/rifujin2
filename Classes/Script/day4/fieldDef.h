﻿#pragma once
//#pragma  execution_character_set("utf-8")

#include "../../System/field.h"
#include "../../System/control.h"
#include "../../System/item.h"
#include "../../System/object.h"
#include "../../System/novel.h"
#include "../../System/chapter.h"
#include "../../System/cursor.h"
#include "define.h"

namespace day4
{
	//メンバを追加できるように}は定義しない
	CREATE_FIELD(Prison) };
	CREATE_FIELD(Aisle) };
	CREATE_FIELD(Aisle2)};
	CREATE_FIELD(Aisle3)};
	CREATE_FIELD(Aisle4)};
	CREATE_FIELD(Torture)};
	CREATE_FIELD(Lab)};
	CREATE_FIELD(Library)};

	class Day : public Chapter
	{
	public:
		static cocos2d::Scene* createScene();
		void initChapter() override;

		CREATE_FUNC(Day);

	private:
		//cocos2d::SpriteBatchNode* mHandImage[3];
	};

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
		CREATE_FUNC(Esc);
		void initField();
	};

	class ItemMgr : public Item {
	public:
		void initItem();
	};

	class HintMgr : public Hint {
	public:
		virtual void showHint();
		CREATE_FUNC(HintMgr);
	};
}