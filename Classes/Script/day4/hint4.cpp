#pragma  execution_character_set("utf-8")
#include "Script\day4\fieldDef.h"

USING_NS_CC;

namespace day4 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		if (getObjState("magic_team", "flag") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継", "まずは、この牢屋から出る方法を探そう");
			novel->addSentence(0, "継", "壁にヒビが入っているのが気になるね");
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