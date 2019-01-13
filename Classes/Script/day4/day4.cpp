#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Sequence/Title.h"
#include "Script\day4\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;


namespace day4 {
	Scene* Day::createScene()
	{
		auto scene = Scene::create();
		auto layer = Day::create();
		layer->playFirst();
		scene->addChild(layer);
		return scene;
	}

	void Day::initChapter()
	{
		auto cursor = Cursor::create();
		cursor->setCursorNum(Cursor::NOVEL);
		this->addChild(cursor, 1, "cursor");

		//BGM
		AudioEngine::stopAll();

		mFuncNum = 0;
		mChapterNum = 4;


		//シナリオ
		mFuncList.push_back([this]() {
			mSituation = "呪縛";
			playSoundBS("SE/chapter.ogg");
			auto bg = Sprite::create("bg/chapter4.png");
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
			mSituation = "闇で出会って（ノベル）";
			AudioEngine::stopAll();
			playSoundBS("BGM/underground.ogg", true);

			auto novel = Novel::create();

			novel->setBg(0, "chara/remon_fallen.png");
			//novel->setCharaR(0, "chara/bandana1.png");
			//novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "え…君は…");
			novel->addSentence(0, "バンダナ", "確か…今朝学校で会った…");
			novel->addSentence(0, "継", "水無月檸檬さん……？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "………");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "意識はあるのか？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "………");
			novel->addSentence(0, "檸檬", "………ん…");
			novel->addSentence(0, "檸檬", "……うーん…");
			novel->addSentence(0, "檸檬", "…あれ…ここは……？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "あ、気が付いたみたいだね");
			novel->setBg(0, "aisle.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setCharaC(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/remon1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "あんたたちは…確か…");
			novel->addSentence(0, "檸檬", "って、どういうことなのッ！？なんで私がこんなところに閉じ込められてるのよ！！");
			novel->addSentence(0, "檸檬", "国家権力を使って私を消すつもりなのっ！？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "お、落ち着いて水無月さん…あんまり音を立てると誰か来ちゃうよ…");
			novel->addSentence(0, "継", "僕たちも同じくここに閉じ込められて、脱出の手立てを探しているところなんだ。");
			novel->addSentence(0, "継", "今、扉を開けるよ。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "なんだ、そうだったのね。");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ガチャガチャ…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "……あれ、開かない。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "は？？ホントに？？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "俺にやらせろ！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ガッシャンガッシャン！！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "バンダナ…！音！誰か来ちゃうって…！");
			novel->addSentence(0, "バンダナ", "どうやらカギをかけられたみたいだな。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "そんな…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "僕たちがカギを探してくるよ。水無月さんはここで待ってて。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "…早く帰ってきてちょうだいね。");

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "地下の迷宮で（探索）";
			if (!AudioEngine::getPlayingAudioCount())playSoundBS("BGM/underground.ogg", true);
			removeChildByName("cursor");

			auto control = (day4::Esc*)day4::Esc::createControl();
			addChild(control, 1, "control");

			return 1;
		});


		mFuncList.push_back([this]() {
			mSituation = "chapter4 end";
			AudioEngine::stopAll();

			auto origin = Director::getInstance()->getVisibleOrigin();
			auto visibleSize = Director::getInstance()->getVisibleSize();
			

			auto label = Label::createWithTTF("chapter2 end", FONT_NAME, 30);
			label->setPosition(Vec2(visibleSize.width - 70, 50));
			label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
			label->setColor(Color3B::WHITE);
			label->setOpacity(0.0f);
			label->runAction(Sequence::create(DelayTime::create(5.0f),FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), CallFunc::create([this] {
				//Director::getInstance()->replaceScene(TransitionFade::create(1.0f, day3::Day::createScene(), Color3B::WHITE));
			}), NULL));
			this->addChild(label, 3, "label");

			return 10;
		});
	}

}


