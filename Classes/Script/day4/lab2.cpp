#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"
#include "Sequence\Title.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

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
		aisle4->setArea(Rect(260, 0, 150, 150));
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
		door->setMsg("鍵がかかっている");
		addObject(door, "baking", 1, true);

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


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Torture::changedField() {
	}


}