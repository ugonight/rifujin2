#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Script\day1\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;


namespace day1 {
	Scene* Day::createScene()
	{
		auto scene = Scene::create();
		auto layer = Day::create();
		scene->addChild(layer);
		return scene;
	}

	void Day::initChapter()
	{
		auto cursor = Cursor::create();
		cursor->setCursorNum(8);
		this->addChild(cursor, 1, "cursor");

		//BGM
		AudioEngine::pauseAll();

		mFuncNum = 0;

		//シナリオ
		mFuncList.push_back([this]() {
			auto bg = Sprite::create("bg/chapter1.png");
			bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
			bg->setOpacity(0.0f);
			bg->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(4.0f), FadeOut::create(0.5f), CallFunc::create([this] {
				mFuncType = mFuncList[++mFuncNum]();
				removeChildByName("bg");
			}), NULL));
			addChild(bg, 0, "bg");

			return 10;
		});

		mFuncList.push_back([this]() {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::BLACK);

			novel->setBg(0, "bg/book.png");
			novel->addSentence(0, "幼いころずっと読んでいた大好きな絵本");
			novel->addSentence(0, "絵本の中のあの子が大好きでなんどもなんども読み返した");
			novel->addSentence(0, "大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー");
			novel->setBg(0, "");
			novel->addSentence(0, "私だけの物にしたいと思った");

			novel->setEndTask(0);
			this->addChild(novel, 0, "novel");

			return 0;
		});
	}

}

