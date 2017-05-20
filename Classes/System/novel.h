#pragma once
#include "cocos2d.h"

#define MAX_BRANCH 10

class Novel : public cocos2d::Layer {

private:
	enum ImagePos {
		IMG_NONE,
		IMG_BG,
		IMG_CENTER,
		IMG_LEFT,
		IMG_RIGHT
	};

	typedef struct Task {
		int num;
		ImagePos imgPos;
		std::string imgName;
	} Task;

	typedef struct CTask {
		int num;
		cocos2d::Color3B color;
	} CTask;

	typedef struct FTask {
		int num;
		cocos2d::CallFunc* func;
	} FTask;

	typedef struct STask {
		int num;
		int branchTo[4];
		std::string branchStr[4];
	} STask;

	int mNovelNum[MAX_BRANCH], mNovelSetNum[MAX_BRANCH], mCount, mCharNum, mBranch;
	int mTouchTime; bool mHideMsg, mFast;
	int mImageNum[4]; //Bg,CharaC,CharaL,CharaR
	bool mEndFlag;
	bool mSwitch; //�I�������[�h
	STask mCurrentSTask;	//�I�����[�h���̃^�X�N
	bool mLogOnly;
	std::vector<std::string> mSentense[MAX_BRANCH];	//0�����C���A1�`����
	std::vector<Task> mTask[MAX_BRANCH];
	std::vector<CTask> mColorTask[MAX_BRANCH];
	std::vector<FTask> mFuncTask[MAX_BRANCH];
	std::vector<STask> mSwitchTask[MAX_BRANCH];
	cocos2d::ValueVector mLog;
	int mLogScrollX, mLogScrollY;

	void func();
	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void readTalk();
	//�o�b�N���O
	bool logEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void end();
	bool endCheck();
	void setDelayAnime();

	//�摜�X�V
	void updateImg();
	//�F�X�V
	void updateColor();
	//�C�x���g���s
	void updateFunc();
	//�I�������s
	void updateSwitch();

public:
	virtual ~Novel();

	virtual bool init();
	virtual void update(float delta);

	
	//�I���t���O
	bool getEndFlag();

	//���ǉ�
	void addSentence(int branch,std::string s);
	//�w�i�ݒ�
	void setBg(int branch,std::string s);
	//�L�����N�^�[�E�Z���^�[
	void setCharaC(int branch, std::string s);
	//�L�����N�^�[�E���t�g
	void setCharaL(int branch, std::string s);
	//�L�����N�^�[�E���C�g
	void setCharaR(int branch, std::string s);

	//�^�X�N�̏I���
	void setEndTask(int branch);

	//�����F�ύX
	void setFontColor(int branch, cocos2d::Color3B c);

	//�C�x���g�^�X�N�ǉ�
	void addEvent(int branch, cocos2d::CallFunc* func);

	//�I�������[�h�ǉ�
	void addSwitchEvent(int branch, int br1, std::string st1 = "", int br2 = -1, std::string st2 = "", int br3 = -1, std::string st3 = "", int br4 = -1, std::string st4 = "");

	//���O�����\�����郂�[�h
	void setLogOnly();

	CREATE_FUNC(Novel);
};