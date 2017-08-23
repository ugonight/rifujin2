#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Sequence/Title.h"
#include "Script\day2\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
USING_NS_CC;


namespace day2 {
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
		AudioEngine::pauseAll();

		mFuncNum = 0;
		mChapterNum = 2;

		//シナリオ
		mFuncList.push_back([this]() {
			mSituation = "怪奇";
			AudioEngine::play2d("SE/chapter.ogg");
			auto bg = Sprite::create("bg/chapter2.png");
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
			mSituation = "暗闇の中で（ノベル）";
			//AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「うぅ……ここは…？」");
			novel->addSentence(0, "継「！？」");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "僕は、この感じを覚えている。");
			novel->addSentence(0, "無機質な石の臭いと、生臭い鉄に似た臭い。");
			novel->addSentence(0, "息苦しさを増していく閉鎖空間…そう、きっとここは…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「うぐッ……けほっ……ゴホッゴホッ………」");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "僕は堪らず咽てしまう");
			novel->addSentence(0, "ぎゅっと瞑った目を恐る恐る開くとそこは…");
			novel->setCharaL(0, "");
			novel->addEvent(0, CallFunc::create([this] {
				auto bg = Sprite::create("prison.png");
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
				bg->setOpacity(0.0f);
				bg->runAction(FadeIn::create(5.0f));
				addChild(bg,0,"bg0");
				bg = Sprite::create("bandana_hurted.png");
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
				bg->setOpacity(0.0f);
				bg->runAction(FadeIn::create(5.0f));
				addChild(bg, 1, "bg1");
				
				AudioEngine::play2d("BGM/fear.ogg", true);
			}));
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「バンダナ…！！！」");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "目覚める前の悪夢が現実のものだったのだと理解すると、僕は大きな絶望に包まれた。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「おい！！しっかりしろよッ！！！！バンダナ！！！バンダナ…ッ！！！！」");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "徐々に昔の記憶が甦り、理性が失われていく。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継「ごめんなさい……僕がしっかりしてなかったから…僕のせいで……ごめんなさい…ごめんなさい…」");
			novel->addSentence(0, "継「僕のせいで、バンダナまで居なくなったら…僕は…僕は……」");
			novel->addEvent(0, CallFunc::create([this] {
				if (AudioEngine::getPlayingAudioCount())AudioEngine::stopAll();
			}));
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "バンダナ「つぐるん」");
			novel->addSentence(0, "継「ごめんなさい…ごめんなさい…ごめんなさい…」");
			novel->addSentence(0, "バンダナ「おい継、しっかりしろ」");
			novel->addSentence(0, "継「…うわああああああ！！！ぞ、ゾンビだ！！！！」");
			novel->addSentence(0, "バンダナ「死んでねえよ！！」");
			novel->addSentence(0, "バンダナ「…心配かけて悪かった。さっきまで気絶してたんだ」");
			novel->addSentence(0, "継「本当に大丈夫なの…？こんなに酷い怪我で、出血もしているのに…」");
			novel->addSentence(0, "バンダナ「大丈夫だ、こんな怪我大したことない。俺様を何だと思ってるんだ」");
			novel->addSentence(0, "バンダナ「ただ、俺を射った矢に毒が塗られてたみたいでな…身動きができないんだ」");
			novel->addSentence(0, "継「そうなんだ…何か傷の手当てをしたいな」");
			novel->addSentence(0, "継「見たところ、ここは何かの施設の牢屋に見えるね。僕たちを襲った奴の本拠地なら、解毒剤もあるかもしれない。僕、探してくるよ」");
			novel->addSentence(0, "バンダナ「おお、なるほどな。お前の方は何ともないのか？」");
			novel->addSentence(0, "継「うん、僕は眠らされただけみたいだから、いくらでも動けるよ。」");
			novel->addSentence(0, "バンダナ「そうか、いつも通りの冷静さを取り戻したな。」");
			novel->addSentence(0, "バンダナ「お前は、全然できないヤツなんかじゃないんだ。その力で、俺を救ってくれ。」");
			novel->addSentence(0, "継「やってみるよ、バンダナ。」");
			novel->addSentence(0, "継「まずは、この部屋を出る方法を見つけよう」");
			novel->addEvent(0, CallFunc::create([this] {
				getChildByName("bg0")->runAction(Sequence::create(FadeOut::create(0.5), RemoveSelf::create(), NULL));
				getChildByName("bg1")->runAction(Sequence::create(FadeOut::create(0.5), RemoveSelf::create(), NULL));
			}));

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "地下の迷宮で（探索）";
			//if (!AudioEngine::getPlayingAudioCount())AudioEngine::play2d("BGM/school.ogg", true);
			removeChildByName("cursor");

			auto control = (day2::Esc*)day2::Esc::createControl();
			addChild(control, 1, "control");

			return 1;
		});

	}



}

