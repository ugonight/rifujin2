#pragma once

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 

#define FONT_NAME "fonts/font_1_honokamarugo_1.1.ttf"

//stringstream‚Ì‰Šú‰»
inline void resetStr(std::stringstream &str) {
	str.clear(); str.str("");
}

//ƒm[ƒh‚Ì•\Ž¦/”ñ•\Ž¦‚ðƒ^ƒbƒ`‚Ì—LŒø/–³Œø‚Æ‚Æ‚à‚ÉÝ’è‚·‚é
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

//userDefault“o˜^
inline void setGetStill(int id) {
	auto userDef = cocos2d::UserDefault::getInstance();
	userDef->setBoolForKey(cocos2d::StringUtils::format("still%02d", id).c_str(), true);
	userDef->flush();
}

//userDefault“o˜^
inline void setGetMusic(int id) {
	auto userDef = cocos2d::UserDefault::getInstance();
	userDef->setBoolForKey(cocos2d::StringUtils::format("music%02d", id).c_str(), true);
	userDef->flush();
}

// BGMESEÄ¶
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
		return cocos2d::experimental::AudioEngine::play2d(filename.c_str(), loop, volume);

	return -1;
}