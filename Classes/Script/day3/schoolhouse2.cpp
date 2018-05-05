#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

namespace day3 {
	void Corridor::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "廊下";

		auto bg = Sprite::create("corridor.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");


		auto remon = ObjectN::create();
		remon->setTexture("remon.png");
		remon->setArea(Rect(30, 110, 140, 370));
		remon->setCursor(Cursor::NEW);
		remon->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["remon"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/remon1.png");
				novel->addSentence(0, "寿甘", "ちょっといい？");
				novel->addSentence(0, "檸檬", "何かしら");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかったー？");
				novel->addSentence(0, "檸檬", "さあ、知らないわ");
				novel->addSentence(0, "寿甘", "そっかー…あ、そういえば");
				novel->addSentence(0, "寿甘", "さっきの体育でボール拾いに行ってくれてありがとうね！");
				novel->addSentence(0, "寿甘", "魔球用ボールが入ってたなんて気付かなくてさー…飛ばしすぎちゃった！");
				novel->addSentence(0, "檸檬", "…ああ、いいのよ。大したことないわ");
				novel->addSentence(0, "檸檬", "それじゃあ、私は用事があるからこれで");
				novel->addSentence(0, "檸檬", "じゃあね");
				novel->setCharaR(0, "");
				novel->addEvent(0, CallFunc::create([this] (){
					mObjectList["remon"]->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f),RemoveSelf::create()));
				}));
				novel->addSentence(0, "寿甘", "うん、またねー！");
				novel->addSentence(0, "寿甘", "帰っちゃった…");
				mObjectList["remon"]->setState(1);


				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(remon, "remon", 3, true);

		auto entrance = ObjectN::create();
		entrance->setArea(Rect(784, 0, 70, 480));
		entrance->setCursor(Cursor::RIGHT);
		entrance->setFieldChangeEvent("entrance");
		addObject(entrance, "entrance", 2, true);

		auto classroom = ObjectN::create();
		classroom->setArea(Rect(420, 120, 90, 360));
		classroom->setCursor(Cursor::ENTER);
		classroom->setFieldChangeEvent("classroom");
		addObject(classroom, "classroom", 2, true);

		auto artroom = ObjectN::create();
		artroom->setArea(Rect(175, 180, 145, 150));
		artroom->setCursor(Cursor::FORWARD);
		artroom->setFieldChangeEvent("artroom");
		addObject(artroom, "artroom", 2, true);

		auto flag = ObjectN::create();
		addObject(flag, "flag", 0, false);
	}

	void Corridor::changedField() {
	}

	void ClassRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "教室";

		auto bg = Sprite::create("classroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto usawa = ObjectN::create();
		usawa->setTexture("usawa.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::NEW);
		usawa->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["usawa"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "寿甘", "おい宇沢");
				novel->addSentence(0, "宇沢", "なんですか、いきなり呼び捨てにして…");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかった？");
				novel->addSentence(0, "宇沢", "うーん…私も今戻ったところなので見てないですねぇ…");
				novel->addSentence(0, "寿甘", "あっそ、新聞部もその程度なのね、じゃあな");
				novel->addSentence(0, "宇沢", "ああああ待ってください！！…そういえばこんな噂があります");
				novel->addSentence(0, "宇沢", "バンダナさんが継様に言い寄っているところを見た人がいたとか…これは禁断の三角関係の香りが…");
				novel->addSentence(0, "寿甘", "えっ……うそ…………そんな………………");
				novel->addSentence(0, "宇沢", "あ、嘘です…");
				novel->addSentence(0, "寿甘", "……");
				mObjectList["usawa"]->setState(1);
				mObjectList["usawa"]->setCursor(Cursor::INFO);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["usawa"]->getState() == 1) {
				if (getObjState("backyard","flag") == 2) {
					// 裏庭探索後
					if ((getObjState("gate", "crow") == 2) &&
						mObjectList["memo"]->getState() == 1 &&
						getObjState("gate","cenotaph") == 1) {
						// 謎解きモード
						auto novel = Novel::create();

						novel->setFontColor(0, Color3B::RED);
						novel->setCharaL(0, "chara/suama1.png");
						novel->setCharaR(0, "chara/usawa1.png");
						novel->addSentence(0, "宇沢", "準備はできました？");
						novel->addSentence(0, "寿甘", "うん、ばっちり");

						AudioEngine::stopAll();
						int n;
						novel->addEvent(0, CallFunc::create([this] { AudioEngine::play2d("BGM/mystery.ogg", true); }));
						novel->addSentence(0, "宇沢", "それでは、まずは今回の事件を振り返ってみましょう。");
						novel->addSentence(0, "寿甘", "私が、体育の授業を終えて着替えて教室へ戻ってきたら、待ち合わせしていたはずの二人が居なかった。");
						novel->addSentence(0, "寿甘", "体育の時は二人とも見かけたし、教室で待ってるよう念を押したから、私たちが着替えている間になにかあったのかも。");
						novel->addSentence(0, "寿甘", "そこで、しばらく二人を探してみたけど、どこにもいなかった。");
						novel->addSentence(0, "宇沢", "その後で、校舎裏で大量の血痕がのこっていたのを発見したんですよね。");
						novel->addSentence(0, "宇沢", "さらに、そばにあったクロユリの花には、お二人が何者かに担がれて運ばれている記憶がありました。");
						n = novel->addSentence(0, "宇沢", "さて、二人はどうなったと考えるのが妥当でしょうか？");
						novel->addSwitchEvent(0, 1, "誘拐された", 2, "帰った", 3, "構内のどこかにいる");
						novel->addSentence(0, "寿甘", "それは…");

						novel->addSentence(1, "寿甘", "クロユリの記憶が物語っていたわ");
						novel->addSwitchEvent(1, 0);
						novel->setFontColor(1, Color3B::RED);
						novel->addSentence(1, "寿甘", "二人は…誘拐されたのね");

						novel->addSentence(2, "寿甘", "まさか、二人とも帰っちゃったとか…");
						novel->addSentence(2, "宇沢", "いやいや、そこは信じてあげましょうよ。");
						novel->addSentence(2, "宇沢", "それに、神北さんが二人とも校門から出てきてないとおっしゃってましたよね。");
						novel->addSentence(2, "寿甘", "それもそうね…");
						novel->setJump(2, 0, n);

						novel->addSentence(3, "寿甘", "まだ、構内のどこかにいるのかしら…");
						novel->addSentence(3, "宇沢", "でも、どれだけ探し回ってもいなかったんですよね？");
						novel->addSentence(3, "寿甘", "うーん…");
						novel->addSentence(3, "宇沢", "ええ…しっかりしてくださいよ…");
						novel->setJump(3, 0, n);


						novel->setFontColor(0, Color3B::RED);
						novel->addSentence(0, "宇沢", "そう考えるのが妥当だと思います。");
						novel->addSentence(0, "寿甘", "うぅ…一体だれが何のために…");
						novel->setCharaL(0, "");
						novel->setCharaR(0, "");
						novel->setBg(0, "chara/memory4.png");
						novel->addSentence(0, "宇沢", "あの黒づくめの人物…");
						novel->addSentence(0, "宇沢", "…！");
						n = novel->addSentence(0, "宇沢", "私、写真を見ていて気付いたことがあるのですが。");
						novel->addSentence(0, "寿甘", "気付いたこと？");
						novel->addPauseEvent(0, Sequence::createWithTwoActions(
							CallFunc::create([this] {
							auto back = Sprite::create("bg/black.png");
							back->setPosition(Director::getInstance()->getVisibleSize() / 2);
							back->runAction(Sequence::create(FadeIn::create(0.5f), DelayTime::create(5.0f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
							addChild(back, 2, "back");
							for (int i = 0; i < 4; i++) {

								if (i != 2) {
									auto spr = Sprite::create(StringUtils::format("chara/memory%d.png", i + 1));
									spr->setPosition(Director::getInstance()->getVisibleSize() / 2);
									spr->setOpacity(0.0f);
									if (i == 3) {
										spr->runAction(Sequence::create(DelayTime::create(2.0f * 2), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
									}
									else {
										spr->runAction(Sequence::create(DelayTime::create(2.0f * (float)i), FadeIn::create(0.5f), DelayTime::create(1.5f), FadeOut::create(0.5f), RemoveSelf::create(), NULL));
									}
									addChild(spr, 3, StringUtils::format("bg%d", i));
								}
							}
						}),
							DelayTime::create(6.0f)
							));
						novel->addSentence(0, "宇沢", "写真の前後関係から考えて、現場から消えている物がありますよね？");
						novel->addSwitchEvent(0, 4, "人形", 5, "手紙", 6, "血痕");
						novel->addSentence(0, "寿甘", "それって…");

						novel->addSentence(4, "寿甘", "人形かしら");
						novel->addSwitchEvent(4, 0);
						novel->setFontColor(4, Color3B::RED);
						novel->addSentence(4, "宇沢", "ですです！");

						novel->addSentence(5, "寿甘", "手紙？");
						novel->addSentence(5, "宇沢", "確かに、バンダナさんが手紙を読んでいる写真以外には手紙は映っていませんね…");
						novel->addSentence(5, "宇沢", "でも、先ほど私たちが現場を調査した時には、手紙はありましたよね？");
						novel->addSentence(5, "宇沢", "他の場面では手紙は視界から消えていただけなのだと思います");
						novel->addSentence(5, "寿甘", "それもそうね…");
						novel->setJump(5, 0, n);

						novel->addSentence(6, "寿甘", "血痕かしら");
						novel->addSentence(6, "宇沢", "消えた血痕…！いいですねぇ、サスペンスドラマっぽくて！");
						novel->addSentence(6, "宇沢", "しかし、残念ながら血痕は消えていませんでしたね…");
						novel->addSentence(6, "寿甘", "残念ね…（？）");
						novel->setJump(6, 0, n);


						novel->setBg(0, "");
						novel->setCharaL(0, "chara/suama1.png");
						novel->setCharaR(0, "chara/usawa1.png");
						novel->addSentence(0, "寿甘", "でもこの人形が何だっていうのよ");
						novel->addSentence(0, "宇沢", "ずばり、誘拐犯は…この人形なのでしょう");
						novel->addSentence(0, "寿甘", "ど、どういうことよ？");
						novel->addSentence(0, "宇沢", "こんな話を聞いたことがあります…");
						novel->addSentence(0, "宇沢", "この学校には、人形を思い通りの姿かたちで自分の分身のように動かせる「人形遣い」の特殊能力を持つ生徒がいるらしいんです。");
						novel->addSentence(0, "寿甘", "じゃあ、真犯人はその「人形遣い」の特殊能力を持つ生徒っていうこと…？");
						novel->addSentence(0, "宇沢", "おそらく…");
						novel->addSentence(0, "寿甘", "で、誰なのよ？その生徒っていうのは…");
						novel->addSentence(0, "宇沢", "うーん、どなたでしたっけ…ちょっと思い出せないんです…すみません");
						novel->addSentence(0, "寿甘", "チッ…今から調べてそいつをとっ捕まえるか…");
						novel->addSentence(0, "寿甘", "……ん？");
						novel->addSentence(0, "寿甘", "フフ…私も写真を見て気づいたことがあるわ");
						novel->addSentence(0, "宇沢", "おお、何ですかそれは");
						novel->addSentence(0, "寿甘", "犯人は…この写真に写っているわ！");
						novel->addEvent(0, CallFunc::create([this] {
							auto visibleSize = Director::getInstance()->getVisibleSize();

							auto layer = Layer::create();
							layer->setCascadeOpacityEnabled(true);
							layer->setOpacity(0.0f);
							layer->runAction(FadeIn::create(0.2));
							auto listener = EventListenerTouchOneByOne::create();
							listener->setSwallowTouches(true);
							listener->onTouchBegan = [this](Touch* touch, Event* event) {
								if (Rect(570, 270, 40, 50).containsPoint(touch->getLocationInView())) {
									AudioEngine::play2d("SE/choice.ogg");
									getChildByName("layer_c")->runAction(Sequence::createWithTwoActions(FadeOut::create(0.2), RemoveSelf::create()));
								}
								return true;
							};
							this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);
							addChild(layer,11,"layer_c");
							auto spr = Sprite::create("chara/memory2.png");
							spr->setPosition(visibleSize / 2);
							layer->addChild(spr, 0, "spr");
							auto label = Label::createWithTTF("怪しいところをタップしよう", FONT_NAME, 30);
							label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
							label->setColor(Color3B::WHITE);
							label->enableOutline(Color4B::BLACK, 2);
							layer->addChild(label, 3, "label");
						}));
						novel->addSentence(0, "宇沢", "これでしょうか…？");
						novel->addSentence(0, "寿甘", "そうよ！犯人はこいつに違いないわ！");
						novel->addSentence(0, "宇沢", "この翼はもしかして…リアスさん！？");
						novel->addSentence(0, "寿甘", "これでようやく、あの手紙の既視感の謎が解けたわ。");
						novel->setBg(0, "chara/scene5.png");
						novel->addSentence(0, "寿甘", "あの手紙は赤文字で書かれていた、同じく赤文字で書かれたノートを私たちは見ているのよ。");
						novel->addSentence(0, "寿甘", "朝、校庭で見つけたリアスの宝箱に入っていたノートよ。");
						novel->addSentence(0, "寿甘", "きっとあいつが手紙でバンダナを呼び出したに違いないわ…");
						novel->addSentence(0, "宇沢", "なるほど…その可能性は高そうですね");

						novel->setBg(0, "");
						novel->addSentence(0, "寿甘", "あいつどこに行ったのよ…マリアちゃんが何か探しているようだって言ってたけど…");
						novel->addSentence(0, "宇沢", "リアスさんが行きそうな場所、ですか…");
						novel->addSentence(0, "宇沢", "そういえば、誘拐犯もとい人形はどこへ消えてしまったのでしょう？");
						n = novel->addSentence(0, "宇沢", "そもそも、どうやって二人を連れ去ったのでしょうか…？");
						novel->addSwitchEvent(0, 7, "空を飛んだ", 8, "正門から出ていった", 9, "別の道を通って行った");
						novel->addSentence(0, "寿甘", "それは…");

						novel->addSentence(7, "寿甘", "空を飛んで連れ去っていったとか？");
						novel->addSentence(7, "宇沢", "確か…神北さんが私のスクープを見てからずっとUFOを探していらしたんでしたよね？");
						novel->addSentence(7, "宇沢", "二人を抱えた大男が空を飛んでいたら普通気づくでしょうけど、結局何も見つからなかったんでしたよね。");
						novel->addSentence(7, "寿甘", "そうだったわね…");
						novel->setJump(7, 0, n);

						novel->addSentence(8, "寿甘", "正門から出て行ったとか？");
						novel->addSentence(8, "宇沢", "確か…神北さんが私のスクープを見てからずっとUFOを探していらしたんでしたよね？");
						novel->addSentence(8, "宇沢", "それから校門前から離れていなかったらしいのですが、二人は出てこなかったんでしたよね。");
						novel->addSentence(8, "寿甘", "そうだったわね…");
						novel->setJump(8, 0, n);

						novel->addSentence(9, "寿甘", "どこか抜け道を通って行ったとか…？");
						novel->addSwitchEvent(9, 0);
						novel->addSentence(9, "宇沢", "そう、それです！");

						novel->addSentence(0, "宇沢", "二人が消えたと思われる校舎裏には、しっかりと誘拐犯の足跡が残ってました。");
						novel->addSentence(0, "宇沢", "もう一度、校舎裏を調査してみれば居場所がわかるかもしれません！");
						novel->addSentence(0, "寿甘", "なるほど！");
						novel->addSentence(0, "寿甘", "っていうか、最初からそうしておいた方がよかった気もしなくもないわね…");

						novel->addEvent(0, CallFunc::create([this] { AudioEngine::stopAll(); AudioEngine::play2d("BGM/school.ogg", true); }));
						novel->addSentence(0, "寿甘", "ま、そうと決まればまた校舎裏に行くわよ！");
						novel->addSentence(0, "宇沢", "いや、ここは手分けしていきましょう。");
						novel->addSentence(0, "宇沢", "私は「人形遣い」の生徒について調査しています、寿甘さんは校舎裏へ向かってください。");
						novel->addSentence(0, "寿甘", "わかったわ、何かわかったら教えてね");
						novel->addSentence(0, "寿甘", "あ、そうだ。この笛渡しておくから、調査したことを紙に書いて翼くんに届けさせて！");
						novel->addEvent(0, CallFunc::create([this] {
							ItemMgr::sharedItem()->deleteItem("whistle");
							mObjectList["usawa"]->setState(2);
							mObjectList["usawa"]->setCursor(Cursor::INFO);
						}));
						novel->addSentence(0, "宇沢", "と、鳥を呼び出すのですか…私にできるでしょうか…");
						novel->addSentence(0, "宇沢", "とりあえず任せてください！そちらもお気をつけて");
						novel->addSentence(0, "寿甘", "問題ないわ、それじゃ");


						novel->setEndTask(-1);
						this->addChild(novel, 10, "novel");
					}
					else {
						auto novel = Novel::create();

						novel->setFontColor(0, Color3B::RED);
						novel->setCharaL(0, "chara/suama1.png");
						novel->setCharaR(0, "chara/usawa1.png");
						novel->addSentence(0, "宇沢", "準備はできました？");
						novel->addSentence(0, "寿甘", "うーん…もうちょっと調査してみるわ");

						novel->setEndTask(0);
						this->addChild(novel, 10, "novel");
					}
				}
				else {
					// 裏庭探索前、一度話しかけた後
					auto novel = Novel::create();

					novel->setFontColor(0, Color3B::RED);
					novel->setCharaL(0, "chara/suama1.png");
					novel->setCharaR(0, "chara/usawa1.png");
					novel->addSentence(0, "宇沢", "二人とも見てないです…ごめんなさい…");

					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
			}
			else if (mObjectList["usawa"]->getState() == 2) {
				// 推理完了
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "宇沢", "調査の方は任せてください！お気をつけて…！");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(usawa, "usawa", 1, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);

		auto memo = ObjectN::create();
		memo->setArea(Rect(0, 200, 170, 140));
		memo->setCursor(Cursor::NEW);
		memo->setItemGetEvent("paper");
		memo->setMsg("メモを手に入れた");
		memo->setTouchEvent(CallFunc::create([this] {
			auto novel = Novel::create();

			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "あ、これ今朝拾ったメモだ");
			novel->addSentence(0, "寿甘", "つぐるん置きっぱなしにしちゃったのかー…");
			novel->addSentence(0, "寿甘", "しばらくリアスに返さないで持ってようかな、手掛かりになるかもしれないし。");

			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");

			mObjectList["memo"]->setState(1);
		}));
		addObject(memo, "memo", 3, true);

		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->runAction(FadeIn::create(0.5f));
	}

	void ClassRoom::changedField() {

	}

	void ArtRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		mFieldName = "美術室";

		auto bg = Sprite::create("art_room.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto maria = ObjectN::create();
		maria->setTexture("maria.png");
		maria->setArea(Rect(60, 180, 230, 300));
		maria->setCursor(Cursor::NEW);
		maria->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["maria"]->getState() == 0) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/maria1.png");
				novel->addSentence(0, "寿甘", "おつかれー！");
				novel->addSentence(0, "マリア", "おつかれー");
				novel->addSentence(0, "寿甘", "つぐるんとバンダナ見なかったー？");
				novel->addSentence(0, "マリア", "うーん、ごめんねー見てないかな…");
				novel->addSentence(0, "寿甘", "ううん、大丈夫だよー");
				novel->addSentence(0, "マリア", "そういえば、リアスちゃんが何か探してるみたいだったの");
				novel->addSentence(0, "寿甘", "えぇ…どうせバンダナのことだと思うよ…");
				novel->addSentence(0, "寿甘", "あいつより早く見つけなきゃ…");
				novel->addSentence(0, "マリア", "あのね、ちょっと違う気がするんだ。");
				novel->addSentence(0, "マリア", "なんだか悲しそうな顔をしてた");
				novel->addSentence(0, "寿甘", "ん？そうだったんだ");
				novel->addSentence(0, "寿甘", "まあいいや、ありがとねー！");
				mObjectList["maria"]->setState(1);
				mObjectList["maria"]->setCursor(Cursor::INFO);

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else if (mObjectList["maria"]->getState() == 1) {
				auto novel = Novel::create();

				novel->setFontColor(0, Color3B::RED);
				novel->setCharaL(0, "chara/suama1.png");
				novel->setCharaR(0, "chara/maria1.png");
				novel->addSentence(0, "マリア", "二人とも見てないの…ごめんね");

				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(maria, "maria", 1, true);

		auto whistle = ObjectN::create();
		whistle->setTexture("whistle.png");
		whistle->setArea(Rect(520, 430, 60, 50));
		whistle->setCursor(Cursor::NEW);
		whistle->setItemGetEvent("whistle");
		whistle->setMsg("木片を手に入れた");
		addObject(whistle, "whistle", 2, true);

		auto chisel = ObjectN::create();
		chisel->setTexture("chisel.png");
		chisel->setArea(Rect(120, 40, 80, 40));
		chisel->setCursor(Cursor::NEW);
		chisel->setItemGetEvent("chisel");
		chisel->setMsg("彫刻刀を手に入れた");
		addObject(chisel, "chisel", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::ENTER);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}