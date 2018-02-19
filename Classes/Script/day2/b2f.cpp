#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day2 {
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

		auto hiru = ObjectN::create();
		hiru->setArea(Rect(90, 150, 110, 210));
		hiru->setTexture("hiru.png");
		hiru->setCursor(Cursor::INFO);
		hiru->setMsg("扉にヒルが張り付いている");
		hiru->setTouchEvent(CallFunc::create([this] (){
			if (ItemMgr::sharedItem()->getSelectedItem() == "solt") {
				Control::me->showMsg("ヒルに塩を振りかけた");
				mObjectList["hiru"]->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				ItemMgr::sharedItem()->deleteItem("solt");
				mObjectList["hiru"]->setState(1);
				AudioEngine::play2d("SE/hiru.ogg");
				mObjectList["flag"]->setState(1);
				addChild(mObjectList["library"], 1, "library");

				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "ちょっとかわいそうだな…ごめんよ");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "びちゃっ");
				novel->addEvent(0, CallFunc::create([this] {ItemMgr::sharedItem()->getItem("nume", Point(140, 250)); }));
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "うわっ");
				novel->addSentence(0, "継", "ヒルの体液が手についちゃった…べたべたするなあ…");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		hiru->addCanUseItem("solt");
		addObject(hiru, "hiru", 2, true);

		auto library = ObjectN::create();
		library->setArea(Rect(90, 80, 110, 250));
		library->setCursor(Cursor::ENTER);
		library->setFieldChangeEvent("library");
		addObject(library, "library", 1, false);

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

		door = ObjectN::create();
		door->setArea(Rect(310, 50, 190, 250));
		door->setCursor(Cursor::INFO);
		door->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["exit"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "ここを登ると地上に出られそうだ");
				novel->addSentence(0, "継", "バンダナの傷が治ったら一緒に出よう");
				novel->addEvent(0, CallFunc::create([this] {
					mObjectList["exit"]->setMsg("バンダナを置いては行けない");
					mObjectList["exit"]->setState(1);
				}));

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		//door->setMsg("バンダナを置いては行けない");
		addObject(door, "exit", 1, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle4::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaC(0, "chara/scene7.png");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "扉にナメクジのような生物が群がっているのが見える");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "これは…ヒルかな");
			novel->addSentence(0, "継", "近づくと危ないな、血を吸われるかもしれない");
			mObjectList["flag"]->setState(1);

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}
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
		book->setCursor(Cursor::NEW);
		book->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["book1"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "ここら辺に薬物についての本が並んでいる");
				novel->addSentence(0, "継", "バンダナに使われた毒についての項目を探そう");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "パラパラパラ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "……");
				novel->addSentence(0, "継", "お、これかな");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "【シレビノ毒】");
				novel->addSentence(0, "", "違法に作られた薬物。ドラゴン族を狩るために、秘密裏に作られたと考えられている。");
				novel->addSentence(0, "", "血液中に入ると身体が痺れて動けなくなる。この状態から回復するには解毒薬が必要。");
				novel->addSentence(0, "", "以下に解毒薬の作り方を示す。");
				novel->addSentence(0, "", "・水　４０ｍL\n・血清　２～３滴\n・トカゲのしっぽ　一本\n・ヒルの体液　適量");
				novel->addSentence(0, "", "これらの材料を混ぜ合わせれば完成。対象者に注射すれば、すぐに効果が出る。");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "なるほど…早速作ってみよう");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");

				mObjectList["book1"]->setCursor(Cursor::INFO);
				mObjectList["book1"]->setState(1);
			}
			else if (mObjectList["book1"]->getState() == 1) {
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
			}
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
			novel->setFontColor(0, Color3B::BLACK);
			//switch (cocos2d::random() % 3)
			//{
			//case 0:
				novel->addSentence(0, "", "牢屋にいる囚人が、腹を空かせて牢屋に出没するトカゲを食べてしまっているところを見つけた。");
				novel->addSentence(0, "", "研究結果に支障をきたす可能性がある。しっかり駆除しておかなければ。");
			//	break;
			//case 1:
			//	novel->addSentence(0, "", "");
			//	novel->addSentence(0, "", "");
			//	break; 
			//case 2:
			//	break;
			//default:
			//	break;
			//}

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}));
		addObject(book, "book3", 1, true);
	}

	void Library::changedField() {
	}
}