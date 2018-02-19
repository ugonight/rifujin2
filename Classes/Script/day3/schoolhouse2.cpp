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
		artroom->setArea(Rect(90, 150, 170, 200));
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

			}
		}));
		addObject(usawa, "usawa", 1, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);


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

			}
		}));
		addObject(maria, "maria", 1, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::ENTER);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}