#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day2 {
	void Prison::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "牢屋";

		auto bg = Sprite::create("prison.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto bandana = ObjectN::create();
		bandana->setTexture("bandana_hurted.png");
		bandana->setArea(Rect(180, 130, 120, 260));
		bandana->setCursor(Cursor::INFO);
		bandana->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);

			novel->addSentence(0, "バンダナ", "俺はここで休んでるから、薬を探してきてくれ");
			novel->addSentence(0, "継", "わかった、なるべく急ぐよ");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		//renji->addCanUseItem("clothes");
		addObject(bandana, "bandana", 1, true);

		auto paper = ObjectN::create();
		paper->setArea(Rect(480, 270, 20, 30));
		paper->setCursor(Cursor::NEW);
		paper->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaL(0, "chara/tuguru1.png");

			if (mObjectList["paper"]->getState() == 0) {
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "壁のヒビの隙間に何か挟まっている…慎重に取り出してみよう");
				novel->addSentence(0, "継", "よいしょっ…と。これは紙切れかな、読んでみよう。");
			}
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "この手紙を読んでいる君へ");
			novel->addSentence(0, "", "毛布の下に通路へとつながる穴を掘った");
			novel->addSentence(0, "", "監視にバレないように魔法で入り口をロックしておいた");
			novel->addSentence(0, "", "私も逃げ切れるかはわからないが、君はどうか生き残って欲しい。健闘を祈る。");
			novel->addSentence(0, "", "ロック解除に必要な暗号:全ての方向の和を同一にせよ");
			if (mObjectList["paper"]->getState() == 0) {
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "なるほど。布団の下を調べてみよう");
				mObjectList["paper"]->setState(1);
				mObjectList["paper"]->setCursor(Cursor::INFO);
			}

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(paper, "paper", 1, true);

		auto blanket = ObjectN::create();
		blanket->setArea(Rect(550, 400, 120, 80));
		blanket->setCursor(Cursor::INFO);
		blanket->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["paper"]->getState() == 0) {
				Control::me->showMsg("粗末な毛布が敷いてある");
			}
			else if (mObjectList["paper"]->getState() == 1) {
				if (Control::me->getField("magic_team")->getObject("flag")->getState() == 2) {
					auto novel = Novel::create();
					novel->setCharaL(0, "chara/tuguru1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継", "地下へ降りてみよう");
					novel->setBg(0, "bg/black.png");
					novel->addSentence(0, "継", "狭いから這っていかないと…");
					novel->addSentence(0, "継", "…んしょ…んしょと……");
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "ガサッ…ガサッ…");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継", "？");
					novel->addSentence(0, "継", "バンダナ…？ついてきたのか…？");
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "", "ガサッ…ガサッ…");
					novel->addSentence(0, "", "…ガサガサガサガサッ！！！");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継", "！");
					novel->addEvent(0, CallFunc::create([this] {
						auto black = Sprite::create("bg/black.png");
						black->setPosition(Director::getInstance()->getVisibleSize() / 2);
						auto listener = EventListenerTouchOneByOne::create();
						listener->setSwallowTouches(true);
						listener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
						this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black);
						black->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create(CC_CALLBACK_0(Prison::attackZombie, this)), NULL));
						addChild(black, 5, "black");
					}));

					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
				else {
					Control::me->changeField("magic_team");
				}
			}
			else if (mObjectList["paper"]->getState() == 2) {
				Control::me->changeField("aisle");
			}
		}));
		addObject(blanket, "blanket", 1, true);

		{
			auto searchPoint = ObjectN::create();
			searchPoint->setArea(Rect(0, 100, 100, 270));
			searchPoint->setCursor(Cursor::INFO);
			searchPoint->setMsg("鎖が垂れ下がっている");
			addObject(searchPoint, "kusari", 1, true);
		}

		auto lizard = ObjectN::create();
		lizard->setTexture("lizard.png");
		lizard->setPosition(Vec2(620,480 + 100));
		lizard->setCursor(Cursor::INFO);
		auto act = Sequence::create(
			DelayTime::create(cocos2d::random() % 5 + 5),
			MoveBy::create(1.0f,Vec2(0,-200)),
			DelayTime::create(cocos2d::random() % 7 + 3),
			FlipY::create(true),
			MoveBy::create(1.0f, Vec2(0, 200)),
			FlipY::create(false),
			NULL);
		lizard->setAction(RepeatForever::create(act));
		lizard->setTouchEvent(CallFunc::create([this] {
			mObjectList["lizard"]->stopAllActions();
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "えいっ");
			novel->addSentence(0, "継", "捕まえたぞ！");
			novel->addSentence(0, "継", "…あ");
			novel->addSentence(0, "継", "尻尾を嚙み切って逃げちゃった…");
			novel->addSentence(0, "継", "注射器に入れておこう");
			novel->addEvent(0, CallFunc::create([this] {
				removeChildByName("lizard");
				Control::me->getField("AboutItem")->getObject("syringe_r")->setState(1);
			}));

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(lizard, "lizard", 3, false);
		lizard->setArea(lizard->getBoundingBox());

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		mHit = 0;

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}
	void Prison::updateField() {
		if (getChildByName("lizard")) {
			auto lizard = mObjectList["lizard"];
			lizard->setArea(Rect(lizard->getBoundingBox().getMinX(), 480 - lizard->getBoundingBox().getMaxY(), lizard->getBoundingBox().size.width, lizard->getBoundingBox().size.height));
		}
	}
	void Prison::changedField() {
		if (Control::me->getField("magic_team")->getObject("flag")->getState() == 2 &&
			mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "ロックが解除されたみたいだ");
			novel->addSentence(0, "継", "床下に降りてみよう");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
			mObjectList["flag"]->setState(1);
		}
	}

	void Prison::attackZombie() {
		AudioEngine::play2d("BGM/fear.ogg");
		auto layer = Layer::create();
		layer->setPosition(Vec2::ZERO);
		this->addChild(layer, 6, "layer_z");
		auto zombie = Sprite::create("chara/zombie.png");
		zombie->setPosition(Director::getInstance()->getVisibleSize() / 2);
		zombie->setOpacity(0.0f);
		zombie->runAction(FadeIn::create(0.1));
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			mHit++;
			if (mHit % 5 == 0) {
				event->getCurrentTarget()->runAction(Sequence::create(MoveBy::create(0.1, Vec2(50, 0)), MoveBy::create(0.1, Vec2(-100, 0)), MoveBy::create(0.1, Vec2(50, 0)), NULL));
				AudioEngine::play2d("SE/tm2_hit004.ogg");
			}
			if (mHit == 100) {
				getChildByName("layer_z")->setCascadeOpacityEnabled(true);
				getChildByName("layer_z")->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([this] {
					if (AudioEngine::getPlayingAudioCount())AudioEngine::stopAll();
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "？？？", "…イタイ…イタイ……");
					novel->addSentence(0, "？？？", "タスケテ……クレ………");
					novel->addSentence(0, "？？？", "…………………");
					novel->setCharaR(0, "chara/tuguru1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継", "はぁ…はぁ…");
					novel->addSentence(0, "継", "何とか振り切れたみたいだ…");
					novel->addSentence(0, "継", "…ん、行き止まり…？");
					novel->addSentence(0, "継", "あ、上が開くみたいだ");
					novel->setBg(0, "aisle.png");
					novel->addSentence(0, "継", "牢屋の外に出れたみたいだね");
					novel->addSentence(0, "継", "見付からないように行動しよう");
					novel->addEvent(0, CallFunc::create([this] {
						removeChildByName("black");
						Control::me->changeField("aisle");
						mObjectList["paper"]->setState(2);
					}));

					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}), RemoveSelf::create(), NULL));
			}

			return true;
		};
		listener->setSwallowTouches(true);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, zombie);
		layer->addChild(zombie, 1, "zombie");
		auto label = Label::createWithTTF("連打！！", FONT_NAME, 30);
		label->setPosition(Vec2(427, 80));
		label->setColor(Color3B::WHITE);
		label->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL)));
		layer->addChild(label, 2, "label");
	}

	void MagicTeam::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "毛布の下";

		auto bg = Sprite::create("magic_team.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		auto lightLayer = Layer::create();
		lightLayer->setPosition(Vec2::ZERO);
		addChild(lightLayer, 5, "l_layer");

		auto spr = Sprite::create("num2.png");
		auto w = spr->getContentSize().width, h = spr->getContentSize().height;
		//auto rect = Rect(0, 0, w / 9, h);
		Sprite* /*ObjectN**/ number; EventListenerTouchOneByOne *listener;
		std::stringstream name;
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				mNumber[j][i] = i + 1 + j * 3;
				number = Sprite::create();
				if (i + 1 + j * 3 != 9) {
					number->setTexture("num2.png");
					number->setTextureRect(Rect((i + j * 3) * (w / 8), 0, w / 8, h));
				}
				number->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				number->setPosition(205 + (w / 8) * i, visibleSize.height - h * j - 100);
				//number->setState(1);
				resetStr(name);
				name << "num" << i + 1 + j * 3;
				listener = EventListenerTouchOneByOne::create();
				listener->setSwallowTouches(true);
				listener->onTouchBegan = [this, i, j, w, h](Touch *touch, Event *event) {
					if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()) && mCanMove) {
						auto num = (Sprite*)event->getCurrentTarget();
						auto q = (Sprite*)getChildByName("num9");
						int numBack[3][3];

						int id = i + 1 + j * 3, pos[2] = { 0,0 }, posq[2] = { 0,0 };
						//検索
						for (int j_ = 0; j_ < 3; j_++) {
							for (int i_ = 0; i_ < 3; i_++) {
								if (mNumber[j_][i_] == id) { pos[0] = j_; pos[1] = i_; }
								if (mNumber[j_][i_] == 9) { posq[0] = j_; posq[1] = i_; }
								numBack[j_][i_] = mNumber[j_][i_];	//変更前の状態をバックアップ
							}
						}
						//入れ替え
						if (((abs(pos[0] - posq[0]) == 1) && pos[1] == posq[1]) ||
							((abs(pos[1] - posq[1]) == 1) && pos[0] == posq[0])) {
							mNumber[pos[0]][pos[1]] = 9;
							mNumber[posq[0]][posq[1]] = id;
							num->runAction(MoveTo::create(0.1, q->getPosition()));
							q->runAction(MoveTo::create(0.1, num->getPosition()));
							//this->runAction(Sequence::create(CallFunc::create([this] {mCanMove = false; }), DelayTime::create(0.1), CallFunc::create([this] {mCanMove = true; }), NULL));
						}
						//光らせる
						int match[8][3][2] = { {{0,0},{0,1},{0,2}},
											{{1,0},{1,1},{1,2}},
											{{2,0},{2,1},{2,2}},
											{{0,0},{1,0},{2,0}},
											{{0,1},{1,1},{2,1}},
											{{0,2},{1,2},{2,2}},
											{{0,0},{1,1},{2,2}},
											{{0,2},{1,1},{2,0}} };
						//初期化
						for (int l = 0; l < 8; l++)mMatch[l] = false;
						getChildByName("l_layer")->removeAllChildren();

						auto batchNode = SpriteBatchNode::create("light.png");
						for (int l = 0; l < 8; l++) {
							if (mNumber[match[l][0][0]][match[l][0][1]] + mNumber[match[l][1][0]][match[l][1][1]] + mNumber[match[l][2][0]][match[l][2][1]] == 15) {
								mMatch[l] = true;
								auto start = ((Sprite*)getChildByName(StringUtils::format("num%d", numBack[match[l][0][0]][match[l][0][1]])));
								auto end = ((Sprite*)getChildByName(StringUtils::format("num%d", numBack[match[l][2][0]][match[l][2][1]])));
								int x0 = start->getPositionX(), y0 = start->getPositionY();
								int x1 = end->getPositionX(), y1 = end->getPositionY();
								while (abs(x0 - x1) > 5 || abs(y0 - y1) > 5) {
									auto light = Sprite::createWithTexture(batchNode->getTexture());
									light->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
									light->setPosition(x0 + 50, y0 - 50);
									BlendFunc func;
									func.src = GL_SRC_ALPHA;
									func.dst = GL_ONE;
									light->setBlendFunc(func);
									light->setOpacity(0.0f);
									light->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1.0f), FadeIn::create(1.0f), FadeOut::create(1.f), NULL)));
									getChildByName("l_layer")->addChild(light, 5);
									if (x0 < x1) x0 += 2;
									if (x0 > x1) x0 -= 2;
									if (y0 < y1) y0 += 2;
									if (y0 > y1) y0 -= 2;
								}
							}
						}

						//判定
						bool result = true;
						for (int i_ = 0; i_ < 8; i_++)if (!mMatch[i_])result = false;
						if (result) {
							for (auto light : getChildByName("l_layer")->getChildren()) {
								light->stopAllActions();
								light->runAction(FadeIn::create(1.0f));
							}
							mCanMove = false;
							mObjectList["flag"]->setState(2);
						}

						return true;
					}
					return false;
				};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, number);
				//addObject(number, name.str(), 2, true);
				addChild(number, 2, name.str());
			}
		}

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(0, 430, 854, 50));
		entrance->setCursor(Cursor::BACK);
		entrance->setFieldChangeEvent("prison");
		addObject(entrance, "prison", 1, true);

		for (int i = 0; i < 8; i++)mMatch[i] = false;
		mCanMove = true;
	}

	void MagicTeam::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "これがその隠し通路の扉かな");
			novel->addSentence(0, "継", "このパズルを暗号に従って解けば開きそうだね");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
			mObjectList["flag"]->setState(1);
		}
		//リセット
		getChildByName("l_layer")->removeAllChildren();
		for (int j = 0; j < 3; j++) {
			for (int i = 0; i < 3; i++) {
				mNumber[j][i] = i + 1 + j * 3;
				getChildByName(StringUtils::format("num%d", i + 1 + j * 3))->setPosition(205 + 100 * i, Director::getInstance()->getVisibleSize().height - 100 * j - 100);
			}
		}
	}

	void Aisle::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "通路（牢屋）";

		auto bg = Sprite::create("aisle.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(460, 380, 160, 70));
		entrance->setCursor(Cursor::INFO);
		entrance->setFieldChangeEvent("prison");
		addObject(entrance, "prison", 1, true);

		auto b2f = ObjectN::create();
		b2f->setArea(Rect(100, 430, 320, 50));
		b2f->setCursor(Cursor::BACK);
		b2f->setFieldChangeEvent("aisle2");
		addObject(b2f, "b2f", 1, true);
	}

	void Aisle::changedField() {

	}
}