#pragma  execution_character_set("utf-8")
#include "extra.h"
#include "Title.h"
#include "define.h"
#include "System/novel.h"

#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;
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
	mStillList.push_back("chara/tsubasa.png");
	mStillList.push_back("chara/memory1.png");
	mStillList.push_back("chara/memory2.png");
	mStillList.push_back("chara/memory3.png");
	mStillList.push_back("chara/memory4.png");
	mStillList.push_back("chara/scene8.png");
	mStillList.push_back("chara/scene9.png"); // 18
	mStillList.push_back("obj/remon_art.png");
	mStillList.push_back("chara/bad4.png");
	mStillList.push_back("chara/scene13.png");
	mStillList.push_back("chara/bad5.png");
	mStillList.push_back("chara/scene14.png");
	mStillList.push_back("chara/scene15.png");
	mStillList.push_back("chara/scene15_2.png");
	mStillList.push_back("chara/scene16.png");


	// BGM一覧
	mMusicList.push_back({ "paralyzed rose (inst short ver.)", "BGM/curse_inst.ogg" });
	mMusicList.push_back({ "days", "BGM/days.ogg" });
	mMusicList.push_back({ "school", "BGM/school.ogg" });
	mMusicList.push_back({ "mystery", "BGM/mystery.ogg" });
	mMusicList.push_back({ "fear", "BGM/fear.ogg" });
	mMusicList.push_back({ "underground", "BGM/underground.ogg" });
	mMusicList.push_back({ "folklore", "BGM/folklore.ogg" });
	mMusicList.push_back({ "reconciliation", "BGM/reconciliation.ogg" });
	mMusicList.push_back({ "paralyzed rose", "BGM/curse.ogg" });

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

	auto isClear = UserDefault::getInstance()->getBoolForKey("clear", false);
	label = Label::createWithTTF(isClear ? "キャラクター" : "？？？", FONT_NAME, 50);
	label->setPosition(Vec2(origin.x + display.width / 2, origin.y + display.height * 4 / 5));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "character");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this, isClear](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint) && isClear)
		{
			transition(CallFunc::create([this] {character(); }));
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::character() {
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
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height / 12));
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

	label = Label::createWithTTF("リアス", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 3 / 12));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "rias");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/rias1.png");
			((Label*)layer->getChildByName("name"))->setString("リアス・アレキサンドライト");
			((Label*)layer->getChildByName("phonetic"))->setString("りあす　あれきさんどらいと");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
引っ込み思案で恥ずかしがり屋な性格。占いやおまじないなどが趣味。\n \
キラキラしたものが好きで、休日には探知の特殊能力を使って宝探しをしている。\n \
バンダナのことが好きで付きまとい続けているが、軽くあしらわれてしまっている。\n \
檸檬のことは友達として大切に想っている。\n \
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("檸檬", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 4 / 12));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "remon");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/remon1.png");
			((Label*)layer->getChildByName("name"))->setString("水無月　檸檬");
			((Label*)layer->getChildByName("phonetic"))->setString("みなつき　れもん");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
完璧主義者だが面倒見の良い性格。\n \
母方の家系が日本人形作りを生業としていて、人形遣いの特殊能力を引き継いだ。\n \
父方の先祖が研究者で、幼い頃に地下の研究所を見つけてからは秘密基地として入り浸り、ドラゴン族の研究をするのが日課となった。\n \
リアスのことは研究対象としても友達としても大切にしている。\n \
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("宇沢", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 5 / 12));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "usawa");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/usawa1.png");
			((Label*)layer->getChildByName("name"))->setString("宇沢　智恵");
			((Label*)layer->getChildByName("phonetic"))->setString("うさわ　ともえ");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
新聞部に所属しており、地獄耳の特殊能力を持つ。\n \
常時スクープのことしか考えておらず、デリカシーに欠けた言動が目立つ。\n \
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("恋巳", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 6 / 12));
	label->setTextColor(Color4B::WHITE);
	label->enableOutline(Color4B::BLACK, 2);
	layer->addChild(label, 3, "renji");
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = (Label*)event->getCurrentTarget();
		Rect targetBox = target->getBoundingBox();
		Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
		if (targetBox.containsPoint(touchPoint))
		{
			auto layer = getChildByName("layer");
			((Sprite*)layer->getChildByName("image"))->setTexture("chara/renji1.png");
			((Label*)layer->getChildByName("name"))->setString("神北　恋巳");
			((Label*)layer->getChildByName("phonetic"))->setString("かみきた　れんじ");
			((Label*)layer->getChildByName("text"))->setString(" \
継たちのクラスメイト\n \
生粋のオカルト好き\n \
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("マリア", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 7 / 12));
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
学校では美術部に種族している。\n \
描いたものを具現化する能力を持っており、寿甘の困りごとに協力させられていたりする。\n\
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("バンダナ", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 8 / 12));
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
ひょうきんな性格だが、仲間想い。\n\
周りには喧嘩っ早いと思われがちだが、実際のところは事なかれ主義で面倒になって拳で解決してしまっている節がある。\n\
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("寿甘", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 9 / 12));
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
おてんばな性格で、誰とでもすぐに打ち解ける。\n \
動物や幽霊と言葉を交わすことができる特殊能力を持ち、その力を使って彼らに様々な用事を協力させていたりする。\n\
最近、ツバメの翼と交際を始めたがカラスのクロにちょっかいをかけられている。\n\
若干腐女子の気質がある。\n\
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("セリーヌ", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 10 / 12));
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
常に冷静で、機転を利かせた行動をする。\n \
ほとんどの魔法をほぼ完璧にこなす。看護魔法が得意分野。\n\
心理魔法の一環だと言ってたまにメタ発言のようなことを口走ったりするので度々黒幕疑惑が上がってくるが、本人は一貫して否定している。\n\
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

	label = Label::createWithTTF("継", FONT_NAME, 30);
	label->setPosition(Vec2(origin.x + display.width / 6, origin.y + display.height * 11 / 12));
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
最近は仕事が忙しくて学校を休みがちだが、毎晩家庭教師としてセリーヌから勉強をみっちり叩き込まれているのと本人の頭が切れるおかげで、学校では常に成績上位者になっている。\n\
過去にあった出来事が原因で、暗い部屋に閉じ込められること等にトラウマを抱えている。\n\
");
			return true;
		}
		return false;
		};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);

}

void Extra::music() {
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
		listener->onTouchBegan = [this, get, music](Touch* touch, Event* event) {
			auto target = (Label*)event->getCurrentTarget();
			Rect targetBox = target->getBoundingBox();
			Point touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);
			if (targetBox.containsPoint(touchPoint))
			{
				if (get) {
					AudioEngine::stopAll();
					playSoundBS(music.second, true);
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

void Extra::still() {
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
			thumbnail->setPosition(Vec2(190 + (854 * ratio + 20) * i, display.height - (150 + (480 * ratio + 20) * j)));
			if (!userDef->getBoolForKey(StringUtils::format("still%02d", id).c_str(), false)) {
				thumbnail->setColor(Color3B(50, 50, 50));
			}
			layer->addChild(thumbnail, 2, StringUtils::format("thumbnail%d", id));

			auto listener = EventListenerTouchOneByOne::create();
			listener->onTouchBegan = [this, id](Touch* touch, Event* event) {
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