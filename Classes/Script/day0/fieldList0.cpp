#pragma  execution_character_set("utf-8")
//#include "System/control.h"

#include "Script\day0\fieldDef.h"
USING_NS_CC;

namespace day0 {
	Control* Esc::createControl() {
		return Esc::create();
	}

	void Esc::initField() {
		//フィールド一覧
		mFieldList["bedroom"] = BedRoom::create();
		mFieldList["closet"] = Closet::create();

		mFieldList["AboutItem"] = AboutItem::create();

		for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
			it->second->retain();
		}

		//最初に表示させるフィールド
		this->addChild(mFieldList["bedroom"], 0, "field");

		//アイテムの初期化
		auto item = (ItemMgr*)ItemMgr::create();
		item->initItem();
		this->addChild(item, 2, "item");

		// 遊び方
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto help = Sprite::create("help.png");
		help->setPosition(Vec2(origin.x + 30, origin.y + 30));
		this->addChild(help, 1, "help");
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
				auto explain = Sprite::create("explain.png");
				explain->setPosition(Director::getInstance()->getVisibleSize() / 2);
				this->addChild(explain, 5, "explain");
				auto listener2 = EventListenerTouchOneByOne::create();
				listener2->setSwallowTouches(true);
				listener2->onTouchBegan = [this](Touch* touch, Event* event) {
					return true;
				};
				listener2->onTouchEnded = [this](Touch* touch, Event* event) {
					removeChildByName("explain");
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, explain);
				return true;
			}
			return false;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, help);

		//チュートリアルではセーブしない
		//getChildByName("save")->setVisible(false);
		//getChildByName("save")->pause();

		mEndFlag = false;
	}

}