#pragma  execution_character_set("utf-8")
#include "Script\day3\fieldDef.h"

USING_NS_CC;

namespace day3 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		//if (getObjState("gate", "renji") == 0 ||
		//	getObjState("classroom", "usawa_") == 0 ||
		//	getObjState("artroom", "maria") == 0) {
		//	novel->setFontColor(0, Color3B::BLUE);
		//	novel->setCharaL(0, "chara/tuguru1.png");
		//	novel->addSentence(0, "継", "学校で散歩って何をしたらいいんだろう");
		//	novel->setFontColor(0, Color3B::RED);
		//	novel->setCharaR(0, "chara/suama1.png");
		//	novel->addSentence(0, "寿甘", "とりあえずいろんな人に話しかけてみようよ");
		//}
		//else
		{
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/suama1.png");
			novel->addSentence(0, "寿甘", "二人ともどこ行っちゃったんだろ…");
			novel->addSentence(0, "寿甘", "とりあえずいろんな人に聞いてみよう");
		}

		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}