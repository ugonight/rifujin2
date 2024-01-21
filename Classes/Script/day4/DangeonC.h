#pragma once

#include<vector>

class DangeonC
{
public:
	struct Pos
	{
		int x, y;
	};
	enum Direc {
		north,
		east,
		south,
		west
	};

	DangeonC(std::vector<std::vector<int>> stage, Pos initCur, Direc initDirec);

	void toFront();
	void toBack();
	void toLeft();
	void toRight();

	bool backL();
	bool backC();
	bool backR();
	bool frontL();
	bool frontR();

	Pos getPos();
	Direc getDirec();

	void setPos(int x, int y);
	void setDirec(Direc direc);

	Pos getEnemyPos();
	void setEnemyPos(int x, int y);
	
	void moveEnemy();
private:
	std::vector<std::vector<int>> mStage;

	Pos mCurPos = { 3,4 };
	Pos mEnemyPos = { -1,-1 };

	Direc mCurDirec = Direc::north;

	int mView[3][3];
	void getView();

	void moveEnemyA();
	void moveEnemyB();

	bool findStack(std::vector<Pos> stack, Pos target);
	std::vector<Pos> searchPath(Pos start, Pos goal);
	std::vector<Pos> mTrackingPath;
};

