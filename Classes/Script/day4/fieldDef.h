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

class DangeonC;

namespace day4
{
	//メンバを追加できるように}は定義しない
	CREATE_FIELD(Prison)
};
CREATE_FIELD(Aisle) };
CREATE_FIELD(Aisle2)};
CREATE_FIELD(Aisle3)};
CREATE_FIELD(Aisle4)};
CREATE_FIELD(Torture)};
CREATE_FIELD(Lab)};
CREATE_FIELD(Library)};
CREATE_FIELD(Baking)};
CREATE_FIELD(Panel)
		private:
			bool mAdjacency[4 * 5][4 * 5]; // 隣接行列
			int pre[2];	// 前の点
			void touchNode(cocos2d::Touch* touch, cocos2d::Event* event);
			void drawLine();
	};
	CREATE_FIELD(RRoom)};
	CREATE_FIELD(RArt)};
	CREATE_FIELD(Dangeon1)
		private:
			std::shared_ptr<DangeonC> mDangeonC = 0;
			void move();
	};
	CREATE_FIELD(Remains)
		private:
			void reasoning2();
			void reasoning3();
			int mSelectMemory = 1;
			int mLife;
			void gameover1(int hint);
			void takeDamage();
	};

	CREATE_FIELD(Dangeon2)
		public:
			void update(float delta);
		private:
			std::shared_ptr<DangeonC> mDangeonC = 0;
			int mEnemyTime = 0;
			void move();
			void DrawEnemy();
			void gameover();
	};
	CREATE_FIELD(DeadEnd)
		private:
			void gameover();
		};

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
		virtual void initField() override;
		virtual void changedField() override;
		CREATE_FUNC(AboutItem);
		void setAboutItem(std::string itemName) override;
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