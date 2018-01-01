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

		auto aisle4 = ObjectN::create();
		aisle4->setArea(Rect(260, 0, 150, 150));
		aisle4->setCursor(Cursor::FORWARD);
		aisle4->setFieldChangeEvent("aisle4");
		addObject(aisle4, "aisle4", 1, true);

		auto panel = ObjectN::create();
		panel->setArea(Rect(760, 330, 40, 70));
		panel->setCursor(Cursor::INFO);
		panel->setFieldChangeEvent("panel");
		addObject(panel, "panel", 1, true);

		auto lab = ObjectN::create();
		lab->setArea(Rect(690, 110, 65, 310));
		lab->setCursor(Cursor::ENTER);
		lab->setTouchEvent(CallFunc::create([this] () {
			if (Control::me->getField("panel")->getObject("flag")->getState() == 1) {
				Control::me->changeField("lab");
			}
			else {
				Control::me->showMsg("カギがかかっている");
			}
		}));
		addObject(lab, "lab", 1, true);

	}

	void Aisle2::changedField() {

	}

	void Panel::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "ドア横（研究室）";

		auto bg = Sprite::create("panel.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto aisle2 = ObjectN::create();
		aisle2->setArea(Rect(50, 430, 800, 50));
		aisle2->setCursor(Cursor::BACK);
		aisle2->setFieldChangeEvent("aisle2");
		addObject(aisle2, "aisle2", 1, true);

		// パネル
		Sprite* button;
		auto batchNode = SpriteBatchNode::create("piece.png");
		for (int i = 0;i < 5; i++) {
			for (int j = 0;j < 5; j++) {
				mOnOff[i][j] = 0;

				button = Sprite::createWithTexture(batchNode->getTexture());
				button->setPosition(Vec2(300 + i * 65, 348 - j * 65));
				addChild(button, 1, StringUtils::format("button%d%d", i, j));

				auto listener = EventListenerTouchOneByOne::create();
				listener->onTouchBegan = [this, i, j](Touch* touch, Event* event) {
					auto target = (Sprite*)event->getCurrentTarget();
					if (target->getBoundingBox().containsPoint(touch->getLocation()))
					{
						if (mObjectList["flag"]->getState() == 0) {
							// 切り替え
							if (target->getOpacity() == 0.0f) {
								mOnOff[i][j] = 0;
								target->runAction(FadeIn::create(0.1f));
								AudioEngine::play2d("SE/click.ogg");
							}
							else if (target->getOpacity() == 255.0f) {
								mOnOff[i][j] = 1;
								target->runAction(FadeOut::create(0.1f));
								AudioEngine::play2d("SE/click.ogg");
							}

							// 判定
							bool correct[5][5] = {
							{ 0,0,1,0,0 },
							{ 0,1,0,1,0 },
							{ 0,0,1,0,0 },
							{ 0,0,1,0,0 },
							{ 0,0,0,0,0 } };
							bool result = true;
							for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) if (mOnOff[j][i] != correct[i][j])result = false;
							if (result) {
								mObjectList["flag"]->setState(1);
								Control::me->showMsg("カギが開いたようだ");
							}
						}

						return true;
					}

					return false;
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, button);
			}
		}

		// メモ
		auto memo = ObjectN::create();
		memo->setArea(Rect(190, 45, 60, 375));
		memo->addCanUseItem("memo1");
		memo->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "memo1") {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "このメモ…もしかしてこうやって使うのかな");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->deleteItem("memo1");

					mObjectList["memo"]->setOpacity(0.0f);
					mObjectList["memo"]->setTexture("panel_memo.png");
					mObjectList["memo"]->runAction(FadeIn::create(0.5f));
				}));
				novel->addSentence(0, "継", "これで解けそうだね");
				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(memo, "memo", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Panel::changedField() {

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

		auto solt = ObjectN::create();
		solt->setArea(Rect(590, 200, 50, 40));
		solt->setTexture("solt.png");
		solt->setCursor(Cursor::NEW);
		solt->setItemGetEvent("solt");
		solt->setMsg("塩を手に入れた");
		addObject(solt, "solt", 1, true);

		auto hikido = ObjectN::create();
		hikido->setArea(Rect(510, 250, 180, 110));
		hikido->setTexture("hikido.png");
		hikido->setCursor(Cursor::INFO);
		hikido->addCanUseItem("nume");
		hikido->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["hikido"]->getState() == 0) {
				if (ItemMgr::sharedItem()->getSelectedItem() == "nume") {
					mObjectList["hikido"]->setState(1);
					Control::me->showMsg("ヌメヌメを塗って引き戸が滑るようにした");
					ItemMgr::sharedItem()->deleteItem("nume");
				}
				else {
					Control::me->showMsg("さび付いていて開かない");
				}
			}
			else if (mObjectList["hikido"]->getState() == 1) {
				mObjectList["hikido"]->runAction(MoveBy::create(0.5f, Vec2(-150, 0)));
				mObjectList["hikido"]->setState(2);
				mObjectList["hikido"]->setArea(Rect(510 - 150, 250, 180, 110));
			}
			else if (mObjectList["hikido"]->getState() == 2) {
				mObjectList["hikido"]->runAction(MoveBy::create(0.5f, Vec2(150, 0)));
				mObjectList["hikido"]->setState(1);
				mObjectList["hikido"]->setArea(Rect(510, 250, 180, 110));
			}
		}));
		addObject(hikido, "hikido", 3, true);

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
		// aisle2->setFieldChangeEvent("aisle2");
		aisle2->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["flag"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLACK);
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

		auto memo = ObjectN::create();
		memo->setTexture("memo1.png");
		memo->setArea(Rect(350, 400, 50, 30));
		memo->setCursor(Cursor::NEW);
		memo->setMsg("何かのメモを手に入れた");
		memo->setItemGetEvent("memo1");
		memo->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "さっきの奴が落としていったのかな");
			novel->addSentence(0, "継", "手がかりになるかもしれない、拾っておこう");
			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}));
		addObject(memo, "memo", 2, false);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Aisle3::changedField() {
	}

	void Torture::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "拷問室";

		mCount = -1; mFinish = false; mSE = 1;

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
			novel->addSentence(0, "継", "おえぇ…");
			novel->setFontColor(0, Color3B::BLACK);
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
				if (mSE == 2) {
					AudioEngine::stopAll();
					AudioEngine::play2d("SE/heart1.ogg", true);
					mSE = 1;
				}
			}
			else {
				if (mCount >= 0) mCount++;
				((Label*)hide->getChildByName("label"))->setTextColor(Color4B::RED);
				if (mSE == 1) {
					AudioEngine::stopAll();
					AudioEngine::play2d("SE/heart2.ogg", true);
					mSE = 2;
				}
			}

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
				novel->addEvent(0, CallFunc::create([this] { getChildByName("hideLayer")->removeChildByName("hide2"); AudioEngine::stopAll(); }));
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
		std::string str;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		str = "●をマウスカーソルで追っていこう";
#else
		str = "●を指で追っていこう";
#endif
		auto label = Label::createWithTTF(str, FONT_NAME, 30);
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
			act.pushBack(EaseSineInOut::create(MoveTo::create(2.0f, Vec2(cocos2d::random() % ((int)visibleSize.width - 200) + 100, cocos2d::random() % (int)(visibleSize.height - 100) + 50))));
		}
		act.pushBack(ScaleBy::create(1.0, 0.5));
		for (int i = 0; i < 10; i++) {
			act.pushBack(EaseSineInOut::create(MoveTo::create(2.0f, Vec2(cocos2d::random() % ((int)visibleSize.width - 200) + 100, cocos2d::random() % (int)(visibleSize.height - 100) + 50))));
		}
		// クリア後
		act.pushBack(CallFunc::create([this] {
			mFinish = true;
			AudioEngine::stopAll();

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
				mObjectList["shojo"]->setCursor(Cursor::INFO);
				mObjectList["coffin"]->setCursor(Cursor::INFO);

				auto aisle3 = Control::me->getField("aisle3");
				aisle3->getObject("flag")->setState(2);
				aisle3->getObject("aisle2")->setFieldChangeEvent("aisle2");
				aisle3->getObject("aisle2")->setMsg("");
				aisle3->getObject("torture")->setMsg("");
				aisle3->getObject("torture")->setFieldChangeEvent("torture");
				aisle3->getObject("torture")->setCursor(Cursor::ENTER);
				aisle3->getObject("baking")->setCursor(Cursor::ENTER);
				aisle3->addChild(aisle3->getObject("memo"), 1, "memo");
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
			mTouchPos = Point(-1, -1);
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, circle);

	}
}