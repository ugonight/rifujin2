#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void Corridor::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("corridor.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto remon = ObjectN::create();
		remon->setTexture("remon.png");
		remon->setArea(Rect(30, 110, 140, 370));
		remon->setCursor(Cursor::INFO);
		remon->setTouchEvent(CallFunc::create([this] {
			if (ItemMgr::sharedItem()->getSelectedItem() == "paper") {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/remon1.png");
				novel->setCharaL(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「ちょっといいか」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬「何かしら」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「このメモの持ち主を知らないか？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬「あら…？これは【ひゃっくりさん】だわ」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「ひゃっくりさん…？なんじゃそりゃ」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬「一種の占いみたいなものよ。幽霊を呼び出してその質問に答えてもらうの。」");
				novel->addSentence(0, "檸檬「リアスが恋愛運を占いたいって言うから、前に一緒にやったことがあるわ。あの子、あの時は面白いくらいに怖がってたけど、今は何だかんだでハマってたりして」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「んーそうか、サンキュ」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				Control::me->getField("gate")->getObject("cenotaph")->setState(1);
				Control::me->getField("gate")->getObject("cenotaph")->addCanUseItem("paper");
			}
			else {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/remon1.png");
				novel->setCharaL(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "檸檬「うふふ、御機嫌よう」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		remon->addCanUseItem("paper");
		addObject(remon, "remon", 1, true);

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
		if (mObjectList["flag"]->getState() == 1) {
			auto novel = Novel::create();
			novel->setCharaL(0, "chara/bandana1.png");
			novel->setFontColor(0, Color3B::BLACK);
			novel->addSentence(0, "ガチャ…");
			novel->setCharaC(0, "chara/rias1.png");
			novel->addSentence(0, "ドンッ！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「うおっ」");
			//novel->addEvent(0, CallFunc::create([this] {addChild(mObjectList["paper"], 1, "paper"); }));
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「きゃっ」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「わりぃ、怪我はなかったか？」");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "リアス「ぁ…バンダナ様…」");
			novel->setCharaC(0, "");
			novel->addSentence(0, "リアス「ひぃ～～～……」");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "バンダナ「相変わらずだな…」");
			//novel->addSentence(0, "バンダナ「…ん？なんか落としていったぞ」");
			novel->setEndTask(0);
			this->addChild(novel, 10, "novel");
			mObjectList["flag"]->setState(0);
			Control::me->getField("gate")->addChild(Control::me->getField("gate")->getObject("paper"), 1, "paper");
		}
	}

	void ClassRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("classroom.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto usawa = ObjectN::create();
		usawa->setTexture("usawa_hide.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::INFO);
		usawa->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["usawa_"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「…もしもーし」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…何してるんですかー」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…ｺﾁｮｺﾁｮｺﾁｮ」");
				novel->addSentence(0, "？？？「……～～！！」");
				novel->addSentence(0, "寿甘「…ｺﾁｮｺﾁｮｺﾁｮｺﾁｮｺﾁｮｺﾁｮ」");
				novel->addSentence(0, "？？？「……うぐぐ…」");
				novel->addSentence(0, "寿甘「…しぶといわね…」");
				novel->setCharaR(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「…さっきから何をしてるの？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……（ぱあぁ）」");
				novel->setCharaC(0, "chara/bandana1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「うっそだろお前、俺でも気付いたぜ？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……（グサッ）」");
				novel->addSentence(0, "寿甘「こんなにバレバレなのにわかんないの！？」");
				novel->addSentence(0, "？？？「……（グサグサッッ）」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「？？？」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["usawa_"]->setState(1);
				mObjectList["usawa_"]->addCanUseItem("pepper");
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "pepper"){
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「…ぱらぱら」");
				novel->addSentence(0, "？？？「……」");
				novel->addSentence(0, "寿甘「…ぱらぱらぱら」");
				novel->addSentence(0, "？？？「……は」");
				novel->addSentence(0, "寿甘「…ぱらぱらぱらぱらぱらぱら」");
				novel->addSentence(0, "？？？「……ぶわあぁぁぁぁぁぁぁぁくしょおぉおぉぉぉい！！！！」");
				novel->addEvent(0,CallFunc::create([this] {
					ItemMgr::sharedItem()->deleteItem("pepper");
					mObjectList["usawa_"]->runAction(Sequence::create(FadeOut::create(0.5f), RemoveSelf::create(), NULL));
					mObjectList["usawa"]->setOpacity(0.0f);
					mObjectList["usawa"]->runAction(FadeIn::create(0.5f));
					addChild(mObjectList["usawa"], 2, "usawa");
				}));
				novel->addSentence(0, "寿甘「…（グッ）」");
				novel->setCharaR(0, "chara/usawa1.png");
				novel->addSentence(0, "？？？「……チッ…このベテラン新聞部員の宇沢　智恵（うさわ　ともえ）様の”隠れ身の術”を見破るなんて大したものね…」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaC(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ「大丈夫なのか新聞部…」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "宇沢「はぁ？新聞部の調査能力をなめてもらっちゃあ困りますねぇ？」");
				novel->addSentence(0, "宇沢「そう、例えば…立花さん、あなたは現在美術部のマドンナ、マリア・ミルフィーユさんとお付き合いしていてあんなことやこんなことまで…」");
				novel->addSentence(0, "寿甘「してませんけど」");
				novel->addSentence(0, "宇沢「またまた、御冗談を～わたくしの地獄耳は騙せませんよぉ？」");
				novel->addSentence(0, "宇沢「それにわたくし、今あなた方にとっておきの耳寄りな情報があるんですよ…聞いていきます？」");
				novel->addSentence(0, "寿甘「うさんくさいわね…」");
				novel->addSentence(0, "宇沢「そこまで言われちゃあ、教えてあげないわけにもいきませんねぇ？」");
				novel->addSentence(0, "宇沢「た・だ・し。わたくしを楽しませてくれるようなものを持ってきてくれたら、ですねぇ…」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ「なんだこいつ…」");
				novel->addEvent(0, CallFunc::create([this] {
					ItemMgr::sharedItem()->getItem("camera", Director::getInstance()->getVisibleSize() / 2);
					Control::me->showMsg("カメラを手に入れた");
					Control::me->getField("gate")->getObject("renji")->setState(2);
					Control::me->getField("gate")->getObject("renji")->setCursor(Cursor::NEW);
				}));
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "宇沢「んじゃあこれ貸すんで、いいスクープ撮ってきてくださいね～」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
			else {
				auto novel = Novel::create();
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "？？？「……」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(usawa, "usawa_", 1, true);

		usawa = ObjectN::create();
		usawa->setTexture("usawa.png");
		usawa->setArea(Rect(330, 70, 130, 190));
		usawa->setCursor(Cursor::INFO);
		usawa->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["usawa"]->getState() == 0) {
				if (ItemMgr::sharedItem()->getSelectedItem() == "picture") {
					auto novel = Novel::create();
					novel->setCharaL(0, "chara/suama1.png");
					novel->setCharaR(0, "chara/usawa1.png");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "寿甘「はいこれ」");
					novel->addSentence(0, "宇沢「なんですかこれ」");
					novel->addSentence(0, "寿甘「UFO」");
					novel->addSentence(0, "宇沢「…はぁ～～～～～」");
					novel->addSentence(0, "宇沢「わたくし、オカルトってあんまり好きじゃないんですよねぇ。大体、魔法で何でもできるこのご時世にオカルトなんて今更じゃないですか。」");
					novel->setCharaC(0, "chara/bandana1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "バンダナ「確かに」");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "宇沢「まぁ、付き合ってくれたお礼に、例の特ダネ教えてあげますよ」");
					novel->addSentence(0, "宇沢「実はですねぇ…校庭の植え込みに時限爆弾のようなものが仕組まれていたんですよ」");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "バンダナ「ホントかよ…」");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "宇沢「もしかしたら、どっかの国のスパイが爆発テロを企ててるのかも…！？」");
					novel->setCharaL(0, "chara/tuguru1.png");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継「それは大変だ…！」");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "宇沢「よろしければ様子を見に行っていただけます？そしたら、わたくしがこの前代未聞の特ダネ…いや緊急事態を責任をもって学校中にお知らせしますので」");
					novel->setFontColor(0, Color3B::BLUE);
					novel->addSentence(0, "継「うん、王子としても、そんなことは見過ごせないからね」");
					novel->addSentence(0, "バンダナ「まさかねえ…」");
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
					ItemMgr::sharedItem()->deleteItem("picture");
					mObjectList["usawa"]->setState(1);
					Control::me->getField("corridor")->getObject("flag")->setState(1);
					Control::me->getField("entrance")->addChild(Control::me->getField("entrance")->getObject("box"), 3, "box");
				}
				else {
					auto novel = Novel::create();
					novel->setCharaL(0, "chara/tuguru1.png");
					novel->setCharaR(0, "chara/usawa1.png");
					novel->setFontColor(0, Color3B::RED);
					novel->addSentence(0, "宇沢「わたくしを楽しませてくれそうなものは持ってきてくれたかしら？」");
					novel->setEndTask(0);
					this->addChild(novel, 10, "novel");
				}
			} else if (mObjectList["usawa"]->getState() == 1) {
				if (Control::me->getField("box")->getObject("flag")->getState() == 3) {
					//auto novel = Novel::create();
					//novel->setCharaL(0, "chara/tuguru1.png");
					//novel->setCharaR(0, "chara/usawa1.png");
					//novel->setFontColor(0, Color3B::RED);
					//novel->addSentence(0, "宇沢「ふむふむ…かくかくしかじかでこういうわけだったのですか…」");
					//novel->addSentence(0, "宇沢「リアスさんですねぇ…彼女、珍しいドラゴン族の末裔みたいで、おかしな宗教とか引き継いじゃってるみたいですよ？何されるかわかったもんじゃないですねぇ」");
					//novel->setCharaC(0, "chara/suama1.png");
					//novel->addSentence(0, "寿甘「ソースは」");
					//novel->addSentence(0, "宇沢「そ、ソース…？わたくしは目玉焼きには醤油ですよ。ソースなんてかける人の気が知れないですねぇ」");
					//novel->setCharaC(0, "chara/bandana1.png");
					//novel->setFontColor(0, Color3B::BLUE);
					//novel->addSentence(0, "バンダナ「は？お前全国のソース派を敵に回したな？生きて帰れると思うなよ？」");
					//novel->setFontColor(0, Color3B::RED);
					//novel->addSentence(0, "宇沢「ドラゴン族の呪いより恐ろしそうですねぇ…」");
					//novel->setFontColor(0, Color3B::BLUE);
					//novel->addSentence(0, "継「とにかく、今日は帰りもみんなで一緒に帰ろう。いいね？」");
					//novel->addSentence(0, "バンダナ「まあ、用心に越したことはないか…何かあったら面倒くさいし」");
					//novel->setFontColor(0, Color3B::RED);
					//novel->setCharaR(0, "chara/suama1.png");
					//novel->addSentence(0, "寿甘「よし、じゃあ決まりね！先に帰ったら許さないんだから！」");
					//novel->setFontColor(0, Color3B::BLUE);
					//novel->addSentence(0, "継「あ、始業のチャイムが鳴ったよ。みんな席に着こう」");
					//novel->addEvent(0, CallFunc::create([this] { 
					this->runAction(Sequence::create(FadeOut::create(1.0f), CallFunc::create([this] {Control::me->setEndFlag(); }), NULL));
						//}));

						//novel->setEndTask(0);
						//this->addChild(novel, 10, "novel");
					}
					else {
						auto novel = Novel::create();
						novel->setCharaL(0, "chara/tuguru1.png");
						novel->setCharaR(0, "chara/usawa1.png");
						novel->setFontColor(0, Color3B::RED);
						novel->addSentence(0, "宇沢「校庭の様子はどうでしたか？」");
						novel->setEndTask(0);
						this->addChild(novel, 10, "novel");
					}
				}
		}));
		usawa->addCanUseItem("picture");
		addObject(usawa, "usawa", 1, false);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(784, 0, 70, 480));
		corridor->setCursor(Cursor::RIGHT);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ClassRoom::changedField() {

	}

	void ArtRoom::initField() {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::create("art_room.png");
		bg->setPosition(visibleSize / 2);
		addChild(bg, 0, "bg");

		auto maria = ObjectN::create();
		maria->setTexture("maria.png");
		maria->setArea(Rect(60, 180, 230, 300));
		maria->setCursor(Cursor::INFO);
		maria->setTouchEvent(CallFunc::create([this] {
			if (mObjectList["maria"]->getState() == 0) {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「あ、マリアちゃんおはよー！」");
				novel->addSentence(0, "マリア「あ！寿甘ちゃんおはよー」");
				novel->addSentence(0, "寿甘「美術部の朝練？朝からおつかれー！」");
				novel->addSentence(0, "マリア「えへへ…ありがとー」");
				novel->addSentence(0, "寿甘「あ、それと、この前のアレありがとうねー助かったよー」");
				novel->addSentence(0, "マリア「よかったーまた何か描いてほしいものがあったら持ってきていいよー」");
				novel->addSentence(0, "寿甘「ほんと！？じゃあ遠慮なくー！」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				mObjectList["maria"]->setState(1);
				mObjectList["maria"]->addCanUseItem("magazine");
			}
			else if (ItemMgr::sharedItem()->getSelectedItem() == "magazine") {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「マリアちゃん、お願いがあるんだけど」");
				novel->addSentence(0, "マリア「ん？何かな？」");
				novel->addSentence(0, "寿甘「また例のアレをお願いしたいんだー大丈夫ー？」");
				novel->addSentence(0, "マリア「ちょっと恥ずかしいけど…まだ部員の人たちは来てないし、寿甘ちゃん達だけだったらいいよー」");
				novel->addSentence(0, "寿甘「ほんと！？ありがとー！」");
				novel->addSentence(0, "寿甘「ほんじゃ、これでお願いねー」");
				novel->addSentence(0, "マリア「わかった。今から描くからちょっと待っててね」");
				novel->setCharaC(0, "chara/tuguru1.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「例のアレって何のこと…？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "寿甘「まあ見てればわかるって！」");
				novel->addSentence(0, "マリア「できたよー」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「これは…UFOの絵かな？」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "マリア「これをこうやって…えいっ！」");
				novel->setCharaL(0, "");
				novel->setCharaR(0, "");
				novel->setCharaC(0, "");
				novel->setBg(0, "chara/scene4.png");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「うわあ！UFOが絵の中から出て来たよ！」");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "マリア「実は、私の特殊能力は絵に描いたものを具現化することだったの。余計引かれちゃうから秘密にしてたんだけど…」");
				novel->addSentence(0, "寿甘「だーかーらそんなことないって！みんなマリアちゃんの絵、大好きだよ！」");
				novel->addSentence(0, "マリア「ありがとう…そう言ってもらえるとうれしいな」");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "継「UFOが窓の外へ飛んだ行ったよ。見失う前に撮影しに行こう。」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
				
				ItemMgr::sharedItem()->deleteItem("magazine");
				Control::me->getField("entrance")->addChild(Control::me->getField("entrance")->getObject("ufo"), 3, "ufo");
				mObjectList["maria"]->setState(2);
			}
			else {
				auto novel = Novel::create();
				novel->setCharaR(0, "chara/maria1.png");
				novel->setCharaL(0, "chara/suama1.png");
				novel->setFontColor(0, Color3B::RED);
				novel->addSentence(0, "マリア「おはよー」");
				novel->setEndTask(0);
				this->addChild(novel, 10, "novel");
			}
		}));
		addObject(maria, "maria", 1, true);

		auto net = ObjectN::create();
		net->setTexture("net.png");
		net->setArea(Rect(200, 100, 100, 50));
		net->setCursor(Cursor::NEW);
		net->setItemGetEvent("net");
		net->setMsg("金網を手に入れた");
		addObject(net, "net", 2, true);

		auto corridor = ObjectN::create();
		corridor->setArea(Rect(400, 0, 280, 290));
		corridor->setCursor(Cursor::ENTER);
		corridor->setFieldChangeEvent("corridor");
		addObject(corridor, "corridor", 2, true);
	}

	void ArtRoom::changedField() {

	}
}