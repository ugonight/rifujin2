#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void Gate::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("gate.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto renji = ObjectN::create();
		renji->setTexture("renji.png");
		renji->setArea(Rect(50, 110, 120, 370));
		renji->setCursor(Cursor::INFO);
		renji->setTouchEvent(CallFunc::create([this] {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/renji1.png");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);	
				if (mObjectList["renji"]->getState() == 0) {
					novel->addSentence(0, "恋巳「御早う、諸君。」");
					novel->addSentence(0, "恋巳「俺は、神北　恋巳（かみきた　れんじ）。以後、お見知り置きを。」");
					novel->addSentence(0, "継「うん、おはよう。神北くん」");
					mObjectList["renji"]->setState(1);
				}
				else if (mObjectList["renji"]->getState() == 1) {
					novel->addSentence(0, "恋巳「御早う、諸君。」");
				}
				else if (mObjectList["renji"]->getState() == 2){
					novel->addSentence(0, "恋巳「ちょっと待ちたまえ、君たち。」");
					novel->addSentence(0, "継「ん？どうしたのかな、神北くん」");
					novel->addSentence(0, "恋巳「諸君らはオカルトに、興味はあるか？」");
					novel->addSentence(0, "継「オカルト…？うーん、特には」");
					novel->addSentence(0, "恋巳「オカルトはいいぞ…いつまでも俺の知的好奇心を刺激してくれる」");
					novel->addEvent(0, CallFunc::create([this] {
						ItemMgr::sharedItem()->getItem("magazine", Director::getInstance()->getVisibleSize() / 2);
						Control::me->showMsg("雑誌を手に入れた");
						mObjectList["renji"]->setState(1);
						mObjectList["renji"]->setCursor(Cursor::INFO);
					}));
					novel->addSentence(0, "恋巳「これをあげるから、諸君らも是非読んで興味を持ってくれると嬉しい。」");
					novel->addSentence(0, "継「ありがとう、神北くん。」");
				}
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
		}));
		//renji->addCanUseItem("clothes");
		addObject(renji, "renji", 1, true);

		auto cenotaph = ObjectN::create();
		cenotaph->setArea(Rect(700, 100, 100, 180));
		cenotaph->setCursor(Cursor::INFO);
		cenotaph->setMsg("初代学長の慰霊碑がある");
		cenotaph->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "paper") {
				if (mObjectList["cenotaph"]->getState() == 1) {
					auto novel = Novel::create();
					novel->setCharaL(0, "chara/suama1.png");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "寿甘「ねえ、つぐるん」");
					novel->setCharaR(0, "chara/tuguru1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継「ん？」");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "寿甘「確か、【ひゃっくりさん】って幽霊を呼び出す占いだったわよね」");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継「そうだね」");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "寿甘「学校の霊のことなら初代校長先生の霊なら何か知ってるかも」");
					novel->addSentence(0, "寿甘「ちょっと聞いてみるねー」");
					novel->addEvent(0, CallFunc::create([this] {callSpirit(false); }));
					novel->setCharaR(0, "");
					novel->addSentence(0, "寿甘「おつかれさまでーす」");
					novel->addSentence(0, "寿甘「最近、【ひゃっくりさん】で呼び出してきた子とかいませんでしたかー？」");
					novel->addEvent(0, CallFunc::create([this] {
						getChildByName("kokkuri")->getChildByName("spirit")->runAction(RepeatForever::create(Sequence::create(
							EaseSineInOut::create(MoveTo::create(2.0f, Vec2(45, 300))),	// 1
							DelayTime::create(1.0f),
							EaseSineInOut::create(MoveTo::create(2.0f, Vec2(315, 300))),	// 4
							DelayTime::create(1.0f),
							EaseSineInOut::create(MoveTo::create(2.0f, Vec2(690, 300))),	// 8
							DelayTime::create(1.0f),
							EaseSineInOut::create(MoveTo::create(2.0f, Vec2(315, 300))),	// 4
							DelayTime::create(3.0f),
							NULL)));
					}));
					novel->addSentence(0, "寿甘「ふむふむ…なるほど…」");
					novel->addSentence(0, "寿甘「何かメッセージを残していったみたいね」");
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
					mObjectList["cenotaph"]->setState(2);
				}
				else if (mObjectList["cenotaph"]->getState() == 2) {
					callSpirit(true);
				}
			}
		}));
		cenotaph->addCanUseItem("paper");
		addObject(cenotaph, "cenotaph", 3, true);

		auto paper = ObjectN::create();
		paper->setTexture("paper.png");
		paper->setArea(Rect(290, 420, 50, 50));
		paper->setCursor(Cursor::NEW);
		paper->setMsg("紙切れを手に入れた");
		paper->setItemGetEvent("paper");
		paper->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「これは何だろう」");
			novel->addSentence(0, "バンダナ「何かのメモかな、誰が落としたんだろう」");
			novel->addSentence(0, "継「会ったらちゃんと渡しておこう」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
		}));
		addObject(paper, "paper", 1, false);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(300, 140, 270, 100));
		entrance->setCursor(Cursor::FORWARD);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void Gate::changedField() {

	}

	void Gate::callSpirit(bool move) {
		auto layer = Layer::create();
		layer->setPosition(Vec2::ZERO);
		layer->setCascadeOpacityEnabled(true);
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch *touch, Event *event) { return true; };
		listener->onTouchEnded = [this](Touch *touch, Event *event) { getChildByName("kokkuri")->runAction(Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), NULL)); };
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);

		// Cocos2d-x v3.x
		auto size = Director::getInstance()->getVisibleSize();
		auto m_emitter = ParticleFire::createWithTotalParticles(600);
		m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("spark.png"));

		// v2.x及びv3.xで使用することができます
		m_emitter->setAutoRemoveOnFinish(true);
		m_emitter->setDuration(-1);
		//m_emitter->setGravity(Point(0, -240)); // v2.xでは CCPoint( 0, -240 )
		//m_emitter->setAngle(90);
		//m_emitter->setAngleVar(360);
		//m_emitter->setRadialAccel(50);
		//m_emitter->setRadialAccelVar(0);
		//m_emitter->setTangentialAccel(30);
		//m_emitter->setTangentialAccelVar(0);
		m_emitter->setSourcePosition(Vec2::ZERO);
		m_emitter->setPosition(Vec2(size / 2));
		m_emitter->setPosVar(Point(10, 0));
		m_emitter->setLife(1);
		m_emitter->setLifeVar(1);
		//m_emitter->setStartSpin(30);
		//m_emitter->setStartSpinVar(60);
		//m_emitter->setEndSpin(60);
		//m_emitter->setEndSpinVar(60);
		m_emitter->setStartColor(Color4F(0, 0, 255, 1));
		m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
		m_emitter->setEndColor(Color4F(100, 100, 255, 0));
		m_emitter->setEndColorVar(Color4F(100, 100, 100, 0));
		m_emitter->setStartSize(30.0f);
		m_emitter->setStartSizeVar(0);
		m_emitter->setEndSize(20.0f);
		m_emitter->setEndSizeVar(0);
		//m_emitter->setEmissionRate(100);
		BlendFunc func;
		func.src = GL_SRC_ALPHA;
		func.dst = GL_ONE;
		m_emitter->setBlendFunc(func);
		if (move) {
			m_emitter->runAction(RepeatForever::create(Sequence::create(
				EaseSineInOut::create(MoveTo::create(2.0f, Vec2(45, 300))),	// 1
				DelayTime::create(1.0f),
				EaseSineInOut::create(MoveTo::create(2.0f, Vec2(315, 300))),	// 4
				DelayTime::create(1.0f),
				EaseSineInOut::create(MoveTo::create(2.0f, Vec2(690, 300))),	// 8
				DelayTime::create(1.0f),
				EaseSineInOut::create(MoveTo::create(2.0f, Vec2(315, 300))),	// 4
				DelayTime::create(3.0f),
				NULL)));
		}
		layer->addChild(m_emitter, 10, "spirit");

		auto back = Sprite::create("black.png");
		back->setPosition(size / 2);
		layer->addChild(back, 0);

		layer->setOpacity(0.0f);
		layer->runAction(FadeIn::create(1.0f));
		addChild(layer, 5, "kokkuri");
	}

	void Entrance::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("entrance.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto fruit = ObjectN::create();
		fruit->setArea(Rect(270, 230, 100, 100));
		fruit->setCursor(Cursor::NEW);
		fruit->setItemGetEvent("fruit");
		fruit->setMsg("枯れた植物の実を手に入れた");
		addObject(fruit, "fruit", 3, true);

		auto ufo = ObjectN::create();
		ufo->setArea(Rect(650, 0, 100, 100));
		ufo->setTexture("ufo.png");
		ufo->setCursor(Cursor::INFO);
		ufo->setMsg("UFOが飛んでいる");
		ufo->addCanUseItem("camera");
		ufo->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "camera") {
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "継「UFOをカメラで撮影してみよう」");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->getItem("picture", Director::getInstance()->getVisibleSize() / 2);
					Control::me->showMsg("写真を手に入れた");
					removeChildByName("ufo");
				}));
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "パシャッ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「よし、写真が撮れたよ」");
				novel->setEndTask(0);
				addChild(novel, 10, "novel");
			}
		}));
		addObject(ufo, "ufo", 3, false);

		auto box = ObjectN::create();
		box->setArea(Rect(400, 380, 70, 70));
		box->setCursor(Cursor::INFO);
		box->setFieldChangeEvent("box");
		addObject(box, "box", 2, false);

		auto gate = ObjectN::create();
		gate->setArea(Rect(780, 0, 74, 480));
		gate->setCursor(Cursor::RIGHT);
		gate->setFieldChangeEvent("gate");
		addObject(gate, "gate", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(0, 0, 80, 480));
		corridor->setCursor(Cursor::LEFT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void Entrance::changedField() {

	}

	void Box::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("box.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		auto spr = Sprite::create("number.png");
		auto w = spr->getContentSize().width , h = spr->getContentSize().height;
		auto rect = Rect(0, 0, w / 9, h);
		ObjectN* number; EventListenerTouchOneByOne *listener;
		std::stringstream name;
		for (int i = 0; i < 4; i++) {
			number = ObjectN::create();
			number->setTexture("number.png");
			number->setTextureRect(rect);
			number->setPosition(250 + 110 * i, 335);
			number->setState(1);
			resetStr(name);
			name << "num" << i + 1;
			listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this, i, w, h](Touch *touch, Event *event) {
				if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
					auto num = (ObjectN*)event->getCurrentTarget();
					int next = num->getState() + 1;
					if (next > 9) next = 1;
					num->setTextureRect(Rect(w / 9 * (next - 1), 0, w / 9, h));
					num->setState(next);
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, number);
			addObject(number, name.str(), 2, true);
		}
		
		auto entrance = ObjectN::create();
		entrance->setArea(Rect(0, 430, 854, 50));
		entrance->setCursor(Cursor::BACK);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 1, true);
	}

	void Box::changedField(){
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「これがその時限爆弾かな」");
			novel->addSentence(0, "バンダナ「随分かわいらしい時限爆弾だな…」");
			novel->addSentence(0, "継「開けるには４けたのパスワードが必要みたいだね、どこかに手掛かりはないかな」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
			mObjectList["flag"]->setState(1);
		}
	}
}