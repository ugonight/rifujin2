#pragma once

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField() override; \
								virtual void changedField() override; \
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

// BGM・SE再生
#include "audio/include/AudioEngine.h"
inline int playSoundBS(std::string filename, bool loop = false) {
	auto userDef = cocos2d::UserDefault::getInstance();
	float volume;

	if (filename.find("BGM") != std::string::npos) {
		volume = userDef->getFloatForKey("volumeBGM", 1.0f);
	}
	else {
		volume = userDef->getFloatForKey("volumeSE", 1.0f);
	}
	
	if (volume != 0.0)
		return cocos2d::AudioEngine::play2d(filename.c_str(), loop, volume);

	return -1;
}