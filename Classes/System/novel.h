#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

#define MAX_BRANCH 20

// �������ۂ��̂Ŋ��ǃX�L�b�v����
#define USE_ALREADY false
// SetString�Ń��������[�N���Ă�񂶂�ˋ^�f
#define USE_SETSTRING false

class Novel : public cocos2d::Layer {

private:
	enum ImagePos {
		IMG_NONE,
		IMG_BG,
		IMG_CENTER,
		IMG_LEFT,
		IMG_RIGHT
	};

	struct Task {
		int num;
		virtual void update(Novel* parent) {};
	};

	struct ITask : public Task {
		ImagePos imgPos;
		std::string imgName;
		//�摜�X�V
		void update(Novel* parent);
	};

	struct CTask : public Task {
		cocos2d::Color3B color;
		//�F�X�V
		void update(Novel* parent);
	};

	struct FTask : public Task {
		cocos2d::CallFunc* func;
		//�C�x���g���s
		void update(Novel* parent);
		~FTask();
		// ��������~�߂邩
		bool stopFast;
	};

	struct STask : public Task {
		int branchTo[4];
		std::string branchStr[4];
		//�I�������s
		void update(Novel* parent);
	};

	struct JTask : public Task {
		int branch, novelNum;
		//���̓W�����v
		void update(Novel* parent);
	};

	struct PTask : public Task {
		cocos2d::FiniteTimeAction* func;
		// �C�x���g���s�i���͂��~�߂�j
		void update(Novel* parent);
		~PTask();
	};

	int mNovelNum[MAX_BRANCH], mNovelSetNum[MAX_BRANCH], mCount, mCharNum, mBranch;
	int mTouchTime; bool mHideMsg, mFast;
	int mImageNum[4]; //Bg,CharaC,CharaL,CharaR
	bool mEndFlag;
	bool mSwitch; //�I�������[�h
	STask* mCurrentSTask;	//�I�����[�h���̃^�X�N
	bool mLogOnly;
	std::vector<std::string> mSentense[MAX_BRANCH];	//0�����C���A1�`����
	std::vector<std::string> mName[MAX_BRANCH];
	std::vector<std::shared_ptr<Task>> mTask[MAX_BRANCH];
	int mTaskNum[MAX_BRANCH];
	cocos2d::ValueVector mLog;
	int mLogScrollX, mLogScrollY;
	cocos2d::CallFunc* mEndFunc; // �m�x���I����C�x���g
#if USE_ALREADY
	static int mSerialNum[MAX_BRANCH];	// �`���v�^�[���Ƃ̑S�̂ŘA�ԂɂȂ��Ă镶�ԍ�
	int mDefSerialNum[MAX_BRANCH];	// Novel�������̘A��
	cocos2d::ValueMap mAlreadyMap;
#endif

	void func();
	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void readTalk();
	//�o�b�N���O
	bool logEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void end();
	bool endCheck();
	void setDelayAnime();
	void stopDelayAnime();
	void pauseDelayAnime();
	void resumeDelayAnime();
#if !USE_SETSTRING
	void initLabel(std::string text = "", std::string name = "");
#endif

#if USE_ALREADY
	void writeAlready();
	void readAlready();
#endif

public:
	virtual ~Novel();

	virtual bool init();
	virtual void update(float delta);


	//�I���t���O
	bool getEndFlag();

	//���ǉ� (mNovelSetNum��Ԃ�)
	int addSentence(int branch, std::string name, std::string s);
	//�w�i�ݒ�
	void setBg(int branch, std::string s);
	//�L�����N�^�[�E�Z���^�[
	void setCharaC(int branch, std::string s);
	//�L�����N�^�[�E���t�g
	void setCharaL(int branch, std::string s);
	//�L�����N�^�[�E���C�g
	void setCharaR(int branch, std::string s);

	//�^�X�N�̏I���
	void setEndTask(int branch);
	void setEndTask(int branch, cocos2d::CallFunc* endfunc);

	//�����F�ύX
	void setFontColor(int branch, cocos2d::Color3B c);

	//�C�x���g�^�X�N�ǉ�
	void addEvent(int branch, cocos2d::CallFunc* func, bool stopFast = false);

	//�|�[�Y�C�x���g�^�X�N�ǉ��i�摜�𓮂������肷��Ƃ���Novel�̂��͎̂g��Ȃ��j
	void addPauseEvent(int branch, cocos2d::FiniteTimeAction* func);

	//�I�������[�h�ǉ�
	void addSwitchEvent(int branch, int br1, std::string st1 = "", int br2 = -1, std::string st2 = "", int br3 = -1, std::string st3 = "", int br4 = -1, std::string st4 = "");

	//�W�����v�^�X�N�ǉ�
	void setJump(int branch, int branchTo, int novelNum);

	//���O�����\�����郂�[�h
	void setLogOnly();

#if USE_ALREADY
	// �A�Ԃ��������i�`���v�^�[�J�n���j
	void initSerialNum();
#endif

	// ����������~�߂�
	void stopMessage();
	// ����������ĊJ����
	void resumeMessage();

	CREATE_FUNC(Novel);
};

