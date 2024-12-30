#pragma  execution_character_set("utf-8")
#include "Script/day4/fieldDef.h"
#include "Sequence/Title.h"

#include "DangeonC.h"

#include "audio/include/AudioEngine.h"
// using namespace cocos2d::experimental;

USING_NS_CC;

namespace day4 {
	void Dangeon1::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "地下迷宮1";

		auto bg = Sprite::create("dangeon_back.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		// ステージ
		std::vector<std::vector<int>> stage = {
			{1,1,1,1,1,1,0,1},
			{1,1,0,0,1,1,0,1},
			{1,0,1,0,1,0,0,1},
			{1,0,0,0,1,0,1,1},
			{1,0,1,0,0,0,1,1},
			{1,0,1,1,1,1,1,1}
		};
		auto pos = DangeonC::Pos{ 1, 5 };
		mDangeonC = std::make_shared<DangeonC>(stage, pos, DangeonC::north);

		// 壁画像
		Sprite* wall;
		wall = Sprite::create("dangeon_bl.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backL());
		addChild(wall, 1, "wallBL");
		wall = Sprite::create("dangeon_bc.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backC());
		addChild(wall, 2, "wallBC");
		wall = Sprite::create("dangeon_br.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backR());
		addChild(wall, 1, "wallBR");
		wall = Sprite::create("dangeon_fl.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->frontL());
		addChild(wall, 3, "wallFL");
		wall = Sprite::create("dangeon_fr.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->frontR());
		addChild(wall, 3, "wallFR");

		// 移動
		auto move = ObjectN::create();
		move->setArea(Rect(350, 150, 160, 160));
		move->setCursor(Cursor::FORWARD);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toFront(); this->move(); playSoundBS("SE/footsteps.ogg"); }));
		addObject(move, "forward", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(185, 420, 480, 60));
		move->setCursor(Cursor::BACK);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toBack(); this->move(); }));
		addObject(move, "back", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(0, 30, 80, 400));
		move->setCursor(Cursor::LEFT);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toLeft(); this->move(); }));
		addObject(move, "left", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(774, 30, 80, 400));
		move->setCursor(Cursor::RIGHT);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toRight(); this->move(); }));
		addObject(move, "right", 2, true);

		// スタート
		auto start = ObjectN::create();
		start->setTexture("dangeon_start.png");
		start->setArea(Rect(350, 150, 160, 210));
		start->setCursor(Cursor::ENTER);
		start->setFieldChangeEvent("aisle");
		start->setTouchEvent(CallFunc::create([this]() { mObjectList["start"]->setState(1); }));
		addObject(start, "start", 3, false);

		// ゴール
		auto goal = ObjectN::create();
		goal->setTexture("dangeon_goal.png");
		goal->setArea(Rect(350, 150, 160, 210));
		goal->setCursor(Cursor::FORWARD);
		goal->setFieldChangeEvent("remains");
		goal->setTouchEvent(CallFunc::create([this]() { mObjectList["goal"]->setState(1); }));
		addObject(goal, "goal", 3, false);
	}

	void Dangeon1::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "うお…急に暗くなったな");
			novel->addSentence(0, "継", "足元に気を付けて進んでいこう。");
			mObjectList["flag"]->setState(1);

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}

		if (!getChildByName("forward")) {
			if (mObjectList["start"]->getState()) {
				mDangeonC->setPos(1, 5);
				mDangeonC->setDirec(DangeonC::north);
				move();
			}
			else if (mObjectList["goal"]->getState()) {
				mDangeonC->setPos(6, 0);
				mDangeonC->setDirec(DangeonC::south);
				move();
			}
		}
		mObjectList["start"]->setState(0);
		mObjectList["goal"]->setState(0);
	}

	//Dangeon1::~Dangeon1() {
	//	delete mDangeonC;
	//}

	void Dangeon1::move() {
		auto wall = getChildByName("wallBL");
		if (mDangeonC->backL()) {
			wall->runAction(FadeIn::create(0.25f));
		}
		else {
			wall->runAction(FadeOut::create(0.25f));
		}
		wall = getChildByName("wallBC");
		if (mDangeonC->backC()) {
			wall->runAction(FadeIn::create(0.25f));
			if (getChildByName("forward")) {
				removeChildByName("forward");
			}
		}
		else {
			wall->runAction(FadeOut::create(0.25f));
			if (!getChildByName("forward")) {
				addChild(mObjectList["forward"], 2, "forward");
			}
		}
		wall = getChildByName("wallBR");
		if (mDangeonC->backR()) {
			wall->runAction(FadeIn::create(0.25f));
		}
		else {
			wall->runAction(FadeOut::create(0.25f));
		}
		wall = getChildByName("wallFL");
		if (mDangeonC->frontL()) {
			wall->runAction(FadeIn::create(0.25f));
		}
		else {
			wall->runAction(FadeOut::create(0.25f));
		}
		wall = getChildByName("wallFR");
		if (mDangeonC->frontR()) {
			wall->runAction(FadeIn::create(0.25f));
		}
		else {
			wall->runAction(FadeOut::create(0.25f));
		}

		// スタート
		if (mDangeonC->getPos().x == 1 && mDangeonC->getPos().y == 5 && mDangeonC->getDirec() == DangeonC::south) {
			if (!getChildByName("start")) {
				addChild(mObjectList["start"], 3, "start");
			}
		}
		else {
			if (getChildByName("start")) {
				removeChildByName("start");
			}
		}

		// ゴール
		if (mDangeonC->getPos().x == 6 && mDangeonC->getPos().y == 0 && mDangeonC->getDirec() == DangeonC::north) {
			if (!getChildByName("goal")) {
				addChild(mObjectList["goal"], 3, "goal");
			}
		}
		else {
			if (getChildByName("goal")) {
				removeChildByName("goal");
			}
		}
	}

	void Remains::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "隠れ家の入り口";

		auto bg = Sprite::create("remains.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto back = ObjectN::create();
		back->setArea(Rect(0, 430, 854, 50));
		back->setCursor(Cursor::BACK);
		back->setFieldChangeEvent("dangeon1");
		addObject(back, "back", 1, true);

		auto remon = ObjectN::create();
		remon->setTexture("chara/remon1.png");
		remon->setArea(Rect(318, 0, 217, 480));
		remon->addCanUseItem("doll");
		remon->addCanUseItem("diary");
		remon->setTouchEvent(CallFunc::create([this]() {
			// Q. 誘拐犯の正体は？
			if (mObjectList["remon"]->getState() == 0) {
				if (ItemMgr::sharedItem()->getSelectedItem() == "doll") {
					reasoning2();
				}
				else {
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::RED);
					novel->addEvent(0, CallFunc::create(CC_CALLBACK_0(Remains::takeDamage, this)));
					novel->addSentence(0, "檸檬", "そんなものが私たちを襲った犯人だというのかしら？");
					novel->setEndTask(0);
					addChild(novel, 10, "novel");
				}
			}
			// Q. 檸檬がリアスを陥れようとしている証拠は？
			else if (mObjectList["remon"]->getState() == 1) {
				if (ItemMgr::sharedItem()->getSelectedItem() == "diary") {
					reasoning3();
				}
				else {
					auto novel = Novel::create();
					novel->setFontColor(0, Color3B::RED);
					novel->addEvent(0, CallFunc::create(CC_CALLBACK_0(Remains::takeDamage, this)));
					novel->addSentence(0, "檸檬", "それが私がリアスを殺そうとした証拠なの？意味が分からないわ");
					novel->setEndTask(0);
					addChild(novel, 10, "novel");
				}
			}

			}));
		addObject(remon, "remon", 3, false);

		auto door = ObjectN::create();
		door->setTexture("remains_door.png");
		addObject(door, "door", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		// ライフ
		auto lifeLayer = Layer::create();
		lifeLayer->setPosition(Vec2::ZERO);
		lifeLayer->setCascadeOpacityEnabled(true);
		lifeLayer->setOpacity(0.0f);
		for (int i = 0; i < 6; i++)
		{
			auto life = Sprite::create("life.png");
			life->setPosition(854 - 50 * (i + 2), 480 - 25);
			lifeLayer->addChild(life, 0, StringUtils::format("life%d", i));
		}
		addChild(lifeLayer, 15, "life");
	}

	void Remains::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			mLife = 6;

			auto novel = Novel::create();
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "少し開けた場所にたどり着いたね");
			novel->addSentence(0, "バンダナ", "なんか物騒な絵が描いてあるな…");
			novel->addSentence(0, "継", "この扉を開ければ外に出られるかもしれない");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ガチャガチャ…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "……うーん、開かない");
			novel->addSentence(0, "バンダナ", "俺にやらせろ！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ガッシャンガッシャン！！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "？？？", "…おい、そこの筋肉バカ");
			novel->addSentence(0, "バンダナ", "…あん？なんだと？");
			novel->addSentence(0, "継", "扉の上の龍がしゃべった…！？");
			novel->addSentence(0, "？？？", "女王の名前を答えよ");
			novel->addSentence(0, "バンダナ", "女王…？なんのことだ？");
			novel->addSentence(0, "継", "よくわからないけど…ここに描かれている壁画が関係しているのかな？");
			novel->addSentence(0, "？？？", "女王の名前を答えよ");
			novel->addSentence(0, "バンダナ", "おい！ヒントぐらい教えてくれてもいいだろうが！この豚鼻！！");
			novel->addSentence(0, "？？？", "女王の名前を答えよ");
			novel->addSentence(0, "バンダナ", "同じことしか答えなくなったぞ…最初の罵倒はなんだったんだ…");
			novel->setCharaC(0, "chara/remon1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "…ちょっといいかしら");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "どうしたの？水無月さん");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "書斎に国の歴史についての史料があったと思うの、そこから何かヒントが得られるんじゃないかしら。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "ああ、確かにそうだね");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "そこでなんだけど、手分けして調べるというのはどうかしら？");
			novel->addSentence(0, "檸檬", "継さんがここで壁画を調べて、私とバンダナさんが書斎に戻って手掛かりを探してくるわ。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "つぐるん一人で大丈夫か…？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "あら、継さんにはお札があるから大丈夫じゃない");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "しかしだな…");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "継さんはどう思います？");

			// 寿甘の証言を取得しているか
			if (ItemMgr::sharedItem()->getGetItem("suama")) {
				novel->addSwitchEvent(0, 1, "檸檬の意見に賛成する", 2, "檸檬の意見に反対する");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "僕は…");
			}

			// BAD ENDイベント
			int bad;
			{
				novel->setFontColor(0, Color3B::BLUE);
				bad = novel->addSentence(0, "継", "そうだね、ここは手分けして調査をしていこう。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "じゃあ決まりね。…バンダナさん、護衛を頼めるかしら？");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "つぐるん…");
				novel->addSentence(0, "継", "この壁画のどこかに何かしらのメッセージが隠されているかもしれないからね。");
				novel->addSentence(0, "継", "バンダナも気を付けて行ってきてね。");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬", "さあ行くわよ");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "お、おう…");
				novel->setCharaL(0, "");
				novel->setCharaC(0, "");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "…");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "さて、この辺りを調べてみるか");
				novel->setBg(0, "bg/black.png");
				novel->addSentence(0, "継", "…");
				novel->addSentence(0, "継", "……");
				novel->addSentence(0, "継", "………");
				novel->setBg(0, "");
				novel->addSentence(0, "継", "ダメだ…隅々まで調べてみたけど名前らしきものはどこにも書かれていない…");
				novel->setCharaR(0, "");
				novel->addSentence(0, "継", "この絵はおそらく、さっき読んだ絵本の物語の内容を表しているはず…");
				novel->addSentence(0, "継", "王族の女に連れられてマグマに焼かれてしまったドラゴン族の男…王族の女を殺して処刑されたドラゴン族の女…");
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "この場合、「女王」というのは誰を指すのだろう…");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "僕の思考がそこまで到達した時だった。");
				novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll(); }));
				novel->addSentence(0, "", "ヒュン");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "っ…うぐっ…あぁ…っ！");
				novel->addEvent(0, CallFunc::create([this]() { playSoundBS("BGM/fear.ogg", true); }));
				novel->setCharaR(0, "");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "腹部に今まで感じたことのない激しい痛みを感じ、たまらずその場にうずくまった。");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継", "…き、君は…っ");
				novel->setFontColor(0, Color3B::BLACK);
				novel->addSentence(0, "", "痛みで遠のく意識の中、僕が見たのは…");

				novel->setBg(0, "chara/bad4.png");
				novel->addEvent(0, CallFunc::create([this]() {
					setGetStill(20);
					// this->getChildByName("bg")->runAction(FadeOut::create(0.5f));
					auto bg = Sprite::create("bg/black.png");
					bg->setOpacity(0.0f);
					bg->runAction(FadeIn::create(0.5f));
					bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					addChild(bg, 9, "black");
					}));
				novel->addSentence(0, "", "BAD END4「地獄の底で」");

				novel->addPauseEvent(0, Sequence::createWithTwoActions(
					CallFunc::create([this] {
						auto spr = Sprite::create("bg/black.png");
						spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
						spr->setOpacity(0.0f);
						addChild(spr, 0, "bg");
						}),
					DelayTime::create(2.0f)
				));

				novel->addEvent(0, CallFunc::create([this, novel] {
					AudioEngine::stopAll();
					}));
				novel->setFontColor(0, Color3B::BLACK);
				novel->setBg(0, "");
				novel->addSentence(0, "", "…");
				novel->setCharaR(0, "chara/celine1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "セリーヌ", "…なんてことにならないように、私がヒントを差し上げますね。");
				novel->addSentence(0, "セリーヌ", "chapter3で寿甘さんに継様サイドへ情報共有をしてもらう必要があります。");
				novel->addSentence(0, "セリーヌ", "寿甘さんのことですから、幽霊か何かに言伝を頼むことができそうです。");
				novel->addSentence(0, "セリーヌ", "そうするとchapter4で継様サイドの方で幽霊が出現するようになります。");
				novel->addSentence(0, "セリーヌ", "力の弱い霊なのですぐに消えてしまいますが、根気強く追いかけましょう。檸檬様を救出すると霊が出てこなくなるのでお気を付けくださいませ。");
				novel->addSentence(0, "セリーヌ", "あとは愚かな選択をなさらないことですね。");
				novel->addSentence(0, "セリーヌ", "では、検討を祈ります。");

				novel->addEvent(0, CallFunc::create([this] {
					AudioEngine::stopAll();
					Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
					}));
				novel->addSentence(0, "", "");
			}

			novel->addSentence(1, "継", "そうだね、ここは手分けして調査をしていこう。");
			novel->setJump(1, 0, bad);

			int num = 0;
			novel->addSentence(2, "継", "…水無月さん、確認してもいいかな");
			novel->addEvent(2, CallFunc::create([this]() { AudioEngine::stopAll(); }));
			novel->addSentence(2, "継", "どうしてお札のことを君が知っているのかな");
			novel->setFontColor(2, Color3B::RED);
			num = novel->addSentence(0, "檸檬", "！");
			novel->setJump(2, 0, num);

			novel->addEvent(0, CallFunc::create([this]() { playSoundBS("BGM/mystery.ogg", true); }));
			novel->addSentence(0, "檸檬", "…たまたまポケットから出てるのが見えただけよ");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "だとしても、お札の効果で安全だなんて思うのはおかしいよ");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "そうかしら？お札は除霊に効くっていうじゃない");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "どうして幽霊が襲ってくるんだなんて思うんだよ");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "…何が言いたいのかしら");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "とにかく、君にバンダナを連れて行かせてはいけない気がするんだ");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "ふーん…");
			novel->addSentence(0, "檸檬", "まあいいわ…何か誤解しているのなら、それを解いてあげるまでね。");
			novel->addSentence(0, "檸檬", "さて、あなたの考えを聞かせてくれる？");
			novel->addEvent(0, CallFunc::create([this]() { getChildByName("life")->runAction(FadeIn::create(1.0f)); }));
			novel->setFontColor(0, Color3B::BLUE);
			num = novel->addSentence(0, "継", "…君はあるタイミングでこのお札の効果を知ったんだ");
			novel->addSwitchEvent(0, 3, "学校にいる時", 4, "最初に地下で襲われた時", 5, "一緒に行動していた時");
			novel->addSentence(0, "継", "それは…");


			// 不正解
			{
				// 選択:学校にいる時
				novel->addSentence(3, "継", "学校にいた時だよ");
				novel->setFontColor(3, Color3B::RED);
				novel->addSentence(3, "檸檬", "学校にいた時の…いつかしら？");
				novel->setFontColor(3, Color3B::BLUE);
				novel->addSentence(3, "継", "僕がお札をしまっていたのは、このマントのポケットの中だ。そのマントを脱いだのは体育の授業の前に着替えた時くらいだ。");
				novel->addSentence(3, "継", "君はマントがある教室に忍び込んで、そしてお札の存在を知って…");
				novel->setFontColor(3, Color3B::RED);
				novel->addSentence(3, "檸檬", "ちょっと待って、あなた達男子は女子より先に教室に戻ってきたはずよ。");
				novel->addSentence(3, "檸檬", "私はそれまでずっと体育の授業に参加していたからアリバイがあるのよ。後で誰かに聞けば分かると思うけど。");
				novel->setFontColor(3, Color3B::BLUE);
				novel->addEvent(3, CallFunc::create(CC_CALLBACK_0(Remains::takeDamage, this)));
				novel->addSentence(3, "継", "（そう言えば、寿甘も水無月さんはちゃんと体育に参加してたと言ってたな…）");
				novel->setJump(3, 0, num - 1);

				// 選択:一緒に行動していた時
				novel->addSentence(5, "継", "牢から出て僕たちと一緒に行動していた時だ");
				novel->setFontColor(5, Color3B::RED);
				novel->addSentence(5, "檸檬", "ええそうね。その時にチラッとポケットからはみ出しているのが見えたのよ。");
				novel->setFontColor(5, Color3B::BLUE);
				novel->addSentence(5, "バンダナ", "チラッと見えたレベルでそれがお札だと断定できるのはおかしくねーか？普通はただの紙切れにしか見えねえと思うぞ。");
				novel->setFontColor(5, Color3B::RED);
				novel->addSentence(5, "檸檬", "それもそうね。じゃあ私の勘違いだったのかしら。");
				novel->setFontColor(5, Color3B::BLUE);
				novel->addEvent(5, CallFunc::create(CC_CALLBACK_0(Remains::takeDamage, this)));
				novel->addSentence(5, "継", "（違う…もっと前に水無月さんはお札のことを知ったんだ）");
				novel->setJump(5, 0, num - 1);

			}

			// 選択:最初に地下で襲われた時
			novel->addSwitchEvent(4, 0);
			novel->addSentence(4, "継", "水無月さんが牢に閉じ込められてるのを見つける前、僕らはさっきみたいに黒ずくめの何者かにボウガンで襲われたんだ。");


			{
				// 回想
				novel->setCharaR(0, "");
				novel->setCharaL(0, "");
				novel->setCharaC(0, "");
				novel->addEvent(0, CallFunc::create([this]() {
					auto sepia = Sprite::create("bg/sepia.png");
					sepia->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					sepia->setBlendFunc(BlendFunc{ backend::BlendFactor::ONE_MINUS_DST_COLOR,backend::BlendFactor::ONE });
					this->addChild(sepia, 11, "sepia");
					}));
				novel->setBg(0, "chara/stand_bow.png");
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
				novel->addEvent(0, CallFunc::create([this]() {
					this->removeChildByName("sepia");
					}));
				novel->setBg(0, "");
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setCharaL(0, "chara/bandana1.png");
				novel->setCharaC(0, "chara/remon1.png");

			}
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "その時はお札の力で難を逃れたんだけど…");
			novel->addSentence(0, "継", "今思えば…あの時の黒ずくめの人物の声は女性のものだったんだよ。");
			novel->addSentence(0, "バンダナ", "…ああ、そう言えばそうだった！てかお前の声だった！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "あらそうなの？こんな偶然ってあるのね…まあ人の声なんて案外似るものよね。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "偶然が過ぎないか…？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "それに、私がその黒ずくめの人物だったなんてあり得ないのよ。");
			novel->addSentence(0, "檸檬", "だって、ついさっき私だってそいつに襲われたんだもの。あなた達も一緒に居たでしょ？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "君は僕たちを信用させるために、その黒ずくめの人物に自分を襲わせるような真似をしたんだ。");
			novel->addSentence(0, "継", "そう、水無月さんを牢に閉じ込めボウガンで襲い、そして姿を消した黒ずくめの何者かの正体は…");

			novel->setEndTask(-1, CallFunc::create([this]() {
				addChild(mObjectList["remon"], 3, "remon");
				removeChildByName("back");

				auto label = Label::createWithTTF("檸檬にアイテムを突きつけよう", FONT_NAME, 30);
				label->setPosition(Vec2(427, 80));
				label->setColor(Color3B::WHITE);
				addChild(label, 5, "label");
				}));
			addChild(novel, 10, "novel");

			// mObjectList["flag"]->setState(1);
		}
	}

	void Remains::reasoning2() {
		getChildByName("remon")->runAction(Sequence::createWithTwoActions(
			FadeOut::create(0.5f), RemoveSelf::create()
		));
		getChildByName("label")->runAction(Sequence::createWithTwoActions(
			FadeOut::create(0.5f), RemoveSelf::create()
		));
		playSoundBS("SE/choice.ogg");

		auto novel = Novel::create();
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setCharaC(0, "chara/remon1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "この人形だよ");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "は？こんな小さい人形に何ができるっていうのよ？");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "宇沢さんが言っていたんだ。この学校には「人形遣い」の特殊能力を持つ生徒がいるって。");
		novel->addSentence(0, "継", "黒ずくめの人物が操られた人形なんだとしたら、色んなことに説明がつくんだよ。");
		novel->addSentence(0, "継", "まず、学校で僕たちを誘拐してここに連れてきた犯人はその人形だ。");
		novel->addSentence(0, "継", "これらの写真を見てほしい。");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				auto back = Sprite::create("bg/black.png");
				back->setPosition(Director::getInstance()->getVisibleSize() / 2);
				back->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(7.0f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
				addChild(back, 5, "back");
				for (int i = 0; i < 4; i++) {

					// if (i != 2) {
					auto spr = Sprite::create(StringUtils::format("chara/memory%d.png", i + 1));
					spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
					spr->setOpacity(0.0f);
					//if (i == 3) {
					//	spr->runAction(Sequence::create(DelayTime::create(2.0f * 3), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
					//}
					//else {
					spr->runAction(Sequence::create(DelayTime::create(2.0f * (float)i), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
					// }
					addChild(spr, 6, StringUtils::format("bg%d", i));
					// }
				}
				}),
			DelayTime::create(8.0f)
		));
		novel->addSentence(0, "継", "これらは、さっきの消えた黒ずくめの人物のマントについていたクロユリの記憶と、寿甘が学校から送ってきたものを合わせたものだ。");
		novel->addSentence(0, "継", "ここに写っている人形は黒ずくめの人物が現れた時には消えている");
		novel->setCharaR(0, "");
		novel->setCharaL(0, "");
		novel->setCharaC(0, "");
		novel->setBg(0, "chara/memory3.png");
		novel->addSentence(0, "継", "3枚目の写真なんか、人形が一人でに動き出しているように見えないかい？");
		//novel->setCharaR(0, "chara/tuguru1.png");
		//novel->setCharaL(0, "chara/bandana1.png");
		//novel->setCharaC(0, "chara/remon1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "…で、その人形を操っていたのが私だというの？");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "うん。その根拠もあるよ");
		novel->addSentence(0, "継", "実はこれらの写真の中に、君が関係するものが映り込んでいるんだ。");
		novel->addSentence(0, "継", "それは…");
		novel->addEvent(0, CallFunc::create([this, novel] {
			auto visibleSize = Director::getInstance()->getVisibleSize();

			novel->stopMessage();

			auto layer = Layer::create();
			layer->setCascadeOpacityEnabled(true);
			layer->setOpacity(0.0f);
			layer->runAction(FadeIn::create(0.2));
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);
			listener->onTouchBegan = [this, novel, layer](Touch* touch, Event* event) {
				auto next = layer->getChildByName("next");
				auto prev = layer->getChildByName("prev");

				// 正解ポイント
				if (mSelectMemory == 1 && Rect(490, 290, 40, 40).containsPoint(touch->getLocationInView())) {
					playSoundBS("SE/choice.ogg");
					getChildByName("layer_c")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2), RemoveSelf::create()));
					novel->resumeMessage();
				}
				// 間違いポイント
				else if (mSelectMemory == 2 && Rect(570, 275, 40, 40).containsPoint(touch->getLocationInView())) {
					playSoundBS("SE/choice.ogg");
					auto novel2 = Novel::create();
					novel2->setFontColor(0, Color3B::RED);
					novel2->addSentence(0, "檸檬", "この翼…やっぱりあの子が…");
					novel2->setFontColor(0, Color3B::BLUE);
					novel2->addEvent(0, CallFunc::create([this]() {
						takeDamage();
						if (mLife == 0) {
							getChildByName("layer_c")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2f), RemoveSelf::create()));
							getChildByName("novel2")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2f), RemoveSelf::create()));
						}
						}));
					novel2->addSentence(0, "継", "いや、違うんだ…");
					novel2->setEndTask(0, CallFunc::create([this]() {removeChildByName("novel2"); }));
					addChild(novel2, 12, "novel2");
				}
				// 間違いポイント
				else if (mSelectMemory == 4 && Rect(390, 180, 144, 300).containsPoint(touch->getLocationInView())) {
					playSoundBS("SE/choice.ogg");
					auto novel2 = Novel::create();
					novel2->setFontColor(0, Color3B::RED);
					novel2->addSentence(0, "檸檬", "この黒ずくめの人物が私だというの？さっきと言ってることが矛盾してるじゃない");
					novel2->addSentence(0, "檸檬", "それに私はこの時にはクラスの女子たちと一緒に居たからアリバイもあるわよ？");
					novel2->setFontColor(0, Color3B::BLUE);
					novel2->addEvent(0, CallFunc::create([this]() {
						takeDamage();
						if (mLife == 0) {
							getChildByName("layer_c")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2f), RemoveSelf::create()));
							getChildByName("novel2")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2f), RemoveSelf::create()));
						}
						}));
					novel2->addSentence(0, "継", "いや、違うんだ…");
					novel2->setEndTask(0, CallFunc::create([this]() {removeChildByName("novel2"); }));
					addChild(novel2, 12, "novel2");
				}
				// 次へ
				else if (next->getBoundingBox().containsPoint(touch->getLocationInView())) {
					if (mSelectMemory < 4) {
						mSelectMemory++;
						((Sprite*)layer->getChildByName("memory"))->setTexture(StringUtils::format("chara/memory%d.png", mSelectMemory));
					}
					if (mSelectMemory == 4) {
						next->setVisible(false);
					}
					else if (mSelectMemory != 1) {
						prev->setVisible(true);
					}
				}
				// 前へ
				else if (prev->getBoundingBox().containsPoint(touch->getLocationInView())) {
					if (mSelectMemory > 1) {
						mSelectMemory--;
						((Sprite*)layer->getChildByName("memory"))->setTexture(StringUtils::format("chara/memory%d.png", mSelectMemory));
					}
					if (mSelectMemory == 1) {
						prev->setVisible(false);
					}
					else if (mSelectMemory != 4) {
						next->setVisible(true);
					}
				}
				return true;
				};
			this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
			addChild(layer, 11, "layer_c");
			// 写真
			auto spr = Sprite::create("chara/memory1.png");
			spr->setPosition(visibleSize / 2);
			layer->addChild(spr, 0, "memory");
			// 矢印(→)
			spr = Sprite::create("record_next.png");
			spr->setPosition(854 - 60, 480 / 2.0f);
			layer->addChild(spr, 1, "next");
			// 矢印（←）
			spr = Sprite::create("record_next.png");
			spr->setPosition(60, 480 / 2.0f);
			spr->runAction(FlipX::create(true));
			spr->setVisible(false);
			layer->addChild(spr, 1, "prev");

			auto label = Label::createWithTTF("怪しいところをタップしよう", FONT_NAME, 30);
			label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
			label->setColor(Color3B::WHITE);
			label->enableOutline(Color4B::BLACK, 2);
			layer->addChild(label, 3, "label");
			}), true);
		novel->setBg(0, "chara/memory1.png");
		novel->addSentence(0, "継", "ここに映り込んでいるボールだ");
		novel->addSentence(0, "継", "寿甘の話によると、君は体育の時間に寿甘が飛ばしたボールを取りに行っていたみたいだね。");
		novel->addSentence(0, "継", "おそらく、あらかじめボール入れの中に魔球用のボールを混ぜておいていたんじゃないかな。");
		novel->addSentence(0, "継", "そしてボールを取りに行くふりをして、校舎裏に行ったんだ。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "さっきまで人形があなたたちを襲わせたって話じゃなかった？なんで私が様子を見に行かなきゃいけないのよ。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "至近距離で襲われたらバンダナは気づいて反撃するはずだ");
		novel->addSentence(0, "継", "だからボウガンで遠距離からバンダナを撃つためにそこに行ったんだ");
		novel->setBg(0, "chara/memory4.png");
		novel->addSentence(0, "継", "そして動けなくなったバンダナを人形が誘拐していったんだ");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "ふん、なるほどね。一応筋は通っているみたいね。");
		novel->addSentence(0, "檸檬", "でも私より先にもっと怪しむべき人物がいるんじゃないかしら？");
		novel->setBg(0, "chara/memory2.png");
		novel->addSentence(0, "檸檬", "こっちの写真を見てみて。ここに見えている翼って明らかにリアスのものよね？");
		novel->addSentence(0, "檸檬", "それに私に届いた手紙、赤文字で書かれてたんだけど、これってあなたたちのも同じなのよね？");
		novel->addSentence(0, "檸檬", "こんなことするのってリアスくらいしかいないじゃない");
		novel->setBg(0, "");
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setCharaC(0, "chara/remon1.png");

		// 日記を集めているか
		bool completeDiary = false;
		{
			auto userDef = UserDefault::getInstance();
			for (int i = 1; i <= 6; i++) {
				if (userDef->getBoolForKey(StringUtils::format("diary%d", i).c_str(), false)) {
					completeDiary = true;
				}
				else {
					completeDiary = false;
					break;
				}
			}
		}

		if (!completeDiary) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "それは…");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "…これは全部リアスが仕組んだことなの。");
			novel->addSentence(0, "檸檬", "探知の特殊能力を持つあの子なら、私たちがどこで何してるかなんて全部お見通しなんだわ。だからこんな犯行計画を実行できたの。");
			novel->addSentence(0, "檸檬", "やっぱりドラゴン族は人を殺せる民族だった…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "（何か引っかかるんだけど、切り返せる証拠品を持っていない…）");
			novel->setEndTask(0, CallFunc::create([this]() {gameover1(1); }));
		}
		else {
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "…リアスちゃんはこんなことしないよ");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "あら？今朝、あの子がバンダナさんのストーカーだってことを暴いたのはあなた自身じゃなかった？あれは見間違いだったのかしら？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "リアスちゃんは君みたいに大好きな人を傷つけるようなことはしないよ");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "…聞き捨てならないわね、どういうことかしら？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "君は彼女に罪を擦り付けるどころか、バンダナと一緒に殺すつもりだったんだ。その証拠だってあるよ。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "おもしろいわ、その証拠とやらを見せてみてよ");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "…わかった");
			novel->setEndTask(-1, CallFunc::create([this]() {
				mObjectList["remon"]->setOpacity(255.f);
				mObjectList["remon"]->setState(1);
				addChild(mObjectList["remon"], 3, "remon");
				removeChildByName("back");

				auto label = Label::createWithTTF("檸檬にアイテムを突きつけよう", FONT_NAME, 30);
				label->setPosition(Vec2(427, 80));
				label->setColor(Color3B::WHITE);
				addChild(label, 5, "label");
				}));
			novel->setEndTask(0);
		}
		addChild(novel, 10, "novel");
	}

	void Remains::reasoning3() {
		getChildByName("remon")->runAction(Sequence::createWithTwoActions(
			FadeOut::create(0.5f), RemoveSelf::create()
		));
		getChildByName("label")->runAction(Sequence::createWithTwoActions(
			FadeOut::create(0.5f), RemoveSelf::create()
		));
		playSoundBS("SE/choice.ogg");

		auto novel = Novel::create();
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setCharaC(0, "chara/remon1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "この日記はおそらく今回の誘拐計画について書かれているものだ");
		novel->setCharaR(0, "");
		novel->setCharaL(0, "");
		novel->setCharaC(0, "");
		novel->addEvent(0, CallFunc::create([this]() {
			auto layer = Layer::create();
			layer->setPosition(Vec2::ZERO);
			layer->setCascadeOpacityEnabled(true);
			layer->setOpacity(0.0f);
			layer->runAction(FadeIn::create(0.5f));
			addChild(layer, 9, "layer_c");
			auto back = Sprite::create("bg/black.png");
			back->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
			layer->addChild(back, 0, "back");
			back = Sprite::create("item/diary_a.png");
			back->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
			layer->addChild(back, 0, "diary");
			auto label = Label::createWithTTF("", FONT_NAME, 24);
			label->setPosition(Director::getInstance()->getVisibleSize() / 2);
			label->setTextColor(Color4B::BLACK);
			label->enableOutline(Color4B::WHITE, 2);
			label->setAlignment(TextHAlignment::CENTER);
			label->setString("幼いころずっと読んでいた大好きな絵本\n"
				"絵本の中のあの子が大好きでなんどもなんども読み返した\n"
				"\n"
				"大きくなって入学式の日に出会ったのはあの子と同じ瞳のーーーー\n"
				"私だけの物にしたいと思った");
			layer->addChild(label, 3, "label");
			}));
		novel->addSentence(0, "継", "書き手は幼い頃からドラゴン族に憧れていて、そして学校でドラゴン族の子孫の子と出会う。");
		novel->addEvent(0, CallFunc::create([this]() {
			auto layer = getChildByName("layer_c");
			auto label = (Label*)layer->getChildByName("label");

			label->setString("いつしかあの子と仲良くなっていた\n"
				"内気で恥ずかしがり屋のあの子の世話をする毎日\n"
				"私が何を考えているのか知らないで、あの子は楽しそうだった\n"
				"\n"
				"あの子はいつも全身にきれいな宝石を身に着けていた\n"
				"探知の能力で珍しい宝石を集めるのが得意だった\n"
				"じゃあこれはどうかしらとママの作ったかんざしを渡してみた\n"
				"あの子は「こんな素敵なもの見たことない！」とたいそう喜んでくれた\n"
				"あれからあの子はかんざしを毎日着けてきてくれた");
			}));
		novel->addSentence(0, "継", "内気なその子の面倒を見るようにして仲良くなっていくその様子は…まるで君とリアスちゃんのようじゃないかな。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "はっ、そんなものが証拠になるとでも？");
		novel->addSentence(0, "檸檬", "ドラゴン族の生き残りなんて今じゃそこら中にいるし、似たような性格の子だってそこそこいるんじゃないの？");
		novel->addSentence(0, "檸檬", "私達の知らない誰かの日記かもしれないじゃない");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "その言い訳は苦しいと思うぞ…");
		novel->addEvent(0, CallFunc::create([this]() {
			auto layer = getChildByName("layer_c");
			auto label = (Label*)layer->getChildByName("label");

			label->setString("ある日の体育の授業\n"
				"あの子が男子とぶつかって転んでしまった\n"
				"そいつに連れられて保健室にいたあの子の瞳は\n"
				"今まで見たことのない恋をした眼をしていた\n"
				"\n"
				"あれからあの子はあいつを追いかけ回すようになった\n"
				"私があげたかんざしもその日から着けてこなくなった\n\n"
				"あいつのせいで\n"
				"あいつのせいで、私の大切なあの子は…");
			}));
		novel->addSentence(0, "バンダナ", "…リアスとぶつかって保健室まで連れて行ったのは俺だ。あれはこっちが悪かったからな…");
		novel->addSentence(0, "バンダナ", "あいつが付いて回るようになったのはあれからだったような気がするな…");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "仮にそこに書かれているのがリアスだったとして、私は何も関係ないわ。");
		novel->addSentence(0, "檸檬", "あの子は神出鬼没だから、きっと他の誰かとも関わりがあったはず…");
		novel->addSentence(0, "？？？", "…それは違うよ");
		novel->addEvent(0, CallFunc::create([this]() {
			AudioEngine::stopAll();
			auto layer = getChildByName("layer_c");
			layer->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
			}));
		novel->addSentence(0, "檸檬", "！");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				playSoundBS("SE/goro03.ogg");
				getChildByName("door")->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f), RemoveSelf::create()));
				}),
			DelayTime::create(1.0f)
		));
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "ゴゴゴゴゴ…");
		novel->setCharaC(0, "chara/remon1.png");
		novel->setCharaR(0, "chara/rias1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リアス", "私の友達は檸檬ちゃんだけだったよ…ずっと…");
		novel->addSentence(0, "檸檬", "リアス…！");
		novel->addEvent(0, CallFunc::create([this]() {
			playSoundBS("BGM/underground.ogg", true);
			getChildByName("life")->runAction(FadeOut::create(0.5f));
			}));
		novel->setCharaL(0, "chara/suama1.png");
		novel->addSentence(0, "寿甘", "ふぅ…二人とも、なんとか無事だったようね！");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "寿甘！？…どうしてお前もここへ？");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘", "んーとね…");

		// 回想
		{
			novel->addEvent(0, CallFunc::create([this]() {
				// this->getChildByName("bg")->runAction(FadeOut::create(0.5f));
				auto bg = Sprite::create("bg/black.png");
				bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
				bg->setOpacity(0.0f);
				bg->runAction(FadeIn::create(0.5f));
				addChild(bg, 9, "black1");


				}));
			novel->addPauseEvent(0, Sequence::createWithTwoActions(
				CallFunc::create([this] {
					auto spr = Sprite::create("bg/black.png");
					spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
					spr->setOpacity(0.0f);
					addChild(spr, 0, "black2");
					}),
				DelayTime::create(1.0f)
			));

			novel->setFontColor(0, Color3B::BLACK);
			novel->setCharaC(0, "");
			novel->setCharaR(0, "");
			novel->setCharaL(0, "");

			novel->setBg(0, "bg/black.png");
			novel->addSentence(0, "", "寿甘がリアスから逃げて迷い込んだ森の中で");
			novel->setBg(0, "chara/scene8.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス", "…ひひひ…ひひひひひ………");
			novel->addSentence(0, "リアス", "やっと…追いついた……");
			novel->addSentence(0, "寿甘", "っ…");
			novel->setBg(0, "bg/black.png");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "リアスの指が私の首元にかかる");
			novel->addSentence(0, "", "私は、ぎゅっと目を閉じた…");
			novel->addSentence(0, "", "…");
			novel->setBg(0, "forest_run.png");
			novel->setCharaR(0, "chara/rias1.png");
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "", "私が恐る恐る目を開くとリアスの手にはかんざしが握られていた。");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス", "これ…私のだから…");
			novel->addSentence(0, "寿甘", "あ、そうだったの…ごめん…");
			novel->addSentence(0, "リアス", "あと…そのメモも…");
			novel->addSentence(0, "寿甘", "あ、ごめん…返すね…");
			novel->addSentence(0, "リアス", "………");
			novel->addSentence(0, "寿甘", "………");
			novel->addSentence(0, "寿甘", "…じゃあ、帰ろっか…");
			novel->setCharaC(0, "chara/scene12.png");
			novel->addSentence(0, "寿甘", "ここどこだろ…なんかお墓みたいなのがあるけど…");
			novel->addSentence(0, "リアス", "…ここに…私達のご先祖様が…眠ってるの…");
			novel->addSentence(0, "寿甘", "えっ ！そうなんだ…");
			novel->addSentence(0, "リアス", "…この先に…バンダナ様達がいるみたい…");
			novel->addSentence(0, "寿甘", "ほんと！？…この先って…この岩の隙間みたいなところかしら…？");
			novel->addSentence(0, "リアス", "うん…昔、ドラゴン族が隠れ家にしていたほら穴なの…");
			novel->addSentence(0, "寿甘", "なんでそんなところに二人が…あっ！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "バッサバッサ");
			novel->setCharaC(0, "chara/tsubasa2.png");
			novel->addSentence(0, "翼", "チュンチュン！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "翼くん！来てくれたのね！");
			novel->addSentence(0, "寿甘", "なになに…宇沢から言伝？…人形遣いの正体？…そうだったのね…");
			novel->addSentence(0, "リアス", "檸檬ちゃん…");
			novel->addSentence(0, "寿甘", "あ、あんたも知ってたのね");
			novel->addSentence(0, "リアス", "…行こ、これは私自身が決着を着けないといけないことだと思うから…");
			novel->addSentence(0, "寿甘", "そうね！早く二人を助けに行かなくちゃ！");
			novel->addSentence(0, "寿甘", "翼くん、誰かに私達がここに行ったと言うことを伝えておいてくれないかしら…念のためにね");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "翼", "チュンチュンチュン！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "あはは、そんなに心配しなくてもみんなで無事に戻ってくるって！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "バッサバッサ");
			novel->setCharaC(0, "chara/scene12.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "これで心配無用ね！行くわよ！");
			novel->addSentence(0, "リアス", "うん");
		}

		// 回想終わり
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				auto action = Sequence::createWithTwoActions(
					FadeOut::create(1.0f),
					RemoveSelf::create()
				);
				getChildByName("black1")->runAction(action);
				getChildByName("black2")->runAction(action->clone());
				}),
			DelayTime::create(1.0f)
		));
		novel->setBg(0, "");
		novel->setCharaR(0, "");
		novel->setCharaL(0, "chara/suama1.png");
		novel->setCharaC(0, "");

		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘", "…とかいうワケだったのよ");
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->setCharaC(0, "chara/remon1.png");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "なるほどね");
		novel->addSentence(0, "継", "これで水無月さんが人形遣いだってことも証明された…もう認めてくれないかな");
		novel->addSentence(0, "継", "どうして君がこんな事をしなければいけなかったのか、話してくれないかな。どうして、バンダナが傷付かなきゃいけなかったのか…");
		novel->setFontColor(0, Color3B::RED);
		novel->setCharaL(0, "chara/rias1.png");
		novel->addSentence(0, "リアス", "檸檬ちゃん、ごめんね…私のせいで…");
		novel->addSentence(0, "檸檬", "…は？…なんであんたのせいなんかになるのよ…");
		novel->addSentence(0, "檸檬", "何のためって、私がリアスが悲しむようなことをするはずがないじゃない。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->setCharaL(0, "chara/bandana1.png");
		novel->addSentence(0, "バンダナ", "お前なんかおかしくなってねえか？往生際が悪いってレベルじゃねえぞ…");
		int num = novel->addSentence(0, "継", "そうだよ。だって君の計画で最初に狙われていたのは…");
		novel->addSwitchEvent(0, 1, "リアスとバンダナ", 2, "継とバンダナ", 3, "リアスと檸檬");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "犯人の計画で当初誘拐する予定だった二人は？");

		// 不正解
		{
			// 選択: 継とバンダナ
			novel->setFontColor(2, Color3B::BLUE);
			novel->addSentence(2, "継", "僕とバンダナだったじゃないか");
			novel->setFontColor(2, Color3B::RED);
			novel->addSentence(2, "檸檬", "そうよ。だからリアスは関係ないの。");
			novel->setFontColor(2, Color3B::BLUE);
			novel->addSentence(2, "継", "あ、いや、そうじゃなくて…");
			novel->addSentence(2, "継", "（もう一度、日記を見返して考えてみよう）");
			novel->setJump(2, 0, num - 1);

			// 選択: リアスと檸檬
			novel->setFontColor(3, Color3B::BLUE);
			novel->addSentence(3, "継", "水無月さんとリアスちゃんだよ");
			novel->setFontColor(3, Color3B::RED);
			novel->addSentence(3, "檸檬", "…それは私が犯人だという主張を取り下げるということでいいのかしら");
			novel->setFontColor(3, Color3B::BLUE);
			novel->addSentence(3, "継", "あ、いや、そうじゃなくて…");
			novel->addSentence(3, "継", "（もう一度、日記を見返して考えてみよう）");
			novel->setJump(3, 0, num - 1);
		}

		// 選択: リアスとバンダナ
		novel->addSwitchEvent(1, 0);
		novel->addEvent(1, CallFunc::create([this]() {
			auto layer = Layer::create();
			layer->setPosition(Vec2::ZERO);
			layer->setCascadeOpacityEnabled(true);
			layer->setOpacity(0.0f);
			layer->runAction(FadeIn::create(0.5f));
			addChild(layer, 9, "layer_c");
			auto back = Sprite::create("bg/black.png");
			back->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
			layer->addChild(back, 0, "back");
			back = Sprite::create("item/diary_a.png");
			back->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
			layer->addChild(back, 0, "diary");
			auto label = Label::createWithTTF("", FONT_NAME, 24);
			label->setPosition(Director::getInstance()->getVisibleSize() / 2);
			label->setTextColor(Color4B::BLACK);
			label->enableOutline(Color4B::WHITE, 2);
			label->setAlignment(TextHAlignment::CENTER);
			label->setString("まずはあいつを手紙でおびき寄せる\n"
				"その後、あの子が探知であいつを探しにきた所を狙って人形に二人を誘拐させる\n"
				"\n"
				"ここに連れてきた二人を拷問器具で殺す\n"
				"二人分の血液とあの子の首を手に入れて\n"
				"私は生き返るのだ\n"
				"\n"
				"ドラゴン族のきれいなあの子の顔と\n"
				"あの強靭な男の血液があれば\n"
				"この国を焼き払う力を手に入れられるはずだ\n"
				"\n"
				"今こそ眠り続けていたこの積年の恨みを\n"
				"解き放つ時なのだ");
			layer->addChild(label, 3, "label");
			}));
		novel->setFontColor(1, Color3B::BLUE);
		novel->setCharaR(1, "");
		novel->setCharaL(1, "");
		novel->setCharaC(1, "");
		novel->addSentence(1, "継", "あの日記では、最初はバンダナとリアスちゃんを狙う計画だったじゃないか。");

		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "ええそうね、そうだったわ。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "ドラゴン族好きだっただけの君が、そこまでして成し遂げたいことってなんだったんだよ。生き返るって…どういうことなんだよ！");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リアス", "…え…もしかして…");
		novel->addEvent(0, CallFunc::create([this]() {
			AudioEngine::stopAll();
			auto layer = getChildByName("layer_c");
			layer->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
			}));
		novel->setCharaC(0, "chara/remon1.png");
		novel->addSentence(0, "檸檬", "…はぁ、もう時間稼ぎはおしまいなのかしらね。じゃあ、あんたはこれで用済みだわじゃあねバイバイさようなら。");
		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				// 画像作成
				Sprite* bg, * remon1, * remon2, * queen;
				{
					// 背景
					bg = Sprite::create("chara/scene13_back.png");
					bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					bg->setOpacity(0.0f);
					addChild(bg, 7, "black1");
					// 檸檬（立）
					remon1 = Sprite::create("chara/scene13_remon1.png");
					remon1->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					remon1->setOpacity(0.0f);
					addChild(remon1, 9, "remon1");
					// 檸檬（倒）
					remon2 = Sprite::create("chara/scene13_remon2.png");
					remon2->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					remon2->setOpacity(0.0f);
					addChild(remon2, 9, "remon2");
					// 女王
					queen = Sprite::create("chara/scene13_queen.png");
					queen->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
					queen->setOpacity(0.0f);
					addChild(queen, 8, "queen");

					setGetStill(21);
				}

				// 時間調整
				{
					// t  : 0 1 2 3 4 5 6 7 8
					// bg : iddddddddddddddddo
					// r1 : idddddddoo
					// r2 : ddddddddiidddoo
					// qu : ddddiiiiidddddddoo
					bg->runAction(Sequence::create(
						FadeIn::create(0.5f),
						DelayTime::create(8.0f),
						FadeOut::create(0.5f),
						RemoveSelf::create(),
						NULL));
					remon1->runAction(Sequence::create(
						FadeIn::create(0.5f),
						DelayTime::create(3.5f),
						FadeOut::create(1.0f),
						RemoveSelf::create(),
						NULL));
					remon2->runAction(Sequence::create(
						DelayTime::create(4.0f),
						FadeIn::create(1.0f),
						DelayTime::create(1.5f),
						FadeOut::create(1.0f),
						RemoveSelf::create(),
						NULL));
					queen->runAction(Sequence::create(
						DelayTime::create(2.0f),
						EaseSineOut::create(FadeIn::create(2.5f)),
						DelayTime::create(3.5f),
						FadeOut::create(1.0f),
						RemoveSelf::create(),
						NULL));
				}

				}),
			DelayTime::create(9.0f)
		));
		novel->setCharaC(0, "");
		novel->addSentence(0, "リアス", "檸檬ちゃんっ！！！");
		novel->setCharaC(0, "chara/queen1.png");
		novel->addEvent(0, CallFunc::create([this]() {
			playSoundBS("BGM/fear.ogg", true);
			}));
		novel->addSentence(0, "？？？", "ふふふ…来ちゃった");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "お前…一体どうやって…！？");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "？？？", "…人形遣いの能力って、剥製でもギリイケるみたいなのね。ちょっと檸檬ちゃんに頑張ってもらったの。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "つまり、君は彼女を操って…");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "？？？", "そ、ご名答！…まあ最初から操り人形だったのはこの子ってワケね。");
		novel->addSentence(0, "リリア", "…自己紹介が遅れたわね。私はリリア・アレキサンドライト。そこにいるリアスちゃんのご先祖様ってとこね。");
		novel->addSentence(0, "リリア", "私はね、身勝手な女王に愛する人を殺されてしまった可哀想な女の子…");
		novel->addSentence(0, "リリア", "だからね、私がこの国を滅ぼして新しい女王になってやるの。そのためにあなたたちには死んでもらわないとね。");
		novel->addSentence(0, "リリア", "うふふ、みんなもそれを望んでいるみたいだしね。きっとあの人も喜んでくれるわ…");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "グワアアアアァァァ…");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "寿甘", "キャーーーッッ！！！");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "リリアの後ろから次々とゾンビたちが這い出てくる");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "に、逃げよう！！");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リアス", "檸檬ちゃん！！起きてッ！！");
		novel->addSentence(0, "檸檬", "…………");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "こいつは俺が背負ってく！！先に行けッ！！");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "ふふふ、追いかけっこかしら…どこまで逃げ切れるのかしらね！");

		novel->setEndTask(0, CallFunc::create([this]() {
			Control::me->changeField("dangeon2");
			playSoundBS("SE/footsteps.ogg");
			}));

		addChild(novel, 10, "novel");
	}

	void Remains::gameover1(int hint) {
		AudioEngine::stopAll();
		playSoundBS("BGM/underground.ogg", true);

		auto novel = Novel::create();
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->setCharaL(0, "chara/bandana1.png");
		novel->setCharaC(0, "chara/remon1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "はぁ…これでわかったでしょ。私には何もやましいところなんてないの");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "…うん、そうみたいだね");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "じゃあ、こんな無駄な話し合いなんてしてないで、調査に戻るわよ。");
		novel->addSentence(0, "檸檬", "さあバンダナさん、行きましょ？");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "つぐるん…");
		novel->addSentence(0, "継", "この壁画のどこかに何かしらのメッセージが隠されているかもしれないからね。");
		novel->addSentence(0, "継", "バンダナも気を付けて行ってきてね。");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "檸檬", "さあ行くわよ");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "バンダナ", "お、おう…");
		novel->setCharaL(0, "");
		novel->setCharaC(0, "");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "…");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "さて、この辺りを調べてみるか");
		novel->setBg(0, "bg/black.png");
		novel->addSentence(0, "継", "…");
		novel->addSentence(0, "継", "……");
		novel->addSentence(0, "継", "………");
		novel->setBg(0, "");
		novel->addSentence(0, "継", "ダメだ…隅々まで調べてみたけど名前らしきものはどこにも書かれていない…");
		novel->setCharaR(0, "");
		novel->addSentence(0, "継", "この絵はおそらく、さっき読んだ絵本の物語の内容を表しているはず…");
		novel->addSentence(0, "継", "王族の女に連れられてマグマに焼かれてしまったドラゴン族の男…王族の女を殺して処刑されたドラゴン族の女…");
		novel->setCharaR(0, "chara/tuguru1.png");
		novel->addSentence(0, "継", "この場合、「女王」というのは誰を指すのだろう…");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "僕の思考がそこまで到達した時だった。");
		novel->addEvent(0, CallFunc::create([this] {AudioEngine::stopAll(); }));
		novel->addSentence(0, "", "ヒュン");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "っ…うぐっ…あぁ…っ！");
		novel->addEvent(0, CallFunc::create([this]() { playSoundBS("BGM/fear.ogg", true); }));
		novel->setCharaR(0, "");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "腹部に今まで感じたことのない激しい痛みを感じ、たまらずその場にうずくまった。");
		novel->setFontColor(0, Color3B::BLUE);
		novel->addSentence(0, "継", "…き、君は…っ");
		novel->setFontColor(0, Color3B::BLACK);
		novel->addSentence(0, "", "痛みで遠のく意識の中、僕が見たのは…");

		novel->setBg(0, "chara/bad4.png");
		setGetStill(20);

		novel->addEvent(0, CallFunc::create([this]() {
			// this->getChildByName("bg")->runAction(FadeOut::create(0.5f));
			auto bg = Sprite::create("bg/black.png");
			bg->setOpacity(0.0f);
			bg->runAction(FadeIn::create(0.5f));
			bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
			addChild(bg, 9, "black");
			}));
		novel->addSentence(0, "", "BAD END4「地獄の底で」");

		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				auto spr = Sprite::create("bg/black.png");
				spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
				spr->setOpacity(0.0f);
				addChild(spr, 0, "bg");
				}),
			DelayTime::create(1.0f)
		));

		novel->addEvent(0, CallFunc::create([this, novel] {
			AudioEngine::stopAll();
			}));
		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "");
		novel->addSentence(0, "", "…");
		novel->setCharaR(0, "chara/celine1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ", "…なんてことにならないように、私がヒントを差し上げますね。");

		if (hint == 0) {
			novel->addSentence(0, "セリーヌ", "今回の敗因は選択を間違い続けてしまったことのようですね。");
			novel->addSentence(0, "セリーヌ", "一回目にどんな選択をしたか思い出して、次は間違えないようにしましょう。");
		}
		else if (hint == 1) {
			novel->addSentence(0, "セリーヌ", "檸檬様を黙らせるにはchapter2とchapter4で日記の切れ端を集める必要があります。");
			novel->addSentence(0, "セリーヌ", "chapter2で集める日記の切れ端は4枚です。同じ場所を二度調べないと見つからなかったりすることもありますので、隅々まで探してみてください。");
			novel->addSentence(0, "セリーヌ", "chapter4では机の上の日記を調べれば残りの2枚が取得できます。");
			novel->addSentence(0, "セリーヌ", "日記に関しては見つけた時点で取得状態を引き継げるので、そのまま戻ってきて構いません。");
		}

		novel->addSentence(0, "セリーヌ", "では、検討を祈ります。");

		novel->addEvent(0, CallFunc::create([this] {
			AudioEngine::stopAll();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			}));
		novel->addSentence(0, "", "");

		novel->setEndTask(-1);
		addChild(novel, 10, "novel");

	}

	void Remains::takeDamage() {
		mLife--;

		auto life = (Sprite*)getChildByName("life")->getChildByName(StringUtils::format("life%d", mLife));
		life->runAction(Spawn::createWithTwoActions(FadeOut::create(1.0f), JumpBy::create(1.0f, Vec2::ZERO, 10.0f, 5)));

		playSoundBS("SE/tm2_hit004.ogg");

		if (mLife == 0) {
			getChildByName("novel")->runAction(Sequence::create(
				FadeOut::create(1.0f),
				RemoveSelf::create(),
				CallFunc::create([this]() {gameover1(0); }), NULL
			));
		}
	}

	void Dangeon2::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "地下迷宮2";

		auto bg = Sprite::create("dangeon_back.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);

		// ステージ
		std::vector<std::vector<int>> stage = {
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
			{ 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1 },
			{ 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
			{ 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1 },
			{ 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
			{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
			{ 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1 },
			{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		};
		mDangeonC = std::make_shared<DangeonC>(stage, DangeonC::Pos{ 1, 11 }, DangeonC::north);
		mDangeonC->setEnemyPos(1, 14);

		// 壁画像
		Sprite* wall;
		wall = Sprite::create("dangeon_bl.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backL());
		addChild(wall, 1, "wallBL");
		wall = Sprite::create("dangeon_bc.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backC());
		addChild(wall, 2, "wallBC");
		wall = Sprite::create("dangeon_br.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->backR());
		addChild(wall, 1, "wallBR");
		wall = Sprite::create("dangeon_fl.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->frontL());
		addChild(wall, 3, "wallFL");
		wall = Sprite::create("dangeon_fr.png");
		wall->setPosition(visibleSize / 2);
		wall->setOpacity(255.0f * mDangeonC->frontR());
		addChild(wall, 3, "wallFR");

		// 移動
		auto move = ObjectN::create();
		move->setArea(Rect(350, 150, 160, 160));
		move->setCursor(Cursor::FORWARD);
		move->setTouchEvent(CallFunc::create([this]() {	mDangeonC->toFront(); this->move(); playSoundBS("SE/footsteps.ogg"); }));
		addObject(move, "forward", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(185, 420, 480, 60));
		move->setCursor(Cursor::BACK);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toBack(); this->move(); }));
		addObject(move, "back", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(0, 30, 80, 400));
		move->setCursor(Cursor::LEFT);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toLeft(); this->move(); }));
		addObject(move, "left", 2, true);
		move = ObjectN::create();
		move->setArea(Rect(774, 30, 80, 400));
		move->setCursor(Cursor::RIGHT);
		move->setTouchEvent(CallFunc::create([this]() { mDangeonC->toRight(); this->move(); }));
		addObject(move, "right", 2, true);

		// スタート
		auto start = ObjectN::create();
		start->setTexture("dangeon_start.png");
		start->setArea(Rect(350, 150, 160, 210));
		start->setCursor(Cursor::ENTER);
		// start->setFieldChangeEvent("aisle");
		start->setTouchEvent(CallFunc::create([this]() { mObjectList["start"]->setState(1); }));
		addObject(start, "start", 3, false);

		// ゴール
		auto goal = ObjectN::create();
		goal->setTexture("dangeon_goal.png");
		goal->setArea(Rect(350, 150, 160, 210));
		goal->setCursor(Cursor::FORWARD);
		goal->setFieldChangeEvent("deadend");
		goal->setTouchEvent(CallFunc::create([this]() {	mObjectList["goal"]->setState(1); }));
		addObject(goal, "goal", 3, false);

		// 敵
		{
			auto enemy = Sprite::create("dangeon_queen1.png");
			enemy->setPosition(visibleSize / 2.0f);
			enemy->setOpacity(0.0f);
			addChild(enemy, 4, "enemy1");
			enemy = Sprite::create("dangeon_queen2.png");
			enemy->setPosition(visibleSize / 2.0f);
			enemy->setOpacity(0.0f);
			addChild(enemy, 4, "enemy2");
		}

		// マップ
		{
			const int dsX = 10, dsY = 80, size = 10;
			auto mapLayer = Layer::create();
			mapLayer->setPosition(Vec2(Vec2::ZERO.x + dsX, Vec2::ZERO.y - dsY));
			mapLayer->setCascadeOpacityEnabled(true);
			mapLayer->setOpacity(0.0f);
			// mapLayer->setPosition(Vec2::ZERO);
			this->addChild(mapLayer, 5, "map");

			for (int i = 0; i < stage.size(); i++) {
				for (int j = 0; j < stage[i].size(); j++) {
					auto pos = Vec2(j * size, visibleSize.height - size * i);
					auto square = DrawNode::create();
					if (UserDefault::getInstance()->getBoolForKey("dangeon2_hint", false) && stage[i][j]) {
						square->drawSolidRect(pos, Vec2(pos.x + 10, pos.y - 10), Color4F::WHITE);
					}
					else {
						square->drawRect(pos, Vec2(pos.x + 10, pos.y - 10), Color4F::WHITE);
					}
					square->setOpacity(255.0f * 0.5f);
					mapLayer->addChild(square, 0, StringUtils::format("map%d-%d", j, i));
				}
			}

			// プレイヤー
			auto pPos = mDangeonC->getPos();
			auto player = Label::createWithTTF("↑", FONT_NAME, 10);
			player->setTextColor(Color4B::YELLOW);
			player->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			player->setPosition(Vec2(pPos.x * size, visibleSize.height - pPos.y * size));
			mapLayer->addChild(player, 1, "player");

			// 敵
			auto enemy = Sprite::create();
			auto rect = Rect(0, 0, size, size);
			auto ePos = mDangeonC->getEnemyPos();
			auto pos = Vec2(ePos.x * size, visibleSize.height - ePos.y * size);
			enemy->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			enemy->setPosition(pos);
			enemy->setTextureRect(rect);
			enemy->setColor(Color3B::RED);
			mapLayer->addChild(enemy, 1, "enemy");

			// ゴール
			auto goal = Sprite::create();
			pos = Vec2(13 * size, visibleSize.height - 0 * size);
			goal->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			goal->setPosition(pos);
			goal->setTextureRect(rect);
			goal->setColor(Color3B::BLUE);
			mapLayer->addChild(goal, 1, "goal");
		}
	}

	void Dangeon2::changedField() {
		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "クソッ…また真っ暗じゃねーか！");
			novel->addSentence(0, "バンダナ", "寿甘！道案内してくれ！");
			novel->setCharaR(0, "chara/suama1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "そんなこと言われたって、覚えてないわよ！やけに広くて入り組んでるみたいだったし…");
			novel->setCharaL(0, "chara/rias1.png");
			novel->addSentence(0, "リアス", "……それなら私が…");
			novel->addEvent(0, CallFunc::create([this]() { this->getChildByName("map")->runAction(FadeIn::create(0.5f)); }));
			novel->addSentence(0, "リアス", "青いところがゴールだから、そこに向かって。矢印が私たち、赤いのがリリア様…");
			novel->setCharaR(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "リアスちゃん、助かるよ。さあ、急ごう…！");
			novel->addEvent(0, CallFunc::create([this]() { mObjectList["flag"]->setState(1); }));

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}

		if (!getChildByName("forward")) {
			if (mObjectList["start"]->getState()) {
				mDangeonC->setPos(1, 5);
				mDangeonC->setDirec(DangeonC::north);
				move();
			}
			else if (mObjectList["goal"]->getState()) {
				mDangeonC->setPos(6, 0);
				mDangeonC->setDirec(DangeonC::south);
				move();
			}
		}
		mObjectList["start"]->setState(0);
		mObjectList["goal"]->setState(0);
	}

#pragma region サブ関数
	void Dangeon2::DrawEnemy() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		int dx = mDangeonC->getPos().x - mDangeonC->getEnemyPos().x, dy = mDangeonC->getPos().y - mDangeonC->getEnemyPos().y;

		int imageNum = 0;
		switch (mDangeonC->getDirec())
		{
		case DangeonC::north:
			if (dx == 0) {
				if (dy == 1)imageNum = 1;
				else if (dy == 2 && !mDangeonC->backC())imageNum = 2;
			}
			break;
		case DangeonC::east:
			if (dy == 0) {
				if (dx == -1)imageNum = 1;
				else if (dx == -2 && !mDangeonC->backC())imageNum = 2;
			}
			break;
		case DangeonC::south:
			if (dx == 0) {
				if (dy == -1)imageNum = 1;
				else if (dy == -2 && !mDangeonC->backC())imageNum = 2;
			}
			break;
		case DangeonC::west:
			if (dy == 0) {
				if (dx == 1)imageNum = 1;
				else if (dx == 2 && !mDangeonC->backC())imageNum = 2;
			}
			break;
		default:
			break;
		}
		switch (imageNum)
		{
		case 0:
			getChildByName("enemy1")->runAction(FadeOut::create(0.5f));
			getChildByName("enemy2")->runAction(FadeOut::create(0.5f));
			break;
		case 1:
			getChildByName("enemy1")->runAction(FadeIn::create(0.5f));
			getChildByName("enemy2")->runAction(FadeOut::create(0.5f));
			break;
		case 2:
			getChildByName("enemy1")->runAction(FadeOut::create(0.5f));
			getChildByName("enemy2")->runAction(FadeIn::create(0.5f));
			break;
		default:
			break;
		}

		// 捕まったら
		if (dx == 0 && dy == 0)
		{
			mObjectList["flag"]->setState(2);

			// 移動禁止
			if (getChildByName("forward"))removeChildByName("forward");
			if (getChildByName("back"))removeChildByName("back");
			if (getChildByName("left"))removeChildByName("left");
			if (getChildByName("right"))removeChildByName("right");

			auto hand = Sprite::create("hand01.png");
			hand->setPosition((visibleSize / 4) * 3);
			hand->setOpacity(0.0f);
			hand->runAction(Spawn::create(
				FadeIn::create(0.5f),
				ScaleBy::create(1.0f, 2.0f),
				MoveBy::create(1.0f, Vec2(-20.0f, 0)),
				NULL
			));
			addChild(hand, 5, "handR");
			hand = Sprite::create("hand01.png");
			hand->setPosition(visibleSize / 4);
			hand->setOpacity(0.0f);
			hand->setFlippedX(true);
			hand->runAction(Spawn::create(
				FadeIn::create(0.5f),
				ScaleBy::create(1.0f, 2.0f),
				MoveBy::create(1.0f, Vec2(20.0f, 0)),
				NULL
			));
			addChild(hand, 5, "handL");

			this->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFunc::create([this]() {
					playSoundBS("SE/tm2_hit004.ogg");
					}),
				FadeOut::create(0.5f),
				DelayTime::create(1.0f),
				CallFunc::create([this]() { gameover(); }),
				NULL
			));
		}
	}
#pragma endregion

	void Dangeon2::move() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto pPos = mDangeonC->getPos();

		// 壁
		{
			auto wall = getChildByName("wallBL");
			if (mDangeonC->backL()) {
				wall->runAction(FadeIn::create(0.25f));
			}
			else {
				wall->runAction(FadeOut::create(0.25f));
			}
			wall = getChildByName("wallBC");
			if (mDangeonC->backC()) {
				wall->runAction(FadeIn::create(0.25f));
				if (getChildByName("forward")) {
					removeChildByName("forward");
				}
			}
			else {
				wall->runAction(FadeOut::create(0.25f));
				if (!getChildByName("forward")) {
					addChild(mObjectList["forward"], 2, "forward");
				}
			}
			wall = getChildByName("wallBR");
			if (mDangeonC->backR()) {
				wall->runAction(FadeIn::create(0.25f));
			}
			else {
				wall->runAction(FadeOut::create(0.25f));
			}
			wall = getChildByName("wallFL");
			if (mDangeonC->frontL()) {
				wall->runAction(FadeIn::create(0.25f));
			}
			else {
				wall->runAction(FadeOut::create(0.25f));
			}
			wall = getChildByName("wallFR");
			if (mDangeonC->frontR()) {
				wall->runAction(FadeIn::create(0.25f));
			}
			else {
				wall->runAction(FadeOut::create(0.25f));
			}

			// 敵
			{
				DrawEnemy();
			}
		}

		// スタート・ゴール
		{
			// スタート
			if (pPos.x == 1 && pPos.y == 5 && mDangeonC->getDirec() == DangeonC::south) {
				if (!getChildByName("start")) {
					addChild(mObjectList["start"], 3, "start");
				}
			}
			else {
				if (getChildByName("start")) {
					removeChildByName("start");
				}
			}

			// ゴール
			if (pPos.x == 13 && pPos.y == 0 && mDangeonC->getDirec() == DangeonC::north) {
				if (!getChildByName("goal")) {
					addChild(mObjectList["goal"], 3, "goal");
				}
			}
			else {
				if (getChildByName("goal")) {
					removeChildByName("goal");
				}
			}
		}

		// マップ
		{
			auto map = getChildByName("map");

			// プレイヤー
			auto player = (Label*)map->getChildByName("player");
			const int size = 10;
			player->setPosition(Vec2(pPos.x * size, visibleSize.height - pPos.y * size));
			switch (mDangeonC->getDirec())
			{
			case DangeonC::north:
				player->setString("↑");
				break;
			case DangeonC::east:
				player->setString("→");
				break;
			case DangeonC::south:
				player->setString("↓");
				break;
			case DangeonC::west:
				player->setString("←");
				break;
			default:
				break;
			}

			// 敵
			auto enemy = map->getChildByName("enemy");
			auto ePos = mDangeonC->getEnemyPos();
			auto pos = Vec2(ePos.x * size, visibleSize.height - ePos.y * size);
			enemy->setPosition(pos);
		}
	}

	void Dangeon2::update(float delta) {
		Field::update(delta);

		if (mObjectList["flag"]->getState() == 1) {
			auto fps = floor(1.0 / Director::getInstance()->getAnimationInterval());
			int wait_time = 0;

			// 上に行くほど速くなる
			int player_y = mDangeonC->getPos().y;
			if (player_y > 8) {
				wait_time = fps * 2;
			}
			else if (player_y > 4)
			{
				wait_time = fps * 1;
			}
			else {
				wait_time = fps * 0.5;
			}

			if (mEnemyTime > wait_time) {
				mDangeonC->moveEnemy();
				mEnemyTime = 0;

				// 敵の表示を更新する
				DrawEnemy();
			}

			mEnemyTime++;
		}

		// 敵
		auto map = getChildByName("map");
		const int size = 10;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto enemy = map->getChildByName("enemy");
		auto ePos = mDangeonC->getEnemyPos();
		auto pos = Vec2(ePos.x * size, visibleSize.height - ePos.y * size);
		enemy->setPosition(pos);
	}

	void Dangeon2::gameover() {
		AudioEngine::stopAll();
		this->setCascadeOpacityEnabled(false);
		auto bg = Sprite::create("bg/black.png");
		bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
		addChild(bg, 9, "black");

		auto novel = Novel::create();
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "…ふぅ。これで準備は整ったのかしら。");
		novel->addSentence(0, "リリア", "さあ、ここからは私たちの時代よ");
		novel->addSentence(0, "リリア", "私たちの苦しみを、存分に思い知ればいいわ");

		novel->setBg(0, "chara/bad5.png");
		novel->addSentence(0, "", "BAD END5「女王の復讐」");
		setGetStill(22);

		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				}),
				DelayTime::create(1.0f)
				));


		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "");
		novel->addSentence(0, "", "…");
		novel->setCharaR(0, "chara/celine1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ", "…なんていうゴア展開は私が許しませんので、もう少しだけがんばってください。");
		novel->addSentence(0, "セリーヌ", "ここでもヒントをお出ししたいところなのですが、今回は違う形でご協力させていただくことにします。");
		novel->addSentence(0, "セリーヌ", "リアス様の能力を少しだけ強化いたしました。これで少しはやりやすくなると思います。");

		auto userDef = UserDefault::getInstance();

		// すでにヒントモードになっていたら解除を選択できるようにする
		if (userDef->getBoolForKey("dangeon2_hint", false))
		{
			novel->addSentence(0, "セリーヌ", "…と言っても、あなたは既にその力をお試しになっているようですね。");
			novel->addSentence(0, "セリーヌ", "いかがでしたか？チート過ぎてつまらないということであれば、この力を解除して再挑戦してみるのもありかと思いますが。");
			novel->addSwitchEvent(0, 1, "はい", 2, "いいえ");
			novel->setFontColor(0, Color3B::BLACK);
			int num = novel->addSentence(0, "", "地下迷宮2の壁可視化モードを解除しますか？");

			// はい
			novel->setFontColor(1, Color3B::RED);
			novel->addSentence(1, "セリーヌ", "うふふ…頼もしい限りです");
			novel->addEvent(1, CallFunc::create([this, userDef]() {
				userDef->setBoolForKey("dangeon2_hint", false);
				userDef->flush();
				}));
			novel->addSentence(1, "セリーヌ", "能力は解除しました。くれぐれもお気をつけて…");
			novel->setJump(1, 0, num + 1);

			// いいえ
			novel->setFontColor(2, Color3B::RED);
			novel->addSentence(2, "セリーヌ", "さようでございますか。まあ、安全第一ですので無理せず慎重にお願いします。");
			novel->addSentence(2, "セリーヌ", "…強いてヒントをお出しするとしたら、マップ上で上部に行くほど追跡者様もスピードアップいたしますので、少々急いだほうがいいかもしれません。");
			novel->setJump(2, 0, num + 1);
		}

		novel->addSentence(0, "セリーヌ", "では、検討を祈ります。");

		novel->addEvent(0, CallFunc::create([this] {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			}));
		novel->addSentence(0, "", "");

		novel->setEndTask(-1);
		addChild(novel, 10, "novel");

		userDef->setBoolForKey("dangeon2_hint", true);
		userDef->flush();
	}

	void DeadEnd::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "地下迷宮の出口";

		//auto bg = Sprite::create("cave.png");
		//bg->setPosition(visibleSize / 2);
		//addChild(bg, 0, "bg");

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void DeadEnd::changedField() {
		AudioEngine::stopAll();

		if (mObjectList["flag"]->getState() == 0) {
			auto novel = Novel::create();
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "よし！ここを抜けたら、あとは一本道のはず…！");
			novel->addSentence(0, "寿甘", "みんな！着いてきてる？");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "…うん、なんとか");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス", "私も…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "俺はまだまだ余裕だぜ！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リリア", "………マァァァ……テェェェ………");
			novel->addSentence(0, "寿甘", "げ！まだ着いてきてる…入口まで走るよ！");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "…");
			novel->addSentence(0, "", "……");
			novel->addSentence(0, "", "………");
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "はぁ…はぁ…");
			novel->addSentence(0, "継", "やっと…出られた……");
			novel->addSentence(0, "継", "…と思ったのに………");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->setBg(0, "cave.png");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "行き止まりかよッ…クソ……ッ");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "そんな！来た時はこんな風になってなかったのに…！");
			novel->setCharaC(0, "chara/queen1.png");
			novel->addSentence(0, "リリア", "ふふふ…もう逃げられないわね……");

			auto userDef = UserDefault::getInstance();
			if (!userDef->getBoolForKey("celine", false)) {
				novel->addEvent(0, CallFunc::create([this]() {
					this->runAction(Sequence::create(
						DelayTime::create(1.0f),
						CallFunc::create([this]() {
							playSoundBS("SE/tm2_hit004.ogg");
							}),
						FadeOut::create(0.5f),
						DelayTime::create(1.0f),
						CallFunc::create([this]() { gameover(); }),
						NULL
					));
					}));
				novel->setEndTask(0);
				addChild(novel, 10, "novel");
				return;
			}

			novel->addEvent(0, CallFunc::create([this]() {
				playSoundBS("SE/bom16.ogg");
				}));
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "ドッカーン！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ", "な、なんの音だ…？");
			novel->setCharaL(0, "");
			novel->setCharaC(0, "");
			novel->setCharaR(0, "");
			//novel->setBg(0, "chara/scene14.png");
			novel->addPauseEvent(0, Sequence::createWithTwoActions(
				CallFunc::create([this] {
					playSoundBS("SE/bom16.ogg");
					setGetStill(23);
					auto spr = Sprite::create("chara/scene14.png");
					spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
					spr->setOpacity(0.0f);
					spr->runAction(
						FadeIn::create(1.0f)
					);
					addChild(spr, 0, "scene14");
					}),
				DelayTime::create(2.0f)
			));
			novel->setBg(0, "");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "セリーヌ", "ふぅ…なんとか間に合いましたね");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "セリーヌ！");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "セリーヌ", "皆様、お待たせいたしました。急いでこの馬に乗ってください。後ろにも何体か控えております。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "助かるよ！さあ、みんな乗って！");
			novel->addSentence(0, "バンダナ", "おう！水無月は…俺らで挟んで乗るしかないか");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "よいしょっと…リアスちゃんも！大丈夫？");
			novel->addSentence(0, "リアス", "うん…！");
			novel->addSentence(0, "リリア", "させるかぁぁぁァァァァアアア！！！！！");
			novel->addEvent(0, CallFunc::create([this]() {
				playSoundBS("SE/tm2_hit004.ogg");
				}));
			novel->addSentence(0, "セリーヌ", "あなたはここで眠っててください");
			novel->addSentence(0, "セリーヌ", "では、皆様行きましょうか");
			novel->addEvent(0, CallFunc::create([this]() {
				playSoundBS("SE/footsteps.ogg");
				auto spr = getChildByName("scene14");
				spr->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create()));
				}));
			novel->setBg(0, "bg/black.png");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "…");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "セリーヌは、どうしてここが分かったの？");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "セリーヌ", "継様をお迎えに学校まで来たのですが、寿甘様が行方不明になった継様達を探しに行かれたという話を聞いて");
			novel->addSentence(0, "セリーヌ", "その寿甘様の足取りを追っている内に、この抜け道の入り口に辿り着いたというわけです。");
			novel->addSentence(0, "セリーヌ", "辺りに悪い瘴気が漂っていたので…念のため応援を呼んでおいて正解でしたね。");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "なるほど…心配をかけたね");
			novel->addSentence(0, "継", "こっちも色々あってね…実は…");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "", "…");
			novel->addSentence(0, "", "……");
			novel->addSentence(0, "", "………");
			novel->addEvent(0, CallFunc::create([this] {
				// クリア
				AudioEngine::stopAll();
				this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([this] {Control::me->setEndFlag(); }), NULL));
				}));

			novel->setEndTask(0);
			addChild(novel, 10, "novel");
		}
	}

	void DeadEnd::gameover() {
		AudioEngine::stopAll();
		this->setCascadeOpacityEnabled(false);
		auto bg = Sprite::create("bg/black.png");
		bg->setPosition(Director::getInstance()->getVisibleSize() / 2.0f);
		addChild(bg, 9, "black");

		auto novel = Novel::create();
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "リリア", "…ふぅ。これで準備は整ったのかしら。");
		novel->addSentence(0, "リリア", "さあ、ここからは私たちの時代よ");
		novel->addSentence(0, "リリア", "私たちの苦しみを、存分に思い知ればいいわ");

		novel->setBg(0, "chara/bad5.png");
		novel->addSentence(0, "", "BAD END5「女王の復讐」");

		novel->addPauseEvent(0, Sequence::createWithTwoActions(
			CallFunc::create([this] {
				}),
				DelayTime::create(1.0f)
				));

		novel->setFontColor(0, Color3B::BLACK);
		novel->setBg(0, "");
		novel->addSentence(0, "", "…");
		novel->setCharaR(0, "chara/celine1.png");
		novel->setFontColor(0, Color3B::RED);
		novel->addSentence(0, "セリーヌ", "…なんていうゴア展開は私が許しませんので、もう少しだけがんばってください。");
		novel->addSentence(0, "セリーヌ", "……大変申し上げにくいのですが、この結末になってしまう原因は、私の力不足が原因のようです。");
		novel->addSentence(0, "セリーヌ", "chapter3で私が寿甘さんの後を追いかけるパートがあったかと思いますが、そこで上手く寿甘さんの来た道を辿れるかどうかが、この状況を打開する鍵になっております。");
		novel->addSentence(0, "セリーヌ", "この結末に辿り着いてしまっているので、失敗してしまっているのかと思いますが、そこをクリアした上でもう一度チャレンジしてくださいませ。");

		novel->addSentence(0, "セリーヌ", "では、検討を祈ります。");

		novel->addEvent(0, CallFunc::create([this] {
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Title::createScene(), Color3B::WHITE));
			}));
		novel->addSentence(0, "", "");

		novel->setEndTask(-1);
		addChild(novel, 10, "novel");
	}
}