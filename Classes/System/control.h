#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

class Field;

class Control : public cocos2d::Scene {
protected:	
	bool mEndFlag;
	std::map<std::string, Field*> mFieldList;

	std::string mFirstField;

public:
	virtual ~Control();
	virtual void initField();

	void setCursor(int num);
	void changeField(std::string field);
	void showMsg(std::string msg);
	void showAI(std::string itemName);
	void deleteAI();
	
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

