#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	void Corridor::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "廊下";

		auto bg = Sprite::create("corridor.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");


		auto remon = ObjectN::create();
		remon->setTexture("remon.png");
		remon->setArea(Rect(30, 110, 140, 370));
		remon->setCursor(Cursor::INFO);
		remon->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["remon"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/remon1.png");
				novel->addSentence(0, "寿甘", "ちょっといい？");
				novel->addSentence(0, "檸檬", "何かしら");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかったー？");
				novel->addSentence(0, "檸檬", "さあ、知らないわ");
				novel->addSentence(0, "寿甘", "そっかー…あ、そういえば");
				novel->addSentence(0, "寿甘", "さっきの体育でボール拾いに行ってくれてありがとうね！");
				novel->addSentence(0, "寿甘", "魔球用ボールが入ってたなんて気付かなくてさー…飛ばしすぎちゃった！");
				novel->addSentence(0, "檸檬", "…ああ、いいのよ。大したことないわ");
				novel->addSentence(0, "檸檬", "それじゃあ、私は用事があるからこれで");
				novel->addSentence(0, "檸檬", "じゃあね");
				novel->setCharaR(0, "");
				novel->addEvent(0, CallFunc::create([this] (){
					mObjectList["remon"]->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f),RemoveSelf::create()));
				}));
				novel->addSentence(0, "寿甘", "うん、またねー！");
				novel->addSentence(0, "寿甘", "帰っちゃった…");
				mObjectList["remon"]->setState(1);


				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(remon, "remon", 3, true);

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

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Corridor::changedField() {
	}

	void ClassRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "教室";

		auto bg = Sprite::create("classroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto usawa = ObjectN::create();
		usawa->setTexture("usawa.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::INFO);
		usawa->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["usawa"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "寿甘", "おい宇沢");
				novel->addSentence(0, "宇沢", "なんですか、いきなり呼び捨てにして…");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかった？");
				novel->addSentence(0, "宇沢", "うーん…私も今戻ったところなので見てないですねぇ…");
				novel->addSentence(0, "寿甘", "あっそ、新聞部もその程度なのね、じゃあな");
				novel->addSentence(0, "宇沢", "ああああ待ってください！！…そういえばこんな噂があります");
				novel->addSentence(0, "宇沢", "バンダナさんが継様に言い寄っているところを見た人がいたとか…これは禁断の三角関係の香りが…");
				novel->addSentence(0, "寿甘", "あ゛？？？");
				novel->addSentence(0, "宇沢", "すみません…");
				mObjectList["usawa"]->setState(1);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["usawa"]->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "宇沢", "二人とも見てないです…ごめんなさい…");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(usawa, "usawa", 1, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);

		auto memo = ObjectN::create();
		memo->setArea(Rect(0, 200, 170, 140));
		memo->setCursor(Cursor::NEW);
		memo->setItemGetEvent("paper");
		memo->setMsg("メモを手に入れた");
		memo->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "あ、これ今朝拾ったメモだ");
			novel->addSentence(0, "寿甘", "つぐるん置きっぱなしにしちゃったのかー…");
			novel->addSentence(0, "寿甘", "しばらくリアスに返さないで持ってようかな、手掛かりになるかもしれないし。");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(memo, "memo", 3, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void ClassRoom::changedField() {

	}

	void ArtRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "美術室";

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

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/maria1.png");
				novel->addSentence(0, "寿甘", "おつかれー！");
				novel->addSentence(0, "マリア", "おつかれー");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかったー？");
				novel->addSentence(0, "マリア", "うーん、ごめんねー見てないかな…");
				novel->addSentence(0, "寿甘", "ううん、大丈夫だよー");
				novel->addSentence(0, "マリア", "そういえば、リアスちゃんが何か探してるみたいだったの");
				novel->addSentence(0, "寿甘", "えぇ…どうせバンダナのことだと思うよ…");
				novel->addSentence(0, "寿甘", "あいつより早く見つけなきゃ…");
				novel->addSentence(0, "マリア", "あのね、ちょっと違う気がするんだ。");
				novel->addSentence(0, "マリア", "なんだか悲しそうな顔をしてた");
				novel->addSentence(0, "寿甘", "ん？そうだったんだ");
				novel->addSentence(0, "寿甘", "まあいいや、ありがとねー！");
				mObjectList["maria"]->setState(1);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["maria"]->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/maria1.png");
				novel->addSentence(0, "マリア", "二人とも見てないの…ごめんね");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(maria, "maria", 1, true);

		auto whistle = ObjectN::create();
		whistle->setTexture("whistle.png");
		whistle->setArea(Rect(520, 430, 60, 50));
		whistle->setCursor(Cursor::NEW);
		whistle->setItemGetEvent("whistle");
		whistle->setMsg("木片を手に入れた");
		addObject(whistle, "whistle", 2, true);

		auto chisel = ObjectN::create();
		chisel->setTexture("chisel.png");
		chisel->setArea(Rect(120, 40, 80, 40));
		chisel->setCursor(Cursor::NEW);
		chisel->setItemGetEvent("chisel");
		chisel->setMsg("彫刻刀を手に入れた");
		addObject(chisel, "chisel", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::ENTER);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}