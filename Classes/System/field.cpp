#pragma  execution_character_set("utf-8")
#include "field.h"

#include "object.h"
#include "item.h"
#include "control.h"
#include "novel.h"
#include "cursor.h"

USING_NS_CC;

Field::Field() :mFieldName("") {

}

Field::~Field() {
	for (auto obj : mObjectList) {
		//CC_SAFE_RELEASE_NULL(obj.second);
	}
	for (auto lis : mEventListenerList) {
		//CC_SAFE_RELEASE_NULL(lis.first);
		//CC_SAFE_RELEASE_NULL(lis.second);
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
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [this](Touch* touch, Event* event) {
	//	changeCursor(touch);
	//	return true;
	//};
	//listener->onTouchMoved = [this](Touch* touch, Event* event) {
	//	changeCursor(touch);
	//};
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	resetEventListener();


#ifdef _DEBUG 
	// �^�b�`�|�C���g�̕\��
	for (auto obj : mObjectList) {
		Sprite* square = Sprite::create();
		square->setTextureRect(obj.second->getArea());
		square->setPosition(obj.second->getArea().getMidX(), Director::getInstance()->getVisibleSize().height - obj.second->getArea().getMidY());
		square->setColor(Color3B::RED);
		square->setOpacity(50.0f);
		this->addChild(square, 9);
	}
#endif

	// �^�b�`�|�C���g�̃q���g��\�����郌�C���[
	auto layer = Layer::create();
	layer->setPosition(Vec2::ZERO);
	addChild(layer, 9, "pointHintLayer");

	return true;
}

void Field::changeCursor(cocos2d::Touch *touch) {
	Cursor::CursorID cursorNum = Cursor::NOMAL;
	bool loop = true;
	for (int z = 10; z > 0; z--) {	// ��ɂ�����̂�D��
		for (auto obj : mObjectList) {
			if (obj.second->getArea().containsPoint(touch->getLocationInView()) &&
				getChildByName(obj.first) &&
				obj.second->getLocalZOrder() == z) {
				if (obj.second->getCanUse()) {
					cursorNum = Cursor::CANUSE;
				}
				else {
					cursorNum = obj.second->getCursor();
				}
				loop = false;
				break;
			}
		}
		if (!loop) break;
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
	updateField();
}

void Field::updateField() {

}

void Field::addObject(ObjectN* obj, std::string s, int z, bool addchild){
	mObjectList[s] = obj;
	obj->retain();	
	//obj->setZOrder(z);
	obj->setLocalZOrder(z);
	if (addchild) this->addChild(obj, z, s);
}

bool Field::getExistObject(std::string s) {
	return mObjectList[s]->getReferenceCount() > 1;
}

ObjectN* Field::getObject(std::string s) {
	return mObjectList[s];
}

std::string Field::getFieldName() {
	return mFieldName;
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
		// �I�u�W�F�N�g�A�N�V����
		for (auto obj : mObjectList) {
			if (getChildByName(obj.first)) {
				obj.second->runObjectAction();
			}
		}

	}), CallFunc::create(CC_CALLBACK_0(Field::changedField, this)), NULL));


	// �|�C���g�q���g�̕\��
	if (UserDefault::getInstance()->getIntegerForKey("pHint", 1))
		initPointHint();
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
		it.second->resumeEventListener();	
	}

	resetEventListener();

	for (auto listener : mEventListenerList) {
		if (listener.first->getReferenceCount() <= 1) {
			auto lis = listener.first->clone();	// ���̂܂ܓo�^����Ɠ����Ă���Ȃ��̂ŃN���[����o�^
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(lis, listener.second);
		}
	}
}

void Field::resetEventListener(){
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
}

void Field::addOriginalEventListener(cocos2d::EventListener* listener, cocos2d::Node* node) {
	listener->retain();
	mEventListenerList.push_back(std::make_pair(listener, node));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

cocos2d::ValueMap Field::saveField() {
	ValueMap data; int i;
	for (auto obj : mObjectList) {
			data[obj.first + "_visible"] = getChildByName(obj.first);//obj.second->getReferenceCount() > 1;		//addChild()����Ă邩
			data[obj.first + "_state"] = obj.second->getState();					//���
			data[obj.first + "_msg"] = obj.second->getMsg();						//���b�Z�[�W
			data[obj.first + "_texture"] = obj.second->getTexture()->getPath();			//�C���[�W
			data[obj.first + "_field"] = obj.second->getField();	//�ړ���t�B�[���h
			data[obj.first + "_opacity"] = (float)obj.second->getOpacity();	//�����x
			data[obj.first + "_cursor"] = static_cast<int>(obj.second->getCursor());	//�J�[�\��
			i = 0;
			for (auto itemName : obj.second->getCanUseItemList()) {
				if (itemName != "") {
					data[obj.first + StringUtils::format("_canuse%d", i)] = itemName;
					i++;
				}
			}
	}
	return data;
}

void Field::loadField(cocos2d::ValueMap data) {
	int i; bool exist;
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
		//�g����A�C�e��
		i = 0; exist = 0;
		while (!data[obj.first + StringUtils::format("_canuse%d", i)].isNull()) {
			std::string itemName = data[obj.first + StringUtils::format("_canuse%d", i)].asString();
			for (auto name : obj.second->getCanUseItemList())  if (name == itemName) exist = 1;	//���łɒǉ�����Ă����疳��
			if (!exist) obj.second->addCanUseItem(itemName);
			i++;
		}
	}
}


void Field::initPointHint() {
	auto layer = getChildByName("pointHintLayer");
	layer->removeAllChildren();
	float delay = 0.0;
	int num = 0;
	// �t�B�[���h�ɃZ�b�g����Ă���object�̐����擾
	for (auto obj : mObjectList) if (this->getChildByName(obj.first)) if (obj.second->getArea().getMinX() != obj.second->getArea().getMaxX()) num++;
	// ��̃��C���[�ɂ���Ƀ��C���[����������\�����Ȃ�
	for (auto child : this->getChildren()) if (child->getLocalZOrder() > layer->getLocalZOrder()) return;

	// �^�b�`�|�C���g�̕\��
	for (auto obj : mObjectList) {
		if (this->getChildByName(obj.first)) {
			// �^�b�`�G���A���Ȃ��̂͏��O
			if (obj.second->getArea().getMinX() == obj.second->getArea().getMaxX())continue;

			auto ripple = Sprite::create();
			switch (obj.second->getCursor())
			{
			case Cursor::NOMAL:
				return;
			case Cursor::NEW:
				if (UserDefault::getInstance()->getIntegerForKey("pHint", 1) == 2)
					ripple->setTexture("pointHint_r.png");
				break;
			case Cursor::INFO:
				if (UserDefault::getInstance()->getIntegerForKey("pHint", 1) == 2)
					ripple->setTexture("pointHint_b.png");
				break;
			case Cursor::BACK:
			case Cursor::RIGHT:
			case Cursor::LEFT:
			case Cursor::CANUSE:
			case Cursor::FORWARD:
			case Cursor::ENTER:
				ripple->setTexture("pointHint_g.png");
				break;
			case Cursor::NOVEL:
				return;
			default:
				return;
			}
			ripple->setPosition(obj.second->getArea().getMidX(), Director::getInstance()->getVisibleSize().height - obj.second->getArea().getMidY());
			ripple->setOpacity(0.0f);
			ripple->setBlendFunc(BlendFunc{ backend::BlendFactor::SRC_ALPHA, backend::BlendFactor::ONE });
			layer->addChild(ripple, 1, obj.first);
			// �A�j���[�V����
			ripple->runAction(Sequence::create(
				DelayTime::create(delay),
				Spawn::createWithTwoActions(FadeIn::create(0.5f), EaseSineInOut::create(ScaleBy::create(0.5f,2.0f))),
				FadeOut::create(0.5f),
				DelayTime::create(5.0f),
				CallFunc::create([this, delay,num]() {
					if (delay == 0.1f * (num-1)) initPointHint();
				}),	// �ċA�Ń��[�v���X�V�Ή�
				NULL
			));

			delay += 0.1;
		}
	}
}