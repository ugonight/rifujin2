#pragma  execution_character_set("utf-8")
#include "Title.h"
#include "Prologue.h"
#include "extra.h"
#include "Option.h"
#include "System\record.h"
#include "define.h"

#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;
USING_NS_CC;

Scene* Title::createScene()
{
	auto scene = Scene::create();
	auto layer = Title::create();
	scene->addChild(layer);
	return scene;
}

bool Title::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	UserDefault* userDef = UserDefault::getInstance();

	//auto closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(Title::menuCloseCallback, this));

	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
	//	origin.y + closeItem->getContentSize().height / 2));

	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	// タイトル表示
	{
		//auto sprite = Sprite::create("title/title.png");
		//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		//this->addChild(sprite, 0);

		showTitleImage("flower", 0, 0);
		if (userDef->getBoolForKey("chap1end", false)) {
			showTitleImage("tuguru", 0.5f, 10);
			showTitleImage("tuguru_add", 0.5f, 11);

			getChildByName("tuguru_add")->runAction(RepeatForever::create(Sequence::createWithTwoActions(
				EaseSineOut::create(FadeIn::create(3.0f)), EaseSineIn::create(FadeOut::create(3.0f))
			)));
		}
		if (userDef->getBoolForKey("chap2end", false)) {
			showTitleImage("bandana", 1.0f, 10);
			showTitleImage("bandana_add", 1.0f, 11);
		}
		if (userDef->getBoolForKey("chap3end", false)) {
			showTitleImage("rias", 1.5f, 1);
			showTitleImage("rias_add", 1.5f, 2);
		}
		if (userDef->getBoolForKey("chap4end", false)) {
			showTitleImage("remon", 2.0f, 1);
			showTitleImage("remon_add", 2.0f, 2);
		}
		showTitleImage("logo", 3.0f, 21, 2.0f);
		showTitleImage("logo_", 3.0f, 20, 2.0f);

		showTitleImage("menu_start", 4.0f, 30, 2.0f);
		showTitleImage("menu_continue", 4.0f, 30, 2.0f);
		showTitleImage("menu_extra", 4.0f, 30, 2.0f);
		showTitleImage("menu_setting", 4.0f, 30, 2.0f);
		showTitleImage("menu_help", 4.0f, 30, 2.0f);

	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (Rect(65, 420, 225, 60).containsPoint(touch->getLocationInView())) {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Prologue::createScene(), Color3B::WHITE));
		}
		else if (Rect(330, 420, 240, 60).containsPoint(touch->getLocationInView())) {
			auto record = Record::create();
			addChild(record, 50, "record");
		}
		else if (Rect(640, 420, 285, 150).containsPoint(touch->getLocationInView())) {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Extra::create(), Color3B::WHITE));
		}
		else if (Rect(620, 0, 234, 50).containsPoint(touch->getLocationInView())) {
			auto explain = Sprite::create("explain_.png");
			explain->setPosition(Director::getInstance()->getVisibleSize() / 2);
			auto listener2 = EventListenerTouchOneByOne::create();
			listener2->setSwallowTouches(true);
			listener2->onTouchBegan = [this](Touch* touch, Event* event) {return true; };
			listener2->onTouchEnded = [this](Touch* touch, Event* event) { removeChildByName("explain"); };
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, explain);
			addChild(explain, 50, "explain");
		}
		else if (Rect(0, 0, 100, 50).containsPoint(touch->getLocationInView())) {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Option::create(), Color3B::WHITE));
		}
		else {
			// タイトル表示アニメーションを省略
			for (auto child : this->getChildren()) {
				child->setOpacity(255.0f);
			}
		}
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//初回
	if (!userDef->getBoolForKey("first", false)) {
		std::stringstream path;
		for (int i = 0; i < 15; i++) {
			resetStr(path);
			path << FileUtils::getInstance()->getWritablePath() << i + 1;
			FileUtils::getInstance()->createDirectory(path.str());	//セーブフォルダ生成
		}

		userDef->setBoolForKey("first", true);
		userDef->flush();
	}

	//BGM
	setGetMusic(0);
	AudioEngine::preload("BGM/curse_inst.ogg");	if (AudioEngine::getPlayingAudioCount() == 0) playSoundBS("BGM/curse_inst.ogg", true);
	AudioEngine::preload("BGM/days.ogg");
	AudioEngine::preload("BGM/school.ogg");
	AudioEngine::preload("BGM/mystery.ogg");
	AudioEngine::preload("BGM/fear.ogg");
	AudioEngine::preload("BGM/underground.ogg");
	AudioEngine::preload("BGM/folklore.ogg");

	//SE
	AudioEngine::preload("SE/po.ogg");
	AudioEngine::preload("SE/record_on.ogg");
	AudioEngine::preload("SE/record_off.ogg");
	AudioEngine::preload("SE/chapter.ogg");
	AudioEngine::preload("SE/choice.ogg");


	return true;
}


void Title::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void Title::showTitleImage(std::string imageName, float dTime, int order, float fadeTime) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto path = StringUtils::format("title/%s.png", imageName.c_str());
	auto sprite = Sprite::create(path);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setOpacity(0.0f);
	sprite->runAction(Sequence::createWithTwoActions(DelayTime::create(dTime), FadeIn::create(fadeTime)));

	auto blend = BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE_MINUS_SRC_ALPHA };
	if (imageName.find("add") != std::string::npos) {
		blend = BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE };
	}
	else if (imageName.find("mul") != std::string::npos)
	{
		blend = BlendFunc{ backend::BlendFactor::ZERO, backend::BlendFactor::SRC_COLOR };

	}
	sprite->setBlendFunc(blend);

	this->addChild(sprite, order, imageName);
}
