#pragma  execution_character_set("utf-8")
#include "extra.h"
#include "Title.h"
#include "define.h"
#include "System/novel.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;

Extra::Extra() :ratio(1.0 / 4.0) {

}

bool Extra::init() {
	if (Scene::init() == false)
		return false;

	this->scheduleUpdate();

	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bedroom.png");
	bg->setPosition(display / 2);
	addChild(bg, 0, "bg");

	auto layer = Layer::create();
	layer->setPosition(Vec2::ZERO);
	addChild(layer, 1, "layer");

	menu();

	// スチル一覧
	mStillList.push_back("bg/town.png");
	mStillList.push_back("chara/scene3.png");
	mStillList.push_back("chara/scene4.png");
	mStillList.push_back("chara/scene5.png");
	mStillList.push_back("chara/scene6.png");
	mStillList.push_back("chara/zombie.png");
	mStillList.push_back("chara/shojo.png");
	mStillList.push_back("chara/bad2.png");
	mStillList.push_back("chara/stand_bow.png");
	mStillList.push_back("chara/remon_fallen.png");
	mStillList.push_back("bg/book.png");
	mStillList.push_back("chara/dragon_soul.png");

	// BGM一覧
	mMusicList.push_back(std::make_pair("paralyzed rose (inst short ver.)", "BGM/curse_inst.ogg"));
	mMusicList.push_back(std::make_pair("days", "BGM/days.ogg"));
	mMusicList.push_back(std::make_pair("school", "BGM/school.ogg"));
	mMusicList.push_back(std::make_pair("mystery", "BGM/mystery.ogg"));
	mMusicList.push_back(std::make_pair("fear", "BGM/fear.ogg"));
	mMusicList.push_back(std::make_pair("underground", "BGM/underground.ogg"));
	mMusicList.push_back(std::make_pair("folklore", "BGM/folklore.ogg"));

	return true;
}

void Extra::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			removeChild(novel);
		}
	}
}

void Extra::menu() {
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layer = getChildByName("layer");

	auto label = Label::createWithTTF("タイトルへ戻る", FONT_NAME, 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("スチル", FONT_NAME, 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 2 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "still");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {still(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("おんがく", FONT_NAME, 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 3 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "music");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {music(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("キャラクター", FONT_NAME, 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 4 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "character");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {character(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::character(){
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto layer = getChildByName("layer");

	auto description = Sprite::create("title/chara.png");
	description->setPosition(display / 2);
	layer->addChild(description, 1, "description");

	auto label = Label::createWithTTF("", FONT_NAME, 20);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(Vec2(origin.x + 500, origin.y + 350));
	label->setTextColor(Color4B::BLACK);
	label->setDimensions(320, 330);
	layer->addChild(label, 3, "text");

	label = Label::createWithTTF("", FONT_NAME, 35);
	label->setPosition(Vec2(origin.x + 650, origin.y + 400));
	label->setTextColor(Color4B::BLACK);
	label->enableOutline(Color4B::WHITE, 2);
	layer->addChild(label, 3, "name");

	label = Label::createWithTTF("", FONT_NAME, 20);
	label->setPosition(Vec2(origin.x + 650, origin.y + 450));
	label->setTextColor(Color4B::BLACK);
	layer->addChild(label, 3, "phonetic");

	auto chara = Sprite::create();
	chara->setPosition(Vec2(origin.x + 350, origin.y + display.height / 2));
	layer->addChild(chara, 2, "image");


	label = Label::createWithTTF("戻る", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {menu(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("桜", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 2 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "sakura");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/sakura1.png");
			((Label*)layer->getChildByName("name"))->setString("朝星　桜");
			((Label*)layer->getChildByName("phonetic"))->setString("あさぼし　さくら");
			((Label*)layer->getChildByName("text"))->setString(" \
マリアの幼馴染。\n \
１２歳のころまで近所に住んでいたが、親の転勤で遠くの国へ引っ越してしまう。\n \
マリアとは対照的で明るい性格であり、友達想い。\n\
引っ越し先の国で重い病気にかかってしまい、国の魔法が発展途上であったため治す術がなかったが、セリーヌの機転により、魔法が発達した魔界王国の看護魔法で治療を施される。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("マリア", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 3 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "maria");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/maria1.png");
			((Label*)layer->getChildByName("name"))->setString("マリア・ミルフィーユ");
			((Label*)layer->getChildByName("phonetic"))->setString("まりあ・みるふぃーゆ");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
生まれた時から色が識別できない病気を持っていて、波動を使って生活していた\n \
幼馴染の桜に色を教えてもらううちに、桜の脳内から色のイメージを受け取り、病気は奇跡的に回復した。\n\
大人しい性格で、いつも一人で絵を描いたり本を読んで過ごしている。\n\
周囲とうまく馴染めず、次第に色を忘れていってしまう。学校でのハプニングが原因で塞ぎ込み、やがて意識の中から出られなくなってしまう。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("バンダナ", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 4 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "bandana");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/bandana1.png");
			((Label*)layer->getChildByName("name"))->setString("バイロン・ダイエナ");
			((Label*)layer->getChildByName("phonetic"))->setString("ばいろん・だいえな");
			((Label*)layer->getChildByName("text"))->setString(" \
継の友達\n \
魔法学校に通いながらも、魔法に頼らないという信念を持つ。\n \
剣術に長けており、ピンチの時はいつも継達を助けてくれる。\n\
ひょうきんな性格だが、優しいところもある。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("寿甘", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 5 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "suama");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/suama1.png");
			((Label*)layer->getChildByName("name"))->setString("立花　寿甘");
			((Label*)layer->getChildByName("phonetic"))->setString("たちばな　すあま");
			((Label*)layer->getChildByName("text"))->setString(" \
継の友達。\n \
動物や物の声を受け取ることができる特殊能力を持つ。\n \
おてんばな性格で、面倒見がいい。\n\
霊感が強いため、幽霊などを見てしまうことがある。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("セリーヌ", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 6 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "celine");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/celine1.png");
			((Label*)layer->getChildByName("name"))->setString("セリーヌ・ルトストレーム");
			((Label*)layer->getChildByName("phonetic"))->setString("せりーぬ・るとすとれーむ");
			((Label*)layer->getChildByName("text"))->setString(" \
継に仕えるメイド\n \
ほとんどの魔法をほぼ完璧にこなす。看護魔法が得意分野。\n \
常に冷静で、機転を利かせた行動をする。\n\
継からはドSと揶揄され、よくコントのような掛け合いをすることがある。\n\
年齢の話をすると人が変わったようにぶちギレる。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("継", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 7 / 8));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "tuguru");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/tuguru1.png");
			((Label*)layer->getChildByName("name"))->setString("王国　継");
			((Label*)layer->getChildByName("phonetic"))->setString("おうこく　つぐる");
			((Label*)layer->getChildByName("text"))->setString(" \
今は亡き父、守の遺志を継いで魔界王国の国王になった。つぐるんの愛称で親しまれている\n \
政治のことはまだ勉強途中なので大臣などに任せっきりだが、王国の魔法を制御するハンコの管理と、大事な決め事などはできるだけこなしている。\n \
仕事と修行を両立させなきゃいけないため、魔法はあまり使えないが頭が切れるので、数々の問題事を片付けることができる。\n\
");
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::music(){
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto userDef = cocos2d::UserDefault::getInstance();
	auto layer = getChildByName("layer");

	auto label = Label::createWithTTF("戻る", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height / (mMusicList.size() + 2)));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "back");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			transition(CallFunc::create([this] {menu(); }));
			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	int id = 0;
	bool get;
	for (auto music : mMusicList) {
		get = (userDef->getBoolForKey(StringUtils::format("music%02d", id).c_str(), false));
		std::string name = get ? music.first : "？？？？";
		label = Label::createWithTTF(name, FONT_NAME, 30);
		label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * (mMusicList.size() + 2 - id - 1) / (mMusicList.size() + 2)));
		label->setTextColor(Color4B::WHITE);
		label->enableOutline(Color4B::BLACK, 2);
		layer->addChild(label, 3, StringUtils::format("music%02d", id));
		listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this,get,music](Touch* touch, Event* event) {
			auto target = (Label*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				if (get) {
					AudioEngine::stopAll();
					AudioEngine::play2d(music.second, true);
				}

				return true;
			}
			return false;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
		id++;
	}


	//label = Label::createWithTTF("precious smile (inst short ver.)", FONT_NAME, 50);
	//label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 6 / 7));
	//label->setTextColor(Color4B::WHITE);
	//label->enableOutline(Color4B::BLACK, 2);
	//layer->addChild(label, 3, "title");
	//listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [this](Touch* touch, Event* event) {
	//	auto target = (Label*)event->getCurrentTarget();
	//	Rect targetBox = target->getBoundingBox();
	//	Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
	//	if (targetBox.containsPoint(touchPoint))
	//	{
	//		//SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	//		//SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/title.ogg", true);

	//		return true;
	//	}
	//	return false;
	//};
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::still(){
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto userDef = cocos2d::UserDefault::getInstance();

	auto layer = getChildByName("layer");

	//const double ratio = 1.0 / 4.0;
	mPage = 0;

	Rect rect = Rect(0, 0, 854 * ratio, 480 * ratio);

	// スチル
	Sprite* thumbnail;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			int id = 3 * j + i;
			thumbnail = Sprite::create();
			thumbnail->setTexture(mStillList[id]);
			thumbnail->setScale(ratio);
			thumbnail->setPosition(Vec2(190 + (854 * ratio + 20) * i, display.height - (150 + (480 * ratio + 20)*j)));
			if (!userDef->getBoolForKey(StringUtils::format("still%02d", id).c_str(), false)) {
				thumbnail->setColor(Color3B(50, 50, 50));
			}
			layer->addChild(thumbnail, 2, StringUtils::format("thumbnail%d", id));

			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this,id](Touch* touch, Event* event) {
				auto target = (Label*)event->getCurrentTarget();
				Rect targetBox = target->getBoundingBox();
				Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
				if (targetBox.containsPoint(touchPoint))
				{
					if (UserDefault::getInstance()->getBoolForKey(StringUtils::format("still%02d", mPage * 6 + id).c_str(), false)) {
						auto still = Sprite::create(mStillList[mPage * 6 + id]);
						still->setPosition(Director::getInstance()->getVisibleSize() / 2);
						still->setOpacity(0.0f);
						still->runAction(FadeIn::create(0.5));
						addChild(still, 3, "still");
						auto listener = EventListenerTouchOneByOne::create();
						listener->setSwallowTouches(true);
						listener->onTouchBegan = [this, id](Touch* touch, Event* event) {
							event->getCurrentTarget()->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5), RemoveSelf::create()));

							return true;
						};
						this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, still);
					}
					return true;
				}
				return false;
			};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, thumbnail);
		}
	}

	// 矢印
	auto arrow = Sprite::create("record_next.png");
	arrow->setPosition(Vec2(854 - 40, 250));
	layer->addChild(arrow, 1, "next");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			mPage++;
			turnPage();

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, arrow);
	arrow = Sprite::create("record_next.png");
	arrow->setFlippedX(true);
	arrow->setPosition(Vec2(40, 250));
	layer->addChild(arrow, 1, "pre");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			mPage--;
			turnPage();

			return true;
		}
		return false;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, arrow);
	arrow->setVisible(false);
	this->getEventDispatcher()->pauseEventListenersForTarget(arrow);

	// 戻る
	{
		auto label = Label::createWithTTF("戻る", FONT_NAME, 30);
		label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height / 8));
		label->setTextColor(Color4B::WHITE);
		label->enableOutline(Color4B::BLACK, 2);
		layer->addChild(label, 3, "back");
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [this](Touch* touch, Event* event) {
			auto target = (Label*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				transition(CallFunc::create([this] {menu(); }));
				return true;
			}
			return false;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
	}
}

void Extra::transition(cocos2d::CallFunc* func) {
	auto layer = getChildByName("layer");
	func->retain();
	layer->setCascadeOpacityEnabled(true);
	layer->getEventDispatcher()->setEnabled(false);
	layer->runAction(Sequence::create(
		FadeOut::create(0.5f),
		CallFunc::create([this] {
			getChildByName("layer")->getEventDispatcher()->setEnabled(true);
			getChildByName("layer")->removeAllChildren();
	}),	
		func,
		FadeIn::create(0.5f),
		NULL));
}

void Extra::turnPage() {
	Size display = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto userDef = cocos2d::UserDefault::getInstance();
	auto layer = getChildByName("layer");
	Sprite* thumbnail;

	// スチル
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			int id = 3 * j + i;
			thumbnail = (Sprite*)layer->getChildByName(StringUtils::format("thumbnail%d", id));
			if (mPage * 6 + id < mStillList.size()) {
				thumbnail->setTexture(mStillList[mPage * 6 + id]);
				if (!userDef->getBoolForKey(StringUtils::format("still%02d", mPage * 6 + id).c_str(), false)) {
					thumbnail->setColor(Color3B(50, 50, 50));
				}
				else {
					thumbnail->setColor(Color3B(255, 255, 255));
				}
			}
			else {
				thumbnail->setTexture("bg/black.png");
			}
		}
	}

	auto next = layer->getChildByName("next");
	auto pre = layer->getChildByName("pre");

	setVisibleWithTouch(next, mStillList.size() / 6 > mPage);
	setVisibleWithTouch(pre, mPage > 0);
}