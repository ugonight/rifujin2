#include "Prologue.h"
#include "System/cursor.h"
#include "System/novel.h"
#include "Script\day0\fieldDef.h"
using namespace day0;

#pragma execution_character_set("utf-8")

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Scene* Prologue::createScene()
{
	auto scene = Scene::create();
	auto layer = Prologue::create();
	scene->addChild(layer);
	return scene;
}

bool Prologue::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto cursor = Cursor::create();
	cursor->setCursorNum(8);
	this->addChild(cursor, 1, "cursor");

	//BGM
	AudioEngine::pauseAll();

	//バックログを初期化
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.plist";
	FileUtils::getInstance()->removeFile(file);

	//スキップボタン
	//auto skip = Label::createWithTTF("スキップ", "fonts/APJapanesefontT.ttf", 24);
	//skip->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	//skip->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	//skip->setTextColor(Color4B::WHITE);
	//skip->enableOutline(Color4B::BLACK, 2);
	//addChild(skip, 3, "skip");
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [this](Touch* touch, Event* event) {
	//	auto target = (Label*)event->getCurrentTarget();
	//	Rect targetBox = target->getBoundingBox();
	//	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	//	if (targetBox.containsPoint(touchPoint))
	//	{
	//		removeChildByTag(0);
	//		return true;
	//	}
	//	return false;
	//};
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, skip);

	mFuncNum = 0;

	//シナリオ
	mFunc[0] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(0,Color3B::BLACK);
		novel->setBg(0, "bg/book.png");
		novel->addSentence(0,"幼いころずっと読んでいた大好きな絵本");
		novel->addSentence(0,"絵本の中のあの子が大好きでなんどもなんども読み返した");
		novel->addSentence(0,"大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー");
		novel->setBg(0, "");
		novel->addSentence(0,"私だけの物にしたいと思った");

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};


	mFunc[1] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "bg/town.png");
		novel->addSentence(0, "ここは人間も獣人も妖精だって、種族分け隔てなく平和に暮らす国、魔界王国。");
		novel->addSentence(0, "人々は幼い頃から基本的な魔法を学び、日常的に魔法を使って生活をしている。");
		novel->addSentence(0, "特殊能力という生まれつき変わった魔法が使える人もそこそこ多い、豊かな国だ");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaC(0,"chara/tuguru1.png");
		novel->addSentence(0, "継「ふあぁ…おはよう。セリーヌ」");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "そんな平和なこの国を治めているのがこの国の王子である僕、王国　継（おうこく　つぐる）");
		novel->addSentence(0, "便利であるが故に悪用されがちな魔法を王家に伝わるハンコで制御するのが僕の役目だ。");
		novel->addSentence(0, "とはいっても魔法も政治もまだまだ修行中の身、未だ王子と言う身分で大臣達の手伝いや会議での採択等をするのが僕の主な役割だ。");
		novel->addSentence(0, "最近やっと情勢が落ち着いてきたので、数ヵ月ぶりに朝から魔法学校へ行こうと思う。");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/celine1.png");
		novel->addSentence(0, "セリーヌ「おはようございます、今日は随分と早起きなのですね」");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "この目つきがするどい女性はメイドのセリーヌ。");
		novel->addSentence(0, "見た目はちょっと怖いけど、看護魔法から魔力貯蓄、更にはちょっとした読心術も使うことが出来る上級魔法使いだ。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ「…ですから怖くないって、いつも言っていますでしょう？」");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "…心を読まれてしまったみたいだ");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaR(0, "chara/bandana1.png");
		novel->addSentence(0, "バンダナ「おーいつぐるーん！迎えに来たぞー！」");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘「久しぶりー！」");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "城の前で叫んでいる二人は僕の友達のバイロン・ダイエナ、通称バンダナと立花　寿甘（たちばな　すあま）だ。");
		novel->addSentence(0, "王子である僕にも気さくに接してくれる、数少ない友人だ。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継「おはよう！まってて着替えるから！」");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "この2人と仲良くなれたのも、王子である僕が一般の学校に通えるくらいこの国が平和なおかげだと思うと僕は仕事を頑張れるのだ。");
		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};

	mFunc[2] = [this]() {
		removeChildByName("cursor");

		auto control = (Esc*)Esc::create();
		control->initField();	//必ず呼ぶ
		addChild(control, 1, "control");

		auto explain = Sprite::create("explain.png");
		explain->setPosition(Director::getInstance()->getVisibleSize() / 2);
		explain->setOpacity(0);
		explain->runAction(FadeIn::create(0.5f));
		this->addChild(explain, 5, "explain");
		auto listener2 = EventListenerTouchOneByOne::create();
		listener2->setSwallowTouches(true);
		listener2->onTouchBegan = [this](Touch* touch, Event* event) {
			removeChildByName("explain");
			return true;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, explain);

	};

	//mFunc[1] = [this]() {
	//	auto novel = Novel::create();

	//	novel->setFontColor(0,Color3B::BLACK);
	//	novel->addSentence(0,"zzz・・・");
	//	novel->setFontColor(0,Color3B::RED);
	//	novel->addSentence(0,"？？？「つぐる様…」");
	//	novel->setFontColor(0,Color3B::BLACK);
	//	novel->addSentence(0,"zzz・・・");
	//	novel->setFontColor(0,Color3B::RED);
	//	novel->addSentence(0,"？？？「継様…？」");
	//	novel->setFontColor(0,Color3B::BLACK);
	//	novel->addSentence(0,"・・・？");
	//	novel->addSentence(0,"…またこのパターンか");
	//	//addSitchEventは表示させたい文のタイミングの前に書く
	//	novel->addSwitchEvent(0, 1, "狸寝入りを試みる", 2, "再び眠りにつく");
	//	novel->addSentence(0,"僕は…");	
	//	novel->addSentence(1, "継「ぐー」");
	//	novel->addSentence(1, "僕は狸寝入りを試みた");
	//	novel->addSwitchEvent(1, 0);
	//	novel->addSentence(1, "？？？「ちょ…わざと過ぎ…っ」");
	//	novel->addSwitchEvent(2, 0);
	//	novel->addSentence(2, "再び眠りについた");
	//	novel->addSentence(0,"？？？「起きろーーーー！！！！！」");
	//	novel->setBg(0,"bg/white.png");
	//	novel->addSentence(0,"バシャッ");
	//	novel->addSentence(0,"継「うわっ、何するんだよセ…」");
	//	novel->setBg(0,"obj/classroom.png");
	//	novel->addSentence(0,"");

	//	//setEndTaskは最後にまとめて呼ぶこと
	//	novel->setEndTask(0);
	//	novel->setEndTask(1);
	//	novel->setEndTask(2);
	//	this->addChild(novel, 0, "novel");
	//};

	auto attention = Sprite::create("bg/attention.png");
	attention->setOpacity(0.0f);
	attention->setPosition(visibleSize / 2);
	attention->runAction(Sequence::create(DelayTime::create(2.0f), FadeIn::create(1.0f), DelayTime::create(4.0f), FadeOut::create(1.0f),
		CallFunc::create(Prologue::mFunc[0]), NULL));
	addChild(attention, 0, "attention");

	return true;
}

void Prologue::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag() && mFuncNum < 2 /* mFuncの数に応じて変える */) {
			mFunc[++mFuncNum]();
			this->removeChild(novel);
		}
	}
}
