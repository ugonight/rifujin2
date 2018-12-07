#pragma  execution_character_set("utf-8")
#include "Option.h"
#include "define.h"
#include "Title.h"


#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Option::Option()
{
}


Option::~Option()
{
}

bool Option::init() {
	if (Scene::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("title/option.png");
	bg->setPosition(display / 2);
	addChild(bg, 0, "bg");

	//auto layer = Layer::create();
	//layer->setPosition(Vec2::ZERO);
	//addChild(layer, 1, "layer");

	
	auto userDef = UserDefault::getInstance();


	// 音量・BGM

	auto line = Sprite::create("title/scroll_line.png");
	line->setPosition(display.width / 3 * 2, display.height / 5 * 4);
	addChild(line, 2, "line_BGM");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Option::lineBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, line);

	auto nob = Sprite::create("title/scroll_nob.png");
	float x = line->getBoundingBox().getMinX() + line->getContentSize().width * userDef->getFloatForKey("volumeBGM", 1.0);
	nob->setPosition(x, display.height / 5 * 4);
	addChild(nob, 3, "nob_BGM");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Option::slideBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Option::slideMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(Option::slideEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, nob);

	auto label = Label::createWithTTF("BGM音量", FONT_NAME, 40);
	label->setPosition(Vec2(origin.x + display.width / 4, origin.y + display.height / 5 * 4));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	addChild(label, 3, "label_BGM");


	// BGM・SE

	line = Sprite::create("title/scroll_line.png");
	line->setPosition(display.width / 3 * 2, display.height / 5 * 3);
	addChild(line, 2, "line_SE");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Option::lineBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, line);

	nob = Sprite::create("title/scroll_nob.png");
	x = line->getBoundingBox().getMinX() + line->getContentSize().width * userDef->getFloatForKey("volumeSE", 1.0);
	nob->setPosition(x, display.height / 5 * 3);
	addChild(nob, 3, "nob_SE");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Option::slideBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Option::slideMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(Option::slideEnd, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, nob);

	label = Label::createWithTTF("SE音量", FONT_NAME, 40);
	label->setPosition(Vec2(origin.x + display.width / 4, origin.y + display.height / 5 * 3));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	addChild(label, 3, "label_SE");


	// ポイントヒント切り替え
	auto str = userDef->getBoolForKey("pHint", true) ? "on" : "off";
	label = Label::createWithTTF(StringUtils::format("ポイントヒント : %s", str), FONT_NAME, 40);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 5 * 2));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	addChild(label, 3, "label_PH");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto userDef = UserDefault::getInstance();
			userDef->setBoolForKey("pHint", !userDef->getBoolForKey("pHint", true));
			userDef->flush();
			auto str = userDef->getBoolForKey("pHint", true) ? "on" : "off";
			((Label*)target)->setString(StringUtils::format("ポイントヒント : %s", str));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);


	// データ初期化
	label = Label::createWithTTF("データ初期化", FONT_NAME, 40);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 5 * 1));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	addChild(label, 3, "label_reset");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			Size display = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			mReset = 0;

			auto layer = Layer::create();
			layer->setPosition(Vec2::ZERO);
			addChild(layer, 5, "resetLayer");
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this](Touch* touch, Event* event) {return true; };
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);

			auto sprite = Sprite::create("bg/black.png");
			sprite->setPosition(display / 2);
			sprite->setOpacity(255.0 * 0.8);
			layer->addChild(sprite, 0, "bg");

			auto label = Label::createWithTTF("全セーブデータ・実績データ・設定データを削除します。\nよろしいですか？", FONT_NAME, 30);
			label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 3 * 2));
			label->setTextColor(Color4B::WHITE);
			layer->addChild(label, 3, "msg");

			label = Label::createWithTTF("はい", FONT_NAME, 40);
			label->setPosition(Vec2(origin.x + display.width / 3, origin.y + display.height / 3));
			label->setTextColor(Color4B::WHITE);
			layer->addChild(label, 3, "yes");
			listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
					auto msg = (Label*)getChildByName("resetLayer")->getChildByName("msg");
					switch (mReset)
					{
					case 0:
						msg->setString("本当によろしいですか？");
						break;
					case 1:
						msg->setString("後悔しませんね？");
						break;
					case 2:
						msg->setString("データを削除します");
						break;
					case 3: {
						auto path = UserDefault::getInstance()->getXMLFilePath();
						FileUtils::getInstance()->removeFile(path);
						FileUtils::getInstance()->removeDirectory(FileUtils::getInstance()->getWritablePath());
						//						Director::getInstance()->end();
						//
						//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
						//						exit(0);
						//#endif
						removeChildByName("resetLayer");

						break;
					}
					default:
						break;
					}

					mReset++;
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

			label = Label::createWithTTF("いいえ", FONT_NAME, 40);
			label->setPosition(Vec2(origin.x + display.width / 3 * 2, origin.y + display.height / 3));
			label->setTextColor(Color4B::WHITE);
			layer->addChild(label, 3, "no");
			listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this](Touch* touch, Event* event) {
				if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
					removeChildByName("resetLayer");
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);



	// 戻る
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		Rect targetBox = Rect(0, 400, 110, 80);
		Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
		if (targetBox.containsPoint(touchPoint))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);



	AudioEngine::stopAll();
	mBGM = playSoundBS("BGM/curse_inst.ogg", true);

	return true;
}

void Option::update(float delta) {

}

bool Option::slideBegan(Touch* touch, Event* event) {
	auto target = (Label*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	if (targetBox.containsPoint(touchPoint))
	{
		return true;
	}
	return false;
}
void Option::slideMove(Touch* touch, Event* event) {
	event->getCurrentTarget()->setPositionX(touch->getLocation().x);
	
	auto line = getChildByName("line_BGM");

	if (event->getCurrentTarget()->getPositionX() < line->getBoundingBox().getMinX()) {
		event->getCurrentTarget()->setPositionX(line->getBoundingBox().getMinX());
	}else if (event->getCurrentTarget()->getPositionX() > line->getBoundingBox().getMaxX()) {
		event->getCurrentTarget()->setPositionX(line->getBoundingBox().getMaxX());
	}

	if (event->getCurrentTarget()->getName() == "nob_BGM") {
		auto volume = (event->getCurrentTarget()->getPositionX() - line->getBoundingBox().getMinX()) / line->getContentSize().width;
		AudioEngine::setVolume(mBGM, volume);
	}
}

void Option::slideEnd(Touch* touch, Event* event) {
	auto userDef = UserDefault::getInstance();
	auto name =	event->getCurrentTarget()->getName();
	auto line = getChildByName("line_BGM");
	auto volume = (event->getCurrentTarget()->getPositionX() - line->getBoundingBox().getMinX()) / line->getContentSize().width;

	if (name == "nob_BGM") {
		userDef->setFloatForKey("volumeBGM", volume);
		AudioEngine::setVolume(mBGM, volume);
	}
	else {
		userDef->setFloatForKey("volumeSE", volume);
		playSoundBS("SE/set.ogg");
	}

	userDef->flush();
}

bool Option::lineBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto userDef = UserDefault::getInstance();
	auto target = (Label*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	auto volume = (event->getCurrentTarget()->getPositionX() - target->getBoundingBox().getMinX()) / target->getContentSize().width;


	if (targetBox.containsPoint(touchPoint))
	{
		if (target->getName() == "line_BGM") {
			getChildByName("nob_BGM")->setPositionX(touch->getLocation().x);
			userDef->setFloatForKey("volumeBGM", volume);
			AudioEngine::setVolume(mBGM, volume);
		}
		else {
			getChildByName("nob_SE")->setPositionX(touch->getLocation().x);
			userDef->setFloatForKey("volumeSE", volume);
			playSoundBS("SE/set.ogg");
		}

		userDef->flush();

		return true;
	}
	return false;
}