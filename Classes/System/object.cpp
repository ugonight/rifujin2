#pragma  execution_character_set("utf-8")
#include "object.h"

#include "control.h"
#include "item.h"

USING_NS_CC;

ObjectN::~ObjectN() {
	//CC_SAFE_RELEASE_NULL(mTouchEvent);
	//CC_SAFE_RELEASE_NULL(mAction);
}

bool ObjectN::init(){
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();

	//mAreaFlag = 0;
	mCursorNum = Cursor::INFO;
	mState = 0;

	mGetItem = mField = mMsg = "";
	mTouchTime = 0;

	mArea = Rect(0, 0, 0, 0);

	mTouchEvent = CallFunc::create([]() {return; });
	mTouchEvent->retain();

	mAction = DelayTime::create(0.0f);
	mAction->retain();

	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = CC_CALLBACK_2(ObjectN::touchOn, this); /*[&](Touch* touch, Event* event) {return true; };*/
	//listener->onTouchMoved = CC_CALLBACK_2(ObjectN::checkOn, this);
	//listener->onTouchEnded = CC_CALLBACK_2(ObjectN::touchOff, this);/* [=](Touch* touch, Event* event) {};*/
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//デフォルトで中央に表示
	this->setPosition(Director::getInstance()->getVisibleSize() / 2);

	return true;
}

void ObjectN::setArea(cocos2d::Rect rect) {
	mArea = rect; //Rect(x, y, w, h);
	//mAreaFlag = 1;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ObjectN::touchOn, this); /*[&](Touch* touch, Event* event) {return true; };*/
	// listener->setSwallowTouches(true); 
//listener->onTouchMoved = CC_CALLBACK_2(ObjectN::checkOn, this);
	listener->onTouchEnded = CC_CALLBACK_2(ObjectN::touchOff, this);/* [=](Touch* touch, Event* event) {};*/
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

//void ObjectN::checkOn(cocos2d::Touch* touch, cocos2d::Event* event) {
//	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
//		//Control::me->setCursor(mCursorNum);		
//	}
//	else {
//		//Control::me->setCursor(0);
//	}
//
//}

bool ObjectN::touchOn(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
		//Control::me->setCursor(mCursorNum);	//カーソル変化はフィールドで行う
		
		//範囲がタッチされた時
		mTouchTime = 1;

		return true;
	}
	else {
		//Control::me->setCursor(0);
	}
	return false;
}

void ObjectN::touchOff(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (mArea.containsPoint(Vec2(touch->getLocationInView().x, touch->getLocationInView().y))) {
		if (mTouchTime > 0 && mTouchTime < 30) {

			//フィールド移動イベント
			if (mField != "" && getParent()->getOpacity() == 255) {
				Control::me->changeField(mField);
			}

			//その他のイベント
			//mTouchEvent();
			runAction(mTouchEvent);

			//メッセージイベント
			if (mMsg != "") {
				Control::me->showMsg(mMsg); 
			}

			//アイテムゲットイベント
			if (mGetItem != "") {
				Item::sharedItem()->getItem(mGetItem, touch->getLocation());
				runAction(RemoveSelf::create());
				Control::me->setCursor(Cursor::NOMAL);
			}
		}
	}

	mTouchTime = 0;
}

//void ObjectN::setTouchEvent(void (*event)()){
//	mTouchEvent = event;
//}

//void ObjectN::setCursor(int i) { mCursorNum = i; }
void ObjectN::setCursor(Cursor::CursorID i) { mCursorNum = i; }
void ObjectN::setState(int s) { mState = s; }
void ObjectN::setItemGetEvent(std::string s) { mGetItem = s; }
void ObjectN::setFieldChangeEvent(std::string s) { mField = s; }
void ObjectN::setMsg(std::string s) { mMsg = s; };

//void ObjectN::setTouchEvent(void func()) { mTouchEvent = func; }
void ObjectN::setTouchEvent(cocos2d::CallFunc *func) { CC_SAFE_RELEASE_NULL(mTouchEvent); mTouchEvent = func; mTouchEvent->retain(); }
void ObjectN::setAction(cocos2d::Action *act) { CC_SAFE_RELEASE_NULL(mAction); mAction = act; mAction->retain(); }
void ObjectN::addCanUseItem(std::string itemName) { mCanUseItemList.push_back(itemName); }
void ObjectN::removeCanUseItem(std::string itemName) {
	int i = 0;
	for (auto item : mCanUseItemList) {
		if (item == itemName) {
			mCanUseItemList.erase(mCanUseItemList.begin() + i);
			break;
		}
		i++;
	}
}

int ObjectN::getState() { return mState; }
std::string ObjectN::getMsg() { return mMsg; }
std::string ObjectN::getField() { return mField; }
cocos2d::Rect ObjectN::getArea() { return mArea; }
//int ObjectN::getCursor() { return mCursorNum; }
Cursor::CursorID ObjectN::getCursor() { return mCursorNum; }
bool ObjectN::getCanUse() {
	for (auto name : mCanUseItemList) {
		if (name == Item::sharedItem()->getSelectedItem()) return true;
	}
	return false;
}
std::vector<std::string> ObjectN::getCanUseItemList() { return mCanUseItemList; }

void ObjectN::update(float delta) {
	if (mTouchTime > 0) mTouchTime++;
}

void ObjectN::runObjectAction() {
	runAction(mAction);
}

void ObjectN::resumeEventListener() {
	if (mArea.size.width > 0 || mArea.size.height > 0) {
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(ObjectN::touchOn, this);
		listener->onTouchEnded = CC_CALLBACK_2(ObjectN::touchOff, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}
}