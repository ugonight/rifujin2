#pragma execution_character_set("utf-8")

#include "System/cursor.h"
#include "Sequence/Title.h"
#include "Script\day2\fieldDef.h"
#include "Script\day3\fieldDef.h"

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
		AudioEngine::stopAll();

		mFuncNum = 0;
		mChapterNum = 2;

		mCount = 0;
		for (int i = 0; i < 100; i++)mAttack[i] = -1;

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
			novel->addSentence(0, "継", "うぅ……ここは…？");
			novel->addSentence(0, "継", "！？");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "僕は、この感じを覚えている。");
			novel->addSentence(0, "", "無機質な石の臭いと、生臭い鉄に似た臭い。");
			novel->addSentence(0, "", "息苦しさを増していく閉鎖空間…そう、きっとここは…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "うぐッ……けほっ……ゴホッゴホッ………");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "僕は堪らず咽てしまう");
			novel->addSentence(0, "", "ぎゅっと瞑った目を恐る恐る開くとそこは…");
			novel->setCharaL(0, "");
			novel->addEvent(0, CallFunc::create([this] {
				auto bg = Sprite::create("prison.png");
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
				bg->setOpacity(0.0f);
				bg->runAction(FadeIn::create(5.0f));
				addChild(bg, 0, "bg0");
				bg = Sprite::create("bandana_hurted.png");
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
				bg->setOpacity(0.0f);
				bg->runAction(FadeIn::create(5.0f));
				addChild(bg, 1, "bg1");

				AudioEngine::play2d("BGM/fear.ogg", true);
			}));
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "バンダナ…！！！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "目覚める前の悪夢が現実のものだったのだと理解すると、僕は大きな絶望に包まれた。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "おい！！しっかりしろよッ！！！！バンダナ！！！バンダナ…ッ！！！！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "徐々に昔の記憶が甦り、理性が失われていく。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "ごめんなさい……僕がしっかりしてなかったから…僕のせいで……ごめんなさい…ごめんなさい…");
			novel->addSentence(0, "継", "僕のせいで、バンダナまで居なくなったら…僕は…僕は……");
			novel->addEvent(0, CallFunc::create([this] {
				if (AudioEngine::getPlayingAudioCount()) { 
					AudioEngine::stopAll(); 
				}
			}));
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "バンダナ", "つぐるん");
			novel->addSentence(0, "継", "ごめんなさい…ごめんなさい…ごめんなさい…");
			novel->addSentence(0, "バンダナ", "おい継、しっかりしろ");
			novel->addSentence(0, "継", "…うわああああああ！！！ぞ、ゾンビだ！！！！");
			novel->addSentence(0, "バンダナ", "死んでねえよ！！");
			novel->addSentence(0, "バンダナ", "…心配かけて悪かった。さっきまで気絶してたんだ");
			novel->addSentence(0, "継", "本当に大丈夫なの…？こんなに酷い怪我で、出血もしているのに…");
			novel->addSentence(0, "バンダナ", "大丈夫だ、こんな怪我大したことない。俺様を何だと思ってるんだ");
			novel->addSentence(0, "バンダナ", "ただ、俺を射った矢に毒が塗られてたみたいでな…身動きができないんだ");
			novel->addSentence(0, "継", "そうなんだ…何か傷の手当てをしたいな");
			novel->addSentence(0, "継", "見たところ、ここは何かの施設の牢屋に見えるね。僕たちを襲った奴の本拠地なら、解毒剤もあるかもしれない。僕、探してくるよ");
			novel->addSentence(0, "バンダナ", "おお、なるほどな。お前の方は何ともないのか？");
			novel->addSentence(0, "継", "うん、僕は眠らされただけみたいだから、いくらでも動けるよ。");
			novel->addEvent(0, CallFunc::create([this] {
				AudioEngine::play2d("BGM/underground.ogg",true);
				setGetMusic(5);
			}));
			novel->addSentence(0, "バンダナ", "そうか、いつも通りの冷静さを取り戻したな。");
			novel->addSentence(0, "バンダナ", "お前は、全然できないヤツなんかじゃないんだ。その力で、俺を救ってくれ。");
			novel->addSentence(0, "継", "やってみるよ、バンダナ。");
			novel->addSentence(0, "継", "まずは、この部屋を出る方法を見つけよう");
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
			if (!AudioEngine::getPlayingAudioCount())AudioEngine::play2d("BGM/underground.ogg", true);
			removeChildByName("cursor");

			auto control = (day2::Esc*)day2::Esc::createControl();
			addChild(control, 1, "control");

			return 1;
		});

		mFuncList.push_back([this]() {
			mSituation = "解毒薬を作って（ノベル）";
			//AudioEngine::play2d("BGM/school.ogg", true);

			auto novel = Novel::create();

			novel->setBg(0, "prison.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "解毒薬を作ってきたよ、これで大丈夫だ…！");
			novel->addSentence(0, "バンダナ", "おお、流石だな！");
			novel->addSentence(0, "継", "早速注射で薬を打つね");
			novel->addSentence(0, "バンダナ", "んっ…！");
			novel->addSentence(0, "バンダナ", "…ふぅ、身体が楽になってきた。これで動けるぞ！");
			novel->addSentence(0, "バンダナ", "ほんとにサンキュな！つぐるん");
			novel->addSentence(0, "継", "元気になったみたいでよかったよ");
			novel->addSentence(0, "継", "地上につながっていそうな梯子を見つけたんだ。そこへ向かおう！");

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "影と対峙して（ノベル）";
			AudioEngine::stopAll();

			auto novel = Novel::create();

			novel->setBg(0, "aisle2.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "なんだか薄暗いところに出たな");
			novel->addSentence(0, "継", "うん、気を付けて進もう");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "！！…誰だ！！");
			novel->addEvent(0, CallFunc::create([this] {
				AudioEngine::play2d("BGM/fear.ogg", true);
			}));
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "…ふふふ、まさか抜け穴があったなんてね…");
			novel->setBg(0, "chara/stand_bow.png");
			novel->setCharaR(0, "");
			novel->setCharaL(0, "");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "お前は…！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "あなた…こそこそと嗅ぎまわってくれちゃってたみたいね");
			novel->addSentence(0, "？？？", "目障りだから消えてもらうわ");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "継！！ここは俺が何とかする！！逃げろ！！！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "ふふ…そういうわけにもいかないのよね…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "！！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "地面から無数の手が伸びて足に絡みついてくる");
			novel->addSentence(0, "？？？", "……ア゛ア゛ア゛…ア゛ア゛…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "クソッ…なんだこいつら…ッ");

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "無数の手が伸びて（ミニゲーム）";
			if (AudioEngine::getPlayingAudioCount() == 0) AudioEngine::play2d("BGM/fear.ogg", true);

			auto layer = Layer::create();
			layer->setCascadeOpacityEnabled(true);
			layer->setPosition(Vec2::ZERO);
			addChild(layer, 0, "layer_h");
			auto back = Sprite::create("handf.png");
			back->setPosition(Director::getInstance()->getVisibleSize() / 2);
			back->setOpacity(0.0f);
			back->runAction(FadeIn::create(1.0f));
			layer->addChild(back, 0, "back");
			
			//mHandImage[0] = SpriteBatchNode::create("hand01.png");
			//mHandImage[1] = SpriteBatchNode::create("hand02.png");
			//mHandImage[2] = SpriteBatchNode::create("hand03.png");
			//for (auto image : mHandImage)image->retain();

			auto label = Label::createWithTTF("連打！！", FONT_NAME, 30);
			label->setPosition(Vec2(427, 80));
			label->setColor(Color3B::WHITE);
			label->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1), FadeIn::create(1), NULL)));
			layer->addChild(label, 2, "label");

			return 3;
		});

		mFuncList.push_back([this]() {
			mSituation = "数多の手に囚われて（ノベル）";
			if (AudioEngine::getPlayingAudioCount() == 0) AudioEngine::play2d("BGM/fear.ogg", true);

			auto novel = Novel::create();
			novel->setBg(0, "chara/stand_bow.png");
			novel->addEvent(0, CallFunc::create([this] {setGetStill(8); }));
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "どうやらここまでみたいね");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "うグッ…");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "じゃあね、バイバイ。");
			novel->addSentence(0, "？？？", "死んじゃえ");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "どうにかしないと…");
			novel->addSentence(0, "継", "頼む…助けてくれ…！！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "僕は縋る思いで、服の裾を握った。");
			novel->addSentence(0, "", "すると…");
			novel->addEvent(0, CallFunc::create([this] {
				auto light = Sprite::create("chara/stand_bow_light.png");
				light->setOpacity(0.0f);
				light->setPosition(Director::getInstance()->getVisibleSize() / 2);
				light->runAction(FadeIn::create(1.0f));
				light->setBlendFunc(BlendFunc { GL_SRC_ALPHA , GL_ONE });
				addChild(light, 5, "light");
				AudioEngine::stopAll();
			}));
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "ちょ…何よこれ…！");
			novel->addSentence(0, "？？？", "まさか…");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "突然、ポケットから光があふれだし、辺り一面に広がる。");
			novel->addSentence(0, "？？？", "ウ゛ア゛ア゛ア゛……");
			novel->addSentence(0, "", "身体にまとわりついていた手が動きを止め、みるみるうちに消えていく。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "えっ、助かったのかな…？");
			novel->addSentence(0, "バンダナ", "覚悟しろ！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "？？？", "キャッ…！");
			novel->addSentence(0, "？？？", "…チッ、ここは引き下がるしかないようね…");
			novel->addEvent(0, CallFunc::create([this] {
				removeChildByName("light");
			}));
			novel->setBg(0, "aisle2.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "逃げていったぞ");
			novel->addSentence(0, "継", "何が起こったんだろう…");
			novel->addSentence(0, "継", "一先ず、先へ進もう");
			
			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "一難去って…（ノベル）";
			AudioEngine::play2d("BGM/fear.ogg", true);

			auto novel = Novel::create();

			//novel->setBg(0, "aisle4.png");
			novel->addEvent(0, CallFunc::create([this] {
				auto bg = Sprite::create("aisle4.png");
				bg->setOpacity(0.0f);
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
				bg->runAction(FadeIn::create(1.0f));
				addChild(bg, 0, "bg");
				auto ivy = Sprite::create("ivy.png");
				ivy->setOpacity(0.0f);
				ivy->setPosition(Director::getInstance()->getVisibleSize() / 2);
				ivy->runAction(FadeIn::create(1.0f));
				addChild(ivy, 1, "ivy");
			}));
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "これは…！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "出口だと思っていたそこにはツタが生い茂っていた");
			novel->addSentence(0, "", "そのツタは石のように固く、ナイフのように鋭いトゲを付けていた。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "そんな…さっきまでは何もなかったのに");
			novel->addSentence(0, "バンダナ", "そんじょそこらの刃物じゃどうしようもできそうにないな…");
			novel->addSentence(0, "継", "別の道を探すか、あのツタを何とかする方法を探すしかないみたいだ。");
			novel->addSentence(0, "継", "とにかく、ここを離れよう。");
			novel->addSentence(0, "バンダナ", "ああ、そうだな。");
			novel->addEvent(0, CallFunc::create([this] (){
				getChildByName("bg")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f),RemoveSelf::create()));
				getChildByName("ivy")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create()));

			}));

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "道を無くして（ノベル）";
			AudioEngine::stopAll();

			auto novel = Novel::create();

			novel->setBg(0, "aisle.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "結局ここまで戻ってきたな");
			novel->addSentence(0, "継", "うん、そうだね。");
			novel->addSentence(0, "継", "この先はまだ調べてないから、何かあるといいんだけど…");
			novel->addSentence(0, "継", "…ん？");
			novel->addSentence(0, "バンダナ", "どうした？つぐるん");
			novel->addSentence(0, "継", "あそこの牢に人が入っていないか？");
			novel->addSentence(0, "バンダナ", "俺たち以外にも捕らえられた奴がいるってことか…！");
			novel->addSentence(0, "継", "近くに行って確かめてみよう");
			novel->addSentence(0, "継", "……");
			novel->addSentence(0, "バンダナ", "……！");
			novel->addSentence(0, "継", "え…君は…");
			novel->addSentence(0, "バンダナ", "確か…今朝学校で会った…");

			novel->setEndTask(0);
			this->addChild(novel, 4, "novel");

			return 0;
		});

		mFuncList.push_back([this]() {
			mSituation = "chapter2 end";
			AudioEngine::stopAll();

			auto origin = Director::getInstance()->getVisibleOrigin();
			auto visibleSize = Director::getInstance()->getVisibleSize();
			
			setGetStill(9);

			auto bg = Sprite::create("chara/remon_fallen.png");
			bg->setPosition(Director::getInstance()->getVisibleSize() / 2);
			bg->setOpacity(0.0f);
			bg->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(4.0f), FadeOut::create(0.5f), CallFunc::create([this] {
				removeChildByName("bg");
			}), NULL));
			addChild(bg, 0, "bg");

			auto label = Label::createWithTTF("chapter2 end", FONT_NAME, 30);
			label->setPosition(Vec2(visibleSize.width - 70, 50));
			label->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
			label->setColor(Color3B::WHITE);
			label->setOpacity(0.0f);
			label->runAction(Sequence::create(DelayTime::create(5.0f),FadeIn::create(1.0f), DelayTime::create(2.0f), FadeOut::create(1.0f), CallFunc::create([this] {
				Director::getInstance()->replaceScene(TransitionFade::create(1.0f, day3::Day::createScene(), Color3B::WHITE));
			}), NULL));
			this->addChild(label, 3, "label");

			return 10;
		});
	}

	void Day::updateChapter() {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto layer = (Layer*)getChildByName("layer_h");
		int num;

		if (mFuncType == 3) {
			mCount++;

			if (mCount % 10 == 0) {
				for (num = 0; mAttack[num] != -1 && num < 100; num++);

				if (num == 100) {
					// 終了
					layer->runAction(Sequence::create(FadeOut::create(2.0f), CallFunc::create([this] { mFuncType = mFuncList[++mFuncNum](); }), RemoveSelf::create(), NULL));
					//for (auto image : mHandImage) CC_SAFE_RELEASE_NULL(image);
				}
				else {
					// 手出現
					mAttack[num]++;
					std::string name = StringUtils::format("hand%02d.png", cocos2d::random() % 3 + 1);
					auto hand = Sprite::create(name);
					//int n = cocos2d::random() % 3;
					//if (n < 0 || n>2) n = 1;
					//auto hand = Sprite::createWithTexture(mHandImage[n]->getTexture());
					hand->setOpacity(0.0f);
					hand->runAction(FadeIn::create(1.0f));
					hand->setPosition(Vec2(cocos2d::random() % ((int)visibleSize.width - 200) + 100, cocos2d::random() % (int)(visibleSize.height - 100) + 50));
					layer->addChild(hand, 2, StringUtils::format("hand%02d", num));
					auto listener = EventListenerTouchOneByOne::create();
					listener->setSwallowTouches(true);
					listener->onTouchBegan = [this, num](Touch* touch, Event* event) {
						if (event->getCurrentTarget()->getBoundingBox().containsPoint(touch->getLocation()))
						{
							mAttack[num]++;
							event->getCurrentTarget()->runAction(Sequence::create(MoveBy::create(0.05, Vec2(10, 0)), MoveBy::create(0.05f, Vec2(-20, 0)), MoveBy::create(0.05f, Vec2(10, 0)), NULL));
							AudioEngine::play2d("SE/tm2_hit004.ogg");
							if (mAttack[num] == 3) {
								event->getCurrentTarget()->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f), RemoveSelf::create()));
								mAttack[num] = -1;
							}
							return true;
						}
						return false;
					};
					getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, hand);
				}

			}
		}
	}
}


