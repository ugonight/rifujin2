#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void Corridor::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("corridor.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto remon = ObjectN::create();
		remon->setTexture("remon.png");
		remon->setArea(Rect(30, 110, 140, 370));
		remon->setCursor(Cursor::INFO);
		remon->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/remon1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬「うふふ、御機嫌よう」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(remon, "remon", 1, true);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(784, 0, 70, 480));
		entrance->setCursor(Cursor::RIGHT);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		auto classroom = ObjectN::create();
		classroom->setArea(Rect(420, 120, 90, 360));
		classroom->setCursor(Cursor::ENTER);
		classroom->setFieldChangeEvent("classroom");
		addObject(classroom, "classroom", 2, true);

		auto artroom = ObjectN::create();
		artroom->setArea(Rect(175, 180, 145, 150));
		artroom->setCursor(Cursor::FORWARD);
		artroom->setFieldChangeEvent("artroom");
		addObject(artroom, "artroom", 2, true);
	}

	void Corridor::changedField() {

	}

	void ClassRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("classroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto usawa = ObjectN::create();
		usawa->setTexture("usawa_hide.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::INFO);
		usawa->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["usawa_"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「…もしもーし」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…何してるんですかー」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…ｺﾁｮｺﾁｮｺﾁｮ」");
				novel->addSentence(0, "？？？「……～～！！」");
				novel->addSentence(0, "寿甘「…ｺﾁｮｺﾁｮｺﾁｮｺﾁｮｺﾁｮｺﾁｮ」");
				novel->addSentence(0, "？？？「……うぐぐ…」");
				novel->addSentence(0, "寿甘「…しぶといわね…」");
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「…さっきから何をしてるの？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……（ぱあぁ）」");
				novel->setCharaC(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「うっそだろお前、俺でも気付いたぜ？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……（グサッ）」");
				novel->addSentence(0, "寿甘「こんなにバレバレなのにわかんないの！？」");
				novel->addSentence(0, "？？？「……（グサグサッッ）」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「？？？」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["usawa_"]->setState(1);
				mObjectList["usawa_"]->addCanUseItem("pepper");
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "pepper"){
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「…ぱらぱら」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…ぱらぱらぱら」");
				novel->addSentence(0, "？？？「……は」");
				novel->addSentence(0, "寿甘「…ぱらぱらぱらぱらぱらぱら」");
				novel->addSentence(0, "？？？「……ぶわあぁぁぁぁぁぁぁぁくしょおぉおぉぉぉい！！！！」");
				novel->addEvent(0,CallFunc::create([this] {
					ItemMgr::sharedItem()->deleteItem("pepper");
					mObjectList["usawa_"]->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
					mObjectList["usawa"]->setOpacity(0.0f);
					mObjectList["usawa"]->runAction(FadeIn::create(0.5f));
					addChild(mObjectList["usawa"], 2, "usawa");
				}));
				novel->addSentence(0, "寿甘「…（グッ）」");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "？？？「……チッ…このベテラン新聞部員の宇沢　智恵（うさわ　ともえ）様の”隠れ身の術”を見破るなんて大したものね…」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaC(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ「大丈夫なのか新聞部…」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "宇沢「はぁ？新聞部の調査能力をなめてもらっちゃあ困りますねぇ？」");
				novel->addSentence(0, "宇沢「そう、例えば…立花さん、あなたは現在美術部のマドンナ、マリア・ミルフィーユさんとお付き合いしていてあんなことやこんなことまで…」");
				novel->addSentence(0, "寿甘「してませんけど」");
				novel->addSentence(0, "宇沢「またまた、御冗談を～わたくしの地獄耳は騙せませんよぉ？」");
				novel->addSentence(0, "宇沢「それにわたくし、今あなた方にとっておきの耳寄りな情報があるんですよ…聞いていきます？」");
				novel->addSentence(0, "寿甘「うさんくさいわね…」");
				novel->addSentence(0, "宇沢「そこまで言われちゃあ、教えてあげないわけにもいきませんねぇ？」");
				novel->addSentence(0, "宇沢「た・だ・し。わたくしを楽しませてくれるようなものを持ってきてくれたら、ですねぇ…」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「なんだこいつ…」");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->getItem("camera", Director::getInstance()->getVisibleSize() / 2);
					Control::me->showMsg("カメラを手に入れた");
					Control::me->getField("gate")->getObject("renji")->setState(2);
					Control::me->getField("gate")->getObject("renji")->setCursor(Cursor::NEW);
				}));
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "宇沢「んじゃあこれ貸すんで、いいスクープ撮ってきてくださいね～」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(usawa, "usawa_", 1, true);

		usawa = ObjectN::create();
		usawa->setTexture("usawa.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::INFO);
		usawa->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/usawa1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "宇沢「わたくしを楽しませてくれそうなものは持ってきてくれたかしら？」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(usawa, "usawa", 1, false);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ClassRoom::changedField() {

	}

	void ArtRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("art_room.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto maria = ObjectN::create();
		maria->setTexture("maria.png");
		maria->setArea(Rect(60, 180, 230, 300));
		maria->setCursor(Cursor::INFO);
		maria->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["maria"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「あ、マリアちゃんおはよー！」");
				novel->addSentence(0, "マリア「あ！寿甘ちゃんおはよー」");
				novel->addSentence(0, "寿甘「美術部の朝練？朝からおつかれー！」");
				novel->addSentence(0, "マリア「えへへ…ありがとー」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["maria"]->setState(1);
				mObjectList["maria"]->addCanUseItem("magazine");
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "magazine") {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「マリアちゃん、お願いがあるんだけど」");
				novel->addSentence(0, "マリア「ん？何かな？」");
				novel->addSentence(0, "寿甘「また例のアレをお願いしたいんだー大丈夫ー？」");
				novel->addSentence(0, "マリア「ちょっと恥ずかしいけど…まだ部員の人たちは来てないし、寿甘ちゃん達だけだったらいいよー」");
				novel->addSentence(0, "寿甘「ほんと！？ありがとー！」");
				novel->addSentence(0, "寿甘「ほんじゃ、これでお願いねー」");
				novel->addSentence(0, "マリア「わかった。今から描くからちょっと待っててね」");
				novel->setCharaC(0, "chara/tuguru1.png");
				novel->addSentence(0, "継「例のアレって何のこと…？」");
				novel->addSentence(0, "寿甘「まあ見てればわかるって！」");
				novel->addSentence(0, "マリア「できたよー」");
				novel->addSentence(0, "継「これは…UFOの絵かな？」");
				novel->addSentence(0, "マリア「これをこうやって…えいっ！」");
				novel->addSentence(0, "継「うわあ！UFOが絵の中から出て来たよ！」");
				novel->addSentence(0, "マリア「実は、私の特殊能力は絵に描いたものを具現化することだったの。余計引かれちゃうから秘密にしてたんだけど…」");
				novel->addSentence(0, "寿甘「だーかーらそんなことないって！みんなマリアちゃんの絵、大好きだよ！」");
				novel->addSentence(0, "マリア「ありがとう…そう言ってもらえるとうれしいな」");
				novel->addSentence(0, "継「UFOが窓の外へ飛んだ行ったよ。見失う前に撮影しに行こう。」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				
				ItemMgr::sharedItem()->deleteItem("magazine");
				Control::me->getField("entrance")->addChild(Control::me->getField("entrance")->getObject("ufo"), 3, "ufo");
			}
			else {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "マリア「おはよー」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(maria, "maria", 1, true);

		auto net = ObjectN::create();
		net->setTexture("net.png");
		net->setArea(Rect(200, 100, 100, 50));
		net->setCursor(Cursor::NEW);
		net->setItemGetEvent("net");
		net->setMsg("金網を手に入れた");
		addObject(net, "net", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::ENTER);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}