#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day3 {
	void Gate::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "校門";

		auto bg = Sprite::create("gate.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto renji = ObjectN::create();
		renji->setTexture("renji.png");
		renji->setArea(Rect(50, 110, 120, 370));
		renji->setCursor(Cursor::INFO);
		renji->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["renji"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/renji1.png");
				novel->addSentence(0, "寿甘", "おい神北");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳", "俺は辛辣な方なのか…");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "つぐるんとバンダナがどこに行ったか知らない？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳", "おお、そのことか");
				novel->addSentence(0, "恋巳", "バンダナ殿は、俺が教室に戻ってくるときに校庭へ出ていくところを見た。");
				novel->addSentence(0, "恋巳", "継殿は、その少し後にバンダナ殿を追って出ていったぞ。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "おお、まさかここで有益な情報が手に入るとは…ありがとねー");
				novel->addSentence(0, "寿甘", "ふむ…となると、やっぱり二人とも先に帰っちゃったのかな…");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳", "それはないと思うぞ");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "ん、どうして？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳", "先ほど新聞部が号外を配っていてな、校舎の上空をUFOが飛んでいたというようなことが書かれていた。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "なんだかんだ言って記事に使ったのね…あれ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "恋巳", "それで居ても立っても居られなくなって、すぐに校庭に戻ってUFOを探したんだ。その時は継殿はまだバンダナ殿を探していた。");
				novel->addSentence(0, "恋巳", "それからずっとここで見張っているのだが、二人ともここから出てきていないんだ。UFOも見つかっていない。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "ほう…まだ二人とも構内にいる可能性が高いのか…");
				novel->addSentence(0, "寿甘", "うーん…どこにいるのよ…");
				mObjectList["renji"]->setState(1);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["renji"]->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/renji1.png");
				novel->addSentence(0, "恋巳", "まだ二人ともここから出てきてないぞ");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(renji, "renji", 1, true);

		auto cenotaph = ObjectN::create();
		cenotaph->setArea(Rect(700, 100, 100, 180));
		cenotaph->setCursor(Cursor::INFO);
		cenotaph->setMsg("初代学長の慰霊碑がある");
		addObject(cenotaph, "cenotaph", 3, true);

		auto crow = ObjectN::create();
		crow->setTexture("crow.png");
		crow->setArea(Rect(530, 50, 150, 90));
		crow->setCursor(Cursor::INFO);
		crow->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["crow"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->addSentence(0, "寿甘", "こらー！！クロー！！！");
				novel->addSentence(0, "寿甘", "まーた人様のもの盗んでー！！");
				novel->addSentence(0, "寿甘", "今日という今日は許さないんだから！！！");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "は？知ったこっちゃねえよ");
				novel->addSentence(0, "クロ", "俺は落ちてたものを拾っただけだ");
				novel->addSentence(0, "クロ", "落とした奴が間抜けなのが悪い");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "そんなわけないでしょ！！");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "おっと、これ以上近づくと痛い目に遭うぜ？");
				novel->addSentence(0, "クロ", "俺様のこのナイフのように尖ったくちばしでなァ");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "ぐぬぬ…");
				novel->addSentence(0, "寿甘", "こんな時、あの子がいれば…");

				mObjectList["crow"]->setState(1);
				mObjectList["crow"]->setMsg("カラスのクロがいる");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "whistle" && Control::me->getField("AboutItem")->getObject("whistle_o2")->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->addSentence(0, "寿甘", "えい！これでもくらえ！！");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "はんッ");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "シュパンッ！");
				novel->addSentence(0, "", "クロは円筒の木片に穴をあけた");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "お前も穴だらけになりたくなかったら、潔く諦めるんだなァ");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "フフッ…かかったわね…");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "？？？");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				Control::me->getField("AboutItem")->getObject("whistle_o2")->setState(1);
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "whistle" && Control::me->getField("AboutItem")->getObject("whistle_o2")->getState() == 1 && Control::me->getField("AboutItem")->getObject("whistle_o1")->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->addSentence(0, "寿甘", "助けて！！翼くん！！！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "ピューーーーーー！");
				novel->setCharaL(0, "");
				novel->setBg(0, "chara/tsubasa.png");
				novel->addEvent(0,CallFunc::create([this]() {
					setGetStill(12);
				}));
				novel->addSentence(0, "", "バシッ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "のわっ");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "やったー！");
				novel->addEvent(0, CallFunc::create([this]() {
					ItemMgr::sharedItem()->getItem("hatpin", Point(85, 480 - 145));
					ItemMgr::sharedItem()->deleteItem("whistle");
					Control::me->showMsg("簪を手に入れた");
				}));
				novel->addSentence(0, "寿甘", "ありがとー翼くんー！！");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "翼", "フッ…お安い御用だぜ…");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "また、後でね…///");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setBg(0, "");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "クロ", "チッ…");
				novel->addSentence(0, "クロ", "覚えていやがれ！！");
				novel->addEvent(0, CallFunc::create([this]() {
					mObjectList["crow"]->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create()));
				}));
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "さてと");
				novel->addSentence(0, "寿甘", "これは…かんざし、かな？壊れちゃってるみたいだけど…");
				novel->addSentence(0, "寿甘", "持ち主がいたら返してあげたいわね");
				mObjectList["crow"]->setState(2);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		crow->addCanUseItem("whistle");
		addObject(crow, "crow", 4, true);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(300, 140, 270, 100));
		entrance->setCursor(Cursor::FORWARD);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

	}

	void Gate::changedField() {

	}

	void Entrance::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "校舎前";

		auto bg = Sprite::create("entrance.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto gate = ObjectN::create();
		gate->setArea(Rect(780, 0, 74, 480));
		gate->setCursor(Cursor::RIGHT);
		gate->setFieldChangeEvent("gate");
		addObject(gate, "gate", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(0, 0, 80, 480));
		corridor->setCursor(Cursor::LEFT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);

		auto backyard = ObjectN::create();
		backyard->setArea(Rect(620, 80, 130, 250));
		backyard->setCursor(Cursor::FORWARD);
		backyard->setFieldChangeEvent("backyard");
		addObject(backyard, "backyard", 2, false);

	}

	void Entrance::changedField() {
		if ((getObjState("gate", "renji") == 1 &&
			getObjState("classroom", "usawa") == 1 &&
			getObjState("artroom", "maria") == 1 &&
			getObjState("corridor", "remon") == 1) &&
			(getObjState("gate", "crow") == 2) && 
			(mObjectList["backyard"]->getState() == 0)){
			AudioEngine::stopAll();
			AudioEngine::play2d("SE/heart1.ogg", true);

			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ざわざわ…");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "なんだか向こう側が騒がしいわね…");
			novel->addSentence(0, "寿甘", "裏庭の方からだわ…行ってみよう…");
			novel->addSentence(0, "寿甘", "嫌な予感がする…");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");

			mObjectList["backyard"]->setState(1);
			addChild(mObjectList["backyard"], 2, "backyard");
		}
	}

	void Backyard::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "校舎裏";

		auto bg = Sprite::create("backyard.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(50, 430, 750, 50));
		entrance->setCursor(Cursor::BACK);
		entrance->setMsg("まだ調べていない箇所がある");
		//entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		auto blood = ObjectN::create();
		blood->setArea(Rect(50, 260, 120, 150));
		blood->setCursor(Cursor::NEW);
		blood->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["blood"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addSentence(0, "宇沢", "少々見るのがつらいですが、じっくり観察してみましょう…");
				novel->addSentence(0, "宇沢", "臭いからして本物の血痕みたいですねぇ…");
				novel->addSentence(0, "宇沢", "この量だと、血を流した本人はかなりの大怪我をしているのでしょうね。");
				novel->addSentence(0, "寿甘", "血痕が奥の方に伸びているわね");
				//novel->addSentence(0, "寿甘", "怪我をした人が自力で歩いたのか、もしくは…");
				novel->addSentence(0, "寿甘", "さらに、それに沿って足跡が付いているわ。こんな大きな足跡見たことない…");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["blood"]->setState(1);
				mObjectList["blood"]->setMsg("壁に血痕がついている");
				mObjectList["blood"]->setCursor(Cursor::INFO);
			}
		}));
		addObject(blood, "blood", 2, true);

		auto lily = ObjectN::create();
		lily->setArea(Rect(180, 250, 50, 70));
		lily->setCursor(Cursor::NEW);
		lily->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["lily"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addSentence(0, "寿甘", "このクロユリ…光ってるわ…！");
				novel->addSentence(0, "寿甘", "もしかしたら…");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "私はクロユリの花に手をかざしてみた");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "やっぱり…");
				novel->addSentence(0, "寿甘", "このクロユリは、事件が起きた時の記憶を持っているみたいね。");
				novel->addSentence(0, "宇沢", "確かクロユリは、周囲の映像を花弁に残して監視カメラのような役割を担ったりするんですよね！");
				novel->addSentence(0, "宇沢", "早速見てみましょう");
				novel->addSentence(0, "寿甘", "ええ");
				novel->addPauseEvent(0, Sequence::createWithTwoActions(
					CallFunc::create([this] {
					for (int i = 0; i < 4; i++) {
						if (i != 2) {
							auto spr = Sprite::create(StringUtils::format("chara/memory%d.png", i + 1));
							setGetStill(13 + i);
							spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
							spr->setOpacity(0.0f);
							if (i == 3) {
								spr->runAction(Sequence::create(DelayTime::create(2.0f * 2), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
							}
							else {
								spr->runAction(Sequence::create(DelayTime::create(2.0f * (float)i), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
							}
							addChild(spr, 0, StringUtils::format("bg%d", i));
						}
					}
				}),
					DelayTime::create(6.0f)
					));
				novel->addSentence(0, "寿甘", "これって…！");
				novel->addSentence(0, "寿甘", "やっぱり二人とも事件に巻き込まれてたんだ…");
				novel->addSentence(0, "宇沢", "ふむ…写真の中に少し違和感がありますねぇ");
				novel->addSentence(0, "宇沢", "これは後ほど検証してみる価値がありそうですね…");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->getItem("memories", Point(200, 200));
				}));
				novel->addSentence(0, "宇沢", "この映像は、私のカメラにも残しておきましょう。");
				novel->addSentence(0, "寿甘", "二人ともどうか無事でいて…！");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["lily"]->setState(1);
				mObjectList["lily"]->setCursor(Cursor::INFO);
				mObjectList["lily"]->setMsg("クロユリの花が光っている");
			}
		}));
		addObject(lily, "lily", 2, true);

		auto nail = ObjectN::create();
		nail->setArea(Rect(430, 370, 40, 50));
		nail->setCursor(Cursor::NEW);
		nail->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["nail"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addSentence(0, "宇沢", "おや、こんな所に釘が落ちていますね。");
				novel->addSentence(0, "寿甘", "釘なんて落ちててもそんなに不思議じゃないけど…");
				novel->addSentence(0, "寿甘", "一応覚えておくか");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["nail"]->setState(1);
				mObjectList["nail"]->setCursor(Cursor::INFO);
				mObjectList["nail"]->setMsg("釘が落ちている");
			}
		}));
		addObject(nail, "nail", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Backyard::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "ちょっと、みんなどうしたの…って");
			novel->addSentence(0, "寿甘", "な、なにこれ…");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "裏庭の壁には赤いシミがべっとりとついていた");
			novel->addSentence(0, "", "それは、まるで血痕のような…");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaR(0, "chara/usawa1.png");
			novel->addSentence(0, "宇沢", "魔界王国で流血沙汰ってだけで大問題なのに");
			novel->addSentence(0, "宇沢", "この学校でこんな事件が起きるとは…");
			novel->addSentence(0, "宇沢", "これは…大大大大スクープの予感ですねぇ！！");
			novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll(); }));
			novel->addSentence(0, "寿甘", "ふざけないでよ！！");
			novel->addSentence(0, "寿甘", "誰かが怪我してるのかも知れないのよ？");
			novel->addSentence(0, "寿甘", "もしかしたら、つぐるんたちが何かに巻き込まれて…");
			novel->addSentence(0, "宇沢", "…すみません、不謹慎でした。");
			novel->addSentence(0, "宇沢", "でもこの血痕が、お二人の行方に関係があるのなら、調べてみる価値はあるかもしれませんよ。");
			novel->addSentence(0, "宇沢", "調査ならご一緒しますよ？");
			novel->addSentence(0, "寿甘", "…確かにそうね");
			novel->addSentence(0, "寿甘", "じゃあ、この辺りに手掛かりがないか調査するわよ！");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");

			mObjectList["flag"]->setState(1);
		}
	}

	void Backyard::updateField() {
		if (mObjectList["blood"]->getState() == 1 &&
			mObjectList["nail"]->getState() == 1 &&
			mObjectList["lily"]->getState() == 1 &&
			mObjectList["flag"]->getState() == 1) {

			if (!getChildByName("novel")) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addSentence(0, "寿甘", "一通り調べられたみたいね");
				novel->addSentence(0, "寿甘", "よし、早く二人を探しに行かなきゃ…！");
				novel->addSentence(0, "宇沢", "ちょっと待ってください");
				novel->addSentence(0, "寿甘", "何よ");
				novel->addSentence(0, "宇沢", "一旦、対策を練っておくのがよろしいかと思いますねぇ");
				novel->addSentence(0, "宇沢", "闇雲に探すよりは、現場の状況から二人の行き先を推理した方が早く見つかるかもしれませんよ？");
				novel->addSentence(0, "寿甘", "…うーん、まあそうね");
				novel->addEvent(0, CallFunc::create([this] {AudioEngine::play2d("BGM/school.ogg", true); }));
				novel->addSentence(0, "宇沢", "では、そうしましょう！");
				novel->addSentence(0, "宇沢", "手分けして学校の人に聞き込みをした後で、教室で落ち合いましょう！");
				novel->addSentence(0, "寿甘", "うん、じゃあまた後で。");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["flag"]->setState(2);
				mObjectList["entrance"]->setFieldChangeEvent("entrance");
				mObjectList["entrance"]->setMsg("");
			}
		}
	}
}