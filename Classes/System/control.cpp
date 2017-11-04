#pragma  execution_character_set("utf-8")

#include "control.h"

#include "cursor.h"
#include "field.h"
#include "item.h"
#include "novel.h"
#include "object.h"
#include "define.h"
//#include "Script/fieldDef.h"

#include "ui/CocosGUI.h"
USING_NS_CC;

Control* Control::me;

Control::~Control() {
	for (auto field : mFieldList) {
		CC_SAFE_RELEASE_NULL(field.second);
	}
}

bool Control::init() {
	if (!Scene::init())
	{
		return false;
	}
	scheduleUpdate();

	me = this;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto cursor = Cursor::create();
	this->addChild(cursor, 4, "cursor");

	//auto resetCursor = Layer::create();
	//this->addChild(resetCursor, 10);

	//chapterで表示
	//auto save = MenuItemImage::create(
	//	"save.png",
	//	"save2.png",
	//	CC_CALLBACK_1(Control::save, this));
	//save->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	//save->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y));
	//auto menu = Menu::create(save, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1, "save");

	//継承先のinitFieldで記述
	//auto help = Sprite::create("help.png");
	//help->setPosition(Vec2(origin.x + 30, origin.y + 30));
	//this->addChild(help, 1, "help");
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	//listener->onTouchBegan = [this](Touch* touch, Event* event) {
	//	if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
	//		auto explain = Sprite::create("explain.png");
	//		explain->setPosition(Director::getInstance()->getVisibleSize() / 2);
	//		this->addChild(explain, 5, "explain");
	//		auto listener2 = EventListenerTouchOneByOne::create();
	//		listener2->setSwallowTouches(true);
	//		listener2->onTouchBegan = [this](Touch* touch, Event* event) {
	//			return true;
	//		};
	//		listener2->onTouchEnded = [this](Touch* touch, Event* event) {
	//			removeChildByName("explain");
	//		};
	//		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, explain);
	//		return true;
	//	}
	//	return false;
	//};
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, help);

	auto novel = Novel::create();
	novel->addSentence(0,"","");
	novel->setEndTask(0);
	novel->setLogOnly();
	addChild(novel, 1, "log");

	//initFieldは継承先のクラスで作り、使うときに呼び出す。
	initField();

	//this->addChild(mFieldList["forest1"], 0, "field"); //initField()へ

	//継承先のinitField()で記述
	//auto item = Item::create();
	//this->addChild(item, 2, "item");

	auto msg = Label::createWithTTF("", FONT_NAME, 30);
	msg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 50));
	msg->setColor(Color3B::WHITE);
	msg->setOpacity(0.0f);
	this->addChild(msg, 3, "msg");
	auto msgArea = Sprite::create("msgArea.png");
	msgArea->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	msgArea->setOpacity(0.0f);
	this->addChild(msgArea, 2, "msgArea");

	//カーソルの状態をリセットする
	/*listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event) {  setCursor(0); return true; };
	listener->onTouchMoved = [=](Touch* touch, Event* event) {	setCursor(0);};	
	listener->onTouchEnded = [=](Touch* touch, Event* event) {};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, resetCursor);*/

	// フィールド名
	{
		auto back = Sprite::create("fieldName.png");
		back->setPosition(Director::getInstance()->getVisibleSize() / 2);
		back->setOpacity(0.0f);
		back->setBlendFunc(BlendFunc{ GL_SRC_ALPHA, GL_ONE });
		auto label = Label::createWithTTF("", FONT_NAME, 24);
		label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		label->setPosition(Vec2(854, 400));
		label->setOpacity(0.0f);
		label->setTextColor(Color4B::WHITE);
		label->enableOutline(Color4B::BLACK, 1);
		addChild(back, 1, "fname_back");
		addChild(label, 2, "fname_label");
	}
	
	return true;
}

void Control::update(float delta) {
	auto field = getChildByName("field");
	if (field->getChildByName("novel") /*&& ((MenuItemImage*)getChildByName("save"))->getOpacity() >= 255*/) {
		//((MenuItemImage*)getChildByName("save"))->setOpacity(0.0f);

		if (getChildByName("log"))
			removeChildByName("log");
	}
	else if (!field->getChildByName("novel")) {
		//((MenuItemImage*)getChildByName("save"))->setOpacity(255.0f);

		if (!getChildByName("log")) {
			auto novel = Novel::create();
			novel->addSentence(0, "", "");
			novel->setEndTask(0);
			novel->setLogOnly();
			addChild(novel, 1, "log");
		}
	}
}

void Control::save(int i,cocos2d::ValueMap data) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		std::stringstream str;
		str << FileUtils::getInstance()->getWritablePath() << i << "/";
		auto path = str.str();

		//現在いるフィールド&取得しているアイテム
		auto file = path + "saveData.plist";
		//ValueMap data;

		for (auto field : mFieldList) {
			if (field.second->getReferenceCount() > 1 && field.first != "AboutItem") {
				data["currentField"] = field.first;
				break;
			}
		}

		auto item = (Item*)getChildByName("item");
		item->saveItem(&data);

		//ヒントフラグ
		auto hint = (Hint*)getChildByName("hint");
		//data["hint"] = hint->getState();

		if (FileUtils::getInstance()->writeToFile(data, file))
		{
			CCLOG("データを%sに書き出しました。", file.c_str());
		}
		else
		{
			CCLOG("Ops!");
		}

		//フィールドごとのオブジェクトの状態
		for (auto field : mFieldList) {
			file = path + field.first + ".plist";
			if (FileUtils::getInstance()->writeToFile(((Field*)field.second)->saveField(), file))
			{
				CCLOG("データを%sに書き出しました。", file.c_str());
			}
			else
			{
				CCLOG("Ops!");
			}
		}

}

void Control::load(int i) {
	std::stringstream str;
	str << FileUtils::getInstance()->getWritablePath() << i << "/";
	auto path = str.str();

	//現在いるフィールド&取得しているアイテム
	auto file = path + "saveData.plist";

	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(file);
	if (data["currentField"].asString() != mFirstField)
		changeField(data["currentField"].asString());

	auto item = (Item*)getChildByName("item");
	item->loadItem(data);

	//ヒントフラグ
	//auto hint = (Hint*)getChildByName("hint");
	//hint->setState(data["hint"].asInt());

	//フィールドごとのオブジェクトの状態
	for (auto field : mFieldList) {
		file = path + field.first + ".plist";
		data.clear();
		data = FileUtils::getInstance()->getValueMapFromFile(file);
		field.second->loadField(data);
	}
}

//void Control::setCursor(int num) {
//	auto cursor = (Cursor*)this->getChildByName("cursor");
//	if (num != cursor->getCursorNum()) cursor->setCursorNum(static_cast<CursorID>(num));
//}

void Control::setCursor(Cursor::CursorID num) {
	auto cursor = (Cursor*)this->getChildByName("cursor");
	if (num != cursor->getCursorNum()) cursor->setCursorNum(num);
}

void Control::changeField(std::string s) {
	auto field = (Field*)getChildByName("field");
	field->setName("field_");
	field->FadeOut();
	mFieldList[s]->FadeIn();
	addChild(mFieldList[s], 0, "field");

	// フィールド名表示
	{
		auto action = Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), NULL);
		getChildByName("fname_back")->stopAllActions();
		getChildByName("fname_back")->runAction(action);
		((Label*)getChildByName("fname_label"))->setString(mFieldList[s]->getFieldName());
		getChildByName("fname_label")->stopAllActions();
		getChildByName("fname_label")->runAction(action->clone());
	}
}

void Control::showMsg(std::string s) {
	auto msg = (Label*)getChildByName("msg");
	auto msgArea = getChildByName("msgArea");

	msg->setString(s);
	msg->runAction(Sequence::create(FadeIn::create(0.5f), FadeIn::create(3.0f), FadeOut::create(0.5f), NULL));
	msgArea->runAction(Sequence::create(FadeIn::create(0.5f), FadeIn::create(3.0f), FadeOut::create(0.5f), NULL));
}

void Control::showAI(std::string itemName) {
	//CCLOG("super");
	if (getChildByName("AboutItem")) removeChildByName("AboutItem");
	auto ai = (SAboutItem*)mFieldList["AboutItem"];
	ai->setAboutItem(itemName);
	addChild(ai, 3, "AboutItem");
}

void Control::deleteAI() { removeChildByName("AboutItem"); }

//void Control::setHintState(int i) {
//	auto hint = (Hint*)getChildByName("hint");
//	hint->setState(i);
//}

bool Control::getExistObject(std::string field, std::string obj) {
	return mFieldList[field]->getExistObject(obj);
}

Field* Control::getField(std::string field) {
	return mFieldList[field];
}

void Control::pauseField() {
	auto field = (Field*)getChildByName("field");
	field->pauseEventListener();
}

void Control::resumeField() {
	auto field = (Field*)getChildByName("field");
	field->resumeEventListener();
}

bool Control::getEndFlag() { return mEndFlag; }
void Control::setEndFlag() {
	//mEndFlag = true; 
	this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([this] { mEndFlag = true; }), DelayTime::create(0.1), RemoveSelf::create(), NULL));
}

void Control::initField() {
	CCLOG("super");
	//mFieldList["forest1"] = Field1::create();
	//mFieldList["campus"] = Field2::create();

	//mFieldList["AboutItem"] = AboutItem::create();

	//for (auto it = mFieldList.begin(); it != mFieldList.end(); it++) {
	//	it->second->retain();
	//}
}

bool Hint::init() {
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//mState = 0;

	auto hint = Sprite::create("help.png");
	hint->setPosition(Vec2(origin.x + 30, origin.y + 30));
	this->addChild(hint, 1, "hint");
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()) &&
			!this->getChildByName("novel")) {
			return true;
		}
		return false;
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation())) {
			showHint();
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, hint);

	return true;
}

void Hint::update(float delta) {
	//ノベルの表示が終わっていたらタッチイベントを有効にする
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			removeChild(novel);
		}
		else {
			Control::me->setCursor(Cursor::NOVEL);
		}
	}
}

void Hint::showHint() {
	//継承先で記述
}

//void Hint::setState(int i) { mState = i; }
//int Hint::getState() { return mState; }