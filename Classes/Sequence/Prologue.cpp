#include "Prologue.h"
#include "System/cursor.h"
#include "System/novel.h"

#pragma execution_character_set("utf-8")

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
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
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();

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

		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("真っ暗で何も見えない");
		novel->addSentence("そんな不安の中で");
		novel->addSentence("ひたすら自分の犯した過ちを振り返る");
		novel->addSentence("許してもらうために");
		novel->addSentence("…誰に？");
		novel->addSentence("でも、こうして罰を受け続けているのだから、懺悔を繰り返す他に道はないのだ");
		novel->addSentence("そもそも、僕の罪は何なのだろう");
		novel->addSentence("漠然とした記憶");
		novel->addSentence("…何かが足りない");
		novel->addSentence("この闇から抜け出すには、まだ、何かが足りないのだ");
		novel->addSentence("今はその時ではない");
		novel->addSentence("そして、また僕は思考を手放す");

		novel->setEndTask();
		this->addChild(novel, 0, "novel");
	};

	mFunc[1] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("zzz・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「つぐる様…」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("zzz・・・");
		novel->setFontColor(Color3B::RED);
		novel->addSentence("？？？「継様…？」");
		novel->setFontColor(Color3B::BLACK);
		novel->addSentence("・・・？");
		novel->addSentence("…またこのパターンか");
		novel->addSentence("僕は狸寝入りを試みる");
		novel->addSentence("？？？「起きろーーーー！！！！！」");
		novel->setBg("bg/white.png");
		novel->addSentence("バシャッ");
		novel->addSentence("継「うわっ、何するんだよセ…」");
		novel->setBg("obj/classroom.png");
		novel->addSentence("");


		novel->setEndTask();
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
