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
						node->runAction(Sequence::create(
							FadeOut::create(0.25),
							CallFunc::create([this] {
							((ObjectN*)getChildByName("memory"))->setState(2);
							((ObjectN*)getChildByName("memory"))->setTexture("chara/memory4.png");
						}),
							FadeIn::create(0.25),
							NULL));
						break;
					}
					case 2: {
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
		/*if (itemName == "fak") {
			addChild(mObjectList["fak"], 1, "fak");
			if (mObjectList["fak_s"]->getState() == 0) {
				addChild(mObjectList["fak_s"], 2, "fak_s");
			}
		}
		else */{
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}