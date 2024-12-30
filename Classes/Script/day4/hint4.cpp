#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {
	void HintMgr::showHint() {
		// 迷宮1をクリア後はヒントを発生させない
		if (getObjState("dangeon1", "goal") == 1) {
			return;
		}

		auto novel = Novel::create();

		if (getObjState("aisle3", "baking") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "早いとこ水無月を牢屋から出しちまわないとな…");
			novel->addSentence(0, "バンダナ", "…と言っても、どっから始めたらいいのか全然わかんないぞ…つぐるんは何か当てがあったりしないか？");
			novel->addSentence(0, "継", "うーん…僕は個人的に拷問室の隣の部屋が気になるんだよね");
			novel->addSentence(0, "継", "確かあそこの扉は開かなかったんだけど…ちょっと調べてみよう");
		}

		else if (getObjState("aisle3", "baking") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "木製の扉を壊すのにつるはしのような物があればいいんだが…そんなものどこかにあったか？");
			novel->addSentence(0, "継", "あの石のツタのトゲなんか使えそうじゃないかな");
			novel->addSentence(0, "継", "問題はそれをどうやって取るかだけど…どこかに石を溶かせそうな薬品があったはずだ");
		}

		else if (getObjState("aisle", "remon") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "剥製室に入れるようになったが…次はどうしていこうか？");
			novel->addSentence(0, "継", "うーん…一度水無月さんと話してみてもいいかもね。何か知ってるかもしれない。");
		}

		else if (getObjState("library", "book3") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "業務日誌なんてどこにあるんだ？");
			novel->addSentence(0, "継", "確か書斎にあったはずだ。探してみよう。");
		}

		else if (getObjState("baking", "skeleton") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "「記念に剥製室に飾っておこう」って…倫理観ぶっ壊れてんな…");
			novel->addSentence(0, "継", "本当に酷いね…飲み込んだ鍵が何かに使えるかもしれない。剥製室に行ってみよう。");
		}

		else if (getObjState("library", "book3") == 1 && getObjState("panel", "flag") <= 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "一筆書きのパズルが解けねえな…");
			novel->addSentence(0, "継", "解くための手がかりが少ない気がする…もう一度書斎の日記を調べてみよう。");
		}

		else if (getObjState("panel", "flag") <= 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "一筆書きのパズルが解けねえな…");
			novel->addSentence(0, "継", "パズルで描く図形は日記に挟まっていたメモの通りになるはず…");
			novel->addSentence(0, "継", "下から2行目の真ん中2つの点のどちらからか描き始めると上手くいく気がする");
		}

		else if (getObjState("torture", "guillotine") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "どうやってこの骸骨からカギを取り出すかな…");
			novel->addSentence(0, "継", "…拷問室に行ってみよう");
			novel->addSentence(0, "バンダナ", "…？");
		}

		else if (getObjState("aisle4", "library") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "壊れちまったカギをなんとか直せねえかな…");
			novel->addSentence(0, "継", "ノリとして使えそうなものがどこかにあったはず…何かヌメヌメしたものが…");
		}

		else if (getObjState("aisle", "remon") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "このカギで水無月の牢屋の扉が開くかもな！早速試してみようぜ！");
			novel->addSentence(0, "継", "そうだね。…その前にやり残したことがないか見直しておくのもいいかもしれない。");
		}

		else if (getObjState("aisle2", "flag") == 0) {
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/remon1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "早くこんなところから出ましょう");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "うん。だけど、そのために出口を探さないと…");
		}

		else if (getObjState("aisle4", "rroom") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "バンダナ", "なんだかいっぱいアイテムを入手できたな！");
			novel->addSentence(0, "継", "このカギでどこかの扉が開くかもしれないね。");
		}

		else if (!ItemMgr::sharedItem()->getGetItem("candle") && getObjState("rroom", "skull") <= 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "あの部屋で見たドクロ…同じ形のものがどこかにあった気がするな");
		}

		else if (getObjState("rroom", "skull") <= 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "継", "ろうそくに火を点けないと…");
			novel->addSentence(0, "バンダナ", "火を起こすなら俺の出番だな！");
			novel->addSentence(0, "継", "なんか前にも同じような展開があった気が…火を起こせそうな道具が揃ったらろうそくに使ってみよう。");
		}

		else if (getObjState("rroom", "flag") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "あの絵に何か仕掛けがありそうだね");
			novel->addSentence(0, "継", "ドクロの光の順番に絵の中のドクロに触れてみよう");
		}

		else if (getObjState("aisle", "dangeon") == 0) {
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/remon1.png");
			novel->setFontColor(0, Color3B::RED);
			novel->addSentence(0, "檸檬", "このカギで牢屋の部屋の奥の扉が開くかもしれないわ！早速使ってみましょう！");
			novel->setFontColor(0, Color3B::BLUE);
			novel->addSentence(0, "継", "う、うん");
		}

		else if (getObjState("dangeon1", "goal") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->setCharaR(0, "chara/bandana1.png");
			novel->addSentence(0, "継", "暗いしなんだか迷路みたいで、迷ってしまいそうでなんだか不安だな…");
			novel->addSentence(0, "バンダナ", "まあ適当に道なりに進んでいけばなんとかなるって！");
			novel->addSentence(0, "継", "あはは、そうかもね。入口が南西にあるとしたら北東の方に進んでいくと出口がありそうな気がする。");
		}

		else
		{
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "まだ調べていないところがありそうだ");
		}


		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}