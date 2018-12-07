#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

//#include "object.h"
//#include "item.h"
//#include "control.h"
//#include "novel.h"

class ObjectN;

class Field : public cocos2d::Layer {
protected:
	std::map<std::string, ObjectN*> mObjectList;
	std::string mFieldName;
	void addObject(ObjectN* obj,std::string objName, int ZOder, bool addChild);
	std::vector<std::pair<cocos2d::EventListener*, cocos2d::Node*>> mEventListenerList;

	//void pauseEventListener();
	//void resumeEventListener();

public:
	Field();
	virtual ~Field();

	virtual bool init();
	virtual void update(float delta);

	void changeCursor(cocos2d::Touch *touch);

	bool getExistObject(std::string objName);
	ObjectN* getObject(std::string objName);
	std::string getFieldName();

	void FadeOut();
	void FadeIn();

	void pauseEventListener();
	void resumeEventListener();
	void resetEventListener();
	void addOriginalEventListener(cocos2d::EventListener* listener,cocos2d::Node* node);	// 3.16�Ή� initField����EventListener�Ɏg��

	cocos2d::ValueMap saveField();
	void loadField(cocos2d::ValueMap map);

	virtual void changedField();	// ���݂̃t�B�[���h�ɐ؂�ւ�������̃C�x���g
	virtual void initField();		// �t�B�[���h�ɃI�u�W�F�N�g��z�u
	virtual void updateField();		// �ǉ��ŉ����������Ƃ��puodate
	
	CREATE_FUNC(Field);

private:
	void initPointHint();
};


class SAboutItem : public Field {
public:
	virtual void initField() {}
	virtual void changedField() {}
	CREATE_FUNC(SAboutItem);
	virtual void setAboutItem(std::string itemName) {}
};