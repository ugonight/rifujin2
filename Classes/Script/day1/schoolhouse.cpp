#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void Corridor::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("corridor.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto remon = ObjectN::create();
		remon->setTexture("remon.png");
		remon->setArea(Rect(30, 110, 140, 370));
		remon->setCursor(Cursor::INFO);
		remon->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/remon1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬「うふふ、御機嫌よう」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(remon, "remon", 1, true);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(190, 420, 330, 60));
		entrance->setCursor(Cursor::BACK);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		auto classroom = ObjectN::create();
		classroom->setArea(Rect(420,120,90,360));
		classroom->setCursor(Cursor::INFO);
		classroom->setFieldChangeEvent("classroom");
		addObject(classroom, "classroom", 2, true);

		auto artroom = ObjectN::create();
		artroom->setArea(Rect(170, 180, 150, 150));
		artroom->setCursor(Cursor::FORWARD);
		artroom->setFieldChangeEvent("artroom");
		addObject(artroom, "artroom", 2, true);
	}

	void Corridor::changedField() {

	}

	void ClassRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("classroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ClassRoom::changedField() {

	}

	void ArtRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
				//novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「あ、マリアちゃんおはよー！」");
				novel->addSentence(0, "マリア「あ！寿甘ちゃんおはよー」");
				novel->addSentence(0, "寿甘「美術部の朝練？朝からおつかれー！」");
				novel->addSentence(0, "マリア「えへへ…ありがとー」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["maria"]->setState(1);
			}
			else {
				auto novel = Novel::create();
				//novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "マリア「おはよー」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(maria, "maria", 1, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::INFO);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}