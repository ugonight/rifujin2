#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"
#include "Sequence\Title.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day2 {
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
	}

	void Aisle2::changedField() {

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
		// aisle2->setFieldChangeEvent("aisle2");
		aisle2->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["flag"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setFontColor(0,Color3B::BLACK);
				novel->addSentence(0, "", "……コツコツ…");
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "！…誰か来る…");
				novel->addSentence(0, "継", "どこかに隠れよう");
				novel->setEndTask(0);
				addChild(novel, 10, "novel");

				mObjectList["flag"]->setState(1);
				mObjectList["aisle2"]->setFieldChangeEvent("");
				mObjectList["aisle2"]->setMsg("戻ってる場合ではない");
			}
		}));
		addObject(aisle2, "aisle2", 1, true);

		auto door = ObjectN::create();
		door->setArea(Rect(560, 160, 120, 200));
		door->setCursor(Cursor::ENTER);
		door->setMsg("…入りたくない");
		door->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["flag"]->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "う…");
				novel->addSentence(0, "継", "嫌な予感がするけど…ここに隠れよう");
				novel->addEvent(0, CallFunc::create([this] { Control::me->changeField("torture"); }));

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(door, "torture", 1, true);
		
		door = ObjectN::create();
		door->setArea(Rect(90, 160, 110, 300));
		door->setCursor(Cursor::ENTER);
		door->setMsg("鍵がかかっている");
		addObject(door, "baking", 1, true);


		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

	}

	void Aisle3::changedField() {
	}

	void Torture::initField(){ 
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "拷問室";

		mCount = -1; mFinish = false;

		auto bg = Sprite::create("torture.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		bg = Sprite::create("bg/black.png");
		bg->setPosition(visibleSize / 2);
		bg->setOpacity(200.f);
		addChild(bg, 5, "black");

		auto aisle3 = ObjectN::create();
		aisle3->setArea(Rect(550, 430, 120, 50));
		aisle3->setCursor(Cursor::BACK);
		aisle3->setMsg("戻っている場合ではない");
		//aisle3->setFieldChangeEvent("aisle3");
		addObject(aisle3, "aisle3", 1, true);

		auto shojo = ObjectN::create();
		shojo->setArea(Rect(540, 90, 120, 260));
		shojo->setCursor(Cursor::NEW);
		shojo->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["flag"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "人が入れそうなスペースがある");
				novel->addSentence(0, "継", "ここに入ろう");
				novel->addSentence(0, "継", "…！？");
				novel->addSentence(0, "継", "扉の内側に棘がついている…！");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "ガチャ…");
				novel->addSentence(0, "？？？", "まさか、自分から殺されに来るなんてね…");
				novel->addSentence(0, "", "ドンッ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "うわあああああああああああああああああ");

				novel->setEndTask(0);
				addChild(novel, 10, "novel_bad");
			}
		}));
		addObject(shojo, "shojo", 1, true);

		auto coffin = ObjectN::create();
		coffin->setArea(Rect(50, 330, 200, 150));
		coffin->setCursor(Cursor::NEW);
		coffin->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["flag"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "人が入れそうなスペースがある");
				novel->addSentence(0, "継", "ここに入ろう");
				novel->addSentence(0, "継", "これは…棺桶かな");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "ガチャ…");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "誰か入ってきたみたいだ…");
				novel->addSentence(0, "継", "部屋を出ていくまで音を立てないようにやり過ごそう");
				novel->addEvent(0, CallFunc::create([this] {
					auto black = Sprite::create("bg/black.png");
					black->setPosition(Director::getInstance()->getVisibleSize() / 2);
					black->setOpacity(0.0f);
					auto listener = EventListenerTouchOneByOne::create();
					listener->setSwallowTouches(true);
					listener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
					this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black);
					black->runAction(Sequence::create(FadeIn::create(1.0f), CallFunc::create(CC_CALLBACK_0(Torture::hide, this)), FadeOut::create(1.0f), NULL));
					addChild(black, 5, "black_");
				}));

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(coffin, "coffin", 1, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Torture::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "うっ…");
			novel->setFontColor(0,Color3B::BLACK);
			novel->addSentence(0, "", "部屋の中では、血生臭い臭いが辺り一面に立ち込めていた");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "くそっ…カギがかからない…");
			novel->addSentence(0, "継", "部屋のどこかに身を隠そう…");

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}
	}

	void Torture::updateField() {
		// BADEND
		Novel* novel = (Novel*)(this->getChildByName("novel_bad"));
		if (novel) {
			if (novel->getEndFlag()) {
				removeChild(novel);
				// BADEND2
				this->runAction(CallFunc::create([this]() {
					auto red = Sprite::create("bg/red.png");
					red->setOpacity(0.0f);
					red->setPosition(Director::getInstance()->getVisibleSize() / 2);
					red->runAction(Sequence::create(FadeIn::create(1.0f), FadeOut::create(1.0f), CallFunc::create([this] {
						auto novel = Novel::create();
						novel->setFontColor(0, Color3B::BLACK);
						novel->setBg(0, "chara/shojo.png");
						novel->addSentence(0, "", "BAD　END2「鉄の処女」");
						novel->addEvent(0, CallFunc::create([this] {
							Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
						}));

						novel->setEndTask(0);
						addChild(novel, 10, "novel");
					}), RemoveSelf::create(), NULL));
					addChild(red, 12, "red");
					auto listener = EventListenerTouchOneByOne::create();
					listener->setSwallowTouches(true);
					listener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
					this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, red);
				}));
			}
			else {
				Control::me->setCursor(Cursor::NOVEL);
			}
		}

		// かくれんぼゲーム
		auto hide = getChildByName("hideLayer");
		if (hide && !mFinish) {
			if (hide->getChildByName("circle")->getBoundingBox().containsPoint(mTouchPos)) {
				mCount = 0;
				((Label*)hide->getChildByName("label"))->setTextColor(Color4B::WHITE);
			}
			else {
				if (mCount >= 0) mCount++;
				((Label*)hide->getChildByName("label"))->setTextColor(Color4B::RED);
			}
			// ((Label*)hide->getChildByName("label"))->setString(StringUtils::toString(mCount));
			// BAD END3
			if (mCount > 100) {
				mCount = -1;
				hide->getChildByName("hide2")->stopAllActions();
				hide->getChildByName("circle")->stopAllActions();
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "？？？", "…");
				novel->addSentence(0, "？？？", "…誰かいるのかしら？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "あ…");
				novel->setFontColor(0, Color3B::BLACK);
				novel->setBg(0, "bg/black.png");
				novel->addEvent(0, CallFunc::create([this] { getChildByName("hideLayer")->removeChildByName("hide2"); }));
				novel->addSentence(0, "", "ガチャリ…");
				novel->setBg(0, "chara/bad3.png");
				novel->addSentence(0, "？？？", "…ふふふ");
				novel->addSentence(0, "？？？", "みーつけた");
				novel->addSentence(0, "", "BAD　END3「かくれんぼ失敗」");
				novel->addEvent(0, CallFunc::create([this] {
					Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
				}));

				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}
	}

	void Torture::hide() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto layer = Layer::create();
		layer->setPosition(Vec2::ZERO);
		layer->setCascadeOpacityEnabled(true);
		layer->setOpacity(0.0f);
		layer->runAction(FadeIn::create(1.0f));
		addChild(layer, 6, "hideLayer");

		// 背景
		auto bg = Sprite::create("hide3.png");
		bg->setPosition(visibleSize / 2);
		layer->addChild(bg, 0, "hide3");
		bg = Sprite::create("hide1.png");
		bg->setPosition(visibleSize / 2);
		layer->addChild(bg, 2, "hide1");
		bg = Sprite::create("hide2.png");
		bg->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
		bg->runAction(Spawn::createWithTwoActions(
			Sequence::create(EaseSineInOut::create(MoveBy::create(20.0f, Vec2(-visibleSize.width, 0))), FlipX::create(true), MoveBy::create(20.0f, Vec2(visibleSize.width + bg->getContentSize().width, 0)), NULL),
			Repeat::create(Sequence::create(MoveBy::create(1.0f, Vec2(0, 10)), MoveBy::create(1.0f, Vec2(0, -10)), NULL), 20)
		));
		layer->addChild(bg, 1, "hide2");
		auto label = Label::createWithTTF("●をカーソルで追っていこう", FONT_NAME, 30);
		label->setPosition(Vec2(427, 80));
		label->setColor(Color3B::WHITE);
		label->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL)));
		layer->addChild(label, 2, "label");

		// ●
		auto circle = Sprite::create("hide_c.png");
		circle->setPosition(visibleSize / 2);
		layer->addChild(circle, 3, "circle");
		cocos2d::Vector<cocos2d::FiniteTimeAction *> act;
		std::random_device rnd;
		act.pushBack(DelayTime::create(2.0));
		act.pushBack(CallFunc::create([this] { mCount = 0; }));
		for (int i = 0; i < 9; i++) {
			act.pushBack(EaseSineInOut::create(MoveTo::create(2.0f, Vec2(cocos2d::random() % (int)visibleSize.width, cocos2d::random() % (int)visibleSize.height))));
		}
		act.pushBack(ScaleBy::create(1.0, 0.5));
		for (int i = 0; i < 10; i++) {
			act.pushBack(EaseSineInOut::create(MoveTo::create(2.0f, Vec2(cocos2d::random() % (int)visibleSize.width, cocos2d::random() % (int)visibleSize.height))));
		}
		// クリア後
		act.pushBack(CallFunc::create([this] {
			mFinish = true;
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "…もう行ったかな");
			novel->addSentence(0, "継", "棺から出よう");
			novel->setBg(0, "bg/black.png");
			novel->addSentence(0, "継", "よいしょっ…と");
			novel->addEvent(0, CallFunc::create([this] { 
				removeChildByName("hideLayer");
				removeChildByName("black_");
			}));
			novel->setBg(0, "");
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "暗くて調べられないな…電気は点けられないかな");
			novel->addSentence(0, "継", "お、スイッチはこれかな");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "カチッ");
			novel->addEvent(0, CallFunc::create([this] {
				getChildByName("black")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create()));
				mObjectList["flag"]->setState(1);
				mObjectList["aisle3"]->setFieldChangeEvent("aisle3");
				mObjectList["aisle3"]->setMsg("");
				
				auto aisle3 = Control::me->getField("aisle3");
				aisle3->getObject("flag")->setState(2);
				aisle3->getObject("aisle2")->setFieldChangeEvent("aisle2");
				aisle3->getObject("aisle2")->setMsg("");
				aisle3->getObject("torture")->setMsg("");
				aisle3->getObject("torture")->setFieldChangeEvent("torture");
				aisle3->getObject("torture")->setCursor(Cursor::ENTER);
				aisle3->getObject("baking")->setCursor(Cursor::ENTER);
			}));
			novel->addSentence(0, "継", "これは…ここであったことはあまり想像したくないな…");

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}));
		circle->runAction(Sequence::create(act));
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			mTouchPos = touch->getLocation();
			return true; 
		};
		listener->onTouchMoved = [this](Touch* touch, Event* event) {
			mTouchPos = touch->getLocation();
		};
		listener->onTouchEnded = [this](Touch* touch, Event* event) {
			mTouchPos = Point(-1,-1);
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, circle);

	}
}