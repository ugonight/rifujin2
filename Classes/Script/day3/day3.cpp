#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Sequence/Title.h"
#include "Script\day3\fieldDef.h"
#include "Script\day4\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;


namespace day3 {
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
		mChapterNum = 3;

		//シナリオ
		mFuncList.push_back([this]() {
			mSituation = "逃走";
			playSoundBS("SE/chapter.ogg");
			auto bg = Sprite::create("bg/chapter3.png");
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
			mSituation = "とある昔話で（ノベル）";
			playSoundBS("BGM/folklore.ogg", true);
			setGetMusic(6);

			auto novel = Novel::create();

			novel->setBg(0,"bg/book.png");
			novel->addEvent(0, CallFunc::create([this] {setGetStill(10); }));
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "昔々魔界王国に、ドラゴン族が住んでいる集落がありました。");
			novel->addSentence(0, "", "ドラゴン族には、特殊能力「探知」を持つものが多くいて、度々鉱山に宝石を採掘してきてはそれを売って生活していました。");
			novel->addSentence(0, "", "ドラゴン族は、その特徴的な角や翼から恐ろしい印象がありましたが、実際はとても温厚な種族でした。");
			novel->addSentence(0, "", "なんでも、ドラゴン族には古くから「決して怒りを感じてはならない」と言うしきたりがあったとか。");
			novel->addSentence(0, "", "そんなドラゴン族の集落に、ある男女がいました。");
			novel->addSentence(0, "", "その男女のドラゴン族は幼馴染で、女は男のことが大好きでした。");
			novel->addSentence(0, "", "しかしある日、集落で一番の好青年だった男は、集落に視察に来た王族の女に見惚れられ、城へ連れていかれました。");
			novel->addSentence(0, "", "それから暫く経ったある日、ドラゴン族の集落に男が結婚した旨の通達が来て、ドラゴン族の女は男への想いを諦められずも「あの人が幸せなら…」とその涙をのみました。");
			novel->addSentence(0, "", "更に数多の年月が経ったある日、集落に「男が死んだ」と言う噂が流れ始めました。");
			novel->addSentence(0, "", "いてもたってもいられなくなったドラゴン族の女は城へ向かいます。");
			novel->addSentence(0, "", "そこでは男の葬儀が行われていました。");
			novel->addSentence(0, "", "女は民衆を掻き分け、男の亡骸にすがり付いて泣き叫びます。");
			novel->addSentence(0, "", "遺体は酷く損傷しており、男の面影は見る影もありませんでした。");
			novel->addSentence(0, "", "泣き叫ぶドラゴン族の女を見下ろして、王族の女は言いました。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "王族の女", "そいつは最後まで馬鹿な男だったよ。");
			novel->addSentence(0, "王族の女", "あたしが頼んだら危険な火山の洞窟に宝石を探しにいってくれてね、マグマに焼かれて死んだのさ。最初から利用されていただけとも知らないでさ。");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "高らかに笑う王族の女を見て、ドラゴン族の女は生まれて初めて心からの怒りを感じました。");
			novel->setBg(0, "");
			novel->addPauseEvent(0, Sequence::createWithTwoActions(
				CallFunc::create([this] {
				auto spr = Sprite::create("chara/dragon_soul.png");
				spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
				spr->setOpacity(0.0f);
				spr->runAction(Sequence::create(DelayTime::create(1.0f), FadeIn::create(0.25f), FadeOut::create(0.25f), FadeIn::create(0.25f), FadeOut::create(0.25f), FadeIn::create(0.25f), FadeOut::create(0.25f), DelayTime::create(0.5f), RemoveSelf::create(), NULL));
				addChild(spr, 0, "bg");
			}),
				DelayTime::create(3.0f)
			));
			novel->addEvent(0, CallFunc::create([this] {setGetStill(11); }));
			novel->addSentence(0, "", "その時、ドラゴン族の女の中を何かが駆け巡ります。");
			novel->setBg(0, "chara/dragon_soul.png");
			novel->addSentence(0, "", "一族が代々封印してきた龍の魂が");
			novel->addSentence(0, "", "気が付いたら王族の女は黒焦げになっていました。");
			novel->addSentence(0, "", "ドラゴン族の女はすぐさま捕らえられ、断頭台に乗せられました。");
			novel->addSentence(0, "", "やがて、「ドラゴン族は人を殺すことができる危険な種族」と言う認識が国中に広まり、残りのドラゴン族も次々と捕らえられてしまいます。");
			novel->addSentence(0, "", "こうして、ドラゴン族は迫害され、その個体数は大きく減ってしまいました。");
			novel->addSentence(0, "", "かわいそうな首のないドラゴン族の女の魂は、今でもどこかで復讐の炎を燃やしているそうです。");
			novel->addSentence(0, "", "おしまい");

			novel->setEndTask(0);
			this->addChild(novel, 0, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "待ち合わせに遅れて（ノベル）";
			AudioEngine::stopAll();

			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "継達がさらわれる少し後の教室にて");
			novel->addEvent(0, CallFunc::create([this] {
				playSoundBS("BGM/school.ogg", true);
			}));
			novel->setBg(0, "obj/classroom.png");
			novel->setCharaL(0, "chara/suama1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "ごっめーん！！遅くなったー！！！");
			novel->addSentence(0, "寿甘", "…ってあれ…？");
			novel->addSentence(0, "寿甘", "二人ともいないじゃん！！");
			novel->addSentence(0, "寿甘", "一緒に帰ろうって言ったのになんでいないのよー！！");
			novel->addSentence(0, "寿甘", "あんなやつら、ストーカーにさらわれてあんなことやこんなことされちゃえばいいのよー！！");
			novel->addSentence(0, "寿甘", "…自分のこと棚に上げといて何を言ってるんだ私は");
			novel->addSentence(0, "寿甘", "うーん…先に校門で待ってるとか、どっかで暇つぶしでもしてるとかなのかな…");
			novel->addSentence(0, "寿甘", "ちょっくら探してみますか！");

			novel->setEndTask(0);
			this->addChild(novel, 0, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "二人を探して（探索）";
			if (!AudioEngine::getPlayingAudioCount())playSoundBS("BGM/school.ogg", true);
			removeChildByName("cursor");

			auto control = (day3::Esc*)day3::Esc::createControl();
			//control->initField();	//必ず呼ぶ
			addChild(control, 1, "control");

			return 1;
		});


		mFuncList.push_back([this]() {
			mSituation = "chapter3 end";
			AudioEngine::stopAll();

			auto origin = Director::getInstance()->getVisibleOrigin();
			auto visibleSize = Director::getInstance()->getVisibleSize();

			auto label = Label::createWithTTF("chapter3 end", FONT_NAME, 30);
			label->setPosition(Vec2(visibleSize.width - 70, 50));
			label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
			label->setColor(Color3B::WHITE);
			label->setOpacity(0.0f);
			label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), CallFunc::create([this] {
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, day4::Day::createScene(), Color3B::WHITE));
			}), NULL));
			this->addChild(label, 3, "label");

			// チャプター終了フラグを立てる。
			UserDefault::getInstance()->setBoolForKey("chap3end", true);

			return 10;
		});
	}

}

