#include "DangeonC.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <cocos2d.h>

DangeonC::DangeonC(std::vector<std::vector<int>> stage, Pos initCur, Direc initDirec)
	: mStage(stage), mCurPos(initCur), mCurDirec(initDirec)
{
	getView();
}

void DangeonC::toFront()
{
	Pos dstPos = { 0, 0 };

	switch (mCurDirec)
	{
	case north:
		dstPos.x = mCurPos.x;
		dstPos.y = mCurPos.y - 1;
		break;
	case east:
		dstPos.x = mCurPos.x + 1;
		dstPos.y = mCurPos.y;
		break;
	case south:
		dstPos.x = mCurPos.x;
		dstPos.y = mCurPos.y + 1;
		break;
	case west:
		dstPos.x = mCurPos.x - 1;
		dstPos.y = mCurPos.y;
		break;
	}

	if (dstPos.x < mStage.at(0).size() && dstPos.y < mStage.size() && mStage[dstPos.y][dstPos.x] == 0) {
		mCurPos = dstPos;
	}

	// 敵を動かす
	//if (mEnemyPos.x > 0) {
	//	moveEnemy();
	//}

	getView();
}

void DangeonC::toBack()
{
	mCurDirec = (Direc)(((int)mCurDirec + 2) % 4);
	getView();
}

void DangeonC::toLeft()
{
	mCurDirec = (Direc)(mCurDirec - 1);
	if (mCurDirec < 0) mCurDirec = (Direc)3;
	getView();
}

void DangeonC::toRight()
{
	mCurDirec = (Direc)(((int)mCurDirec + 1) % 4);
	getView();
}

bool DangeonC::backL()
{
	return mView[0][0];
}

bool DangeonC::backC()
{
	return mView[0][1];
}

bool DangeonC::backR()
{
	return mView[0][2];
}

bool DangeonC::frontL()
{
	return mView[1][0];
}

bool DangeonC::frontR()
{
	return mView[1][2];
}

DangeonC::Pos DangeonC::getPos()
{
	return mCurPos;
}

DangeonC::Direc DangeonC::getDirec()
{
	return mCurDirec;
}

void DangeonC::setPos(int x, int y)
{
	mCurPos.x = x;
	mCurPos.y = y;
	getView();
}

void DangeonC::setDirec(Direc direc)
{
	mCurDirec = direc;
	getView();
}

DangeonC::Pos DangeonC::getEnemyPos()
{
	return mEnemyPos;
}

void DangeonC::setEnemyPos(int x, int y)
{
	mEnemyPos.x = x;
	mEnemyPos.y = y;
}

void DangeonC::getView()
{
	const int SIZE_X = mStage.at(0).size(), SIZE_Y = mStage.size();

	// 回転行列
	float th = -(3.141592f / 2.0f) * (float)(int)mCurDirec;
	using namespace boost::numeric::ublas;
	matrix<int> rotate(2, 2);
	rotate(0, 0) = cos(th), rotate(0, 1) = -sin(th);
	rotate(1, 0) = sin(th), rotate(1, 1) = cos(th);
	// 周辺切り出し
	int around[3][3] = { {1,1,1}, {1,1,1}, {1,1,1} };
	if (mCurPos.y - 1 >= 0 && mCurPos.x - 1 >= 0) around[0][0] = mStage[mCurPos.y - 1][mCurPos.x - 1];
	if (mCurPos.y - 1 >= 0) around[0][1] = mStage[mCurPos.y - 1][mCurPos.x];
	if (mCurPos.y - 1 >= 0 && mCurPos.x + 1 < SIZE_X) around[0][2] = mStage[mCurPos.y - 1][mCurPos.x + 1];
	if (mCurPos.x - 1 >= 0) around[1][0] = mStage[mCurPos.y][mCurPos.x - 1];
	around[1][1] = mStage[mCurPos.y][mCurPos.x];
	if (mCurPos.x + 1 < SIZE_X) around[1][2] = mStage[mCurPos.y][mCurPos.x + 1];
	if (mCurPos.y + 1 < SIZE_Y && mCurPos.x - 1 >= 0) around[2][0] = mStage[mCurPos.y + 1][mCurPos.x - 1];
	if (mCurPos.y + 1 < SIZE_Y) around[2][1] = mStage[mCurPos.y + 1][mCurPos.x];
	if (mCurPos.y + 1 < SIZE_Y && mCurPos.x + 1 < SIZE_X) around[2][2] = mStage[mCurPos.y + 1][mCurPos.x + 1];
	// 回転
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix<int> pos(2, 1);
			pos(0, 0) = j - 1; pos(1, 0) = i - 1;
			matrix<int> dst = prod(rotate, pos);
			int x = dst(0, 0) + 1, y = dst(1, 0) + 1;
			mView[y][x] = around[i][j];
		}
	}
}

void DangeonC::moveEnemy()
{
	int dx = mEnemyPos.x - mCurPos.x, dy = mEnemyPos.y - mCurPos.y;
	int d = sqrt(pow(dx, 2) + pow(dy, 2));

	if (d <= 3)
	{
		// 距離が近かったら単純に追いかける
		moveEnemyA();
	}
	else
	{
		// 距離が遠かったら迷路を探索する
		moveEnemyB();
	}
}

void DangeonC::moveEnemyA() {
	int dx = mEnemyPos.x - mCurPos.x, dy = mEnemyPos.y - mCurPos.y;

	// 右
	if (dx < 0 && mStage[mEnemyPos.y].size() > mEnemyPos.x && mStage[mEnemyPos.y][mEnemyPos.x + 1] == 0) {
		mEnemyPos.x = mEnemyPos.x + 1;
	}
	// 左
	else if (dx > 0 && mEnemyPos.x > 0 && mStage[mEnemyPos.y][mEnemyPos.x - 1] == 0) {
		mEnemyPos.x = mEnemyPos.x - 1;
	}
	// 上
	else if (dy > 0 && mEnemyPos.y > 0 && mStage[mEnemyPos.y - 1][mEnemyPos.x] == 0) {
		mEnemyPos.y = mEnemyPos.y - 1;
	}
	// 下
	else if (dy < 0 && mStage.size() > mEnemyPos.y && mStage[mEnemyPos.y + 1][mEnemyPos.x] == 0) {
		mEnemyPos.y = mEnemyPos.y + 1;
	}
	// 同じ位置
	else if (dx == 0 && dy == 0) {

	}
	// ハマったら動ける方向へ移動
	else
	{
		bool loop = true;
		while (loop)
		{
			int direc = cocos2d::random(0, 3);
			switch (direc)
			{
			case 0:
				// 右
				if (mStage[mEnemyPos.y].size() > mEnemyPos.x && mStage[mEnemyPos.y][mEnemyPos.x + 1] == 0) {
					mEnemyPos.x = mEnemyPos.x + 1;
					loop = false;
				}
				break;
			case 1:
				// 左
				if (mEnemyPos.x > 0 && mStage[mEnemyPos.y][mEnemyPos.x - 1] == 0) {
					mEnemyPos.x = mEnemyPos.x - 1;
					loop = false;
				}
				break;
			case 2:
				// 上
				if (mEnemyPos.y > 0 && mStage[mEnemyPos.y - 1][mEnemyPos.x] == 0) {
					mEnemyPos.y = mEnemyPos.y - 1;
					loop = false;
				}
				break;
			case 3:
				// 下
				if (mStage.size() > mEnemyPos.y && mStage[mEnemyPos.y + 1][mEnemyPos.x] == 0) {
					mEnemyPos.y = mEnemyPos.y + 1;
					loop = false;
				}
				break;
			default:
				loop = false;
				break;
			}
		}

	}
}

void DangeonC::moveEnemyB() {

	if (mTrackingPath.empty())
	{
		mTrackingPath = searchPath(mEnemyPos, mCurPos);
		mTrackingPath.erase(mTrackingPath.begin());
	}

	if (mTrackingPath.size() > 0)
	{
		auto next = mTrackingPath.at(0);
		mEnemyPos.x = next.x;
		mEnemyPos.y = next.y;
		
		mTrackingPath.erase(mTrackingPath.begin());
	}
}

#pragma region 経路探索

inline bool DangeonC::findStack(std::vector<Pos> stack, Pos target) {
	return std::find_if(stack.begin(), stack.end(), [target](Pos p) {return p.x == target.x && p.y == target.y; }) != stack.end();
}

std::vector<DangeonC::Pos> DangeonC::searchPath(Pos start, Pos goal) {
	std::vector<Pos> stack;
	std::vector<Pos> trace;
	trace.push_back(start);

	Pos current = start;
	int stackPos = 0;

	while (true)
	{
		// ゴールに着いたら終了
		if (current.x == goal.x && current.y == goal.y)
		{
			break;
		}

		// スタックになかったら追加
		if (!findStack(stack, current)) {
			stack.push_back(current);
		}

		// 進めるマスを探す
		auto next = Pos{ -1,-1 };
		{
			int cx = current.x, cy = current.y;

			std::vector<std::pair<int, Pos>> dstPosList = {
				// ↑
				{ current.y - goal.y, Pos{ cx,cy - 1 }},
				// ↓
				{ goal.y - current.y, Pos{ cx,cy + 1 }},
				// ←
				{ current.x - goal.x, Pos{ cx - 1,cy }},
				// →
				{ goal.x - current.x, Pos{ cx + 1,cy }},
			};

			// ゴールの位置関係で優先度を付ける
			std::sort(dstPosList.begin(), dstPosList.end(), [](std::pair<int, Pos> a, std::pair<int, Pos> b) {
				return a.first > b.first;
				});

			for (auto dstPos : dstPosList)
			{
				int dx = dstPos.second.x, dy = dstPos.second.y;
				if (dx >= 0 && dy >= 0 && dx < mStage[0].size() && dy < mStage.size() &&
					mStage[dy][dx] == 0 && !findStack(stack, Pos{ dx,dy }))
				{
					next = Pos{ dx,dy };
					break;
				}
			}

		}

		// 進めなくなったら一つ戻る
		if (next.x < 0 && next.y < 0)
		{
			trace.pop_back();
			if (trace.empty()) break;

			current = trace.back();
		}

		// 進める場合移動
		else
		{
			current = next;
			trace.push_back(next);
		}
	}

	return trace;
}

#pragma endregion
