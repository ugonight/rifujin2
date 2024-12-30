#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"
#include "ghost.h"

#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;

USING_NS_CC;

namespace day4 {
	void Prison::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "牢屋";

		auto bg = Sprite::create("prison.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");


		auto blanket = ObjectN::create();
		blanket->setArea(Rect(550, 400, 120, 80));
		blanket->setCursor(Cursor::INFO);
		blanket->setFieldChangeEvent("aisle");
		addObject(blanket, "blanket", 1, true);

		{
			auto searchPoint = ObjectN::create();
			searchPoint->setArea(Rect(0, 100, 100, 270));
			searchPoint->setCursor(Cursor::INFO);
			searchPoint->setMsg("鎖が垂れ下がっている");
			addObject(searchPoint, "kusari", 1, true);
		}

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

	}

	void Prison::changedField() {
	}

	void Aisle::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（牢屋）";

		auto bg = Sprite::create("aisle.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(460, 380, 160, 70));
		entrance->setCursor(Cursor::INFO);
		entrance->setFieldChangeEvent("prison");
		addObject(entrance, "prison", 1, true);

		auto remon = ObjectN::create();
		remon->setArea(Rect(95, 200, 100, 170));
		remon->setTexture("aisle_remon.png");
		remon->setCursor(Cursor::NEW);
		remon->setTouchEvent(CallFunc::create([this]() {
			if (mObjectList["remon"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/remon1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "継さん、ちょっといいかしら？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ん？なにかな？");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "そばにこんな紙切れが落ちていたの");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "おお、どれどれ…");
				novel->addSentence(0, "継", "「業務日誌　○○番　××ページ」…これはここの従業員か誰かが残したメモかな？");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "さあ？そうかもしれないわね。");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ありがとう、きっとヒントになると思うよ。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "そう、頑張ってね。");
				mObjectList["remon"]->setState(1);
				mObjectList["remon"]->setCursor(Cursor::INFO);
				Control::me->getField("library")->getObject("book3")->setCursor(Cursor::NEW);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["remon"]->getState() == 1) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/remon1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "早く牢のカギを持ってきてちょうだい");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["remon"]->getState() == 2) {
				// クロユリの花びらを拾う
			}
			}));
		addObject(remon, "remon", 2, true);

		// 牢屋の扉
		auto door = ObjectN::create();
		door->setArea(Rect(225, 155, 55, 205));
		door->setCursor(Cursor::INFO);
		door->setMsg("牢の扉だ、カギがかかっている。");
		door->addCanUseItem("key");
		door->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "key") {
				// 檸檬救出。回収不可能にする
				deleteGhost();

				ItemMgr::sharedItem()->deleteItem("key");
				mObjectList["remon"]->setState(2);
				removeChildByName("door");

				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "ガチャ");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "よし、カギが開いたぞ！");
				novel->setFontColor(0, Color3B::RED);
				novel->setCharaR(0, "chara/remon1.png");
				novel->addSentence(0, "檸檬", "ふぅ、これでここから出られるわ…ありがとね。");
				novel->addEvent(0, CallFunc::create([this]() {mObjectList["remon"]->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create())); }));
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "どういたしまして。水無月さんはここに来る前はどうしてたの？");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "どうもこうも、学校を出ようとしたら後ろから誰かが何かを嗅がせてきて、それで意識を失って…って感じよ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "なるほど、僕も同じような感じだよ…バンダナはひどい傷を負わされてしまったんだ。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "あら、大丈夫なの？");
				novel->setCharaC(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "ああ、さっき継に治してもらってすっかり動けるようになった。");
				novel->addSentence(0, "バンダナ", "それより、とっとと出口を探そうぜ。あっちの地上に出るはしごは今使えなくなっちまってんだ。");
				novel->addSentence(0, "継", "そうだね、他に道があるとすれば…ここの奥にある扉かな。");
				novel->addSentence(0, "継", "まずは、あそこを開ける方法を探そう。");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			}));
		addObject(door, "door", 2, true);


		auto b2f = ObjectN::create();
		b2f->setArea(Rect(100, 430, 320, 50));
		b2f->setCursor(Cursor::BACK);
		b2f->setFieldChangeEvent("aisle2");
		addObject(b2f, "b2f", 1, true);


		auto dangeon = ObjectN::create();
		dangeon->setArea(Rect(380, 140, 100, 160));
		dangeon->setCursor(Cursor::ENTER);
		dangeon->setMsg("カギがかかっている");
		dangeon->addCanUseItem("key2");
		dangeon->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "key2") {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "ガチャ");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "よし、カギが開いたぞ！");
				novel->setFontColor(0, Color3B::RED);
				novel->setCharaR(0, "chara/remon1.png");
				novel->addSentence(0, "檸檬", "ここから外に出られるのかしら？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "まだわからないけど…行ってみよう。");

				novel->setEndTask(0, CallFunc::create([this]() {
					Control::me->changeField("dangeon1"); 
					playSoundBS("SE/door.ogg");
					}));
				this->addChild(novel, 10, "novel");

				ItemMgr::sharedItem()->deleteItem("key2");
				mObjectList["dangeon"]->setState(1);
				mObjectList["dangeon"]->setMsg("");
				mObjectList["dangeon"]->setFieldChangeEvent("dangeon1");
			}
			}));
		addObject(dangeon, "dangeon", 1, true);


		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create([this]() {
			// 日記取得
			bool gotdiary = false;
			for (int i = 1; i <= 4; i++) { if (UserDefault::getInstance()->getBoolForKey(StringUtils::format("diary%d", i).c_str())) { gotdiary = true; break; } }
			if (gotdiary && !ItemMgr::sharedItem()->getGetItem("diary")) {
				ItemMgr::sharedItem()->getItem("diary", Point(-100, -100));
			}
			}), NULL));
	}

	void Aisle::changedField() {

	}
}