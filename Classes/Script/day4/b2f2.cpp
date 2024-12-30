#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"
#include "ghost.h"

#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;

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

				mObjectList["library"]->setState(1);

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
		light->setPosition(Vec2(565, 480 - 125));
		light->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
		light->setAction(RepeatForever::create(Sequence::create(FadeOut::create(3.0f), FadeIn::create(3.0f), NULL)));
		addObject(light, "light", 2, true);

		auto door = ObjectN::create();
		door->setArea(Rect(755, 80, 75, 380));
		door->setCursor(Cursor::ENTER);
		// door->setMsg("カギがかかっている");
		door->addCanUseItem("key_remon");
		door->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "key_remon") {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "お、ここの扉のカギが開きそうだ");
				novel->addSentence(0, "継", "さっきの襲撃者はここに逃げ込もうとしていたのかな…？");

				novel->setEndTask(0, CallFunc::create([this]() {
					Control::me->changeField("rroom");
					ItemMgr::sharedItem()->deleteItem("key_remon");
					mObjectList["rroom"]->setFieldChangeEvent("rroom");
					mObjectList["rroom"]->setState(1);
					playSoundBS("SE/door.ogg");
					}));
				addChild(novel, 10, "novel");
			}
			else {
				if (mObjectList["rroom"]->getState() != 1)
					Control::me->showMsg("カギがかかっている");
			}
			}));
		addObject(door, "rroom", 1, true);

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
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
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
					ItemMgr::sharedItem()->getItem("thorn", Vec2(mObjectList["ivy"]->getArea().getMidX(), mObjectList["ivy"]->getArea().getMidY()));
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

		auto cape = ObjectN::create();
		cape->setArea(Rect(190, 400, 200, 80));
		cape->setTexture("cape.png");
		cape->setCursor(Cursor::INFO);
		cape->setMsg("マントが落ちている");
		cape->setTouchEvent(CallFunc::create([this]() {
			if (mObjectList["cape"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setCharaC(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "マントだけが残されている…身体は跡形もなく消えてしまっているみたいだ");
				novel->addSentence(0, "バンダナ", "これで襲われる心配はなくなったが…出口を聞き出すこともできなくなっちまったな…");
				novel->addSentence(0, "継", "いや、もしかしたら何か手掛かりが残されているかもしれない。調べてみよう。");
				novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("key_remon", Point(275, 30)); }));
				novel->addSentence(0, "バンダナ", "お、言ったそばからカギが出てきたぞ！");
				novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("bowgun", Point(275, 30)); }));
				novel->addSentence(0, "継", "これが僕らを襲ったボウガンかな");
				novel->addSentence(0, "バンダナ", "矢は残ってないか…");
				novel->addEvent(0, CallFunc::create([this]() {ItemMgr::sharedItem()->getItem("doll", Point(275, 30)); }));
				novel->addSentence(0, "継", "それと…これは藁人形かな？");
				novel->addSentence(0, "バンダナ", "誰かに恨みでも持ってたのか…？");
				// 写真を取得していたら
				if (ItemMgr::sharedItem()->getGetItem("memories")) {
					setGetStill(15);
					novel->setCharaL(0, "chara/scene10.png");
					novel->addSentence(0, "継", "あれ…花びらがついてる");
					novel->addSentence(0, "バンダナ", "どこかで見たことがあるような色だな…");
					novel->addSentence(0, "継", "…これ、クロユリの花びらじゃないかな");
					novel->addSentence(0, "継", "何か記憶しているかな…");
					novel->setCharaL(0, "");
					novel->setCharaR(0, "");
					novel->setCharaC(0, "");
					novel->setBg(0, "chara/memory3.png");
					novel->addSentence(0, "継", "…");
					novel->addSentence(0, "継", "これは…");
					novel->addSentence(0, "バンダナ", "つぐるんが俺を見つけて駆け寄ってるところみたいだな…");
					novel->addSentence(0, "継", "この直後に後ろから襲われたんだけど…ほかには誰も写っていないね。どうしてだろう。");
					novel->addSentence(0, "バンダナ", "もしかして、ここに写ってる藁人形…これと同じものなんじゃねえか…？");
					novel->addSentence(0, "継", "確かによく似ているね。だとすると僕を襲ったのは…");
					novel->addSentence(0, "継", "この記憶は寿甘からもらったものと一緒に持っておこう。");
					novel->setBg(0, "");
					novel->setCharaR(0, "chara/tuguru1.png");
					novel->setCharaC(0, "chara/bandana1.png");
				}
				novel->setCharaL(0, "chara/remon1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "はぁ…あなたたち、何か見つかったかしら…？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "あ、水無月さん…置いて行ってごめんね");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "まあいいわ、さっさと出口を探しましょう。");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "うん");
				mObjectList["cape"]->setState(1);

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
			}));
		addObject(cape, "cape", 2, false);


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle4::changedField() {
		if (Control::me->getField("aisle2")->getObject("flag")->getState() == 1 &&
			mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "…よしっ…つかまえた…！");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "バンダナ！あんまり無茶はするなよ…！");
			novel->addEvent(0, CallFunc::create([this]() {
				auto light = Sprite::create("cape_l.png");
				auto cape = mObjectList["cape"];
				light->setPosition(Director::getInstance()->getVisibleSize() / 2);
				light->setOpacity(0.0f);
				light->runAction(Sequence::create(
					EaseSineOut::create(FadeIn::create(1.5f)),
					EaseSineIn::create(FadeOut::create(1.5f)),
					RemoveSelf::create(), NULL
				));
				light->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA,backend::BlendFactor::ONE });
				cape->setPositionY(cape->getPositionY() + 200.0f);
				cape->setOpacity(0.0f);
				cape->runAction(Sequence::createWithTwoActions(
					FadeIn::create(1.5f),
					MoveTo::create(1.5f, Director::getInstance()->getVisibleSize() / 2)
				));

				addChild(light, 3, "cape_l");
				addChild(cape, 2, "cape");
				}));
			novel->setCharaR(0, "");
			novel->setCharaL(0, "");
			novel->addSentence(0, "バンダナ", "おらっ！観念しろっ……！？");
			novel->addSentence(0, "継", "！？");
			novel->addSentence(0, "バンダナ", "身体が…消えた…？");

			novel->setEndTask(0, CallFunc::create([this]() {
				AudioEngine::stopAll();
				playSoundBS("BGM/underground.ogg", true);
				}));
			this->addChild(novel, 10, "novel");

			mObjectList["flag"]->setState(1);
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
					mObjectList["book3"]->setState(2);
					break;
				case 2:
					novel->addSentence(0, "継", "…参考になりそうなところは大体読み終わったかな");
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

	void RRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "？？？の部屋";

		auto bg = Sprite::create("remon_room.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle4 = ObjectN::create();
		aisle4->setArea(Rect(0, 430, 854, 50));
		aisle4->setCursor(Cursor::BACK);
		aisle4->setFieldChangeEvent("aisle4");
		addObject(aisle4, "aisle4", 1, true);

		auto rias = ObjectN::create();
		rias->setArea(Rect(660, 190, 100, 210));
		rias->setCursor(Cursor::INFO);
		rias->setMsg("どこかで見たような服が飾ってある");
		addObject(rias, "rias", 2, true);

		auto diary = ObjectN::create();
		diary->setArea(Rect(530, 285, 70, 25));
		diary->setCursor(Cursor::INFO);
		diary->setMsg("日記が置いてある");
		diary->setTouchEvent(CallFunc::create([this]() {
			std::function<void()> func = [this]() {
				std::string text[] = {
"まずはあいつを手紙でおびき寄せる\n"
"その後、あの子が探知であいつを探しにきた所を狙って\n"
"人形に二人を誘拐させる\n"
"\n"
"ここに連れてきた二人を拷問器具で殺す\n"
"二人分の血液とあの子の首を手に入れて\n"
"私は生き返るのだ\n"
"\n"
"ドラゴン族のきれいなあの子の顔と\n"
"あの強靭な男の血液があれば\n"
"この国を焼き払う力を手に入れられるはずだ\n"
"\n"
"今こそ眠り続けていたこの積年の恨みを\n"
"解き放つ時なのだ",
"計画が狂った\n\n"
"あろうことか人形はあの子と間違って\n"
"王子を誘拐してきてしまったようだ\n"
"あの優秀なメイドにでも気付かれたら私の計画は台無しだ\n"
"\n"
"…待てよ\n"
"この王子が死ねば国は大混乱に陥る\n"
"そこで私達が蘇れば\n"
"国を手っ取り早く滅ぼすことができるのではないか…？\n"
"\n"
"ここまで来たらやるしかない\n"
				};
				mObjectList["diary"]->setState(1);

				auto back = Sprite::create("bg/book.png");
				back->setCascadeOpacityEnabled(true);
				back->setOpacity(0.0f);
				back->runAction(FadeIn::create(0.25f));
				back->setColor(Color3B(100, 100, 100));
				back->setPosition(Director::getInstance()->getVisibleSize() / 2.0);
				auto listener = EventListenerTouchOneByOne::create();
				listener->setSwallowTouches(true);
				listener->onTouchBegan = [this](Touch* touch, Event* event) {
					return true;
				};
				listener->onTouchEnded = [this, text](Touch* touch, Event* event) {
					auto state = mObjectList["diary"]->getState();
					auto back = getChildByName("layer_c");
					auto booktext = (Label*)back->getChildByName("book_text");
					switch (state)
					{
					case 1:
					{
						booktext->setString(text[1]);
						mObjectList["diary"]->setState(2);

						break;
					}
					case 2:
					{
						back->runAction(Sequence::createWithTwoActions(FadeOut::create(0.25f), RemoveSelf::create()));
						mObjectList["diary"]->setState(1);

						break;
					}
					default:
						break;
					}
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, back);
				addChild(back, 11, "layer_c");

				auto label = Label::createWithTTF(text[0], FONT_NAME, 24);
				label->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2.0));
				label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				label->setColor(Color3B::WHITE);
				label->setDimensions(700, 400);
				label->setAlignment(TextHAlignment::CENTER);
				back->addChild(label, 12, "book_text");
			};

			if (mObjectList["diary"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "日記が置いてあるね");
				novel->addSentence(0, "継", "読んでみよう");
				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/remon1.png");
				novel->addSentence(0, "檸檬", "少しは躊躇しなさいよ…女の子の日記なんだから");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "…でも、手掛かりになるかもしれないからね");

				novel->addEvent(0, CallFunc::create(func), true);

				novel->addSentence(0, "継", "僕たちをさらってきた犯人が書いたもので間違いなさそうだね");
				novel->setCharaL(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "なんだか相当恨まれてるみたいだが…お前何かしたのか？");
				novel->addSentence(0, "継", "気づかない所で誰かを犠牲にしてしまったりしてしまう立場なんだよ、王族というのは。");
				novel->addSentence(0, "バンダナ", "…わりぃ、野暮なこと聞いちまったな");
				novel->addSentence(0, "バンダナ", "何があったとしても、仲間の命を危険に晒すなんて真似は絶対に許せねえな！");

				auto userDef = UserDefault::getInstance();
				bool gotdiary = false;
				for (int i = 1; i <= 4; i++) {
					if (userDef->getBoolForKey(StringUtils::format("diary%d", i).c_str(), false)) {
						gotdiary = true; break;
					}
				}
				if (gotdiary) {
					novel->addSentence(0, "継", "よく見たらこの日記、ページを破った跡があるね。");
					novel->addSentence(0, "継", "今まで拾ってきた紙切れとぴったり合いそうだ。一緒に持っておこう。");
				}

				novel->setEndTask(0);
				addChild(novel, 10, "novel");


				userDef->setBoolForKey("diary5", true);
				userDef->setBoolForKey("diary6", true);
				userDef->flush();
			}
			else {
				func();
			}
			}));
		addObject(diary, "diary", 2, true);

		auto skull = ObjectN::create();
		skull->setArea(Rect(240, 240, 50, 65));
		skull->setCursor(Cursor::INFO);
		skull->setMsg("ドクロが置いてある");
		skull->addCanUseItem("candle");
		skull->setTouchEvent(CallFunc::create([this]() {
			if (mObjectList["skull"]->getState() < 2 &&
				ItemMgr::sharedItem()->getSelectedItem() == "candle" && Control::me->getField("AboutItem")->getObject("candle")->getState() == 1) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setCharaL(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "このドクロとこのろうそく、なんか似てるな。");
				novel->addSentence(0, "継", "ほんとだね");
				novel->addSentence(0, "継", "…ちょうどドクロ中の空洞にこのロウソクを置けそうだね。置いてみよう。");
				novel->addEvent(0, CallFunc::create([this]() {
					this->addChild(mObjectList["skull_light"], 3, "skull_light");
					mObjectList["skull_light"]->runObjectAction();
				}));
				novel->addSentence(0, "バンダナ", "うおっ！ドクロがカラフルに光り始めたぞ！");
				mObjectList["skull"]->setState(2);
				ItemMgr::sharedItem()->deleteItem("candle");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
			else if (mObjectList["skull"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "角の生えたドクロが置いてある");
				novel->addSentence(0, "継", "中が空洞になっている。なにか置けそうだね。");
				mObjectList["skull"]->setState(1);

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
			}));
		addObject(skull, "skull", 2, true);

		// 髑髏の光
		Vector<FiniteTimeAction*> actionList;
		actionList.pushBack(FadeIn::create(0.5f));
		actionList.pushBack(EaseOut::create(TintTo::create(1.0f, Color3B::MAGENTA), 1));
		actionList.pushBack(EaseOut::create(TintTo::create(2.0f, Color3B::YELLOW), 1));
		actionList.pushBack(EaseOut::create(TintTo::create(2.0f, Color3B::RED), 1));
		actionList.pushBack(EaseOut::create(TintTo::create(2.0f, Color3B::GREEN), 1));
		actionList.pushBack(EaseOut::create(TintTo::create(3.0f, Color3B::BLUE), 1));
		actionList.pushBack(FadeOut::create(0.5f));
		actionList.pushBack(TintTo::create(0.0f, Color3B::MAGENTA));
		actionList.pushBack(DelayTime::create(0.5f));

		skull = ObjectN::create();
		skull->setTexture("skull_light.png");
		skull->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
		skull->setAction(RepeatForever::create(Sequence::create(actionList)));
		skull->setOpacity(0.0f);
		addObject(skull, "skull_light", 3, false);

		auto book = ObjectN::create();
		book->setArea(Rect(55, 200, 20, 85));
		book->setCursor(Cursor::INFO);
		book->setMsg("絵本が置いてある");
		book->setTouchEvent(CallFunc::create([this]() {
			std::function<void()> func = [this]() {
				std::string text[] = {
					"昔々魔界王国に、ドラゴン族が住んでいる集落がありました。\n"
					"ドラゴン族には、特殊能力「探知」を持つものが多くいて、度々鉱山に宝石を採掘してきてはそれを売って生活していました。\n"
					"ドラゴン族は、その特徴的な角や翼から恐ろしい印象がありましたが、実際はとても温厚な種族でした。\n"
					"なんでも、ドラゴン族には古くから「決して怒りを感じてはならない」と言うしきたりがあったとか。\n\n"
					"そんなドラゴン族の集落に、ある男女がいました。\n"
					"その男女のドラゴン族は幼馴染で、女は男のことが大好きでした。\n"
					"しかしある日、集落で一番の好青年だった男は、集落に視察に来た王族の女に見惚れられ、城へ連れていかれました。\n"
					"それから暫く経ったある日、ドラゴン族の集落に男が結婚した旨の通達が来て、ドラゴン族の女は男への想いを諦められずも「あの人が幸せなら…」とその涙をのみました。\n",
					"更に数多の年月が経ったある日、集落に「男が死んだ」と言う噂が流れ始めました。\n"
					"いてもたってもいられなくなったドラゴン族の女は城へ向かいます。\n"
					"そこでは男の葬儀が行われていました。\n"
					"女は民衆を掻き分け、男の亡骸にすがり付いて泣き叫びます。\n"
					"遺体は酷く損傷しており、男の面影は見る影もありませんでした。\n"
					"泣き叫ぶドラゴン族の女を見下ろして、王族の女は言いました。\n"
					"「そいつは最後まで馬鹿な男だったよ。」\n"
					"「あたしが頼んだら危険な火山の洞窟に宝石を探しにいってくれてね、マグマに焼かれて死んだのさ。最初から利用されていただけとも知らないでさ。」\n"
					"高らかに笑う王族の女を見て、ドラゴン族の女は生まれて初めて心からの怒りを感じました。\n"
					"その時、ドラゴン族の女の中を何かが駆け巡ります。\n"
					"一族が代々封印してきた龍の魂が\n",
					"気が付いたら王族の女は黒焦げになっていました。\n"
					"ドラゴン族の女はすぐさま捕らえられ、断頭台に乗せられました。\n"
					"やがて、「ドラゴン族は人を殺すことができる危険な種族」と言う認識が国中に広まり、残りのドラゴン族も次々と捕らえられてしまいます。\n"
					"こうして、ドラゴン族は迫害され、その個体数は大きく減ってしまいました。\n"
					"かわいそうな首のないドラゴン族の女の魂は、今でもどこかで復讐の炎を燃やしているそうです。\n\n"
					"おしまい\n"
				};
				mObjectList["book"]->setState(1);
				
				auto novel = (Novel*)getChildByName("novel");
				if (novel) novel->stopMessage();

				auto back = Sprite::create("bg/book.png");
				back->setCascadeOpacityEnabled(true);
				back->setOpacity(0.0f);
				back->runAction(FadeIn::create(0.25f));
				back->setColor(Color3B(100, 100, 100));
				back->setPosition(Director::getInstance()->getVisibleSize() / 2.0);
				auto listener = EventListenerTouchOneByOne::create();
				listener->setSwallowTouches(true);
				listener->onTouchBegan = [this](Touch* touch, Event* event) {
					return true;
				};
				listener->onTouchEnded = [this, text, novel](Touch* touch, Event* event) {
					auto state = mObjectList["book"]->getState();
					auto back = getChildByName("layer_c");
					auto booktext = (Label*)back->getChildByName("book_text");
					switch (state)
					{
					case 1:
					{
						booktext->setString(text[1]);
						mObjectList["book"]->setState(2);

						break;
					}
					case 2:
					{
						booktext->setString(text[2]);
						mObjectList["book"]->setState(3);

						break;
					}
					case 3:
					{
						back->runAction(Sequence::createWithTwoActions(FadeOut::create(0.25f), RemoveSelf::create()));
						mObjectList["book"]->setState(1);
						if (novel) novel->resumeMessage();

						break;
					}
					default:
						break;
					}
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, back);
				addChild(back, 11, "layer_c");

				auto label = Label::createWithTTF(text[0], FONT_NAME, 24);
				label->setPosition(Vec2(Director::getInstance()->getVisibleSize() / 2.0));
				label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
				label->setColor(Color3B::WHITE);
				label->setDimensions(700, 400);
				label->setAlignment(TextHAlignment::CENTER);
				back->addChild(label, 12, "book_text");
			};

			if (mObjectList["book"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "ん？この本だけ背表紙の色が違うな…");
				novel->addSentence(0, "継", "読んでみよう");
				novel->addEvent(0, CallFunc::create(func), true);

				novel->setCharaL(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "なんというか…悲しい話だな…");
				novel->addSentence(0, "継", "首がないと言えば…剥製室に首のない女性が飾られていたね、何か関係があるのかな。");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
			else {
				func();
			}
			}));
		addObject(book, "book", 2, true);

		auto art = ObjectN::create();
		art->setTexture("remon_room_art.png");
		art->setArea(Rect(305, 120, 240, 140));
		art->setCursor(Cursor::INFO);
		art->setFieldChangeEvent("rart");
		addObject(art, "art", 2, true);

		auto chair = Sprite::create("remon_room_chair.png");
		chair->setPosition(visibleSize / 2);
		addChild(chair, 3, "chair");

		auto key = ObjectN::create();
		key->setArea(Rect(390, 190, 60, 40));
		key->setCursor(Cursor::INFO);
		key->setItemGetEvent("key2");
		key->setMsg("カギを手に入れた");
		addObject(key, "key2", 2, false);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void RRoom::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "ここは…誰かの私室っぽいな");
			novel->addSentence(0, "継", "ここの部屋を使ってる人は研究熱心みたいだね。");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaC(0, "chara/remon1.png");
			novel->addSentence(0, "檸檬", "……");
			mObjectList["flag"]->setState(1);
			setGetStill(19);

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}
		else if (Control::me->getField("rart")->getObject("flag")->getState() == 6 && mObjectList["flag"]->getState() == 1) {
			mObjectList["flag"]->setState(2);
			auto art = mObjectList["art"];
			art->runAction(EaseIn::create(MoveTo::create(1.0f, Vec2(art->getPositionX(), art->getPositionY() + 60)), 1.0f));
			art->setArea(Rect(art->getArea().origin.x, art->getArea().origin.y - 60, art->getArea().size.width, art->getArea().size.height));
			addChild(mObjectList["key2"], 2, "key2");

			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "絵が動くぞ！");
			novel->addSentence(0, "継", "…絵の後ろに何か隠されているみたいだね。");

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}
	}

	void RArt::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "絵画";

		auto bg = Sprite::create("remon_art.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto rroom = ObjectN::create();
		rroom->setArea(Rect(0, 430, 854, 50));
		rroom->setCursor(Cursor::BACK);
		rroom->setFieldChangeEvent("rroom");
		addObject(rroom, "rroom", 1, true);


		std::vector < std::tuple<Rect, std::string, Color3B, std::function<void()>>> skullList;
		skullList.push_back(std::make_tuple(Rect(75, 260, 90, 100), "skull_red", Color3B(255, 100, 100), [this]() { if (mObjectList["flag"]->getState() == 2) mObjectList["flag"]->setState(3); else mObjectList["flag"]->setState(0); }));
		skullList.push_back(std::make_tuple(Rect(230, 360, 90, 100), "skull_purple", Color3B(255, 100, 255), [this]() { mObjectList["flag"]->setState(1); }));
		skullList.push_back(std::make_tuple(Rect(520, 360, 90, 100), "skull_green", Color3B(100, 255, 100), [this]() { if (mObjectList["flag"]->getState() == 3) mObjectList["flag"]->setState(4); else mObjectList["flag"]->setState(0); }));
		skullList.push_back(std::make_tuple(Rect(650, 260, 90, 100), "skull_yellow", Color3B(255, 255, 100), [this]() { if (mObjectList["flag"]->getState() == 1) mObjectList["flag"]->setState(2); else mObjectList["flag"]->setState(0); }));
		skullList.push_back(std::make_tuple(Rect(410, 40, 90, 100), "skull_blue", Color3B(100, 100, 255), [this]() { if (mObjectList["flag"]->getState() == 4) mObjectList["flag"]->setState(5); else mObjectList["flag"]->setState(0); }));
		for (auto skullp : skullList)
		{
			auto skull = ObjectN::create();
			auto rect = std::get<0>(skullp);
			auto name = std::get<1>(skullp);
			auto color = std::get<2>(skullp);
			auto func = std::get<3>(skullp);
			skull->setTexture("art_light.png");
			skull->setArea(rect);
			skull->setPosition(rect.getMidX(), visibleSize.height - rect.getMidY());
			// skull->setAction(Sequence::createWithTwoActions(FadeIn::create(0.5), FadeOut::create(0.5)));
			skull->setOpacity(0.0f);
			skull->setColor(color);
			skull->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
			skull->setTouchEvent(CallFunc::create([this, name, func, skullList]() {
				mObjectList[name]->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5), FadeOut::create(0.5)));
				if (mObjectList["flag"]->getState() < 5)
					func();
				// 正解時
				if (mObjectList["flag"]->getState() == 5) {
					for (auto s : skullList)
					{
						mObjectList[std::get<1>(s)]->runAction(Sequence::create(DelayTime::create(1.5f), FadeIn::create(0.5), FadeOut::create(0.5), NULL));
					}
					Control::me->showMsg("どこかで物音がした");
					mObjectList["flag"]->setState(6);
				}
				}));
			addObject(skull, name, 2, true);
		}

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void RArt::changedField() {

	}
}