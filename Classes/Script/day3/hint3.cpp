#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

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

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}