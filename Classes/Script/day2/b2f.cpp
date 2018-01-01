#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day2 {
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

		auto hiru = ObjectN::create();
		hiru->setArea(Rect(90, 150, 110, 210));
		hiru->setTexture("hiru.png");
		hiru->setCursor(Cursor::INFO);
		hiru->setMsg("扉にヒルが張り付いている");
		hiru->setTouchEvent(CallFunc::create([this] (){
			if (ItemMgr::sharedItem()->getSelectedItem() == "solt") {
				Control::me->showMsg("ヒルに塩を振りかけた");
				mObjectList["hiru"]->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				ItemMgr::sharedItem()->deleteItem("solt");
				mObjectList["hiru"]->setState(1);
				AudioEngine::play2d("SE/hiru.ogg");
				mObjectList["flag"]->setState(1);
				addChild(mObjectList["library"], 1, "library");

				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "ちょっとかわいそうだな…ごめんよ");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "びちゃっ");
				novel->addEvent(0, CallFunc::create([this] {ItemMgr::sharedItem()->getItem("nume", Point(140, 250)); }));
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "うわっ");
				novel->addSentence(0, "継", "ヒルの体液が手についちゃった…べたべたするなあ…");

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		hiru->addCanUseItem("solt");
		addObject(hiru, "hiru", 2, true);

		auto library = ObjectN::create();
		library->setArea(Rect(90, 80, 110, 250));
		library->setCursor(Cursor::ENTER);
		library->setFieldChangeEvent("library");
		addObject(library, "library", 1, false);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle4::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaC(0, "chara/scene7.png");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "扉にナメクジのような生物が群がっているのが見える");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "これは…ヒルかな");
			novel->addSentence(0, "継", "近づくと危ないな、血を吸われるかもしれない");
			mObjectList["flag"]->setState(1);

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
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

	}

	void Library::changedField() {
	}
}