#include "record.h"
#include "Sequence/Title.h"
#include "define.h"
#pragma execution_character_set("utf-8")

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Record::Record() : mPage(0), mSelectNum(0),mMode(0)
{}

Record::~Record() {
	//CC_SAFE_RELEASE_NULL(mSaveFunc);
}
//Scene* Record::createScene()
//{
//    auto scene = Scene::create();
//    auto layer = Record::create();
//    scene->addChild(layer);
//    return scene;
//}

bool Record::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	AudioEngine::play2d("SE/record_on.ogg");

	//枠
	auto bg = Sprite::create("record.png");	//x25y25w550h350d70
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 3 / 2));
	bg->runAction(EaseSineOut::create(MoveBy::create(0.2, Vec3(0, -visibleSize.height, 0))));
	addChild(bg, 0, "bg");

	auto select = Sprite::create("record_select.png");
	select->setPosition(visibleSize / 2);
	select->setOpacity(0.0);
	addChild(select, 2, "select");

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			int my = event->getCurrentTarget()->getBoundingBox().getMaxY() - 25;
			for (int i = 0; i < 5; i++) {
				if (touch->getLocation().y >= my - 70 * (i + 1) && touch->getLocation().y <= my - 70 * i) {
					auto select = getChildByName("select");
					select->setPosition(Vec2(visibleSize.width / 2, my - 70 * i - 35));
					select->setOpacity(0.0);
					select->runAction(FadeIn::create(0.1));
					mSelectNum = mPage * 5 + i + 1;
				}
			}
		}
		else {
			this->runAction(Sequence::create(EaseSineIn::create(MoveBy::create(0.2, Vec3(0, visibleSize.height, 0)))
				,RemoveSelf::create(),NULL));
			AudioEngine::play2d("SE/record_off.ogg");
			mSelectNum = 0;
		}
		return true;
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		getChildByName("select")->runAction(FadeOut::create(0.1));
		if (mSelectNum) {
			if (mMode) {
				mSaveFunc(mSelectNum);
				updateInfo();
			}
			else {
				load();
			}
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, bg);

	//テキスト
	int my = bg->getBoundingBox().getMaxY() - 25 - visibleSize.height;
	for (int i = 0; i < 5; i++) {
		std::stringstream str;
		str << i + 1;
		auto num = Label::createWithTTF(str.str(), FONT_NAME, 30);
		num->setPosition(Vec2(250,my - 70 * i - 35));
		//str.clear(); str.str("");
		resetStr(str);
		str << "num_" << i + 1;
		addChild(num, 3, str.str());
		auto chapter = Label::createWithTTF("chapter", FONT_NAME, 25);
		chapter->setPosition(Vec2(visibleSize.width / 2 + 20, my - 70 * i - 20));
		chapter->setColor(Color3B::BLACK);
		resetStr(str);
		str << "chapter_" << i + 1;
		addChild(chapter, 3, str.str());
		auto situation = Label::createWithTTF("situation", FONT_NAME, 25);
		situation->setPosition(Vec2(visibleSize.width / 2 + 20, my - 70 * i - 50));
		situation->setColor(Color3B::BLACK);
		resetStr(str);
		str << "situation_" << i + 1;
		addChild(situation, 3, str.str());
	}
	updateInfo();

	//ページ切り替え
	auto arrow = Sprite::create("record_next.png");
	arrow->setPosition(Vec2(visibleSize.width / 2 + 250, visibleSize.height / 2));
	arrow->runAction(FadeIn::create(0.2));
	addChild(arrow, 5, "next");
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			mPage++;
			turnPage();
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, arrow);
	arrow = Sprite::create("record_next.png");
	arrow->setPosition(Vec2(visibleSize.width / 2 - 250, visibleSize.height / 2));
	arrow->runAction(Spawn::createWithTwoActions(FlipX::create(true), FadeIn::create(0.2)));
	arrow->setVisible(false);
	addChild(arrow, 5, "pre");
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			mPage--;
			turnPage();
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, arrow);
	getEventDispatcher()->pauseEventListenersForTarget(arrow);

    return true;
}

void Record::update( float delta ) {

}

void Record::turnPage() {
	for (int i = 0; i < 5; i++) {
		std::stringstream name;
		name << "num_" << i + 1;
		auto num = (Label*)getChildByName(name.str());
		//name.clear(); name.str("");
		resetStr(name);
		name << mPage * 5 + i + 1;
		num->setString(name.str());
	}

	auto next = getChildByName("next");
	auto pre = getChildByName("pre");

	//if (mPage < 2) {
	//	next->setVisible(true);
	//	getEventDispatcher()->resumeEventListenersForTarget(next);
	//}
	//else {
	//	next->setVisible(false);
	//	getEventDispatcher()->pauseEventListenersForTarget(next);
	//}
	//if (mPage > 0) {
	//	pre->setVisible(true);
	//	getEventDispatcher()->resumeEventListenersForTarget(pre);
	//}
	//else {
	//	pre->setVisible(false);
	//	getEventDispatcher()->pauseEventListenersForTarget(pre);
	//}
	
	setVisibleWithTouch(next, mPage < 2);
	setVisibleWithTouch(pre, mPage > 0);

	updateInfo();
}

void Record::updateInfo() {
	int dataNum;
	std::stringstream str;
	for (int i = 0; i < 5; i++) {
		dataNum = mPage * 5 + i + 1;
		resetStr(str);
		str << FileUtils::getInstance()->getWritablePath() <<  dataNum << "/";
		auto path = str.str();

		auto file = path + "saveData.plist";

		resetStr(str);
		str << "chapter_" << i + 1;
		auto label = (Label*)getChildByName(str.str());
		ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);
		if (data["chapter"].asInt() > 0) {
			label->setString("chapter" + data["chapter"].asString());
		}
		else {
			label->setString("no data");
		}

		resetStr(str);
		str << "situation_" << i + 1;
		label = (Label*)getChildByName(str.str());
		if (data["situation"].asString() != "") {
			label->setString(data["situation"].asString());
		}
		else {
			label->setString("");
		}
		
	}
}

void Record::save(std::function<void(int)> &func) {
	mSaveFunc = func;
	//mSaveFunc->retain();
	mMode = true;

	auto goTitle = Label::createWithTTF("タイトルへ", FONT_NAME, 25);
	goTitle->setPosition(200,80);
	goTitle->setTextColor(Color4B::BLACK);
	goTitle->setOpacity(0.0f);
	goTitle->runAction(FadeIn::create(0.2f));
	addChild(goTitle, 5, "goTitle");
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			this->runAction(Sequence::create(EaseSineIn::create(MoveBy::create(0.2, Vec3(0, visibleSize.height, 0)))
				, RemoveSelf::create(), NULL));	
			AudioEngine::stopAll();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, Title::createScene()));
			return true;
		}
		return false;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, goTitle);

}

