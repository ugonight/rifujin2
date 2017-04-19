#pragma once
#include "cocos2d.h"

#include "object.h"

class Item : public cocos2d::Layer {
public:
	virtual ~Item();

	virtual bool init();
	virtual void update(float delta);

	void getItem(std::string itemName,cocos2d::Point point);

	void deleteItem(std::string itemName);
	std::string getSelectedItem();

	void saveItem(cocos2d::ValueMap* map);
	void loadItem(cocos2d::ValueMap map);

	static Item* sharedItem();



	CREATE_FUNC(Item);
protected:
	class ItemObj{
		std::string imgName;
		bool getFlag = 0;
		cocos2d::Layer* aiLayer;	//AI�ŕ\������I�u�W�F�N�g��z�u���郌�C���[

	public:
		ItemObj(std::string imageName) {
			imgName = imageName;
		}

		std::string getImage() { return imgName; };
		void setGetFlag(bool i) { getFlag = i; };
		bool getGetFlag() { return getFlag; };
		
		//aiLayer��init()���`����֐��i�H�j�����
		//�킴�킴�A�C�e�����ƂɃN���X�����̂��߂�ǂ��Ȃ̂ŁA�ȒP�ɒ�`�ł���悤�ɂ������B

	};

	std::map<std::string, ItemObj*> mItemList;
	virtual void initItem();

	bool mShowWindow;
	bool mShowAboutItem;
	int mWindowW;
	int mTouchTime;
	std::string mSelectedItem;

	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void moveEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void endEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void showAboutItem();
};