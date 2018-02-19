#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Sequence/Title.h"
#include "Script\day1\fieldDef.h"
#include "Script\day2\fieldDef.h"

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
		cursor->setCursorNum(Cursor::NOVEL);
		this->addChild(cursor, 1, "cursor");

		//BGM
		AudioEngine::stopAll();

		mFuncNum = 0;
		mChapterNum = 1;

		//シナリオ
		mFuncList.push_back([this]() {
			mSituation = "狂愛";
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
			setGetMusic(2);
			AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setBg(0, "obj/gate.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "学校に着いたね、たまには歩きもいいもんだ");
			novel->setCharaC(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "…！(ｿﾞｸｯ)");
			novel->setCharaR(0, "chara/rias1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス", "バンダナ様……♥");
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "あれ？確かあの子……ドラゴン族の");
			novel->setCharaC(0, "chara/remon1.png");
			novel->addSentence(0, "檸檬", "こら！！リアス！！");
			novel->setCharaR(0, "");
			novel->addSentence(0, "リアス", "ヒッ！");
			novel->addSentence(0, "檸檬", "まったくもうあの子は人を追いかけ回して……ごめんなさいね");
			novel->addSentence(0, "寿甘", "あなたは確か…水無月　檸檬（みなつき　れもん）ちゃんかな？");
			novel->addSentence(0, "檸檬", "そうよ、継様のせいで万年学年筆記テスト2位の人よ");
			novel->addSentence(0, "檸檬", "さっきのドラゴン族の子はリアス・アレキサンドライト。ああ見えていい子なのよ？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "お、おう");
			novel->setCharaC(0, "");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "リアスー！待ちなさーい！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "…最近嫌な視線を感じると思ったらあいつか？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "そうなの！？");
			novel->setCharaC(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "授業開始まで、まだ時間があるね。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "ちょっと学校の中を散歩していこっか！");

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
		mFuncList.push_back([this]() {
			mSituation = "朝の騒動の後で（ノベル）";
			if (!AudioEngine::getPlayingAudioCount())AudioEngine::play2d("BGM/school.ogg", true);
			//AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setBg(0, "classroom.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/usawa1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "宇沢", "ふむふむ…かくかくしかじかでこういうわけだったのですか…");
			novel->addSentence(0, "宇沢", "リアスさんですねぇ…彼女、珍しいドラゴン族の末裔みたいで、おかしな宗教とか引き継いじゃってるみたいですよ？何されるかわかったもんじゃないですねぇ");
			novel->setCharaC(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "ソースは");
			novel->addSentence(0, "宇沢", "そ、ソース…？わたくしは目玉焼きには醤油ですよ。ソースなんてかける人の気が知れないですねぇ");
			novel->setCharaC(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "は？お前全国のソース派を敵に回したな？生きて帰れると思うなよ？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "宇沢", "ドラゴン族の呪いより恐ろしそうですねぇ…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "とにかく、今日は帰りもみんなで一緒に帰ろう。いいね？");
			novel->addSentence(0, "バンダナ", "まあ、用心に越したことはないか…何かあったら面倒くさいし");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaR(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "よし、じゃあ決まりね！先に帰ったら許さないんだから！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "あ、始業のチャイムが鳴ったよ。みんな席に着こう");

			novel->setEndTask(0);
			this->addChild(novel, 0, "novel");

			return 0;
		});
		mFuncList.push_back([this]() {
			mSituation = "放課後にて（ノベル）";
			//AudioEngine::stopAll();
			if (!AudioEngine::getPlayingAudioCount())AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::BLUE);
			novel->setBg(0, "classroom.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "ふぃー…学校、終わったな！");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "さっきの体育の授業でのバンダナ、すごかったよ。大活躍だったじゃないか");
			novel->addSentence(0, "バンダナ", "へへへ、まあな。");
			novel->addSentence(0, "継", "女子はまだ戻ってきてないみたいだね、寿甘が来るまで明日の予習でもしようかな");
			novel->addSentence(0, "バンダナ", "つぐるんは相変わらず真面目だな。よし、この際俺も勉強を教えてもらうか…");
			novel->addSentence(0, "バンダナ", "…ん？");
			novel->addSentence(0, "継", "どうしたの？");
			novel->addSentence(0, "バンダナ", "あー…なんだか急に催してきた…ちょっとトイレ行ってくるわ");
			novel->addSentence(0, "継", "ああ、うん。行ってらっしゃい");
			novel->setCharaR(0, "");
			novel->addSentence(0, "継", "…紙切れのようなものを見てた気がするけど、気のせいかな…");
			novel->setBg(0, "");
			novel->setCharaL(0, "");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "―――数十分後―――");
			novel->setBg(0, "classroom.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "…やっぱり、トイレにしてはちょっと遅いな。探しに行こう");
			novel->setBg(0, "corridor.png");
			novel->setCharaR(0, "chara/renji1.png");
			novel->addSentence(0, "継", "あ、神北くん");
			novel->addSentence(0, "恋巳", "どうした、継殿");
			novel->addSentence(0, "継", "バンダナの奴、見なかった？");
			novel->addSentence(0, "恋巳", "おお、バンダナ殿だったら、さっき校庭の方へ出ていったぞ");
			novel->addSentence(0, "継", "え…？あいつ、先に帰っちゃったの…？");
			novel->addSentence(0, "継", "ありがとう、神北くん。");
			novel->setCharaL(0, "");
			novel->addSentence(0, "恋巳", "お、おう…");
			novel->setBg(0, "");
			novel->setCharaR(0, "");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "その後、僕は校庭を探し回ったけど、バンダナは見付からなかった");
			novel->setBg(0, "entrance.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "どこ行ったんだろう…");
			novel->addSentence(0, "継", "…やっぱり、本当に先に帰っちゃったのかな");
			novel->addSentence(0, "継", "いや、あいつに何かあったのかもしれない");
			novel->addSwitchEvent(0, 1, "ここにとどまる", 2, "このまま帰る");
			novel->addSentence(0, "継", "どうするか");

			novel->addSentence(1, "継", "まだ探してないとこがあるはずだ。");
			novel->addSentence(1, "継", "もしかしたら、校舎裏とかにいるかもしれない");
			novel->addSentence(1, "継", "行ってみよう");
			novel->addEvent(1, CallFunc::create([this] {
				if (AudioEngine::getPlayingAudioCount())AudioEngine::stopAll();
			}));
			novel->setBg(1, "");
			novel->addSentence(1, "継", "薄暗くなってきたな…");
			novel->addSentence(1, "継", "…ん？");
			novel->setFontColor(1, Color3B::BLACK);
			novel->addSentence(1, "", "裏庭に回り込んだ僕はすぐに異様な空気を感じた");
			novel->addSentence(1, "", "壁の隅の暗がりに目を凝らしてみると、そこにいたのは…");
			novel->addEvent(1, CallFunc::create([this] {
				AudioEngine::play2d("BGM/fear.ogg", true);
				setGetMusic(4);
			}));
			novel->setFontColor(1, Color3B::BLUE);
			novel->setCharaL(1, "");
			novel->setBg(1, "chara/scene6.png");
			novel->addEvent(1, CallFunc::create([this] {setGetStill(4); }));
			novel->addSentence(1, "継", "バンダナ…？");
			novel->addSentence(1, "継", "おい…しっかりしろ…！");
			novel->addSentence(1, "継", "どうしよう…怪我をしている…");
			novel->setFontColor(1, Color3B::BLACK);
			novel->addSentence(1, "", "彼の腹部には、何者かから攻撃を受けてできたような、刺し傷があった");
			novel->addSentence(1, "", "魔界王国ではハンコの制御によって、人を傷つけるような魔法は使えず、また、全ての器物が人を傷つけることのないようになっているはずなのだ。");
			novel->addSentence(1, "", "こんな事ができるのは…");
			novel->setFontColor(1, Color3B::BLUE);
			novel->addSentence(1, "継", "ん？…これは…");
			novel->setFontColor(1, Color3B::BLACK);
			novel->addSentence(1, "", "脇には、先ほど見ていたであろう紙切れが落ちていた。");
			novel->addSentence(1, "", "そこには「放課後、校舎裏でお待ちしております。」とだけ書かれていた。赤文字で。");
			novel->setFontColor(1, Color3B::BLUE);
			novel->addSentence(1, "継", "これももしかして、あの子が…");
			novel->addSentence(1, "継", "！？…んぐっ…");
			novel->setFontColor(1, Color3B::BLACK);
			novel->addSentence(1, "", "いきなり、後ろから誰かにハンカチで口をふさがれた。");
			novel->addSentence(1, "", "甘ったるい匂いに、次第に意識は遠のき");
			novel->addSentence(1, "", "僕は気を失った…");

			novel->addSentence(2, "継", "何か用事ができたのかもしれない、僕も帰ろう");
			novel->setBg(2, "");
			novel->setCharaL(2, "");
			novel->addEvent(2, CallFunc::create([this] {
				if (AudioEngine::getPlayingAudioCount())AudioEngine::stopAll();
			}));
			novel->setFontColor(2, Color3B::BLACK);
			novel->addSentence(2, "", "僕は、迎えに来たセリーヌに連れられて、何事もなく家に帰ることができた。");
			novel->addSentence(2, "", "勝手に帰ったことで、後から寿甘には怒られたが…");
			novel->addSentence(2, "", "しかし、バンダナはあれから行方不明となってしまったのだ。");
			novel->addSentence(2, "", "数ヵ月経った今でもバンダナは見付かっていない");
			novel->addSentence(2, "", "あの時、バンダナを信じて、学校に残っていれば");
			novel->addSentence(2, "", "あいつは、今でも僕の傍にいてくれたのだろうか。");
			novel->addSentence(2, "", "BAD　END１「行方不明」");
			novel->addEvent(2, CallFunc::create([this] {
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			}));

			novel->setEndTask(-1);
			this->addChild(novel, 0, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "chapter1 end";
			AudioEngine::stopAll();

			auto origin = Director::getInstance()->getVisibleOrigin();
			auto visibleSize = Director::getInstance()->getVisibleSize();

			auto label = Label::createWithTTF("chapter1 end", FONT_NAME, 30);
			label->setPosition(Vec2(visibleSize.width - 70, 50));
			label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
			label->setColor(Color3B::WHITE);
			label->setOpacity(0.0f);
			label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), CallFunc::create([this] {
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, day2::Day::createScene(), Color3B::WHITE));
			}), NULL));
			this->addChild(label, 3, "label");

			return 10;
		});
	}

}

