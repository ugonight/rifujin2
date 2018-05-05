#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		// 置き換え例
		// mObjectList\[(?<name>.*)\]->getState\(\)
		// getObjState("backyard",${name})

		if (getObjState("gate", "renji") == 0 ||
			getObjState("classroom", "usawa") == 0 ||
			getObjState("artroom", "maria") == 0 || 
			getObjState("corridor", "remon") == 0)
		{
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "二人ともどこ行っちゃったんだろ…");
			novel->addSentence(0, "寿甘", "とりあえずいろんな人に聞いてみよう");
		}
		else if (getObjState("entrance", "backyard") == 0) {
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "もう一度校庭の方を探してみよう");
		}
		else if((getObjState("backyard","blood") != 1 ||
			getObjState("backyard","nail") != 1 ||
			getObjState("backyard", "letter") != 1 ||
			getObjState("backyard","lily") != 1 ) &&
			getObjState("backyard","flag") == 1){
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "まだまだ手掛かりが集められそうね");
			novel->setCharaR(0, "chara/usawa1.png");
			novel->addSentence(0, "宇沢", "血痕以外でも、目についたものは一通り調べてみましょう。");
		}
		else if (getObjState("AboutItem", "whistle_o1") == 0 ||
			getObjState("AboutItem", "whistle_o2") == 0) {
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "何とかしてクロが持ってる物を取り返したいな…");
			novel->addSentence(0, "寿甘", "あの子なら呼べば駆けつけてくれると思うけど、呼ぶための笛は忘れてきちゃったし");
			novel->addSentence(0, "寿甘", "何とか笛を作れないかなー…");
			novel->addSentence(0, "寿甘", "適当な材料を刃物みたいなもので加工できれば…");
			novel->addSentence(0, "寿甘", "穴をあけるのはあいつのくちばしを利用してやろう");
		}
		else if (getObjState("classroom","memo") == 0) {
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "二人が何か手掛かりを残していってるかも");
			novel->addSentence(0, "寿甘", "教室の机を調べてみよう");
		}
		else if (getObjState("gate", "cenotaph") == 0) {
			novel->setFontColor(0, Color3B::RED);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "なんとかして二人に集めた証拠について伝えられないかな…");
			novel->addSentence(0, "寿甘", "幽霊の力を借りればいけるかも…！校門の慰霊碑のところに行ってみよう");
		}
		else {
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "まだ調べていないところがありそうね…");
		}

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}