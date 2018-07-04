#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"
#include "Sequence\Title.h"

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
		renji->setCursor(Cursor::NEW);
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
				mObjectList["renji"]->setCursor(Cursor::INFO);

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
		cenotaph->addCanUseItem("memories");
		cenotaph->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "memories" && mObjectList["cenotaph"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->addSentence(0, "寿甘", "何とかして二人に連絡が取れないかしら…");
				novel->addSentence(0, "寿甘", "…そうだ！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "私は初代学長の霊を呼び出した");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘", "すみません！友達が危険なんです…！さっき一緒にいた二人なんですけど…");
				novel->addSentence(0, "寿甘", "二人にこの写真の映像が届くように「風のうわさ」を流してくれませんか？きっと役に立つと思うんです…！");
				novel->addSentence(0, "寿甘", "…やっていただけるのですか！？ありがとうございます！");
				novel->addSentence(0, "寿甘", "つぐるんなら、きっとこの写真から何かわかってくれるはず…");
				novel->addSentence(0, "寿甘", "どうか無事でいて…");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["cenotaph"]->setState(1);
				mObjectList["cenotaph"]->removeCanUseItem("memories");
			}
		}));
		addObject(cenotaph, "cenotaph", 3, true);

		auto crow = ObjectN::create();
		crow->setTexture("crow.png");
		crow->setArea(Rect(530, 50, 150, 90));
		crow->setCursor(Cursor::NEW);
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
				mObjectList["crow"]->setCursor(Cursor::INFO);
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
				novel->addEvent(0, CallFunc::create([this] {
					AudioEngine::play2d("SE/toshi.ogg");
				}));
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
					//ItemMgr::sharedItem()->deleteItem("whistle");
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
			//(getObjState("gate", "crow") == 2) && 
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
		blood->setArea(Rect(50, 260, 80, 150));
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
					auto back = Sprite::create("bg/black.png");
					back->setPosition(Director::getInstance()->getVisibleSize() / 2);
					back->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(5.0f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
					addChild(back, 0, "back");

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

		auto letter = ObjectN::create();
		letter->setArea(Rect(140, 320, 40, 35));
		letter->setCursor(Cursor::NEW);
		letter->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["letter"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addSentence(0, "宇沢", "血痕のそばに紙切れが落ちてますね");
				novel->addSentence(0, "寿甘", "赤い文字で何か書いてあるわね…");
				novel->setFontColor(0, Color3B(200,0,0));
				novel->addSentence(0, "", "放課後、校舎裏でお待ちしております。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "宇沢", "おそらく、この手紙で呼び出されたんでしょうね。");
				novel->addSentence(0, "寿甘", "この文字…どこかで見たような…");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["letter"]->setState(1);
				mObjectList["letter"]->setCursor(Cursor::INFO);
				mObjectList["letter"]->setMsg("手紙が落ちている");
			}
		}));
		addObject(letter, "letter", 2, true);

		auto forest = ObjectN::create();
		forest->setArea(Rect(250, 160, 160, 130));
		forest->setCursor(Cursor::NEW);
		forest->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");

			novel->addSentence(0, "寿甘", "この足跡を追っていくわよ");
			novel->addSentence(0, "寿甘", "…");
			novel->addSentence(0, "寿甘", "どうやら足跡は、学校の裏にある森に続いてるみたいね");
			novel->addSentence(0, "寿甘", "草に紛れて足跡が途切れ途切れになってるわ…");
			novel->addSentence(0, "寿甘", "どうしよう…これじゃ、足跡が追えないわ……");

			novel->addEvent(0, CallFunc::create([this] {
				AudioEngine::stopAll();
				setGetStill(17);
			}));
			novel->setCharaL(0, "");
			novel->setBg(0, "chara/scene8.png");
			novel->addSentence(0, "リアス","…ねぇ");
			novel->addSentence(0, "寿甘", "！？");

			novel->setBg(0, "");
			novel->setCharaL(0, "chara/suama1.png");
			novel->setCharaR(0, "chara/rias1.png");

			novel->addEvent(0, CallFunc::create([this] {
				AudioEngine::play2d("BGM/fear.ogg",true);
			}));
			novel->addSentence(0, "寿甘", "あんたは…！");
			novel->addSentence(0, "リアス", "…それ……");
			novel->addSentence(0, "リアス", "返して……私の…………返して！！");
			novel->addSentence(0, "寿甘", "？……あんたこそ！つぐるんたちを返しなさいよ…！！！！");
			novel->addSentence(0, "リアス", "あなたが……バンダナ様まで……！！！");
			novel->addSentence(0, "寿甘", "はぁ…？？あんたが何かしたんでしょ……？？");
			novel->addSentence(0, "リアス", "返して…返して…！返して……！！！");
			novel->addSentence(0, "リアス", "返して返して返して返して返して返して返して返して返して返して返して返して返して返して返せぇぇぇぇぇぇええええええ！！！！！");
			novel->addSentence(0, "寿甘", "きゃっ");
			novel->addSentence(0, "寿甘", "(な、なんかヤバイ……？逃げよう！)");
			novel->addSentence(0, "リアス", "ドコ行くの？？待って…待てぇぇぇぇぇぇええええええ！！！！");
			novel->addEvent(0, CallFunc::create([this] {
				mObjectList["flag"]->setState(3);
			}));

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(forest, "forest", 1, false);

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
			novel->addEvent(0, CallFunc::create([this] {AudioEngine::play2d("BGM/folklore.ogg", true);; }));

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");

			mObjectList["flag"]->setState(1);
		}
	}

	void Backyard::updateField() {
		if (mObjectList["blood"]->getState() == 1 &&
			mObjectList["nail"]->getState() == 1 &&
			mObjectList["lily"]->getState() == 1 &&
			mObjectList["letter"]->getState() == 1 &&
			mObjectList["flag"]->getState() == 1) {

			if (!getChildByName("novel")) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");

				novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll(); }));
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
				Control::me->getField("classroom")->getObject("usawa")->setCursor(Cursor::NEW);
			}
		}
		else if (mObjectList["flag"]->getState() == 3) {
			Control::me->changeField("forest");
			mObjectList["flag"]->setState(4);
		}
	}

	void Forest::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "校舎裏の森";

		auto bg = Sprite::create("forest_run.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto left = ObjectN::create();
		left->setArea(Rect(0, 50, 270, 430));
		left->setCursor(Cursor::LEFT);
		left->setTouchEvent(CallFunc::create([this] { move(0); }));
		addObject(left, "left", 1, true);

		auto right = ObjectN::create();
		right->setArea(Rect(580, 50, 270, 430));
		right->setCursor(Cursor::RIGHT);
		right->setTouchEvent(CallFunc::create([this] { move(1); }));
		addObject(right, "right", 1, true);

		auto fore = ObjectN::create();
		fore->setArea(Rect(275, 50, 300, 430));
		fore->setCursor(Cursor::FORWARD);
		fore->setTouchEvent(CallFunc::create([this] { move(2); }));
		addObject(fore, "fore", 1, true);

		mCount = 0;
		mLife = 3;

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Forest::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "勢いで森の中に逃げ込んでしまったけれど、どうやって逃げればいいのよ…！！");
			novel->addSentence(0, "寿甘", "何か手がかりになるものはなかったかしら…？");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");

			mObjectList["flag"]->setState(1);
		}
	}

	void Forest::move(int direc) {
		getChildByName("bg")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5), FadeIn::create(0.5)));
		AudioEngine::play2d("SE/footsteps.ogg");

		int correct[8] = { 1,0,2,1,1,2,0,2 };

		if (correct[mCount] == direc) {
			mCount++;

			if (mCount == 8) {
				if (mObjectList["flag"]->getState() == 1) {
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::RED);
					novel->setCharaL(0, "chara/suama1.png");
					novel->setBg(0, "bg/black.png");

					novel->addSentence(0, "寿甘", "はぁ…はぁ……");
					novel->addSentence(0, "寿甘", "…行き止まり……");
					novel->addSentence(0, "寿甘", "もう…逃げられない……");
					novel->setCharaL(0, "");
					novel->setBg(0, "chara/scene8.png");
					novel->addSentence(0, "リアス", "…ひひひ…ひひひひひ………");
					novel->addSentence(0, "リアス", "やっと…追いついた……");
					novel->addSentence(0, "寿甘", "っ…");
					novel->setBg(0, "bg/black.png");
					novel->addEvent(0, CallFunc::create([this] { getChildByName("bg")->runAction(FadeOut::create(0.5)); }));

					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "リアスの指が私の首元にかかる");
					novel->addSentence(0, "", "私は、ぎゅっと目を閉じた…");
					novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll(); }));

					novel->addPauseEvent(0, DelayTime::create(2.0f));

					// セリーヌパート

					novel->addSentence(0, "", "そのしばらく後…");
					novel->setFontColor(0, Color3B::RED);
					novel->setCharaL(0, "chara/celine1.png");
					novel->addEvent(0, CallFunc::create([this] {
						AudioEngine::play2d("BGM/folklore.ogg", true);
						ItemMgr::sharedItem()->deleteItem("paper");
						ItemMgr::sharedItem()->deleteItem("chisel");
						ItemMgr::sharedItem()->deleteItem("hatpin");
						ItemMgr::sharedItem()->deleteItem("memories");
						mObjectList["flag"]->setState(2);
						mLife = 5;
						mCount = 0;
					}));
					novel->addSentence(0, "セリーヌ", "…");
					novel->addSentence(0, "セリーヌ", "（学校まで継様をお迎えに来たのですが、どこにも見当たらなかったので）");
					novel->addSentence(0, "セリーヌ", "（近くにいた方に尋ねてみたところ、どうやら、何かの事件に巻き込まれた可能性が高いようです。）");
					novel->setBg(0, "backyard.png");
					novel->addSentence(0, "セリーヌ", "ここが、その事件現場のようですね。");
					novel->addSentence(0, "セリーヌ", "足跡も途中で途切れてしまっているようです。");
					novel->addEvent(0, CallFunc::create([this] {getChildByName("bg")->runAction(FadeIn::create(0.5)); }));
					novel->setBg(0, "");
					novel->addSentence(0, "セリーヌ", "…");
					novel->addSentence(0, "セリーヌ", "ふむ…");
					novel->addSentence(0, "セリーヌ", "ここでの痕跡はしっかり残ってるみたいですね");
					novel->addSentence(0, "セリーヌ", "どこに…って、それは…");
					novel->addSentence(0, "セリーヌ", "”目の前のあなた”の頭の中ですわ");
					novel->addSentence(0, "セリーヌ", "うふふ…これも心理魔法の一環です");
					novel->addSentence(0, "セリーヌ", "あまりこう言うことをすると怒られてしまうのですが…緊急事態なので致し方ありませんね。");
					novel->addSentence(0, "セリーヌ", "それでは、よろしくお願いします。");
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
				else if (mObjectList["flag"]->getState() == 2) {
					// セリーヌパートクリア

					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->setCharaL(0, "chara/celine1.png");
					novel->setBg(0, "bg/black.png");

					novel->addSentence(0, "セリーヌ", "どうやらここまでみたいですね。");
					novel->addEvent(0, CallFunc::create([this] {getChildByName("bg")->runAction(FadeOut::create(0.5)); }));
					novel->addSentence(0, "セリーヌ", "周りには…誰もいないようです。");
					novel->addSentence(0, "セリーヌ", "…");
					novel->addSentence(0, "セリーヌ", "おや…ここは……");
					novel->addSentence(0, "セリーヌ", "…！");
					novel->addSentence(0, "セリーヌ", "直ちに応援を呼びに行きましょう。");
					novel->addSentence(0, "セリーヌ", "継様達の命が危ないかもしれません。");

					novel->addEvent(0, CallFunc::create([this] {
						// クリア
						AudioEngine::stopAll();
						auto userDef = UserDefault::getInstance();
						userDef->setBoolForKey("celine", true);
						userDef->setBoolForKey("sendEvd", getObjState("gate", "cenotaph"));
						userDef->flush();
						this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([this] {Control::me->setEndFlag(); }), NULL));
					}));
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
			}
		}
		else {
			if (mLife == 0) {
				if (mObjectList["flag"]->getState() == 1) {

					// BAD END
					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->setBg(0, "bg/white.png");
					novel->addSentence(0, "寿甘", "やった！開けた場所に出てこれたみたいね…！");
					novel->addSentence(0, "寿甘", "これでなんとかあいつを撒くことが…");
					novel->addSentence(0, "寿甘", "…って、きゃぁぁぁぁあああああ！！！！！！！");
					novel->setFontColor(0, Color3B::BLACK);
					novel->setBg(0, "bg/black.png");
					novel->addSentence(0, "", "ズルズルズルズル………");
					novel->addSentence(0, "", "BAD　END3「転落」");
					novel->addEvent(0, CallFunc::create([this] {
						AudioEngine::stopAll();
						Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
					}));
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				
				}if (mObjectList["flag"]->getState() == 2) {
					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->setCharaL(0, "chara/celine1.png");
					novel->addSentence(0, "セリーヌ", "道に迷ってしまいました。");
					novel->addSentence(0, "セリーヌ", "仕方ないですね、他を当たって探してみましょう。");
					novel->addSentence(0, "セリーヌ", "皆様、ご無事だといいのですが…");

					novel->addEvent(0, CallFunc::create([this] {
						// クリア
						AudioEngine::stopAll();
						auto userDef = UserDefault::getInstance();
						userDef->setBoolForKey("celine", false);
						userDef->setBoolForKey("sendEvd", getObjState("gate", "cenotaph"));
						userDef->flush();
						this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([this] {Control::me->setEndFlag(); }), NULL));
					}));
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
			}
			else {
				mLife--;

				if (mObjectList["flag"]->getState() == 1) {
					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "寿甘", "こっちじゃないっぽいわ…");
					novel->addSentence(0, "寿甘", "戻らなきゃ…！");
					novel->addEvent(0, CallFunc::create([this] {
						getChildByName("bg")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5), FadeIn::create(0.5)));
						AudioEngine::play2d("SE/footsteps.ogg");
					}));
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}if (mObjectList["flag"]->getState() == 2) {
					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "セリーヌ", "どうやら間違いのようですね。");
					novel->addSentence(0, "セリーヌ", "もと来た道へ、戻りましょう。");
					novel->addEvent(0, CallFunc::create([this] {
						getChildByName("bg")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5), FadeIn::create(0.5)));
						AudioEngine::play2d("SE/footsteps.ogg");
					}));
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
			}
		}
	}
}