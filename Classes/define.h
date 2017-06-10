#pragma once

#define CREATE_FIELD(cName) class cName : public Field { \
							public: \
								virtual void initField(); \
								virtual void changedField(); \
								CREATE_FUNC(cName); 

#define FONT_NAME "fonts/font_1_honokamarugo_1.1.ttf"

//stringstream�̏�����
inline void resetStr(std::stringstream &str) {
	str.clear(); str.str("");
}

//�m�[�h�̕\��/��\�����^�b�`�̗L��/�����ƂƂ��ɐݒ肷��
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