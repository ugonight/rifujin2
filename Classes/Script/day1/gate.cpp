#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

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
					novel->setFontColor(0, Color3B::BLACK);
					novel->addSentence(0, "寿甘は幽霊とも会話できる特殊能力を持っているのだ");
					novel->setFontColor(0, Color3B::RED);
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
		//cenotaph->addCanUseItem("paper");
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
		if (Control::me->getField("box")->getObject("flag")->getState() == 2) {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継「よし、開いたみたいだ」");
			novel->addSentence(0, "継「中身を確認してみよう」");
			novel->setCharaL(0, "");
			novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll();}));
			novel->setBg(0, "chara/scene5.png");
			novel->addSentence(0, "継「これは…」");
			novel->addSentence(0, "バンダナ「げ…俺の名前を書きなぐったノートと、俺の写真の山…よく撮れてるなぁ」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘「感心してる場合！？…盗撮よ？盗撮！」");
			novel->addSentence(0, "寿甘「このノートだって何かのおまじないなのよ、きっと…あんたかなり執着されてるわよ」");
			novel->setBg(0, "");
			novel->setCharaL(0, "chara/suama1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "寿甘「…これ、もしかしてあの子が…」");
			novel->setCharaC(0, "chara/rias1.png");
			novel->addSentence(0, "リアス「あの…」");
			novel->addSentence(0, "寿甘「あ…」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「ええと…」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「…うわぁ…ひどいですね、これ…いったい誰がこんなことを…」");
			novel->addSentence(0, "リアス「も、もしかして宇沢さんですかね、彼女、いつも写真撮ってますし…」");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「！」");
			novel->addSentence(0, "継「それは違うと思うよ」");
			novel->addSentence(0, "リアス「ど、どうしてですか」");
			novel->addSentence(0, "継「確か…僕たちが写真を宇沢さんに見せた時…」");
			novel->addSwitchEvent(0, 1, "オカルトは嫌い", 2, "バンダナが好き");
			novel->addSentence(0, "継「彼女はこう言っていたはずだ」");

			novel->addSentence(1, "継「そう、彼女はオカルトが嫌いだったはずだ」");
			novel->addSwitchEvent(1, 0);
			novel->setFontColor(1, Color3B::RED);
			novel->addSentence(1, "リアス「そ、それがなんだって言うのよ…！」");

			novel->addSentence(2, "バンダナ「あいつがそんなこと言ってたのか…」");
			novel->addSentence(2, "継「え！…あ、違うね」");
			novel->addSentence(2, "継「もう一度考え直そう」");
			novel->setJump(2, 0, 16);

			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「オカルト嫌いの人が、こんなおまじないなんかに頼るかな」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「うぅ…」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「それにこの箱の存在を教えてくれたのも宇沢さんだ。わざわざ見つからないように隠していたものを、自分から明かすとは考えにくい」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「わからないよ…？もしかしたらわざと探させて想いを伝えたかったのかもしれないし…」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「それに、宇沢さんよりもっと怪しい人がいるんだ」");
			novel->addSwitchEvent(0, 3, "神北恋巳", 4, "リアス・アレキサンドライト");
			novel->addSentence(0, "継「その人物は…」");

			novel->addSentence(3, "バンダナ「神北が俺のことを…？」");
			novel->setCharaR(3, "chara/suama1.png");
			novel->setFontColor(3, Color3B::RED);
			novel->addSentence(3, "寿甘「いいぞもっとやれ」");
			novel->setFontColor(3, Color3B::BLUE);
			novel->addSentence(3, "継「うん、違うね」");
			novel->setJump(3, 0, 22);

			novel->addSentence(4, "継「リアス、君だ」");
			novel->setFontColor(4, Color3B::RED);
			novel->addSentence(4, "リアス「ひぃぃ…」");
			novel->addSwitchEvent(4, 0);
			novel->addSentence(4, "リアス「な、なにを根拠に…」");

			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「まず、この箱の中にあるものについて見てみよう」");
			novel->setCharaR(0, "");
			novel->setCharaC(0, "");
			novel->setCharaL(0, "");
			novel->setBg(0, "chara/scene5.png");
			novel->addSwitchEvent(0, 5, "写真", 6, "文字のインク", 7, "書いてある名前");
			novel->addSentence(0, "継「この中でリアスちゃんを連想できるものは…」");

			novel->addSentence(5, "バンダナ「俺の写真がどうかしたか？」");
			novel->addSentence(5, "継「いやぁ、よく撮れてるなと思って」");
			novel->setFontColor(5, Color3B::RED);
			novel->addSentence(5, "リアス「いやぁ、それほどでも～…」");
			novel->setFontColor(5, Color3B::BLUE);
			novel->addSentence(5, "継「ん？」");
			novel->setFontColor(5, Color3B::RED);
			novel->addSentence(5, "リアス「はぅっ…なんでもないです…」");
			novel->setFontColor(5, Color3B::BLUE);
			novel->setJump(5, 0, 24);

			novel->addSentence(6, "継「こんなどす黒い赤色のインクなんてそうそうないだろう…きっと血を使ったに違いない」");
			novel->addSentence(6, "継「血液検査をすれば、きっと君の君の血液型と一致するはずだ…！」");
			novel->setFontColor(6, Color3B::RED);
			novel->addSentence(6, "リアス「私でもそこまではしないわよ…」");
			novel->setFontColor(6, Color3B::BLUE);
			novel->setJump(6, 0, 24);

			novel->addSentence(7, "継「”バンダナ様”なんて呼んでいるのは君くらいだよ、リアス」");
			novel->setFontColor(7, Color3B::RED);
			novel->addSwitchEvent(7, 0);
			novel->addSentence(7, "リアス「うぐっ…」");

			novel->setBg(0, "");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaC(0, "chara/rias1.png");
			novel->addSentence(0, "リアス「でもでも！！もしかしたら…もしかしたら！！陰でそう呼んでる人もいるかもしれないじゃない！！」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「お前以外にいたかなぁ…そんなやつ」");
			novel->addSentence(0, "継「根拠はそれだけじゃないよ。この箱を開けるまでの経緯を振り返ってみよう」");
			novel->addSentence(0, "継「僕たちは、このメモを拾って、それをヒントにこの箱を開けた。つまり、このメモの持ち主が箱の持ち主と一致する可能性が高いということだ。」");
			novel->addSwitchEvent(0, 8, "水無月　檸檬", 9, "マリア・ミルフィーユ");
			novel->addSentence(0, "継「このメモについて、ある人が証言してくれたよ。それは…」");

			novel->addSentence(8, "継「君は水無月さんから【ひゃっくり】さんのやり方を教えてもらっていた」");
			novel->addSentence(8, "継「はっきりとこのメモは君のものだとは言わなかったけど、少なくとも君はこのメモをどうやって使うかはわかっていたことがわかる」");
			novel->setFontColor(8, Color3B::RED);
			novel->addSwitchEvent(8, 0);
			novel->addSentence(8, "リアス「うぅ…」");

			novel->setCharaR(9, "chara/suama1.png");
			novel->setFontColor(9, Color3B::RED);
			novel->addSentence(9, "寿甘「マリアちゃんそんなこと言ってたっけなー…？」");
			novel->setFontColor(9, Color3B::BLUE);
			novel->addSentence(9, "継「言ってなかったね」");
			novel->setJump(9, 0, 30);

			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「これが僕の推理だ」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「…ふふふ、ご名答。そうよ、私が全部やったの。隠し撮りも、このおまじないも」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「知ってた」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「今日もいつも通り、私の自慢の特殊能力の探知でバンダナ様をストーキングしてたの。その途中でメモを無くしちゃってね。」");
			novel->addSentence(0, "リアス「あわてて探知でメモの在処を探してたら、先にあなた達に拾われちゃって、どうやって取り返すか悩んでるうちに箱まで開けられちゃって…」");
			novel->addSentence(0, "リアス「あはは…私、ものすごく惨め。好きな人の目の前で…こんな形でバラされて…」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「…ごめん、そんなつもりじゃなかったんだ」");
			novel->addSentence(0, "バンダナ「こいつ生真面目な性格だからな…悪気はないんだ、許してやってくれ」");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘「ちょっと待って、なんでつぐるんが悪いみたいな流れになってんの。」");
			novel->addSentence(0, "寿甘「この子、あんたのこと付け回して、こんな事してたのよ！？」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「いや、頼むからそっとしといてやれよ…」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「…許さない……許さないゆるさないユルサナイ……！！！」");
			novel->addSentence(0, "リアス「こうなったら力づくであなた達からバンダナ様を奪い取って見せる…」");
			novel->addSentence(0, "リアス「バンダナ様は私のもの…あなたがどこでなにしているか全部知ってる…私は…絶対あなたを逃がさない…」");
			novel->addSentence(0, "リアス「うふふふふ…えへへへ…あーっはっはっは！！！！」");
			novel->setCharaC(0, "");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「逃げていったぞ」");
			novel->addSentence(0, "バンダナ「めんどくさいことになったな…」");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継「とりあえず宇沢さんに箱のことを伝えに行こう」");
			novel->addEvent(0, CallFunc::create([this] {
				Control::me->getField("box")->getObject("flag")->setState(3);
			}));

			novel->setEndTask(-1);
			addChild(novel, 10, "novel");
		}
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

		auto ok = ObjectN::create();
		ok->setArea(Rect(330, 280, 200, 40));
		ok->setCursor(Cursor::INFO);
		ok->setTouchEvent(CallFunc::create([this]() {
			if (mObjectList["num1"]->getState() == 1 &&
				mObjectList["num2"]->getState() == 4 && 
				mObjectList["num3"]->getState() == 8 &&
				mObjectList["num4"]->getState() == 4) {
				mObjectList["flag"]->setState(2);
				Control::me->changeField("entrance");
			}
			else if(mObjectList["flag"]->getState() == 3) {
				Control::me->showMsg("もう開ける必要はない");
			}
			else {
				Control::me->showMsg("パスワードが間違っているようだ。");
			}
		}));
		addObject(ok, "ok", 2, true);

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