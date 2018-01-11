#pragma once
//#pragma  execution_character_set("utf-8")

#include "../../System/field.h"
#include "../../System/control.h"
#include "../../System/item.h"
#include "../../System/object.h"
#include "../../System/novel.h"
#include "../../System/chapter.h"
#include "../../System/cursor.h"
#include "define.h"

namespace day2
{
	//メンバを追加できるように}は定義しない
	CREATE_FIELD(Prison) void updateField(); private: int mHit; void attackZombie(); };
	CREATE_FIELD(MagicTeam) private: int mNumber[3][3]; bool mMatch[8]; bool mCanMove;  };
	CREATE_FIELD(Aisle) };
	CREATE_FIELD(Aisle2)};
	CREATE_FIELD(Aisle3)};
	CREATE_FIELD(Aisle4)};
	CREATE_FIELD(Torture) void updateField(); private: void hide(); cocos2d::Point mTouchPos; int mCount; bool mFinish; int mSE; };
	CREATE_FIELD(Panel) private: bool mOnOff[5][5]; };
	CREATE_FIELD(Lab)};
	CREATE_FIELD(MWater) void updateField(); private: int mFrom; int mCup[2]; };
	CREATE_FIELD(Library)};

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