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
	bool mSwitch; //選択肢モード
	STask mCurrentSTask;	//選択モード中のタスク
	bool mLogOnly;
	std::vector<std::string> mSentense[MAX_BRANCH];	//0がメイン、1～分岐
	std::vector<Task> mTask[MAX_BRANCH];
	std::vector<CTask> mColorTask[MAX_BRANCH];
	std::vector<FTask> mFuncTask[MAX_BRANCH];
	std::vector<STask> mSwitchTask[MAX_BRANCH];
	cocos2d::ValueVector mLog;
	int mLogScrollX, mLogScrollY;

	void func();
	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void readTalk();
	//バックログ
	bool logEvent(cocos2d::Touch* touch, cocos2d::Event* event);

	void end();
	bool endCheck();
	void setDelayAnime();

	//画像更新
	void updateImg();
	//色更新
	void updateColor();
	//イベント実行
	void updateFunc();
	//選択肢実行
	void updateSwitch();

public:
	virtual ~Novel();

	virtual bool init();
	virtual void update(float delta);

	
	//終了フラグ
	bool getEndFlag();

	//文追加
	void addSentence(int branch,std::string s);
	//背景設定
	void setBg(int branch,std::string s);
	//キャラクター・センター
	void setCharaC(int branch, std::string s);
	//キャラクター・レフト
	void setCharaL(int branch, std::string s);
	//キャラクター・ライト
	void setCharaR(int branch, std::string s);

	//タスクの終わり
	void setEndTask(int branch);

	//文字色変更
	void setFontColor(int branch, cocos2d::Color3B c);

	//イベントタスク追加
	void addEvent(int branch, cocos2d::CallFunc* func);

	//選択肢モード追加
	void addSwitchEvent(int branch, int br1, std::string st1 = "", int br2 = -1, std::string st2 = "", int br3 = -1, std::string st3 = "", int br4 = -1, std::string st4 = "");

	//ログだけ表示するモード
	void setLogOnly();

	CREATE_FUNC(Novel);
};