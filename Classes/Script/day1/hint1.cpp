#pragma  execution_character_set("utf-8")
#include "Script\day1\fieldDef.h"

USING_NS_CC;

namespace day1 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		if (getObjState("gate", "renji") == 0 ||
			getObjState("classroom", "usawa_") == 0 ||
			getObjState("artroom", "maria") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "学校で散歩って何をしたらいいんだろう");
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaR(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "とりあえずいろんな人に話しかけてみようよ");
		}
		else if (Control::me->getField("entrance")->getObject("fruit")->getReferenceCount() > 1 ||
			Control::me->getField("artroom")->getObject("net")->getReferenceCount() > 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "校舎前の花壇と、美術室にアイテムがありそうだよ");
		}
		else if (Control::me->getField("classroom")->getObject("usawa_")->getReferenceCount() > 1) {
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaR(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "うーん…なかなかしぶといわね…あいつ");
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "持ってるアイテムを組み合わせて何かできないかな");
		}
		else if (getObjState("gate", "renji") == 2) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "スクープって言っても何を持ってくればいいんだろう");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "校門前のあいつが知ってそうだぜ？");
		}
		else if (getObjState("artroom", "maria") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "雑誌を見せてもスクープとは認めてくれないだろうね");
			novel->setCharaR(0, "chara/suama1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "寿甘", "マリアちゃんのところへ行こ！私に考えがあるの");
		}
		else if (getObjState("classroom", "usawa") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "校舎から出てUFOの写真を撮った後、宇沢さんに見せに行こう");
		}
		else if (getObjState("box", "flag") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "まだ時限爆弾らしきものは見つけてないね");
			novel->addSentence(0, "継", "校舎前の花壇をよく探してみよう");
		}
		else if (getObjState("gate", "cenotaph") == 0 &&
			Control::me->getField("gate")->getObject("paper")->getReferenceCount() == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "このメモは誰のだろう…見当もつかないや");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "廊下にいる奴が知ってそうだぜ？");
			novel->addSentence(0, "継", "バンダナって妙な勘が働くよね");
		}
		else if (getObjState("gate", "cenotaph") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "結局、箱のパスワードもメモの持ち主もわからないな…どうしよう");
			novel->addSentence(0, "継", "霊繋がりのありそうなものが校門前にあったような…？");
		}
		else if (getObjState("box", "flag") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "ヒトダマの動きと拾ったメモ、何か関係がありそうだね");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "もしかしたら、それが箱のパスワードのヒントだったりしてな");
		}
		else if (!Control::me->getEndFlag()) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "宇沢さんに報告しに行こう");
		}
		else
		{
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "とりあえずいろんな人に話しかけてみよう");
			novel->addSentence(0, "継", "アイテムを手に入れたら、人に使ってみたり、組み合わせてみよう。");
		}

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}