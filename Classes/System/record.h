#pragma once

#include "cocos2d.h"

class Record : public cocos2d::Layer
{
public:
	Record();
	virtual ~Record();
	//static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float delta);

	void save(std::function<void(int)> &data);

    CREATE_FUNC(Record);
private:
	int mPage, mSelectNum;
	std::function<void(int)> mSaveFunc;
	bool mMode; //0:ロード 1:セーブ

	void turnPage();
	void updateInfo();
	void load();
};
