#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

USING_NS_CC;

namespace day2 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		if (getObjState("magic_team", "flag") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "まずは、この牢屋から出る方法を探そう");
			novel->addSentence(0, "継", "壁にヒビが入っているのが気になるね");
		}
		else if (getObjState("magic_team", "flag") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "メモの暗号の意味は、タテ・ヨコ・ナナメ全ての和が一緒になればいいということだね");
			novel->addSentence(0, "継", "要するに、毛布の下のパズルはスライドパズルで魔方陣を解けばいいんだ");
			novel->addSentence(0, "継", "各ラインの数字の和は１５、真ん中の数字は５になると思うよ");
			novel->addSentence(0, "継", "例えば\n６　１　８\n７　５　３\n２　９　４\nができそうだね");

		}
		else if (getObjState("aisle3","flag") < 2 ) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "フロアの奥の方まで調べてみよう。");
			novel->addSentence(0, "継", "●は継続して接触している必要はないから、落ち着いて追っていこう。");
		}
		else if (/*ItemMgr::sharedItem()->getGetItem("memo1") &&*/ getObjState("panel","flag") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "落ちていたメモをヒントにパネルを操作しよう。メモはパネルに使うことができるみたいだ。");
			novel->addSentence(0, "継", "数字はその列で連続して押されているボタンの数を表すよ");
			novel->addSentence(0, "継", "例えば１２１だったら●〇●●〇●みたいな感じだね");
		}
		else if (getObjState("aisle4","hiru") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "ドアにヒルが群がっていて入れない部屋があるね");
			novel->addSentence(0, "継", "どこかに塩がなかったかな…");
		}
		else if (getObjState("library","book1") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "書斎で解毒薬についての本を探そう");
		}
		else if (getObjState("lab","hikido") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "研究室にさび付いていて開かない引き戸があったね");
			novel->addSentence(0, "継", "何か潤滑剤になりそうなものは持っていなかったかな");

		}
		else if (!ItemMgr::sharedItem()->getGetItem("syringe")) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "注射器はどこだろう");
			novel->addSentence(0, "継", "救急箱の中を探してみよう");

		}
		else if (getObjState("m_water","flag") < 2) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "片方のカップからもう一方のカップへ水を移すとき、注がれる側が満杯になったら余った水は注ぐ側のカップに残るよ。");
			novel->addSentence(0, "継", "例えば、３０ｍLのカップに２０ｍLの水が、５０ｍLのカップに満杯に水が入っている時、５０ｍLのカップから３０ｍLのカップに水を移すと、５０ｍLのカップには４０ｍLの水が残るね。");
		}
		else if (getObjState("torture","serum") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "血清なんてどこにあるんだろう…");
			novel->addSentence(0, "継", "そういえば拷問室の天井から何かが滴り落ちていたような…");
		}
		else if (getObjState("AboutItem","syringe_r") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "トカゲを探さなくちゃ");
			novel->addSentence(0, "継", "本には牢屋に出没するというようなことが書いてあったけど、今でもいるのかな…");
			novel->addSentence(0, "継", "気長に待ってみよう");
		}
		else if (getObjState("AboutItem","syringe") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "解毒薬が完成したよ！");
			novel->addSentence(0, "継", "急いでバンダナの元へ向かおう");

		}
		else {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "まだ調べていないところがありそうだ");
		}


		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}