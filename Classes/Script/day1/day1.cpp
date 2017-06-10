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
		layer->playFirst();
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
		mChapterNum = 1;

		//シナリオ
		mFuncList.push_back([this]() {
			mSituation = "Chapter1 : 狂愛";
			AudioEngine::play2d("SE/chapter.ogg");
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
			mSituation = "学校に着いて（ノベル）";
			AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setBg(0, "obj/gate.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「学校に着いたね、たまには歩きもいいもんだ」");
			novel->setCharaC(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ「…！(ｿﾞｸｯ)」");
			novel->setCharaR(0, "chara/rias1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス｢バンダナ様……♥｣");
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘｢あれ？確かあの子……ドラゴン族の｣");
			novel->setCharaC(0, "chara/remon1.png");
			novel->addSentence(0, "檸檬｢こら！！リアス！！｣");
			novel->setCharaR(0, "");
			novel->addSentence(0, "リアス｢ヒッ！｣");
			novel->addSentence(0, "檸檬｢まったくもうあの子は人を追いかけ回して……ごめんなさいね｣");
			novel->addSentence(0, "寿甘「あなたは確か…水無月　檸檬（みなつき　れもん）ちゃんかな？」");
			novel->addSentence(0, "檸檬「そうよ、継様のせいで万年学年筆記テスト2位の人よ」");
			novel->addSentence(0, "檸檬「さっきのドラゴン族の子はリアス・アレキサンドライト。ああ見えていい子なのよ？」");
			novel->setFontColor(0, Color3B::BLUE);	
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ「お、おう」");
			novel->setCharaC(0, "");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬「リアスー！待ちなさーい！」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「…最近嫌な視線を感じると思ったらあいつか？」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘「そうなの！？」");
			novel->setCharaC(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「授業開始まで、まだ時間があるね。」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘「ちょっと学校の中を散歩していこっか！」");

			novel->setEndTask(0);
			this->addChild(novel, 0, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "学校に着いて（探索）";
			if (!AudioEngine::getPlayingAudioCount())AudioEngine::play2d("BGM/school.ogg", true);
			removeChildByName("cursor");

			auto control = (day1::Esc*)day1::Esc::createControl();
			//control->initField();	//必ず呼ぶ
			addChild(control, 1, "control");

			return 1;
		});
	}

}

