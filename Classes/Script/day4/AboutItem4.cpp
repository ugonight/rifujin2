#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		// 硫酸
		auto ai = ObjectN::create();
		ai->setTexture("item/sulfate_a.png");
		ai->setMsg("硫酸だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "sulfate", 1, false);

		// トゲ
		ai = ObjectN::create();
		ai->setTexture("item/thorn_a.png");
		ai->setMsg("石のツタに付いていたトゲだ。とてもかたい。");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "thorn", 1, false);

		// メモ2
		ai = ObjectN::create();
		ai->setTexture("item/memo2_a.png");
		ai->setMsg("剥製室のケースを開けるためのメモらしい");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "memo2", 1, false);

		// 骸骨
		ai = ObjectN::create();
		ai->setTexture("item/skeleton_a.png");
		ai->setMsg("剥製室にあった骸骨だ。カギをのみこんでいるらしい。");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "skeleton", 1, false);

		// カギ
		ai = ObjectN::create();
		ai->setTexture("item/key_broken_a.png");
		ai->setMsg("牢屋のカギだ。真っ二つに切られてしまっている。");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "key_broken", 1, false);

		// カギ
		ai = ObjectN::create();
		ai->setTexture("item/key_a.png");
		ai->setMsg("牢屋のカギだ。");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "key", 1, false);

		// 記憶
		ai = ObjectN::create();
		ai->setTexture("item/memories_a.png");
		ai->setTouchEvent(CallFunc::create([this] {
			auto spr = ObjectN::create();
			spr->setTexture("chara/memory1.png");
			spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
			spr->setOpacity(0.0f);
			spr->setState(0);
			spr->runAction(FadeIn::create(0.5f));
			addChild(spr, 20, "memory");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				auto node = (ObjectN*)event->getCurrentTarget();
				if (node->getBoundingBox().containsPoint(touch->getLocation())) {
					switch (node->getState())
					{
					case 0: {
						node->runAction(Sequence::create(
							FadeOut::create(0.25),
							CallFunc::create([this] {
								((ObjectN*)getChildByName("memory"))->setState(1);
								((ObjectN*)getChildByName("memory"))->setTexture("chara/memory2.png");
								}),
							FadeIn::create(0.25),
									NULL));
						break;
					}
					case 1: {
						if (Control::me->getField("aisle4")->getObject("cape")->getState() >= 1) {
							node->runAction(Sequence::create(
								FadeOut::create(0.25),
								CallFunc::create([this] {
									((ObjectN*)getChildByName("memory"))->setState(2);
									((ObjectN*)getChildByName("memory"))->setTexture("chara/memory3.png");
									}),
								FadeIn::create(0.25),
										NULL));
							break;
						}
					}
					case 2: {
						node->runAction(Sequence::create(
							FadeOut::create(0.25),
							CallFunc::create([this] {
								((ObjectN*)getChildByName("memory"))->setState(3);
								((ObjectN*)getChildByName("memory"))->setTexture("chara/memory4.png");
								}),
							FadeIn::create(0.25),
									NULL));
						break;
					}
					case 3: {
						node->runAction(Sequence::create(
							FadeOut::create(0.5),
							RemoveSelf::create(),
							NULL));
						break;
					}
					default:
						break;
					}
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spr);
			}));
		ai->setArea(ai->getBoundingBox());
		ai->setMsg("寿甘から送られてきた事件現場の映像だ");
		addObject(ai, "memories", 1, false);

		// 寿甘の調査資料
		ai = ObjectN::create();
		ai->setTexture("item/suama_report_a.png");
		ai->setArea(ai->getBoundingBox());
		ai->setMsg("寿甘から送られてきた調査メモだ");
		ai->setTouchEvent(CallFunc::create([this] {
			auto layer = Layer::create();
			layer->setPosition(Vec2::ZERO);
			addChild(layer, 20, "slayer");
			auto spr = ObjectN::create();
			spr->setTexture("bg/black.png");
			spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
			spr->setOpacity(255.0f / 2.0f);
			spr->setState(0);
			layer->addChild(spr, 0, "black");
			auto label = Label::createWithTTF("", FONT_NAME, 24);
			label->setPosition(Director::getInstance()->getVisibleSize() / 2);
			label->setTextColor(Color4B::BLACK);
			label->enableOutline(Color4B::WHITE, 2);
			label->setString("宇沢\n"
				"　・二人のことは何も見ていない\n"
				"　・こいつと一緒に調査した\n"
				"檸檬\n"
				"　・何も知らない\n"
				"　・体育の時にボールを拾いに行ってくれた\n"
				"　・話した後すぐに帰ってしまった"
			);
			layer->addChild(label, 3, "label");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				return true;
			};
			listener->onTouchEnded = [this](Touch* touch, Event* event) {
				auto node = (ObjectN*)event->getCurrentTarget()->getChildByName("black");
				auto label = (Label*)event->getCurrentTarget()->getChildByName("label");
				switch (node->getState())
				{
				case 0: {
					label->setString("マリア\n"
						"　・二人のことは見ていない\n"
						"　・リアスが悲しそうな顔で何かを探していた\n"
						"恋巳\n"
						"　・教室に戻ってくるときにバンダナが校庭に出て行った\n"
						"　・その少し後に継が後を追って出てきた\n"
						"　・校門近くで校庭の上空をずっと見張っていたが、二人とも出てこなかった。\n"
					);
					node->setState(1);
					break;
				}
				case 1: {
					label->setString("裏庭の調査\n"
						"　・壁に大量の血痕が残っていて、足跡とともに校舎の奥へと続いていた。\n"
						"　・赤文字で「放課後、校舎裏でお待ちしております。」\n"
						"　　と書かれた手紙が落ちていた。\n"
						"　・クロユリに誘拐された時の記憶が残っていた。\n"
						"　・木のそばに釘が落ちていた。\n"
					);
					node->setState(2);
					break;
				}
				case 2: {
					label->setString("推理\n"
						"　・二人は誘拐された可能性が高い\n"
						"　・現場から消えた人形がある。\n"
						"　　「人形遣い」の特殊能力を使える生徒が人形を使って誘拐したのかも。\n"
						"　・写真にリアスの翼が映り込んでいた\n"
						"　・誘拐犯は裏庭の抜け道を通って逃げた可能性が高い。\n"
					);
					node->setState(3);
					break;
				}
				case 3: {
					removeChild(event->getCurrentTarget());

					break;
				}
				default:
					break;
				}
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
			}));
		addObject(ai, "suama", 1, false);

		// カギ（檸檬の部屋）
		ai = ObjectN::create();
		ai->setTexture("item/key_remon_a.png");
		ai->setMsg("何者かが持っていたどこかの部屋のカギだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "key_remon", 1, false);

		// ボウガン
		ai = ObjectN::create();
		ai->setTexture("item/bowgun_a.png");
		ai->setMsg("何者かが持っていたボウガンだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "bowgun", 1, false);

		// 藁人形
		ai = ObjectN::create();
		ai->setTexture("item/straw_doll_a.png");
		ai->setMsg("何者かが持っていた藁人形だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "doll", 1, false);

		// 日記
		std::string text[6] = { "　　　　　　　　　　　　　　　1/6 ページ\n"
			"私の将来の夢は研究者になること。\n"
"小さなころからずっとあこがれだった。\n"
"\n"
"いつもどおりパパの研究室で過ごす\n"
"今日もお気に入りの本のページをめくる\n"
"\n"
"現在は絶滅したと言われているドラゴン族\n"
"まだ見たことのない存在に思いを馳せた\n"
"彼らがこの理不尽で退屈な世界を変えてくれた" ,
"　　　　　　　　　　　　　　　2/6 ページ\n"
		"幼いころずっと読んでいた大好きな絵本\n"
"絵本の中のあの子が大好きでなんどもなんども読み返した\n"
"\n"
"大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー\n"
"私だけの物にしたいと思った",
"　　　　　　　　　　　　　　　3/6 ページ\n"
"いつしかあの子と仲良くなっていた\n"
"内気で恥ずかしがり屋のあの子の世話をする毎日\n"
"私が何を考えているのか知らないで、あの子は楽しそうだった\n"
"\n"
"あの子はいつも全身にきれいな宝石を身に着けていた\n"
"探知の能力で珍しい宝石を集めるのが得意だった\n"
"じゃあこれはどうかしらとママの作ったかんざしを渡してみた\n"
"あの子は「こんな素敵なもの見たことない！」とたいそう喜んでくれた\n"
"あれからあの子はかんざしを毎日着けてきてくれた",
"　　　　　　　　　　　　　　　4/6 ページ\n"
"ある日の体育の授業\n"
"あの子が男子とぶつかって転んでしまった\n"
"そいつに連れられて保健室にいたあの子の瞳は\n"
"今まで見たことのない恋をした眼をしていた\n"
"\n"
"あれからあの子はあいつを追いかけ回すようになった\n"
"私があげたかんざしもその日から着けてこなくなった\n\n"
"あいつのせいで\n"
"あいつのせいで、私の大切なあの子は…",
"　　　　　　　　　　　　　　　5/6 ページ\n"
"まずはあいつを手紙でおびき寄せる\n"
"その後、あの子が探知であいつを探しにきた所を狙って人形に二人を誘拐させる\n"
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
"　　　　　　　　　　　　　　　6/6 ページ\n"
"計画が狂った\n"
"あろうことか人形はあの子と間違って王子を誘拐してきてしまったようだ\n"
"あの優秀なメイドにでも気付かれたら私の計画は台無しだ\n"
"\n"
"…待てよ\n"
"この王子が死ねば国は大混乱に陥る\n"
"そこで私達が蘇れば国を手っ取り早く滅ぼすことができるのではないか…？\n"
"\n"
"ここまで来たらやるしかない\n"
		};
		std::function<int(int)> getNextPage = [this](int current) {
			auto userDef = UserDefault::getInstance();
			for (int i = current + 1; i <= 6; i++) {
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
			label->setString(text[getNextPage(0) - 1]);
			layer->addChild(label, 3, "label");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				return true;
			};
			listener->onTouchEnded = [this, text, getNextPage](Touch* touch, Event* event) {
				auto node = (ObjectN*)event->getCurrentTarget()->getChildByName("black");
				auto label = (Label*)event->getCurrentTarget()->getChildByName("label");

				if (node->getState() > 6 || node->getState() <= 1) {
					removeChild(event->getCurrentTarget());
				}
				else {
					label->setString(text[node->getState() - 1]);
					node->setState(getNextPage(node->getState()));
				}

				//switch (node->getState())
				//{
				//case 2: {
				//	label->setString(text[1]);
				//	node->setState(getNextPage(2));
				//	break;
				//}
				//case 3: {
				//	label->setString(text[2]);
				//	node->setState(getNextPage(3));
				//	break;
				//}
				//case 4: {
				//	label->setString(text[3]);
				//	node->setState(-1);
				//	break;
				//}
				//default:
				//	removeChild(event->getCurrentTarget());
				//	break;
				//}
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
			}));
		addObject(ai, "diary", 1, false);

		// 蝋燭
		ai = ObjectN::create();
		ai->setTexture("item/candle_a.png");
		ai->setMsg("ドクロ型のろうそくだ");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this]() {
			auto itemMgr = ItemMgr::sharedItem();
			if ((itemMgr->getGetItem("thorn") && itemMgr->getGetItem("bowgun") && itemMgr->getGetItem("doll"))
				&& (itemMgr->getSelectedItem() == "thorn" || itemMgr->getSelectedItem() == "bowgun" || itemMgr->getSelectedItem() == "doll")
				&& mObjectList["candle"]->getState() == 0) {

				auto novel = Novel::create();
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "火を起こすなら俺の出番だな？");
				novel->addSentence(0, "継", "うん、よろしく頼むよ。");
				novel->setCharaC(0, "chara/scene11.png");
				novel->addSentence(0, "バンダナ", "ボウガンの弓とこの石のトゲがあれば、あれができそうだな。火種はこの藁人形でいいか");
				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/remon1.png");
				novel->addSentence(0, "檸檬", "呪われるわよ…");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "よし、これで火が起こせたな。ロウソクに点けるぞ");
				mObjectList["candle"]->setState(1);
				mObjectList["candle"]->setMsg("ドクロ型のろうそくだ。火が点いている。");

				novel->setEndTask(0, CallFunc::create([this]() {
					auto light = Sprite::create("item/candle_light.png");
					light->setPosition(Director::getInstance()->getVisibleSize() / 2);
					light->setOpacity(0.0f);
					light->runAction(FadeIn::create(0.5f));
					light->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
					addChild(light, 3);
					}));
				addChild(novel, 10, "novel");
			}
			}));
		addObject(ai, "candle", 1, false);

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
		if (itemName == "candle") {
			addChild(mObjectList[itemName], 2, itemName);
			if (mObjectList["candle"]->getState() > 0) {
				auto light = Sprite::create("item/candle_light.png");
				light->setPosition(Director::getInstance()->getVisibleSize() / 2);
				light->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
				addChild(light, 3);
			}
		}
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}