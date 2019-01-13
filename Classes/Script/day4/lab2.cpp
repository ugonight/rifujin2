#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"
#include "Sequence\Title.h"
#include "ghost.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

// #include <fstream>


namespace day4 {
	void Aisle2::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（B2F-1）";

		auto bg = Sprite::create("aisle2.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto prison = ObjectN::create();
		prison->setArea(Rect(490, 50, 110, 220));
		prison->setCursor(Cursor::ENTER);
		prison->setFieldChangeEvent("aisle");
		addObject(prison, "prison", 1, true);

		auto aisle3 = ObjectN::create();
		aisle3->setArea(Rect(50, 430, 800, 50));
		aisle3->setCursor(Cursor::BACK);
		aisle3->setFieldChangeEvent("aisle3");
		addObject(aisle3, "aisle3", 1, true);

		auto aisle4 = ObjectN::create();
		aisle4->setArea(Rect(260, 0, 100, 150));
		aisle4->setCursor(Cursor::FORWARD);
		aisle4->setFieldChangeEvent("aisle4");
		addObject(aisle4, "aisle4", 1, true);

		auto lab = ObjectN::create();
		lab->setArea(Rect(690, 110, 65, 310));
		lab->setCursor(Cursor::ENTER);
		lab->setFieldChangeEvent("lab");
		addObject(lab, "lab", 1, true);

		auto door = ObjectN::create();
		door->setArea(Rect(0, 90, 50, 320));
		door->setCursor(Cursor::ENTER);
		door->setMsg("カギがかかっている");
		addObject(door, "locked", 1, true);

		// chap3で寿甘が証拠を送っていたら
		//auto ghost = ObjectN::create();
		//ghost->setTexture("ghost.png");
		//ghost->setPosition(Vec2(410, 480 - 180));
		//auto rect = ghost->getBoundingBox();
		//rect.setRect(rect.getMinX(), 480 - rect.getMaxY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY());
		//ghost->setArea(rect);
		//ghost->setCursor(Cursor::INFO);
		//ghost->setOpacity(0.0f);
		//ghost->setBlendFunc(BlendFunc{ GL_SRC_ALPHA ,GL_ONE });
		//ghost->setAction(RepeatForever::create(Spawn::createWithTwoActions(
		//	Sequence::createWithTwoActions(EaseSineOut::create(FadeIn::create(3.0f)), EaseSineIn::create(FadeOut::create(3.0f)))
		//	, Sequence::createWithTwoActions(EaseSineOut::create(MoveBy::create(3.0f, Vec2(0.0f, 30.0f))), EaseSineIn::create(MoveBy::create(3.0f, Vec2(0.0f, -30.0f))))
		//))
		//);
		addObject(createGhost(420, 180, "aisle2"), "ghost", 1, UserDefault::getInstance()->getBoolForKey("sendEvd"));
	}

	void Aisle2::changedField() {

	}


	void Lab::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "研究室";

		auto bg = Sprite::create("lab.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle2 = ObjectN::create();
		aisle2->setArea(Rect(500, 420, 354, 60));
		aisle2->setCursor(Cursor::BACK);
		aisle2->setFieldChangeEvent("aisle2");
		addObject(aisle2, "aisle2", 1, true);


		auto hikido = Sprite::create();
		hikido->setPosition(visibleSize / 2);
		hikido->setTexture("hikido.png");
		addChild(hikido, 3, "hikido");

		auto sulfate = ObjectN::create();
		sulfate->setTexture("sulfate.png");
		sulfate->setArea(Rect(410, 195, 20, 50));
		sulfate->setCursor(Cursor::NEW);
		sulfate->setItemGetEvent("sulfate");
		sulfate->setMsg("硫酸を手に入れた");
		addObject(sulfate, "sulfate", 3, true);

		addObject(createGhost(800, 150, "lab"), "ghost", 1, false);

	}

	void Lab::changedField() {

	}


	void Aisle3::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（B2F-2）";

		auto bg = Sprite::create("aisle3.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle2 = ObjectN::create();
		aisle2->setArea(Rect(190, 430, 664, 50));
		aisle2->setCursor(Cursor::BACK);
		aisle2->setFieldChangeEvent("aisle2");
		addObject(aisle2, "aisle2", 1, true);

		auto door = ObjectN::create();
		door->setArea(Rect(560, 160, 120, 200));
		door->setCursor(Cursor::ENTER);
		door->setFieldChangeEvent("torture");
		addObject(door, "torture", 1, true);

		door = ObjectN::create();
		door->setArea(Rect(90, 160, 110, 300));
		door->setCursor(Cursor::ENTER);
		// door->setMsg("鍵がかかっている");
		// door->setFieldChangeEvent("baking");
		door->setTouchEvent(CallFunc::create([this] (){
			if (mObjectList["baking"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ん…？よく見たらこの扉は木製みたいだ。");
				novel->addSentence(0, "バンダナ", "それに、若干腐りかけてるな…");
				novel->addSentence(0, "バンダナ", "素手だと時間がかかるけど、つるはしのようなものがあれば簡単に壊せそうだな。");
				novel->addSentence(0, "継", "どこかにあるかな、探してみよう。");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");

				mObjectList["baking"]->setState(1);
				mObjectList["baking"]->addCanUseItem("thorn");

			}
			else if (mObjectList["baking"]->getState() == 1) {
				Control::me->showMsg("鍵がかかっている。");

				if (ItemMgr::sharedItem()->getSelectedItem() == "thorn") {
					auto novel = Novel::create();
					novel->setCharaR(0, "chara/bandana1.png");
					novel->setCharaC(0, "chara/tuguru1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継", "この石のトゲなら扉を壊せるかな。");
					novel->addSentence(0, "バンダナ", "よし、やってみるぜ。");
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "ガッ…ガッ…");
					novel->addSentence(0, "", "ガッ……ガッ……");
					novel->addSentence(0, "", "バキンッ");
					novel->addEvent(0, CallFunc::create([this]() {
						mObjectList["hole"]->setOpacity(0.0f);
						mObjectList["hole"]->runAction(FadeIn::create(1.0f));
						addChild(mObjectList["hole"], 2, "hole");
					}));
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "バンダナ", "これで通れそうだな！");
					novel->addSentence(0, "継", "入ってみよう");
					
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");

					mObjectList["baking"]->setState(2);
					mObjectList["baking"]->setFieldChangeEvent("baking");
					mObjectList["baking"]->removeCanUseItem("thorn");

				}
			}
		}));
		addObject(door, "baking", 1, true);

		auto hole = ObjectN::create();
		hole->setTexture("hole.png");
		addObject(hole, "hole", 2, false);

		auto light = ObjectN::create();
		light->setTexture("light_.png");
		light->setPosition(Vec2(395, 480 - 130));
		light->setBlendFunc(BlendFunc{ GL_SRC_ALPHA, GL_ONE });
		light->setAction(RepeatForever::create(Sequence::create(FadeOut::create(3.0f), FadeIn::create(3.0f), NULL)));
		addObject(light, "light", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle3::changedField() {
	}

	void Torture::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "拷問室";

		auto bg = Sprite::create("torture.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto bl = ObjectN::create();
		bl->setTexture("bg/black.png");
		bl->setPosition(visibleSize / 2);
		bl->setOpacity(200.f);
		addObject(bl, "black", 5, false);

		auto aisle3 = ObjectN::create();
		aisle3->setArea(Rect(550, 430, 120, 50));
		aisle3->setCursor(Cursor::BACK);
		aisle3->setFieldChangeEvent("aisle3");
		addObject(aisle3, "aisle3", 1, true);

		auto shojo = ObjectN::create();
		shojo->setArea(Rect(540, 90, 120, 260));
		shojo->setCursor(Cursor::INFO);
		shojo->setMsg("鉄の処女だ。危ないから離れよう");
		addObject(shojo, "shojo", 1, true);

		auto guillotine = ObjectN::create();
		guillotine->setArea(Rect(330, 100, 170, 280));
		guillotine->setCursor(Cursor::INFO);
		guillotine->setTexture("guillotine.png");
		guillotine->setMsg("ギロチンだ。危ないから触らないようにしよう。");
		guillotine->addCanUseItem("skeleton");
		guillotine->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "skeleton") {
				ItemMgr::sharedItem()->deleteItem("skeleton");
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "バンダナ", "まさか…これを使うのか？");
				novel->addSentence(0, "継", "うん…骸骨をギロチンにかけて首を落とせば、カギを取りだせると思うんだ。");
				novel->addSentence(0, "バンダナ", "まあもう死んでるしバチは当たらないか…");
				novel->addSentence(0, "継", "この人には申し訳ないけど、一刻を争うからね。");
				novel->addSentence(0, "バンダナ", "そうだな、この台に乗せればいいか？");
				novel->addSentence(0, "継", "うん…助かるよ");
				novel->addSentence(0, "バンダナ", "間違って刃を落とすなよ？…よし、セットできた。");
				novel->addSentence(0, "継", "それじゃいくよ……えいっ！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addEvent(0, CallFunc::create([this]() {
					mObjectList["guillotine_h"]->runAction(Sequence::createWithTwoActions(
						EaseOut::create(MoveBy::create(0.03f, Vec2(0, -110.0f)),2), 
						CallFunc::create([this]() {playSoundBS("SE/crash22_b.ogg"); })));
				}));
				novel->addSentence(0, "", "ガチャン！");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "思ったより勢いよく落ちたな…");
				novel->addSentence(0, "継", "さて、カギはあるかな…");
				novel->addSentence(0, "継", "…あ");
				novel->addSentence(0, "バンダナ", "どうした？");
				novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("key_broken", Director::getInstance()->getVisibleSize() / 2); }));
				novel->addSentence(0, "継", "カギも真っ二つになっちゃったみたいだ…");
				novel->addSentence(0, "バンダナ", "まじか…");
				novel->addSentence(0, "継", "くっつけられるものを探さないと");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(guillotine, "guillotine", 3, true);
		guillotine = ObjectN::create();	// 背景
		guillotine->setTexture("guillotine_b.png");
		addObject(guillotine, "guillotine_b", 1, true);
		guillotine = ObjectN::create();	// 刃
		guillotine->setTexture("guillotine_h.png");
		addObject(guillotine, "guillotine_h", 2, true);
		guillotine = ObjectN::create();	// 
		guillotine->setTexture("guillotine.png");
		addObject(guillotine, "guillotine_", 3, true);

		auto coffin = ObjectN::create();
		coffin->setArea(Rect(50, 330, 200, 150));
		coffin->setCursor(Cursor::INFO);
		coffin->setMsg("棺桶だ");
		addObject(coffin, "coffin", 1, true);

		auto drop = ObjectN::create();
		drop->setTexture("drop.png");
		drop->setPosition(Vec2(310, 480-65));
		auto act = Sequence::create(
			FadeIn::create(0.1f),
			EaseSineOut::create(MoveTo::create(0.5f, Vec2(310, 480 - 350))),
			FadeOut::create(0.1f),
			DelayTime::create(2.0f),
			MoveTo::create(0.0f, Vec2(310, 480 - 65)),
			NULL
		);
		drop->setAction(RepeatForever::create(act));
		addObject(drop, "drop", 2, true);

		addObject(createGhost(270, 210,"torture"), "ghost", 1, false);


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Torture::changedField() {
	}



	void Baking::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "剥製室";

		auto bg = Sprite::create("bakingroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle3 = ObjectN::create();
		aisle3->setArea(Rect(25, 440, 800, 40));
		aisle3->setCursor(Cursor::BACK);
		aisle3->setFieldChangeEvent("aisle3");
		addObject(aisle3, "aisle3", 1, true);


		auto skeleton = ObjectN::create();
		skeleton->setArea(Rect(680, 120, 70, 250));
		skeleton->setCursor(Cursor::INFO);
		skeleton->setTexture("skeleton.png");
		skeleton->setMsg("骸骨が飾られている");
		skeleton->setTouchEvent(CallFunc::create([this]() {
			if (mObjectList["skeleton"]->getState() == 1) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "これが業務日誌に書いてあった囚人かな");
				novel->addSentence(0, "バンダナ", "下の説明に「カギを飲み込んで死んだ囚人」って書いてあるな");
				novel->addSentence(0, "継", "この人が本当にカギを呑み込んだとすると…");
				novel->addSentence(0, "継", "まだ、喉に鍵が挟まってるかもしれないね。");
				novel->addSentence(0, "バンダナ", "この骸骨を調べるにしても結界が張られていて取り出せないな…");
				novel->addSentence(0, "継", "横にあるパネルを操作すれば開きそうだ、調べてみよう。");
				mObjectList["skeleton"]->setState(2);
				addChild(mObjectList["panel"], 2, "panel");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(skeleton, "skeleton", 2, true);

		auto glass = ObjectN::create();
		glass->setTexture("glass.png");
		addObject(glass, "glass", 3, true);

		auto panel = ObjectN::create();
		panel->setArea(Rect(650, 210, 20, 40));
		panel->setCursor(Cursor::INFO);
		panel->setFieldChangeEvent("panel");
		addObject(panel, "panel", 2, false);



		auto scene = ObjectN::create();
		scene->setTexture("chara/scene9.png");
		scene->setArea(Rect(0, 0, visibleSize.width, visibleSize.height));
		addObject(scene, "scene", 5, true);

		
		addObject(createGhost(40, 220, "baking"), "ghost", 1, false);


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Baking::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			setGetStill(18);
			AudioEngine::stopAll();
			runAction(Sequence::create(
				CallFunc::create([this] {
				mObjectList["scene"]->runAction(Sequence::create(
					DelayTime::create(1.0f),
					EaseSineOut::create(FadeOut::create(2.0f)),
					RemoveSelf::create(), NULL
				));
			}),
				DelayTime::create(2.0f),
				CallFunc::create([this] {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->addEvent(0, CallFunc::create([this]() {playSoundBS("BGM/underground.ogg", true); }));
				novel->addSentence(0, "継", "こ…この部屋は…");
				novel->addSentence(0, "バンダナ", "こいつら…死んでるのか…？");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "…ああ、どうやら…みんな剥製のようだね。");
				novel->addSentence(0, "バンダナ", "マジかよ…");
				novel->addSentence(0, "継", "ひどい…この人は目を抉られてる…");
				novel->addSentence(0, "バンダナ", "こっちは脚がないし、こっちは骸骨になってるな…");
				novel->addSentence(0, "継", "どうしてこんな部屋があるんだろう。");
				mObjectList["flag"]->setState(1);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}),
				NULL
				));
	
		}
		else if (mObjectList["flag"]->getState() == 1 && Control::me->getField("panel")->getObject("flag")->getState() == 2) {
			mObjectList["glass"]->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f),RemoveSelf::create()));
			
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "ケースが開いたみたいだ");
			novel->addSentence(0, "バンダナ", "これで骸骨が取り出せるな！");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "バンダナ", "よし、つぐるん！引っ張るぞ！");
			novel->addSentence(0, "継", "え…ど、どこを…？");
			novel->addSentence(0, "バンダナ", "どこって…首だよ。カギを飲み込んでいるかもしれないんだろ？");
			novel->addSentence(0, "継", "首を外すのか…仕方ない、やってみよう。");
			novel->addSentence(0, "バンダナ", "俺が頭を引っ張るから、つぐるんは肩を抑えていてくれ。");
			novel->addSentence(0, "継", "うん、わかった。");
			novel->setCharaR(0, "");
			novel->setCharaC(0, "chara/bandana1.png");
			novel->addEvent(0, CallFunc::create([this] (){
				mObjectList["skeleton"]->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
			}));
			novel->addSentence(0, "バンダナ", "しっかり持ったかー？いくぞー！");
			novel->addSentence(0, "継", "うん…！");
			novel->addSentence(0, "バンダナ", "ふん…っ！");
			novel->addSentence(0, "継", "うわぁぁぁぁ");
			novel->setCharaC(0, "");
			novel->setCharaL(0, "");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "どすんっ");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "だいぶ吹っ飛んだな…");
			novel->addSentence(0, "継", "いててて……ごめん…");
			novel->addSentence(0, "バンダナ", "肝心の骸骨は無傷か…何か別な方法を探すしかないな。");
			novel->addSentence(0, "継", "ごめん……");
			novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("skeleton", Director::getInstance()->getVisibleSize() / 2); }));
			novel->addSentence(0, "バンダナ", "これは俺が背負っていくか…よいしょっと");
			novel->addSentence(0, "継", "ありがとう…僕がいい方法を考えるよ。");

			mObjectList["flag"]->setState(2);

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}
	}

	void Panel::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "パネル（剥製室）";

		auto bg = Sprite::create("panel2.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto baking = ObjectN::create();
		baking->setArea(Rect(650, 430, 200, 50));
		baking->setCursor(Cursor::BACK);
		baking->setFieldChangeEvent("baking");
		addObject(baking, "baking", 1, true);

		ObjectN* circle;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				circle = ObjectN::create();
				circle->setCursor(Cursor::INFO);
				circle->setTexture("panel2_c.png");
				circle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				circle->setPosition(200 + 80 * i, visibleSize.height - (80 + 80 * j));
				circle->setArea(Rect(
					circle->getBoundingBox().getMinX(),
					visibleSize.height - circle->getBoundingBox().getMaxY(),
					circle->getContentSize().width,
					circle->getContentSize().height));
				addObject(circle, StringUtils::format("cirlce%d%d", i, j), 2, true);
			}
		}

		auto reset = ObjectN::create();
		reset->setArea(Rect(500, 375, 100, 45));
		reset->setCursor(Cursor::INFO);
		reset->setTouchEvent(CallFunc::create([this]() {
			//std::ofstream ofs("panel2.txt");
			//for (int i = 0; i < 4*5; i++) {
			//	ofs << "{";
			//	for (int j = 0; j < 4 * 5; j++) {
			//		ofs << mAdjacency[i][j] << ",";
			//	}
			//	ofs << "}," << std::endl;
			//}

			for (int i = 0; i < 4 * 5; i++) for (int j = 0; j < 4 * 5; j++) mAdjacency[i][j] = 0;
			pre[0] = pre[1] = -1;
			drawLine();
		}));
		addObject(reset, "reset", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);


		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) { return true; };
		listener->onTouchMoved = CC_CALLBACK_2(Panel::touchNode, this);
		listener->onTouchEnded = [this](Touch* touch, Event* event) { drawLine(); };
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
		auto layer = Layer::create();
		layer->setPosition(Vec2::ZERO);
		this->addChild(layer, 1, "llayer");

		// 初期化
		for (int i = 0; i < 4 * 5; i++) for (int j = 0; j < 4 * 5; j++) mAdjacency[i][j] = 0;
		pre[0] = pre[1] = -1;
	}

	void Panel::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "点を指でなぞっていけば線を引けるみたいだね");
			novel->addSentence(0, "バンダナ", "前に触れた点との間にしか線が引けないな…つまり一筆書きで線を引かないといけないってわけだ。");
			novel->addSentence(0, "継", "右にあるボタンで引いた線をすべて消してリセットできるみたいだ");
			mObjectList["flag"]->setState(1);

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}
	}

	void Panel::touchNode(Touch* touch, Event* event) {
		auto layer = getChildByName("llayer");
		
		// 触れている点を探す
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				auto node = getChildByName(StringUtils::format("cirlce%d%d", i, j));
				if (node->getBoundingBox().containsPoint(touch->getLocation())) {
					if (pre[0] == i && pre[1] == j) break;	// 同じ点は除外
					// 最初の点はpreを更新
					if (pre[0] < 0) {
						pre[0] = i; pre[1] = j;
						break;
					}

					int n = i * 5 + j, n_ = pre[0] * 5 + pre[1];
					if (!mAdjacency[n][n_]) {
						// 前の点と繋げる
						mAdjacency[n][n_] = true;
						mAdjacency[n_][n] = true;
						pre[0] = i; pre[1] = j;
					}
					break;
				}
			}
		}


		// 線更新
		drawLine();
		// 描画途中
		if (pre[0] > 0) {
			auto line = DrawNode::create();
			line->drawSegment(getChildByName(StringUtils::format("cirlce%d%d", pre[0], pre[1]))->getPosition(),
				touch->getLocation(),
				2.0f, Color4F::RED);
			layer->addChild(line);
		}

		// 判定
		bool correct[4 * 5][4 * 5] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
			{0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
			{0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
			{0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
		};
		bool judge = true;
		for (int i = 0; i < 4 * 5; i++) for (int j = 0; j < 4 * 5; j++) if (mAdjacency[i][j] != correct[i][j])
		{
			judge = false; break;
		}
		if (judge && mObjectList["flag"]->getState() != 2) {
			Control::me->showMsg("ロックが解除された");
			mObjectList["flag"]->setState(2);
		}
	}

	void Panel::drawLine() {
		int i, j, i_, j_;
		auto layer = getChildByName("llayer");
		layer->removeAllChildren();

		for (int n = 0; n < 4 * 5; n++) {
			i = n / 5; j = n % 5;
			// 繋がってる点を探す
			for (int a = n + 1; a < 4 * 5; a++) {
				if (mAdjacency[n][a]) {
					i_ = a / 5; j_ = a % 5;
					auto line = DrawNode::create();
					line->drawSegment(	getChildByName(StringUtils::format("cirlce%d%d", i, j))->getPosition(),
										getChildByName(StringUtils::format("cirlce%d%d", i_, j_))->getPosition(),
										2.0f, Color4F::RED);
					layer->addChild(line);
				}
			}
		}
	}
	
}