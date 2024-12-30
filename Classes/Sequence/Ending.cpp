#pragma execution_character_set("utf-8")

#include "Ending.h"
#include "System/cursor.h"
#include "System/novel.h"
#include "Sequence/Title.h"

#include "audio/include/AudioEngine.h"
#include <define.h>
// using namespace cocos2d::experimental;
USING_NS_CC;

Scene* Ending::createScene()
{
	auto scene = Scene::create();
	auto layer = Ending::create();
	scene->addChild(layer);
	return scene;
}

bool Ending::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto cursor = Cursor::create();
	cursor->setCursorNum(Cursor::NOVEL);
	this->addChild(cursor, 1, "cursor");

	//BGM
	AudioEngine::stopAll();

	mFuncNum = 0;

	//シナリオ
	mFunc[0] = [this]() {
		auto novel = Novel::create();

		novel->setBg(0, "forest_run.png");
		novel->setCharaR(0, "chara/suama1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘", "やった…！やっと出られた！");
		novel->setCharaL(0, "chara/tuguru1.png");
		novel->setCharaC(0, "chara/scene12.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "おや…？これは…お墓かな…？");
		novel->setCharaR(0, "chara/rias1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リアス", "ここは…ご先祖様のお墓……");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "なるほど…あの地下室と繋がっているのは、何か関係があるのかな。");
		novel->setCharaR(0, "chara/celine1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ", "…継様のお父様が、この辺りに捨てられていたご遺体を埋葬されていたようです。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "…そっか");
		novel->setCharaC(0, "chara/queen1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "はぁ…あぁぁ………ッッ");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "お前！まだ追ってきてたのか！");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "そん…な………");
		novel->addSentence(0, "リリア", "…こんな…ところに………いたなんて………………");
		novel->setCharaC(0, "");
		novel->setCharaR(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘", "ちょっと！なんでお墓を荒らしてるのよ！！");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				setGetStill(24);
				auto spr = Sprite::create("chara/scene15.png");
				spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
				spr->setOpacity(0.0f);
				spr->runAction(FadeIn::create(3.f));
				addChild(spr, 0, "bg");
				}),
			DelayTime::create(3.0f)
		));
		novel->setCharaL(0, "");
		novel->setCharaR(0, "");
		novel->setBg(0, "");
		novel->addSentence(0, "", "…");
		novel->addEvent(0, CallFunc::create([this]() {
			setGetMusic(7);
			playSoundBS("BGM/reconciliation.ogg", true);
		}));
		novel->addSentence(0, "リリア", "やっと…やっと会えた……");
		novel->addSentence(0, "リリア", "…本当にただそれだけだった。ただ、あなたに会いたかっただけなのに…");
		novel->addSentence(0, "リリア", "復讐なんかしたって、何の意味もないことも、あなたはそんなこと望んでいないのも、全部、分かっていたのに…");
		novel->addSentence(0, "リリア", "ごめんなさい……ごめんなさい……");
		novel->addSentence(0, "リリア", "私を…許して……");
		novel->addSentence(0, "リアス", "あ…あの…");
		novel->addSentence(0, "リリア", "リアスちゃん");
		novel->addSentence(0, "リアス", "は、はい！");
		novel->addSentence(0, "リリア", "これからのドラゴン族のこと…よろしくね。");
		novel->addSentence(0, "リリア", "あなたたちのことを怖がる人はまだいるかもしれないけど…受け入れてくれる人が少しずつでも増えてくれれば、それでいいから");
		novel->addSentence(0, "リアス", "はい…がんばります…！");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "僕も協力するよ。王子として、僕にもまだまだできることがたくさんあるはずだから。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "そっか…リアスちゃんには頼もしいお友達がたくさんできたものね…");
		novel->addSentence(0, "リリア", "あなたが幸せになってくれてよかった…これでもう心残りはないわ");
		novel->addSentence(0, "リアス", "わ、わたしっ…ちゃんと幸せになって、みんなに受け入れてもらえるようにがんばりますから…っ！");
		novel->addSentence(0, "リアス", "みなさんのこと、ずっと…ずっと忘れませんから…っ！");
		novel->addSentence(0, "リリア", "ふふ…ありがとうね。これで死んでいったみんなも報われるわ。");
		novel->addSentence(0, "リリア", "さようなら…次の世界では私も、あの人と幸せになれるといいな…");
		novel->addSentence(0, "リアス", "さようなら…どうかお元気で…！");
		novel->addSentence(0, "リリア", "…");
		novel->addSentence(0, "リリア", "……");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				auto bg = getChildByName("bg");
				bg->runAction(FadeOut::create(3.f));

				setGetStill(25);
				auto spr = Sprite::create("chara/scene15_2.png");
				spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
				spr->setOpacity(0.0f);
				spr->runAction(FadeIn::create(3.f));
				addChild(spr, 0, "bg2");
				}),
			DelayTime::create(3.0f)
		));
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "………");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaR(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘", "消えちゃった…ちゃんと成仏してくれているといいんだけど…");
		novel->addSentence(0, "檸檬", "……ん…………うーん……");
		novel->addSentence(0, "リアス", "檸檬ちゃん！？目を覚ました……？");
		novel->addSentence(0, "檸檬", "…リアス……？");
		novel->setCharaR(0, "");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				auto bg = getChildByName("bg2");
				bg->runAction(FadeOut::create(3.f));

				setGetStill(26);
				auto spr = Sprite::create("chara/scene16.png");
				spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
				spr->setOpacity(0.0f);
				spr->runAction(FadeIn::create(3.f));
				addChild(spr, 0, "bg3");
				}),
			DelayTime::create(3.0f)
		));
		novel->addSentence(0, "リアス", "檸檬ちゃん！よかったよぉ……");
		novel->addSentence(0, "檸檬", "わ、どうしたっていうのよ…");
		novel->addSentence(0, "檸檬", "私、どうしてこんな所に……何を…してたんだっけ……");
		novel->addSentence(0, "檸檬", "…あ、思い出した……");
		novel->addSentence(0, "檸檬", "地下での研究に没頭しているうちに、黒いもやもやが頭の中で渦巻いて…気が付いたら、あんな馬鹿げた計画を立てていて…");
		novel->addSentence(0, "檸檬", "…私、あなたに酷いことをしようとしてた。もう、取り返しのつかないくらい。");
		novel->addSentence(0, "檸檬", "リアス、本当にごめんなさい。あなたになんて言ったらいいか…");
		novel->addSentence(0, "リアス", "ううん…檸檬ちゃんは何も悪くないよ。ただ取り憑かれていただけだし、本当の檸檬ちゃんはそんなことしないって分かってるから…");
		novel->addSentence(0, "リアス", "覚えてるかな？入学してすぐの事、ここら辺ではドラゴン族って珍しいから好奇の目で見られて…私も性格こんなだしなかなか友達できなくて、でも、檸檬ちゃんは話し掛けてくれて……私すごく嬉しかった");
		novel->addSentence(0, "檸檬", "それは！私がドラゴン族を……！");
		novel->addSentence(0, "リアス", "でも私は嬉しかった");
		//novel->addSentence(0, "リアス", "私の方こそ、ごめんね…優しい檸檬ちゃんに甘えてばっかりで、いつも迷惑ばっかりかけてた");
		novel->addSentence(0, "リアス", "…ね、だから、また仲良くしてくれる…？私、今まで檸檬ちゃんに甘えてばっかりだったけど、もっとしっかりできるようにがんばるから…");
		novel->addSentence(0, "檸檬", "そんな…私の方こそ…！あなたのこと、友達としても大好きよ。研究対象としてじゃなくてね。");
		novel->addSentence(0, "リアス", "ありがとうっ…！私も、檸檬ちゃんのこと大好きだよっ…！");
		novel->addSentence(0, "檸檬", "うふふ…バンダナくんのことはいいのかしら…？");
		novel->addSentence(0, "リアス", "バ、バンダナ様のことは、今関係ないじゃないっ…！");
		novel->setBg(0, "forest_run.png");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "…まあ二人とも、あまり他人に執着しすぎないようにな。");
		novel->addEvent(0, CallFunc::create([this] {
			auto bg = getChildByName("bg3");
			bg->runAction(RemoveSelf::create(true));
			}));
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaR(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘", "こんなところで反応しづらい正論言うのやめなさいよ…");
		novel->setCharaC(0, "chara/remon1.png");
		novel->addSentence(0, "檸檬", "継くん");
		novel->setCharaL(0, "chara/tuguru1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "ん？何かな");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "取り憑かれていたとはいえ、私はこの国の王子とその友人を誘拐して、殺人未遂事件を起こしてしまった。");
		novel->addSentence(0, "檸檬", "どんな罰でも受け入れる覚悟でいるわ。ただで済ませる訳にはいかないでしょう？");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "…僕はお咎めなしでいいと思うな。結果的に誰も傷付いたりしなかったし、今回の件は王族として僕たちにも責任があったわけだし。");
		novel->setCharaR(0, "chara/celine1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ", "継様がそうおっしゃるのでしたら、それに従いましょう。");
		novel->addSentence(0, "セリーヌ", "この地下室の存在は報告しておきますが、檸檬様のことは上手く隠しておきます。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "そんなっ…！");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "大丈夫。君はこれからいくらでもやり直せるんだ。");
		novel->addSentence(0, "継", "さあ、暗くなってきちゃったし、みんなで帰ろうか");
		novel->setCharaC(0, "chara/bandana1.png");
		novel->addSentence(0, "バンダナ", "そうだな！腹も減ったし、みんなで飯でも食いに行こうぜ！");
		novel->setCharaR(0, "chara/suama1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘", "あ、それ賛成！私、なんか甘いもの食べたーい！");
		novel->setCharaL(0, "chara/rias1.png");
		novel->addSentence(0, "リアス", "バンダナ様と一緒にご飯だなんて…ぴぎゃあああああああああ！！！///");
		novel->setCharaL(0, "");
		novel->addSentence(0, "寿甘", "え！？リアスちゃん！どこ行くのよー！");
		novel->setCharaL(0, "chara/remon1.png");
		novel->addSentence(0, "檸檬", "まったくもうあの子はしょうがないんだから…");
		novel->setCharaL(0, "");
		novel->addSentence(0, "檸檬", "リアスー！待ちなさいー！！");
		novel->setCharaL(0, "chara/tuguru1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "あ、あははっ");

		novel->setEndTask(0);
		this->addChild(novel, 10, "novel");
		};

	mFunc[1] = [this]() {
		auto novel = Novel::create();

		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "こうしてこの事件は幕を閉じた");
		novel->addSentence(0, "", "リアスちゃんは檸檬ちゃんと楽しく学校に通っている、ストーカー癖は抜けていないらしくバンダナをつけている時も多いが バンダナに気づかれ話しかけられると逆に赤くなって逃げ出してしまうのだった。");
		novel->addSentence(0, "", "檸檬ちゃんは放課後はうちの城で掃除などの手伝いをすることになった。しなくてもいいよと言ったけど｢させて欲しい｣との一点張りだった。");
		novel->addSentence(0, "", "彼女は僕と違ってやり直すことができたんだ。僕はそれを心から嬉しく思う");

		novel->setEndTask(0);
		this->addChild(novel, 10, "novel");
		};

	runAction(Sequence::create(DelayTime::create(.5f),
		CallFunc::create(Ending::mFunc[mFuncNum]), NULL));

	return true;
}

void Ending::update(float delta) {
	Novel* novel = (Novel*)(this->getChildByName("novel"));
	if (novel) {
		if (novel->getEndFlag()) {
			this->removeChild(novel);

			if (mFuncNum < mFuncCount - 1) {
				mFunc[++mFuncNum]();
			}
			else
			{
				AudioEngine::stopAll();
				this->runAction(Sequence::create(DelayTime::create(1.f), CallFunc::create([this]() {
					setGetMusic(8);
					mBgmId = playSoundBS("BGM/curse.ogg");
					mVolume = mVolumeDefault = cocos2d::AudioEngine::getVolume(mBgmId);
					}), NULL));

				Size display = Director::getInstance()->getVisibleSize();
				Vec2 origin = Director::getInstance()->getVisibleOrigin();

				const int edCount = 10;
				const int showTime = 10;
				const int fadeTime = 2;

				auto bg = Sprite::create("bg/ed00.png");
				bg->setPosition(display / 2.f);
				bg->setOpacity(0.f);
				bg->runAction(Sequence::create(
					FadeIn::create(5.f),
					DelayTime::create((showTime + fadeTime * 2) * edCount - 2),
					CallFunc::create([this]() { mEndingLast = true; }),
					FadeOut::create(5.f),
					CallFunc::create([this]() { mToTitle = true; }),
					NULL
				));
				this->addChild(bg, 0, "bg");


				for (size_t i = 1; i <= edCount; i++)
				{
					auto name = StringUtils::format("bg/ed%02d.png", i);
					auto ed = Sprite::create(name);
					ed->setPosition(display / 2.f);
					ed->setOpacity(0.f);
					ed->runAction(Sequence::create(
						DelayTime::create((i - 1) * (showTime + fadeTime * 2)),
						FadeIn::create(fadeTime),
						DelayTime::create(showTime),
						FadeOut::create(fadeTime),
						NULL
					));
					this->addChild(ed, 1, name);
				}

				auto label = Label::createWithTTF("", FONT_NAME, 24);
				label->setPosition(Vec2(origin.x + display.width - 10, origin.y + 30));
				label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
				label->setTextColor(Color4B::BLACK);
				this->addChild(label, 3, "skip_label");

				auto listener = EventListenerTouchOneByOne::create();
				listener->onTouchBegan = [this](Touch* touch, Event* event) {
					mSkip++;
					//log("%d,%d", 50 - mSkip, mEnd);
					if (mSkip == 50) {
						//Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
						mToTitle = true;
					}
					else if (mSkip >= 40) {
						auto label = (Label*)getChildByName("skip_label");
						label->setString(StringUtils::format("あと %d 回でスキップ", 50 - mSkip));
					}
					return true;
					};
				this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, bg);

			}
		}
	}
	if (mEndingLast) {
		float fps = 1.0f / Director::getInstance()->getAnimationInterval();
		float step = mVolume / (fps * 5.0f);
		mVolume -= step;
		cocos2d::AudioEngine::setVolume(mBgmId, mVolume);
	}
	if (mToTitle) {
		cocos2d::AudioEngine::stopAll();
		cocos2d::AudioEngine::setVolume(mBgmId, mVolumeDefault);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
		mEndingLast = false;
		mToTitle = false;
		UserDefault::getInstance()->setBoolForKey("clear", true);
	}
}
