#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

USING_NS_CC;

namespace day2 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		//メモ1
		auto ai = ObjectN::create();
		ai->setTexture("item/memo1_a.png");
		ai->setMsg("数字の書かれたメモだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "memo1", 1, false);

		// 塩
		ai = ObjectN::create();
		ai->setTexture("item/solt_a.png");
		ai->setMsg("塩だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "solt", 1, false);

		// ぬめぬめ
		ai = ObjectN::create();
		ai->setTexture("item/nume_a.png");
		ai->setMsg("ヒルが溶けて出てきたヌメヌメだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "nume", 1, false);

		// 救急箱
		ai = ObjectN::create();
		ai->setTexture("item/fak_a.png");
		ai->setMsg("包帯や消毒薬などが入っている");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "fak", 1, false);
		// 救急箱 - 注射
		ai = ObjectN::create();
		ai->setTexture("item/fak_s.png");
		//ai->setMsg("注射器を手に入れた");
		ai->setItemGetEvent("syringe");
		ai->setCursor(Cursor::NEW);
		ai->setArea(Rect(854 / 2 - 150 + 80, 480 / 2 - 150 + 145, 30, 25));
		ai->setTouchEvent(CallFunc::create([this] {
			mObjectList["fak_s"]->setState(1);  Control::me->showMsg("注射器を手に入れた");
			Control::me->getField("prison")->addChild(Control::me->getField("prison")->getObject("lizard"), 3, "lizard");
			}));
		addObject(ai, "fak_s", 2, false);

		// 注射器
		ai = ObjectN::create();
		ai->setTexture("item/syringe_a.png");
		ai->setMsg("注射器だ。解毒薬の材料を入れていこう。");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this]() {
			if (ItemMgr::sharedItem()->getSelectedItem() == "nume") {
				Control::me->showMsg("注射器にヒルの体液を入れた");
				mObjectList["syringe_h"]->setState(1);
				mObjectList["syringe_h"]->setOpacity(0.0f);
				mObjectList["syringe_h"]->runAction(FadeIn::create(1.0f));
				addChild(mObjectList["syringe_h"], 3, "syringe_h");
				ItemMgr::sharedItem()->deleteItem("nume");
			}
			else if (mObjectList["syringe_w"]->getState() == 1 && mObjectList["syringe_b"]->getState() == 1 && mObjectList["syringe_h"]->getState() == 1 && mObjectList["syringe_r"]->getState() == 1) {
				if (mObjectList["syringe"]->getState() == 0) {
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::BLUE);
					novel->setCharaR(0, "chara/tuguru1.png");
					novel->addSentence(0, "継", "これで解毒薬の完成だ");
					novel->addSentence(0, "継", "急いでバンダナの元へ向かおう");
					mObjectList["syringe"]->setState(1);
					Control::me->getField("prison")->getObject("bandana")->setCursor(Cursor::NEW);
					novel->setEndTask(0);
					addChild(novel, 10, "novel");
				}
				else {
					Control::me->showMsg("解毒薬が完成した");
				}
			}
			}));
		addObject(ai, "syringe", 5, false);
		ai = ObjectN::create();	// 水
		ai->setTexture("item/syringe_w.png");
		addObject(ai, "syringe_w", 1, false);
		ai = ObjectN::create(); // 血清
		ai->setTexture("item/syringe_b.png");
		addObject(ai, "syringe_b", 2, false);
		ai = ObjectN::create(); // 体液
		ai->setTexture("item/syringe_h.png");
		addObject(ai, "syringe_h", 3, false);
		ai = ObjectN::create(); // しっぽ
		ai->setTexture("item/syringe_r.png");
		addObject(ai, "syringe_r", 4, false);

		// 日記
		std::string text[4] = { "　　　　　　　　　　　　　　　1/4 ページ\n"
			"私の将来の夢は研究者になること。\n"
"小さなころからずっとあこがれだった。\n"
"\n"
"いつもどおりパパの研究室で過ごす\n"
"今日もお気に入りの本のページをめくる\n"
"\n"
"現在は絶滅したと言われているドラゴン族\n"
"まだ見たことのない存在に思いを馳せた\n"
"彼らがこの理不尽で退屈な世界を変えてくれた" ,
"　　　　　　　　　　　　　　　2/4 ページ\n"
		"幼いころずっと読んでいた大好きな絵本\n"
"絵本の中のあの子が大好きでなんどもなんども読み返した\n"
"\n"
"大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー\n"
"私だけの物にしたいと思った",
"　　　　　　　　　　　　　　　3/4 ページ\n"
"いつしかあの子と仲良くなっていた\n"
"内気で恥ずかしがり屋のあの子の世話をする毎日\n"
"私が何を考えているのか知らないで、あの子は楽しそうだった\n"
"\n"
"あの子はいつも全身にきれいな宝石を身に着けていた\n"
"探知の能力で珍しい宝石を集めるのが得意だった\n"
"じゃあこれはどうかしらとママの作ったかんざしを渡してみた\n"
"あの子は「こんな素敵なもの見たことない！」とたいそう喜んでくれた\n"
"あれからあの子はかんざしを毎日着けてきてくれた",
"　　　　　　　　　　　　　　　4/4 ページ\n"
"ある日の体育の授業\n"
"あの子が男子とぶつかって転んでしまった\n"
"そいつに連れられて保健室にいたあの子の瞳は\n"
"今まで見たことのない恋をした眼をしていた\n"
"\n"
"あれからあの子はあいつを追いかけ回すようになった\n"
"私があげたかんざしもその日から着けてこなくなった\n\n"
"あいつのせいで\n"
"あいつのせいで、私の大切なあの子は…"
		};
		std::function<int(int)> getNextPage = [this](int current) {
			auto userDef = UserDefault::getInstance();
			for (int i = current + 1; i <= 4; i++) {
				if (userDef->getBoolForKey(StringUtils::format("diary%d", i).c_str(), false)) {
					return i;
				}
			}
			return -1;
		};
		ai = ObjectN::create();
		ai->setTexture("item/diary_a.png");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this, text, getNextPage] {
			auto layer = Layer::create();
			layer->setPosition(Vec2::ZERO);
			addChild(layer, 20, "slayer");
			auto spr = ObjectN::create();
			spr->setTexture("bg/black.png");
			spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
			spr->setOpacity(255.0f / 2.0f);
			spr->setState(getNextPage(getNextPage(0)));
			layer->addChild(spr, 0, "black");
			auto label = Label::createWithTTF("", FONT_NAME, 24);
			label->setPosition(Director::getInstance()->getVisibleSize() / 2);
			label->setTextColor(Color4B::BLACK);
			label->enableOutline(Color4B::WHITE, 2);
			label->setAlignment(TextHAlignment::CENTER);
			label->setString(text[getNextPage(0)-1]);
			layer->addChild(label, 3, "label");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				return true;
			};
			listener->onTouchEnded = [this, text, getNextPage](Touch* touch, Event* event) {
				auto node = (ObjectN*)event->getCurrentTarget()->getChildByName("black");
				auto label = (Label*)event->getCurrentTarget()->getChildByName("label");
				switch (node->getState())
				{
				case 2: {
					label->setString(text[1]);
					node->setState(getNextPage(2));
					break;
				}
				case 3: {
					label->setString(text[2]);
					node->setState(getNextPage(3));
					break;
				}
				case 4: {
					label->setString(text[3]);
					node->setState(-1);
					break;
				}
				default:
					removeChild(event->getCurrentTarget());
					break;
				}
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
			}));
		addObject(ai, "diary", 1, false);
	}
	void AboutItem::changedField() {}
	void AboutItem::setAboutItem(std::string itemName) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		this->removeAllChildren();

		this->scheduleUpdate();
		for (auto it : this->getChildren()) {
			it->scheduleUpdate();
		}

		//ここにAboutItemの処理を書いていく
		//同時に二つ以上表示する場合はitemName == で書く
		if (itemName == "fak") {
			addChild(mObjectList["fak"], 1, "fak");
			if (mObjectList["fak_s"]->getState() == 0) {
				addChild(mObjectList["fak_s"], 2, "fak_s");
			}
		}
		else if (itemName == "syringe") {
			addChild(mObjectList["syringe"], 5, "syringe");
			if (mObjectList["syringe_w"]->getState() == 1) addChild(mObjectList["syringe_w"], 1, "syringe_w");
			if (mObjectList["syringe_b"]->getState() == 1) addChild(mObjectList["syringe_b"], 2, "syringe_b");
			if (mObjectList["syringe_h"]->getState() == 1) addChild(mObjectList["syringe_h"], 3, "syringe_h");
			if (mObjectList["syringe_r"]->getState() == 1) addChild(mObjectList["syringe_r"], 4, "syringe_r");
		}
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}