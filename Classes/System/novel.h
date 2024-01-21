#pragma once
#pragma  execution_character_set("utf-8")
#include "cocos2d.h"

#define MAX_BRANCH 20

// 無理っぽいので既読スキップ封印
#define USE_ALREADY false
// SetStringでメモリリークしてるんじゃね疑惑
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
		//画像更新
		void update(Novel* parent);
	};

	struct CTask : public Task {
		cocos2d::Color3B color;
		//色更新
		void update(Novel* parent);
	};

	struct FTask : public Task {
		cocos2d::CallFunc* func;
		//イベント実行
		void update(Novel* parent);
		~FTask();
		// 早送りを止めるか
		bool stopFast;
	};

	struct STask : public Task {
		int branchTo[4];
		std::string branchStr[4];
		//選択肢実行
		void update(Novel* parent);
	};

	struct JTask : public Task {
		int branch, novelNum;
		//文章ジャンプ
		void update(Novel* parent);
	};

	struct PTask : public Task {
		cocos2d::FiniteTimeAction* func;
		// イベント実行（文章を止める）
		void update(Novel* parent);
		~PTask();
	};

	int mNovelNum[MAX_BRANCH], mNovelSetNum[MAX_BRANCH], mCount, mCharNum, mBranch;
	int mTouchTime; bool mHideMsg, mFast;
	int mImageNum[4]; //Bg,CharaC,CharaL,CharaR
	bool mEndFlag;
	bool mSwitch; //選択肢モード
	STask* mCurrentSTask;	//選択モード中のタスク
	bool mLogOnly;
	std::vector<std::string> mSentense[MAX_BRANCH];	//0がメイン、1～分岐
	std::vector<std::string> mName[MAX_BRANCH];
	std::vector<std::shared_ptr<Task>> mTask[MAX_BRANCH];
	int mTaskNum[MAX_BRANCH];
	cocos2d::ValueVector mLog;
	int mLogScrollX, mLogScrollY;
	cocos2d::CallFunc* mEndFunc; // ノベル終了後イベント
#if USE_ALREADY
	static int mSerialNum[MAX_BRANCH];	// チャプターごとの全体で連番になってる文番号
	int mDefSerialNum[MAX_BRANCH];	// Novel生成時の連番
	cocos2d::ValueMap mAlreadyMap;
#endif

	void func();
	bool touchEvent(cocos2d::Touch* touch, cocos2d::Event* event);
	void readTalk();
	//バックログ
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


	//終了フラグ
	bool getEndFlag();

	//文追加 (mNovelSetNumを返す)
	int addSentence(int branch, std::string name, std::string s);
	//背景設定
	void setBg(int branch, std::string s);
	//キャラクター・センター
	void setCharaC(int branch, std::string s);
	//キャラクター・レフト
	void setCharaL(int branch, std::string s);
	//キャラクター・ライト
	void setCharaR(int branch, std::string s);

	//タスクの終わり
	void setEndTask(int branch);
	void setEndTask(int branch, cocos2d::CallFunc* endfunc);

	//文字色変更
	void setFontColor(int branch, cocos2d::Color3B c);

	//イベントタスク追加
	void addEvent(int branch, cocos2d::CallFunc* func, bool stopFast = false);

	//ポーズイベントタスク追加（画像を動かしたりするときはNovelのものは使わない）
	void addPauseEvent(int branch, cocos2d::FiniteTimeAction* func);

	//選択肢モード追加
	void addSwitchEvent(int branch, int br1, std::string st1 = "", int br2 = -1, std::string st2 = "", int br3 = -1, std::string st3 = "", int br4 = -1, std::string st4 = "");

	//ジャンプタスク追加
	void setJump(int branch, int branchTo, int novelNum);

	//ログだけ表示するモード
	void setLogOnly();

#if USE_ALREADY
	// 連番を初期化（チャプター開始時）
	void initSerialNum();
#endif

	// 文字送りを止める
	void stopMessage();
	// 文字送りを再開する
	void resumeMessage();

	CREATE_FUNC(Novel);
};

