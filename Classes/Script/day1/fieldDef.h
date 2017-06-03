﻿#pragma once
#pragma  execution_character_set("utf-8")

#include "../../System/field.h"
#include "../../System/control.h"
#include "../../System/item.h"
#include "../../System/object.h"
#include "../../System/novel.h"
#include "../../System/chapter.h"
#include "define.h"

namespace day1
{
	//メンバを追加できるように}は定義しない

	class Day : public Chapter
	{
	public:
		static cocos2d::Scene* createScene();
		void initChapter() override;

		CREATE_FUNC(Day);
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
		CREATE_FUNC(Esc);
		void initField();
	};

	class ItemMgr : public Item {
	public:
		void initItem();
	};

}