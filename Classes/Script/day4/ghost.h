#pragma once
#pragma  execution_character_set("utf-8")

#include "../../System/field.h"
#include "../../System/object.h"

USING_NS_CC;

namespace day4 {
	inline void generateGhost(std::string fieldName) {
		std::string fname[5] = {
			"aisle2",
			"baking",
			"lab",
			"library",
			"torture"
		};
		int r;

		do {
			r = cocos2d::random() % 5;
		} while (fieldName == fname[r]);

		auto f = Control::me->getField(fname[r]);
		f->addChild(f->getObject("ghost"), 2, "ghost");
	}

	inline ObjectN* createGhost(int x, int y, std::string fieldName) {
		auto ghost = ObjectN::create();
		ghost->setTexture("ghost.png");
		ghost->setPosition(Vec2(x, 480 - y));
		auto rect = ghost->getBoundingBox();
		rect.setRect(rect.getMinX(), 480 - rect.getMaxY(), rect.getMaxX() - rect.getMinX(), rect.getMaxY() - rect.getMinY());
		ghost->setArea(rect);
		ghost->setCursor(Cursor::INFO);
		ghost->setOpacity(0.0f);
		ghost->setBlendFunc(BlendFunc{ GL_SRC_ALPHA ,GL_ONE });
		ghost->setAction(RepeatForever::create(Spawn::createWithTwoActions(
			Sequence::createWithTwoActions(EaseSineOut::create(FadeIn::create(3.0f)), EaseSineIn::create(FadeOut::create(3.0f)))
			, Sequence::createWithTwoActions(EaseSineOut::create(MoveTo::create(3.0f, Vec2(x, 480 - y + 30.0f))), EaseSineIn::create(MoveTo::create(3.0f, Vec2(x, 480-y))))
		))
		);
		ghost->setTouchEvent(CallFunc::create([ghost, fieldName]() {
			auto field = ghost->getParent();
			auto ghost0 = Control::me->getField("aisle2")->getObject("ghost");
			switch (ghost0->getState()) {
			case 0:
			{			
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "…なあ");
				novel->addSentence(0, "継", "ん？どうしたの？");
				novel->addSentence(0, "バンダナ", "なんだか寒気がしないか…？");
				novel->addSentence(0, "継", "まあ、こんな場所だからね");
				novel->addSentence(0, "バンダナ", "それに、人の顔みたいなものが浮かんでいるように見えるんだが…");
				novel->addSentence(0, "継", "きっとまだ傷が癒えてなくて疲れてるんだよ。少し休もうか？");
				novel->addSentence(0, "バンダナ", "いや…ほらあそこに…");
				novel->addSentence(0, "継", "…ああ！本当だ、僕にも見えるよ！");
				novel->addSentence(0, "バンダナ", "あれが幽霊ってやつなのか…？寿甘じゃなくても見えるのか…");
				novel->addSentence(0, "継", "うーん…もしかしたら僕たちに伝えたいことがあって姿を見せているのかも。");
				novel->addSentence(0, "バンダナ", "近づいてみるか？");
				novel->addSentence(0, "継", "うん");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ghost->stopAllActions();
					ghost->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				}));
				novel->addSentence(0, "継", "…あ");
				novel->addSentence(0, "継", "いなくなっちゃたみたいだ");
				novel->addSentence(0, "バンダナ", "ひょっとしたら、また出てくるかもな");
				novel->addSentence(0, "継", "そうだね、その時は話を聞いてあげよう。");

				generateGhost(fieldName);
				ghost0->setState(1);

				novel->setEndTask(0);
				field->addChild(novel, 10, "novel");

				break;
			}

			case 1:
			{
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaR(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "おお、またいたな。");
				novel->addSentence(0, "バンダナ", "おーい！");
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "あ、待ってよバンダナ！");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ghost->stopAllActions();
					ghost->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				}));
				novel->addSentence(0, "継", "…あ");
				novel->addSentence(0, "継", "またいなくなっちゃたみたいだ");
				novel->addSentence(0, "バンダナ", "すまん、俺が無神経に近づいたせいだな。");
				novel->addSentence(0, "継", "今度はゆっくり近づいてみようか");

				generateGhost(fieldName);
				ghost0->setState(2);

				novel->setEndTask(0);
				field->addChild(novel, 10, "novel");

				break;
			}

			case 2:
			{
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "よし、いたぞ。");
				novel->addSentence(0, "継", "そーっと近づこう");
				novel->addSentence(0, "継", "そー…っと…");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ghost->stopAllActions();
					ghost->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				}));
				novel->addSentence(0, "継", "…あ");
				novel->addSentence(0, "継", "またいなくなっちゃたみたいだ");
				novel->addSentence(0, "バンダナ", "何がしたいんだあの幽霊…");
				novel->addSentence(0, "継", "どうすればいいんだろう…");

				generateGhost(fieldName);
				ghost0->setState(3);

				novel->setEndTask(0);
				field->addChild(novel, 10, "novel");

				break;
			}

			case 3:
			{
				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "またいるのか…");
				novel->addSentence(0, "バンダナ", "今度はつぐるんだけで行ってみたらどうだ？…俺がいるとおびえちゃうのかもしれん");
				novel->addSentence(0, "継", "そうなのかなぁ…まあ、行ってみるよ");
				novel->setCharaR(0, "");
				novel->addSentence(0, "継", "……");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ghost->stopAllActions();
					ghost->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				}));
				novel->addSentence(0, "継", "…あ");
				novel->addSentence(0, "継", "ダメみたいだね");

				generateGhost(fieldName);
				ghost0->setState(4);

				novel->setEndTask(0);
				field->addChild(novel, 10, "novel");

				break;
			}

			case 4:
			{
				auto purple = Color3B(200, 0, 200);

				auto novel = Novel::create();
				novel->setFontColor(0, Color3B::BLUE);
				novel->setCharaL(0, "chara/tuguru1.png");
				novel->setCharaR(0, "chara/bandana1.png");
				novel->addSentence(0, "バンダナ", "呪われてんなぁ");
				novel->addSentence(0, "継", "次はバンダナだけで行ってみてよ");
				novel->addSentence(0, "バンダナ", "ホントに行く必要あるのか…？");
				novel->setCharaL(0, "");
				novel->addSentence(0, "バンダナ", "……");

				novel->addSentence(0, "バンダナ", "…あれ、逃げないみたいだな");
				novel->addSentence(0, "バンダナ", "おいお前、俺たちに何か用があるのか？");
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "……スアマ…チョウサ…ショウコ……カゼウワサ…トドケキタ……");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "ん？寿甘…？寿甘がどうかしたのか！？");
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "コレ…スアマ…タノマレタ……");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "これって…うお！空中から何か出てきたぞ！");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ItemMgr::sharedItem()->getItem("memories", Director::getInstance()->getVisibleSize() / 2);
				}));
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "コレ…ショウコ…キオク……");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ItemMgr::sharedItem()->getItem("suama", Director::getInstance()->getVisibleSize() / 2);
				}));
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "コレ…ショウゲン…ミンナノ……");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "寿甘がこれを残してくれたのか…サンキュな！");
				novel->addSentence(0, "バンダナ", "そういえば、なんでつぐるんがいると逃げてたんだ？");
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "ユーレイ…オフダ…コワイ……");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "お札…？");
				novel->setFontColor(0, purple);
				novel->addSentence(0, "亡霊", "スアマ…ブジ…ツタエル……");
				novel->setFontColor(0, Color3B::BLUE);
				novel->addSentence(0, "バンダナ", "おう！俺たちは無事に帰ってみせるからな！頼むぜ！");
				novel->addEvent(0, CallFunc::create([ghost]() {
					ghost->stopAllActions();
					ghost->runAction(Sequence::createWithTwoActions(FadeOut::create(2.0f), RemoveSelf::create()));
				 }));

				novel->setCharaL(0, "chara/tuguru1.png");
				novel->addSentence(0, "継", "…どうだった？");
				novel->addSentence(0, "バンダナ", "ああ、寿甘が学校で調査してこれを送ってきたみたいなんだ。");
				novel->addSentence(0, "継", "これは…僕たちが襲われた時の映像と、学校のみんなの証言か…");
				novel->addSentence(0, "継", "寿甘にも心配かけてしまったようだね");
				novel->addSentence(0, "バンダナ", "あっちの方に俺たちをさらった犯人の痕跡が残されてたみたいだな");
				novel->addSentence(0, "継", "うん…このことは水無月さんには伏せておこうか。彼女も容疑者の一人だ。");
				novel->addSentence(0, "バンダナ", "ん？生徒の中に犯人がいるってことか…？");
				novel->addSentence(0, "継", "これをみたところ、その可能性はあると思う。疑いたくはないけど…");
				novel->addSentence(0, "バンダナ", "そうか、俺はつぐるんを信じるぜ。");
				novel->addSentence(0, "バンダナ", "ところで、さっきの幽霊がお札がどうのこうのって言ってたんだけど、何か持ってるのか？");
				novel->setCharaC(0, "chara/scene2.png");
				novel->addSentence(0, "継", "ああ、今朝セリーヌに渡されたんだけど…もしかしてこれが原因だったのかな");
				novel->addSentence(0, "バンダナ", "そうみたいだな…");
				novel->addSentence(0, "継", "だとしたら…さっき襲われたときに助かったのも…");
				novel->addSentence(0, "バンダナ", "…ああ、あの時か！");
				novel->addSentence(0, "継", "もしまた襲われそうになったらこのお札を使えばよさそうだね、まだ用心するべきことはありそうだけど。");

				// generateGhost(fieldName);
				ghost0->setState(5);

				novel->setEndTask(0);
				field->addChild(novel, 10, "novel");

				break;
			}

			}
		}));
		return ghost;
	}

	inline void deleteGhost() {
		std::string fname[5] = {
			"aisle2",
			"baking",
			"lab",
			"library",
			"torture"
		};

		for (auto f : fname) {
			auto field = Control::me->getField(f);
			if (field->getChildByName("ghost")) {
				field->removeChildByName("ghost");
				break;
			}
		}
	}

}