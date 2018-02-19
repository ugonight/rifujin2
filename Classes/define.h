#pragma once

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 

#define FONT_NAME "fonts/font_1_honokamarugo_1.1.ttf"

//stringstreamの初期化
inline void resetStr(std::stringstream &str) {
	str.clear(); str.str("");
}

//ノードの表示/非表示をタッチの有効/無効とともに設定する
inline void setVisibleWithTouch(cocos2d::Node *node, bool visible) {
	if (visible) {
		node->setVisible(true);
		node->getEventDispatcher()->resumeEventListenersForTarget(node);
	}
	else {
		node->setVisible(false);
		node->getEventDispatcher()->pauseEventListenersForTarget(node);
	}
}

//userDefault登録
inline void setGetStill(int id) {
	auto userDef = cocos2d::UserDefault::getInstance();
	userDef->setBoolForKey(cocos2d::StringUtils::format("still%02d", id).c_str(), true);
	userDef->flush();
}

//userDefault登録
inline void setGetMusic(int id) {
	auto userDef = cocos2d::UserDefault::getInstance();
	userDef->setBoolForKey(cocos2d::StringUtils::format("music%02d", id).c_str(), true);
	userDef->flush();
}