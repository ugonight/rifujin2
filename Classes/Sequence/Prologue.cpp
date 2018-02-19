#pragma execution_character_set("utf-8")

#include "Prologue.h"
#include "System/cursor.h"
#include "Script\day0\fieldDef.h"
#include "Script\day1\fieldDef.h"	//次のchapter

#include <time.h>
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
	cursor->setCursorNum(Cursor::NOVEL);
	this->addChild(cursor, 1, "cursor");

	//BGM
	AudioEngine::stopAll();

	//バックログを初期化
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.plist";
	FileUtils::getInstance()->removeFile(file);

	//基準時間の初期化
	UserDefault *userDef = UserDefault::getInstance();
	userDef->setIntegerForKey("startTime", (int)time(NULL));
	userDef->setIntegerForKey("totalTime", 0);
	userDef->flush();

	mFuncNum = 1;

	//シナリオ
	mFunc[0] = [this]() {	//暫定、ある程度シナリオが固まってから考え直す
		auto novel = Novel::create();

		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "bg/book.png");
		novel->addSentence(0, "","幼いころずっと読んでいた大好きな絵本");
		novel->addSentence(0, "","絵本の中のあの子が大好きでなんどもなんども読み返した");
		novel->addSentence(0, "","大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー");
		novel->setBg(0, "");
		novel->addSentence(0, "","私だけの物にしたいと思った");

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};


	mFunc[1] = [this]() {
		setGetMusic(1);
		AudioEngine::play2d("BGM/days.ogg", true);

		auto novel = Novel::create();

		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "bg/town.png");
		novel->addEvent(0, CallFunc::create([this] {setGetStill(0); }));
		novel->addSentence(0, "","ここは人間も獣人も妖精だって、種族分け隔てなく平和に暮らす国、魔界王国。");
		novel->addSentence(0, "", "人々は幼い頃から基本的な魔法を学び、日常的に魔法を使って生活をしている。");
		novel->addSentence(0, "", "特殊能力という生まれつき変わった魔法が使える人もそこそこ多い、豊かな国だ");
		novel->setBg(0, "obj/bedroom.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaC(0, "chara/tuguru2.png");
		novel->addSentence(0, "継","ふあぁ…おはよう。セリーヌ");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0,"", "そんな平和なこの国を治めているのがこの国の王子である僕、王国　継（おうこく　つぐる）");
		novel->addSentence(0,"", "便利であるが故に悪用されがちな魔法を王家に伝わるハンコで制御するのが僕の役目だ。");
		novel->addSentence(0,"", "とはいっても魔法も政治もまだまだ修行中の身、未だ王子と言う身分で大臣達の手伝いや会議での採択等をするのが僕の主な役割だ。");
		novel->addSentence(0,"", "最近やっと情勢が落ち着いてきたので、数ヵ月ぶりに朝から魔法学校へ行こうと思う。");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/celine1.png");
		novel->addSentence(0, "セリーヌ","おはようございます、今日は随分と早起きなのですね");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "","この目つきがするどい女性はメイドのセリーヌ。");
		novel->addSentence(0, "","見た目はちょっと怖いけど、看護魔法から魔力貯蓄、更にはちょっとした読心術も使うことが出来る上級魔法使いだ。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ","…ですから怖くないって、いつも言っていますでしょう？");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "…心を読まれてしまったみたいだ");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaR(0, "chara/scene1.png");
		novel->addSentence(0, "バンダナ","おーいつぐるーん！迎えに来たぞー！");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","久しぶりー！");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "","城の前で叫んでいる二人は僕の友達のバイロン・ダイエナ、通称バンダナと立花　寿甘（たちばな　すあま）だ。");
		novel->addSentence(0, "","王子である僕にも気さくに接してくれる、数少ない友人だ。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継","おはよう！まってて着替えるから！");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "","この2人と仲良くなれたのも、王子である僕が一般の学校に通えるくらいこの国が平和なおかげだと思うと僕は仕事を頑張れるのだ。");
		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};

	mFunc[2] = [this]() {
		removeChildByName("cursor");

		auto control = (day0::Esc*)day0::Esc::createControl();
		//control->initField();	//必ず呼ぶ
		addChild(control, 1, "control");

		auto explain = Sprite::create("explain.png");
		explain->setPosition(Director::getInstance()->getVisibleSize() / 2);
		explain->setOpacity(0);
		explain->runAction(FadeIn::create(0.5f));
		this->addChild(explain, 5, "explain");
		auto listener2 = EventListenerTouchOneByOne::create();
		listener2->setSwallowTouches(true);
		listener2->onTouchBegan = [this](Touch* touch, Event* event) {
			return true;
		};
		listener2->onTouchEnded = [this](Touch* touch, Event* event) {
			removeChildByName("explain");
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, explain);

	};

	//mFunc[1] = [this]() {
	//	auto cursor = Cursor::create();
	//	cursor->setCursorNum(8);
	//	this->addChild(cursor, 1, "cursor");

		//auto novel = Novel::create();

		//novel->setFontColor(0, Color3B::BLACK);
		//novel->addSentence(0, "zzz・・・");
		//novel->setFontColor(0, Color3B::RED);
		//novel->addSentence(0, "？？？「つぐる様…」");
		//novel->setFontColor(0, Color3B::BLACK);
		//novel->addSentence(0, "zzz・・・");
		//novel->setFontColor(0, Color3B::RED);
		//novel->addSentence(0, "？？？「継様…？」");
		//novel->setFontColor(0, Color3B::BLACK);
		//novel->addSentence(0, "・・・？");
		//novel->addSentence(0, "…またこのパターンか");
		////addSitchEventは表示させたい文のタイミングの前に書く
		//novel->addSwitchEvent(0, 1, "狸寝入りを試みる", 2, "再び眠りにつく");
		//novel->addSentence(0, "僕は…");
		//novel->addSentence(1, "継「ぐー」");
		//novel->addSentence(1, "僕は狸寝入りを試みた");
		//novel->addSwitchEvent(1, 0);
		//novel->addSentence(1, "？？？「ちょ…わざと過ぎ…っ」");
		//novel->addSwitchEvent(2, 0);
		//novel->addSentence(2, "再び眠りについた");
		//novel->addSentence(0, "？？？「起きろーーーー！！！！！」");
		//novel->setBg(0, "bg/white.png");
		//novel->addSentence(0, "バシャッ");
		//novel->addSentence(0, "継「うわっ、何するんだよセ…」");
		//novel->setBg(0, "obj/classroom.png");
		//novel->addSentence(0, "");

		////setEndTaskは最後にまとめて呼ぶこと
		//novel->setEndTask(0);
		//novel->setEndTask(1);
		//novel->setEndTask(2);
		//this->addChild(novel, 0, "novel");

	//};

	mFunc[3] = [this]() {
		auto cursor = Cursor::create();
		cursor->setCursorNum(Cursor::NOVEL);
		this->addChild(cursor, 1, "cursor");

		auto novel = Novel::create();

		novel->setFontColor(0, Color3B::BLUE);
		novel->setBg(0, "bedroom.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaC(0, "chara/tuguru1.png");
		novel->addSentence(0, "継","着替えたよ");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/celine1.png");
		novel->addSentence(0, "セリーヌ","ではお供させていただきます");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継","今日はセリーヌ休んでて？連日の職務で疲れてるだろうし…学校くらいセリーヌいなくてもいけるよ！");
		novel->setCharaR(0, "chara/bandana1.png");
		novel->addSentence(0, "バンダナ","そうそう！こんな平和なんだしいざとなったら継は俺が守ってやるよ");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ","わかりました。ではせめてこれを…");
		novel->setCharaR(0, "chara/scene2.png");
		novel->addSentence(0, "セリーヌ","これは邪気を一時的に抑えることができるお札です、大丈夫だとは思いますが…万が一の時に使ってください");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継","心配性だなあ…じゃあ行ってくるね");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ","放課後にはお迎えに参ります");

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};

	mFunc[4] = [this]() {
		auto novel = Novel::create();

		novel->setBg(0, "bg/street.png");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘","んで、お仕事忙しいみたいだけどどんな感じなのよ？");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaC(0, "chara/tuguru1.png");
		novel->addSentence(0, "継","相変わらずだよ、特に魔法が発展してない国からの交渉が多くてね…");
		novel->setCharaR(0, "chara/bandana1.png");
		novel->addSentence(0, "バンダナ","せっかくだから魔法に頼らず、剣術でも発展させりゃいいのになーこの俺みたいに！");
		novel->addSentence(0, "継","相変わらずだねバンダナ");
		novel->addSentence(0, "継","僕のところに子供を嫁がせて実権を握ろうとする国もあってさ…正直どうすればいいかわからないよ…");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","それで…相手はどんな王子様なの？(ﾆﾔﾆﾔ)");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継","？…言ってることがよく分からないんだけど");
		novel->addSentence(0, "バンダナ","分からなくていいと思うぞ…");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","ｼﾞｮｳﾀﾞﾝﾃﾞｽｺﾞﾒﾝﾅｻｲ");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ","そう言う寿甘はどうなんだよ。最近一人で帰ってるだろ？彼氏でもできたのか？");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","…ああ…まあ、そんなところかな…ハハ…");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ","は？お前に彼氏なんてできたの！？マジで！？");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","う、うん…ツバメの翼くんって子で……最近巣を作ったって言ってて…気になって…");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ","あっ…そうですか……ゴメン");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘","謝らないでよ！！！そう言うバンダナはどうなのよ！");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ","いやあそれは………");
		novel->addSentence(0, "バンダナ","……ん？");
		novel->addSentence(0, "継","？どうしたのバンダナ？");
		novel->addSentence(0, "バンダナ", "いや……なんでもない");

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};

	mFunc[5] = [this]() {
		AudioEngine::stopAll();
		auto bg = Sprite::create("chara/scene3.png");
		bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
		bg->setOpacity(0.0f);
		bg->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(4.0f), FadeOut::create(0.5f), CallFunc::create([this] {
			mFunc[++mFuncNum]();
			removeChildByName("bg");
		}), NULL));
		addChild(bg, 0, "bg");
		setGetStill(1);
	};

	mFunc[6] = [this]() {			
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, day1::Day::createScene(), Color3B::WHITE));
	};

	auto attention = Sprite::create("bg/attention.png");
	attention->setOpacity(0.0f);
	attention->setPosition(visibleSize / 2);
	attention->runAction(Sequence::create(DelayTime::create(2.0f), FadeIn::create(1.0f), DelayTime::create(4.0f), FadeOut::create(1.0f),
		CallFunc::create(Prologue::mFunc[mFuncNum]), NULL));
	addChild(attention, 0, "attention");

	return true;
}

void Prologue::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag() && mFuncNum < 6 /* mFuncの数に応じて変える */) {
			mFunc[++mFuncNum]();
			this->removeChild(novel);
		}
	}

	auto control = (day0::Esc*)getChildByName("control");
	if (control) {
		if (control->getEndFlag() && mFuncNum == 2) {
			mFunc[++mFuncNum]();
		}
	}
}
