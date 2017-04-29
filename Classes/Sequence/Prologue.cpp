#include "Prologue.h"
#include "System/cursor.h"
#include "System/novel.h"

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
	cursor->setCursorNum(7);
	this->addChild(cursor, 1, 1);

	//BGM
	AudioEngine::pauseAll();

	//バックログを初期化
	auto path = FileUtils::getInstance()->getWritablePath();
	auto file = path + "speak.plist";
	FileUtils::getInstance()->removeFile(file);

	//スキップボタン
	auto skip = Label::createWithTTF("スキップ", "fonts/APJapanesefontT.ttf", 24);
	skip->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	skip->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	skip->setTextColor(Color4B::WHITE);
	skip->enableOutline(Color4B::BLACK, 2);
	addChild(skip, 3, "skip");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			removeChildByTag(0);
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, skip);

	mFuncNum = 0;

	//シナリオ
	mFunc[0] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(0,Color3B::BLACK);
		novel->addSentence(0,"真っ暗で何も見えない");
		novel->addSentence(0,"そんな不安の中で");
		novel->addSentence(0,"ひたすら自分の犯した過ちを振り返る");
		novel->addSentence(0,"許してもらうために");
		novel->addSentence(0,"…誰に？");
		novel->addSentence(0,"でも、こうして罰を受け続けているのだから、懺悔を繰り返す他に道はないのだ");
		novel->addSentence(0,"そもそも、僕の罪は何なのだろう");
		novel->addSentence(0,"漠然とした記憶");
		novel->addSentence(0,"…何かが足りない");
		novel->addSentence(0,"この闇から抜け出すには、まだ、何かが足りないのだ");
		novel->addSentence(0,"今はその時ではない");
		novel->addSentence(0,"そして、また僕は思考を手放す");

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	};

	mFunc[1] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(0,Color3B::BLACK);
		novel->addSentence(0,"zzz・・・");
		novel->setFontColor(0,Color3B::RED);
		novel->addSentence(0,"？？？「つぐる様…」");
		novel->setFontColor(0,Color3B::BLACK);
		novel->addSentence(0,"zzz・・・");
		novel->setFontColor(0,Color3B::RED);
		novel->addSentence(0,"？？？「継様…？」");
		novel->setFontColor(0,Color3B::BLACK);
		novel->addSentence(0,"・・・？");
		novel->addSentence(0,"…またこのパターンか");
		//addSitchEventは表示させたい文のタイミングの前に書く
		novel->addSwitchEvent(0, 1, "狸寝入りを試みる", 2, "再び眠りにつく");
		novel->addSentence(0,"僕は…");	
		novel->addSentence(1, "継「ぐー」");
		novel->addSentence(1, "僕は狸寝入りを試みた");
		novel->addSwitchEvent(1, 0);
		novel->addSentence(1, "？？？「ちょ…わざと過ぎ…っ」");
		novel->addSwitchEvent(2, 0);
		novel->addSentence(2, "再び眠りについた");
		novel->addSentence(0,"？？？「起きろーーーー！！！！！」");
		novel->setBg(0,"bg/white.png");
		novel->addSentence(0,"バシャッ");
		novel->addSentence(0,"継「うわっ、何するんだよセ…」");
		novel->setBg(0,"obj/classroom.png");
		novel->addSentence(0,"");

		//setEndTaskは最後にまとめて呼ぶこと
		novel->setEndTask(0);
		novel->setEndTask(1);
		novel->setEndTask(2);
		this->addChild(novel, 0, "novel");
	};

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
		if (novel->getEndFlag() && mFuncNum < 1) {
			mFunc[++mFuncNum]();
			this->removeChild(novel);
		}
	}
}
