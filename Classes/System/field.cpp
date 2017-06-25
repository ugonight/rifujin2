#pragma  execution_character_set("utf-8")
#include "field.h"

#include "object.h"
#include "item.h"
#include "control.h"
#include "novel.h"

USING_NS_CC;

Field::~Field() {
	for (auto obj : mObjectList) {
		CC_SAFE_RELEASE_NULL(obj.second);
	}
}


bool Field::init() {
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();

	initField();

	//�J�[�\���ω�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		changeCursor(touch);
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		changeCursor(touch);
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


#ifdef _DEBUG 
	// �^�b�`�|�C���g�̕\��
	for (auto obj : mObjectList) {
		Sprite* square = Sprite::create();
		square->setTextureRect(obj.second->getArea());
		square->setPosition(obj.second->getArea().getMidX(), Director::getInstance()->getVisibleSize().height - obj.second->getArea().getMidY());
		square->setColor(Color3B::RED);
		square->setOpacity(100.0f);
		this->addChild(square, 9);
	}
#endif

	return true;
}

void Field::changeCursor(cocos2d::Touch *touch) {
	Cursor::CursorID cursorNum = Cursor::NOMAL;
		for (auto obj : mObjectList) {
			if (obj.second->getArea().containsPoint(touch->getLocationInView()) &&
				getChildByName(obj.first)) {
				if (obj.second->getCanUse()) {
					cursorNum = Cursor::CANUSE;
				}
				else {
					cursorNum = obj.second->getCursor();
				}
				break;
			}
		}
		
		Control::me->setCursor(cursorNum);
}

void Field::initField() {
	//�I�u�W�F�N�g��z�u������
}

void Field::update(float delta) {
	//�m�x���̕\�����I����Ă�����^�b�`�C�x���g��L���ɂ���
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			//resumeEventListener();
			removeChild(novel);
		}
		else {
			Control::me->setCursor(Cursor::NOVEL);
		}
	}
}

void Field::addObject(ObjectN* obj, std::string s, int z, bool addchild){
	mObjectList[s] = obj;
	obj->retain();	
	obj->setZOrder(z);
	if (addchild) this->addChild(obj, z, s);
}

bool Field::getExistObject(std::string s) {
	return mObjectList[s]->getReferenceCount() > 1;
}

ObjectN* Field::getObject(std::string s) {
	return mObjectList[s];
}

void Field::FadeOut(){
	this->setCascadeOpacityEnabled(true);
	this->pauseEventListener();
	this->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
}

void Field::FadeIn() {
	this->setCascadeOpacityEnabled(true);
	//this->resumeEventListener();
	this->setOpacity(0.0f);
	this->runAction(Sequence::create(FadeIn::create(0.5f),
		CallFunc::create([this] {
		this->resumeEventListener();
		this->scheduleUpdate();
		for (auto it : this->getChildren()) {
			it->scheduleUpdate();
		}
	}), CallFunc::create(CC_CALLBACK_0(Field::changedField, this)), NULL));
	
}

void Field::changedField() {
	//���݂̃t�B�[���h�Ɉړ������Ƃ��ɌĂяo����鏈��������
}

void Field::pauseEventListener() {
	//for (auto it : this->getChildren()) {
	//	//it->second->setEventListenerEnabled(false);
	//	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//	dispatcher->pauseEventListenersForTarget(it);
	//}
	for (auto it : mObjectList) {
		it.second->getEventDispatcher()->setEnabled(false);
	}
}

void Field::resumeEventListener() {
	//for (auto it : this->getChildren()) {
	//	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//	dispatcher->resumeEventListenersForTarget(it);
	//}
	for (auto it : mObjectList) {
		it.second->getEventDispatcher()->setEnabled(true);
	}
}

cocos2d::ValueMap Field::saveField() {
	ValueMap data;
	for (auto obj : mObjectList) {
			data[obj.first + "_visible"] = getChildByName(obj.first);//obj.second->getReferenceCount() > 1;		//addChild()����Ă邩
			data[obj.first + "_state"] = obj.second->getState();					//���
			data[obj.first + "_msg"] = obj.second->getMsg();						//���b�Z�[�W
			data[obj.first + "_texture"] = obj.second->getTexture()->getPath();			//�C���[�W
			data[obj.first + "_field"] = obj.second->getField();	//�ړ���t�B�[���h
			data[obj.first + "_opacity"] = (float)obj.second->getOpacity();	//�����x
			data[obj.first + "_cursor"] = static_cast<int>(obj.second->getCursor());	//�J�[�\��
	}
	return data;
}

void Field::loadField(cocos2d::ValueMap data) {
	for (auto obj : mObjectList) {
		if (data[obj.first + "_visible"].asBool()) {
			if (!this->getChildByName(obj.first)) {	//������Ԃŏ����Ă��鎞
				addChild(obj.second, obj.second->getLocalZOrder(), obj.first);
			}
		}
		else {
			if (data[obj.first + "_visible"].isNull()) continue;	//�Z�[�u�f�[�^�ɓo�^����ĂȂ������疳��
			if (this->getChildByName(obj.first)) {	//������Ԃŕ\������Ă��鎞
				removeChild(obj.second);
			}
		}
		//���
		obj.second->setState(data[obj.first + "_state"].asInt());
		//���b�Z�[�W
		obj.second->setMsg(data[obj.first + "_msg"].asString());
		//�C���[�W
		obj.second->setTexture(data[obj.first + "_texture"].asString());
		//�t�B�[���h
		obj.second->setFieldChangeEvent(data[obj.first + "_field"].asString());
		//�����x
		obj.second->setOpacity(data[obj.first + "_opacity"].asFloat());
		//�J�[�\��
		obj.second->setCursor(static_cast<Cursor::CursorID>(data[obj.first + "_cursor"].asInt()));
	}
}