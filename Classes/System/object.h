#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"	

#include "cursor.h"

class ObjectN : public cocos2d::Sprite {
	//bool mAreaFlag;	//タッチエリアが存在するか
	cocos2d::Rect mArea;
	Cursor::CursorID mCursorNum;
	int mState;	//状態・フラグ的なもの
	std::vector<std::string> mCanUseItemList;	//その場所で使えるアイテム

	std::string mGetItem;	//タッチ時に入手するアイテム
	std::string mField;		//移動先のフィールド
	std::string mMsg;		//タッチ時に表示するメッセージ

	//タッチ時のイベント
	//void(*mTouchEvent)();
	cocos2d::CallFunc *mTouchEvent;
	//オブジェクトのアニメ―ション
	cocos2d::Action *mAction;

	int mTouchTime;

	//カーソルイベント
	//void checkOn(cocos2d::Touch* touch, cocos2d::Event* event);
	bool touchOn(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchOff(cocos2d::Touch* touch, cocos2d::Event* event);


public:
	virtual ~ObjectN();

	virtual bool init();
	virtual void update(float delta);

	void setArea(cocos2d::Rect rect);	//(int x, int y, int w, int h)
	//void setCursor(int cursorNum);
	void setCursor(Cursor::CursorID cursorNum);
	void setState(int state);
	void setItemGetEvent(std::string itemName);
	void setFieldChangeEvent(std::string fieldName);
	void setMsg(std::string msg);

	//void setTouchEvent(void (*func)());
	void setTouchEvent(cocos2d::CallFunc *func);
	void setAction(cocos2d::Action *act);
	void addCanUseItem(std::string itemName);
	void removeCanUseItem(std::string itemName);

	int getState();
	std::string getMsg();
	std::string getField();
	cocos2d::Rect getArea();
	//int getCursor();
	Cursor::CursorID getCursor();
	bool getCanUse();
	std::vector<std::string> getCanUseItemList();

	void resumeEventListener();
	void runObjectAction();

	CREATE_FUNC(ObjectN);
};
