#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"
#include "ghost.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day4 {
	void Aisle4::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（B1F）";

		auto bg = Sprite::create("aisle4.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle2 = ObjectN::create();
		aisle2->setArea(Rect(520, 210, 140, 100));
		aisle2->setCursor(Cursor::FORWARD);
		aisle2->setFieldChangeEvent("aisle2");
		addObject(aisle2, "aisle2", 1, true);


		auto library = ObjectN::create();
		library->setArea(Rect(90, 80, 110, 250));
		library->setCursor(Cursor::ENTER);
		// library->setFieldChangeEvent("library");
		library->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "key_broken") {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ヒルの体液はまだ残ってるかな…");
				novel->addSentence(0, "バンダナ", "あのヌメヌメか？");
				novel->addSentence(0, "継", "うん、もしかしたらノリの代わりになるかもしれないと思って。");
				novel->addSentence(0, "バンダナ", "なるほどな");
				novel->addSentence(0, "継", "ああ、まだ残ってたみたいだね。これをカギの切断面に塗って…");
				novel->addEvent(0, CallFunc::create([this]() {
					ItemMgr::sharedItem()->getItem("key", Vec2(mObjectList["library"]->getArea().getMidX(), mObjectList["library"]->getArea().getMidY()));
					ItemMgr::sharedItem()->deleteItem("key_broken");
				}));
				novel->addSentence(0, "継", "ふー、ふー…これなら扉を開ける程度は、問題無く使えそうだね。");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
			else {
				Control::me->changeField("library");
			}
		}));
		library->addCanUseItem("key_broken");
		addObject(library, "library", 1, true);


		auto light = ObjectN::create();
		light->setTexture("light_.png");
		light->setPosition(Vec2(565, 480-125));
		light->setBlendFunc(BlendFunc{ GL_SRC_ALPHA, GL_ONE });
		light->setAction(RepeatForever::create(Sequence::create(FadeOut::create(3.0f), FadeIn::create(3.0f), NULL)));
		addObject(light, "light", 2, true);

		auto door = ObjectN::create();
		door->setArea(Rect(755, 80, 75, 380));
		door->setCursor(Cursor::ENTER);
		door->setMsg("カギがかかっている");
		addObject(door, "locked", 1, true);

		//door = ObjectN::create();
		//door->setArea(Rect(310, 50, 190, 250));
		//door->setCursor(Cursor::INFO);
		//addObject(door, "exit", 1, true);

		auto ivy = ObjectN::create();
		ivy->setArea(Rect(310, 50, 190, 250));
		ivy->setTexture("ivy.png");
		ivy->setCursor(Cursor::INFO);
		ivy->setMsg("石のツタが生い茂っている");
		ivy->addCanUseItem("sulfate");
		ivy->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "sulfate" && mObjectList["ivy"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaL(0,"chara/tuguru1.png");
				novel->setCharaR(0,"chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ここに硫酸をかけてみよう");
				novel->addSentence(0, "バンダナ", "すると、どうなるんだ？");
				novel->addSentence(0, "継", "上手くいけばこのツタを溶かすことができるかもしれない");
				novel->addSentence(0, "バンダナ", "おお、早速やってみようぜ！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "パシャ");
				novel->addSentence(0, "", "……");
				novel->addSentence(0, "", "…シューー…………");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "すげえ！マジで石が溶けてきてるぜ！！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "…シューー…………");
				novel->addSentence(0, "", "……………");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "うーん、これが限界みたいだね…");
				novel->addSentence(0, "バンダナ", "効果はいまいちってところか…");
				novel->addEvent(0, CallFunc::create([this]() {
					ItemMgr::sharedItem()->getItem("thorn",Vec2(mObjectList["ivy"]->getArea().getMidX(), mObjectList["ivy"]->getArea().getMidY()));
					Control::me->showMsg("石のトゲを手に入れた");
					ItemMgr::sharedItem()->deleteItem("sulfate");
				}));
				novel->addSentence(0, "継", "あ、トゲが一つ外れたみたいだ。何かに使えるかもしれないから持っていこう。");
				novel->addSentence(0, "バンダナ", "おう、力仕事は俺に任せときな！");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(ivy, "ivy", 1, true);


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle4::changedField() {
	}

	void Library::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "書斎";

		auto bg = Sprite::create("library.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle4 = ObjectN::create();
		aisle4->setArea(Rect(0, 430, 854, 50));
		aisle4->setCursor(Cursor::BACK);
		aisle4->setFieldChangeEvent("aisle4");
		addObject(aisle4, "aisle4", 1, true);

		auto book = ObjectN::create();
		book->setArea(Rect(660, 300, 130, 60));
		book->setCursor(Cursor::INFO);
		book->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "【シレビノ毒】");
			novel->addSentence(0, "", "違法に作られた薬物。ドラゴン族を狩るために、秘密裏に作られたと考えられている。");
			novel->addSentence(0, "", "血液中に入ると身体が痺れて動けなくなる。この状態から回復するには解毒薬が必要。");
			novel->addSentence(0, "", "以下に解毒薬の作り方を示す。");
			novel->addSentence(0, "", "・水　４DL\n・血清　２～３滴\n・トカゲのしっぽ　一本\n・ヒルの体液　適量");
			novel->addSentence(0, "", "これらの材料を混ぜ合わせれば完成。対象者に注射すれば、すぐに効果が出る。");

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}));
		addObject(book, "book1", 1, true);

		book = ObjectN::create();
		book->setArea(Rect(50, 120, 130, 60));
		book->setCursor(Cursor::INFO);
		book->setTouchEvent(CallFunc::create([this] {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "魔界王国の歴史書があるね");
				novel->addSentence(0, "継", "付箋が貼られているページがある、読んでみよう");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "【ドラゴン族】");
				novel->addSentence(0, "", "昔の魔界王国では、かつてドラゴン族は他の種族と共存していました。当時は、ドラゴン族は王国一の温厚な種族として知られていました。");
				novel->addSentence(0, "", "しかし、ある日ドラゴン族が一団となって国家反逆を企てたとして、ドラゴン族が大量に虐殺される事件が起こりました。");
				novel->addSentence(0, "", "逃亡した者も密猟者に捕らえられ、人体実験に使われたり角をもぎ取られて売り飛ばされたりして、個体数は激減しました。");
				novel->addSentence(0, "", "王国守政権になってからは、生き残ったドラゴン族は保護され、少数ではありますが、また国民として暮らしていくことができるようになりました。");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "…僕もこんな歴史を受け止めて、父さんの遺志を継いでいかないといけないな。");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
		}));
		addObject(book, "book2", 1, true);

		book = ObjectN::create();
		book->setArea(Rect(50, 300, 130, 60));
		book->setCursor(Cursor::INFO);
		book->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "ここら辺にあるのは、ここに従事していた人達の業務日誌かな。");
			novel->addSentence(0, "継", "手掛かりになりそうなものを読んでみよう");
			if (Control::me->getField("aisle")->getObject("remon")->getState() == 0) {
				novel->addSentence(0, "継", "…沢山あってなかなか調べるのが大変だな…");
			}
			else {
				switch (mObjectList["book3"]->getState())
				{
				case 0:
					novel->addSentence(0, "継", "水無月さんからもらったメモの日誌のページを読んでみよう。");
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "囚人の牢屋に餌を持ってきたところ、扉を開けた瞬間に襲い掛かってきて牢のカギを飲み込まれてしまった。");
					novel->addSentence(0, "", "逃げられてしまうと思い、棍棒を振り下ろそうとしたが、既にカギを喉に詰まらせて死んでしまっていた。");
					novel->addSentence(0, "", "記念に剥製室に飾っておこう。カギは複製してもらうか…");
					mObjectList["book3"]->setState(1);
					if (Control::me->getField("baking")->getObject("skeleton")->getState() == 0)
						Control::me->getField("baking")->getObject("skeleton")->setState(1);
					break;
				case 1:
					novel->addSentence(0, "継", "さっきの日誌の続きがあるみたいだ、読んでみよう。");
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "剥製室のケースを開けるための方法をメモしておこう");
					novel->addSentence(0, "", "ケースに付いているパネルにこんな図形を入力すればいいらしい");
					novel->addSentence(0, "", "一筆書きで入れなきゃいけないらしいが…なんとかなるだろう");
					if (!ItemMgr::sharedItem()->getGetItem("memo2")) {
						novel->setFontColor(0, Color3B::BLUE);
						novel->addSentence(0, "継", "ん？このページにメモが挟まってるみたいだ。");
						novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("memo2", Director::getInstance()->getVisibleSize() / 2); }));
						novel->addSentence(0, "継", "なにかヒントになるかもしれない、持っていこう。");
					}
					mObjectList["book3"]->setCursor(Cursor::INFO);
					mObjectList["book3"]->setState(0);
					break;
				default:
					break;
				}
			}

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}));
		addObject(book, "book3", 1, true);

		addObject(createGhost(420, 250, "library"), "ghost", 1, false);
	}

	void Library::changedField() {
	}
}