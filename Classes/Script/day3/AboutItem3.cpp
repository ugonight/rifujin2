#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	void AboutItem::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//オブジェクトを作っておく
		//基本的にアイテム名と同じ名前でオブジェクトを登録する。必ずaddChildをfalseにして登録。

		//紙切れ
		auto ai = ObjectN::create();
		ai->setTexture("item/paper_a.png");
		ai->setMsg("誰かが落としたメモだ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "paper", 1, false);

		// 笛
		ai = ObjectN::create();
		ai->setTexture("item/whistle_a.png");
		ai->setMsg("円筒の木片だ");
		ai->setArea(ai->getBoundingBox());
		ai->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "chisel") {
				Control::me->showMsg("彫刻刀で切れ込みを入れた");
				mObjectList["whistle_o1"]->setState(1);
				mObjectList["whistle_o1"]->setOpacity(0.0f);
				mObjectList["whistle_o1"]->runAction(FadeIn::create(0.5f));
				addChild(mObjectList["whistle_o1"], 2, "whistle_o1");
				ItemMgr::sharedItem()->deleteItem("chisel");
			}
		}));
		ai->addCanUseItem("chisel");
		addObject(ai, "whistle", 1, false);
		ai = ObjectN::create();
		ai->setTexture("item/whistle_o1.png");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "whistle_o1", 2, false);
		ai = ObjectN::create();
		ai->setTexture("item/whistle_o2.png");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "whistle_o2", 2, false);

		// 彫刻刀
		ai = ObjectN::create();
		ai->setTexture("item/chisel_a.png");
		ai->setMsg("彫刻刀だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "chisel", 1, false);

		// 簪
		ai = ObjectN::create();
		ai->setTexture("item/hatpin_a.png");
		ai->setMsg("壊れた誰かの簪だ");
		ai->setArea(ai->getBoundingBox());
		addObject(ai, "hatpin", 1, false);

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
		addObject(ai, "memories", 1, false);
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
		if (itemName == "whistle") {
			addChild(mObjectList["whistle"], 1, "whistle");
			if (mObjectList["whistle_o1"]->getState() == 1) {
				addChild(mObjectList["whistle_o1"], 2, "whistle_o1");
			}
			if (mObjectList["whistle_o2"]->getState() == 1) {
				addChild(mObjectList["whistle_o2"], 2, "whistle_o2");
			}
		}
		else {
			addChild(mObjectList[itemName], 2, itemName);	//基本的に登録名と同じオブジェクトを表示
		}
	}

}