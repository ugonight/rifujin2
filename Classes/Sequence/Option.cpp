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
	std::string str = "";
	switch (userDef->getIntegerForKey("pHint", 1)) {
	case 0:
		str = "off";
		break;
	case 1:
		str = "移動のみ";
		break;
	case 2:
		str = "すべて";
		break;
	}

	label = Label::createWithTTF(StringUtils::format("ポイントヒント : %s", str.c_str()), FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 4, origin.y + display.height / 5 * 2));
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
			int mode = userDef->getIntegerForKey("pHint", 1);
			mode++;
			mode %= 3;
			userDef->setIntegerForKey("pHint", mode);
			userDef->flush();

			std::string str;
			switch (userDef->getIntegerForKey("pHint", 2)) {
			case 0:
				str = "off";
				break;
			case 1:
				str = "移動のみ";
				break;
			case 2:
				str = "すべて";
				break;
			}
			((Label*)target)->setString(StringUtils::format("ポイントヒント : %s", str.c_str()));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);


	// スキップ切り替え
	str = userDef->getBoolForKey("alreadySkip", false) ? "既読のみ" : "すべて";
	label = Label::createWithTTF(StringUtils::format("スキップ : %s", str.c_str()), FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 4 * 3, origin.y + display.height / 5 * 2));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	addChild(label, 3, "label_skip");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto userDef = UserDefault::getInstance();
			userDef->setBoolForKey("alreadySkip", !userDef->getBoolForKey("alreadySkip", true));
			userDef->flush();
			auto str = userDef->getBoolForKey("alreadySkip", true) ? "既読のみ" : "すべて";
			((Label*)target)->setString(StringUtils::format("スキップ : %s", str));
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
			listener->onTouchBegan = [this](Touch* touch, Event* event) { return true; };
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);

			auto sprite = Sprite::create("bg/black.png");
			sprite->setPosition(display / 2);
			sprite->setOpacity(255.0 * 0.8);
			layer->addChild(sprite, 0, "bg");

			auto label = Label::createWithTTF("全セーブデータ・実績データを削除します。\nよろしいですか？", FONT_NAME, 30);
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
					auto yes = (Label*)getChildByName("resetLayer")->getChildByName("yes");
					auto no = (Label*)getChildByName("resetLayer")->getChildByName("no");

					switch (mReset)
					{
					case 0:
						msg->setString("本当によろしいですか？");
						break;
					case 1:
						msg->setString("後悔しませんね？");
						break;
					case 2:
						yes->setString("いいえ");
						no->setString("はい");
						msg->setString("後悔しますか？");
						break;
					case 3: {
						// 実績削除
						auto userDef = UserDefault::getInstance();
						int i;
						for (i = 0; i < 30; i++) {
							userDef->deleteValueForKey(StringUtils::format("still%02d", i).c_str());
						}
						i = 0;
						while (userDef->getBoolForKey(StringUtils::format("music%02d", i).c_str())) {
							userDef->deleteValueForKey(StringUtils::format("music%02d", i).c_str());
							i++;
						}

						// ログ削除
						auto path = FileUtils::getInstance()->getWritablePath();
						auto file = path + "speak.plist";
						FileUtils::getInstance()->removeFile(file);
						for (i = 0; i <= 4; i++) {
							file = path + StringUtils::format("already%02d.plist", i);
							FileUtils::getInstance()->removeFile(file);
						}

						// セーブデータ削除
						//auto path = FileUtils::getInstance()->getWritablePath();
						cocos2d::log("%s", path.c_str());
						cocos2d::log("%d", FileUtils::getInstance()->removeDirectory(path));
						cocos2d::log("%d", FileUtils::getInstance()->createDirectory(path));
						userDef->setBoolForKey("first", false);
						for (i = 1; i <= 4; i++) {
							userDef->setBoolForKey(StringUtils::format("chap%dend", i).c_str(), false);
						}
						userDef->flush();

						yes->setString("はい");
						no->setString("");
						msg->setString("データを初期化しました。\nアプリを再起動してください。");

						// removeChildByName("resetLayer");

						break;
					}
					case 4:
						Director::getInstance()->end();
						break;
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
	}
	else if (event->getCurrentTarget()->getPositionX() > line->getBoundingBox().getMaxX()) {
		event->getCurrentTarget()->setPositionX(line->getBoundingBox().getMaxX());
	}

	if (event->getCurrentTarget()->getName() == "nob_BGM") {
		auto volume = (event->getCurrentTarget()->getPositionX() - line->getBoundingBox().getMinX()) / line->getContentSize().width;
		AudioEngine::setVolume(mBGM, volume);
	}
}

void Option::slideEnd(Touch* touch, Event* event) {
	auto userDef = UserDefault::getInstance();
	auto name = event->getCurrentTarget()->getName();
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
	auto target = event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();
	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	float volume;// = (event->getCurrentTarget()->getPositionX() - target->getBoundingBox().getMinX()) / target->getContentSize().width;


	if (targetBox.containsPoint(touchPoint))
	{
		if (target->getName() == "line_BGM") {
			getChildByName("nob_BGM")->setPositionX(touch->getLocation().x);
			volume = (getChildByName("nob_BGM")->getPositionX() - target->getBoundingBox().getMinX()) / target->getContentSize().width;
			userDef->setFloatForKey("volumeBGM", volume);
			AudioEngine::setVolume(mBGM, volume);
		}
		else {
			getChildByName("nob_SE")->setPositionX(touch->getLocation().x);
			volume = (getChildByName("nob_SE")->getPositionX() - target->getBoundingBox().getMinX()) / target->getContentSize().width;
			userDef->setFloatForKey("volumeSE", volume);
			playSoundBS("SE/set.ogg");
		}

		userDef->flush();

		return true;
	}
	return false;
}