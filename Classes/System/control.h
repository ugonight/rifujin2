#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"
#include "cursor.h"
#include "object.h"
#include "field.h"

class Field;

class Control : public cocos2d::Scene {
protected:	
	bool mEndFlag;
	std::map<std::string, Field*> mFieldList;

	std::string mFirstField;

public:
	virtual ~Control();
	virtual void initField();

	void setCursor(Cursor::CursorID num);	//int num
	//void setCursor(int num);
	void changeField(std::string field);
	void showMsg(std::string msg);
	void showAI(std::string itemName);
	void deleteAI();
	//void setHintState(int i);

	void pauseField();
	void resumeField();

	bool getExistObject(std::string field, std::string obj);
	Field* getField(std::string field);

	bool getEndFlag();
	void setEndFlag();

	virtual bool init();
	virtual void update(float delta);

	void load(int dataNum);
	void save(int dataNum, cocos2d::ValueMap data);

	static Control* me;

	CREATE_FUNC(Control);
};

class Hint : public cocos2d::Layer {
protected:
	//int mState;
public:
	virtual bool init();
	virtual void update(float delta);

	virtual void showHint();

	//void setState(int i);
	//int getState();

	CREATE_FUNC(Hint);
};

//他フィールドのオブジェクトの状態を取得
inline int getObjState(std::string field, std::string obj) {
	return Control::me->getField(field)->getObject(obj)->getState();
}