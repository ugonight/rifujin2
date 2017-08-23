#pragma  execution_character_set("utf-8")
#include "Script\day2\fieldDef.h"

USING_NS_CC;

namespace day2 {
	void HintMgr::showHint() {
		auto novel = Novel::create();

		if (getObjState("magic_team", "flag") == 0) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継「まずは、この牢屋から出る方法を探そう」");
			novel->addSentence(0, "継「壁にヒビが入っているのが気になるね」");
		}else if (getObjState("magic_team", "flag") == 1) {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継「メモの暗号の意味は、タテ・ヨコ・ナナメ全ての和が一緒になればいいということだね」");
			novel->addSentence(0, "継「要するに、毛布の下のパズルはスライドパズルで魔方陣を解けばいいんだ」");
			novel->addSentence(0, "継「各ラインの数字の和は１５、真ん中の数字は５になると思うよ」");
		}
		else {
			novel->setFontColor(0, Color3B::BLUE);
			novel->setCharaL(0, "chara/tuguru1.png");
			novel->addSentence(0, "継「まだ調べていないところがありそうだ」");
		}


		novel->setEndTask(0);
		this->addChild(novel, 0, "novel");
	}
}