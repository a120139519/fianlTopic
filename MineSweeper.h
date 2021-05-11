#pragma once
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<Windows.h>
using namespace std;
class MineSweeper
{
private:
	int row;//行 max=25
	int column;//列 max=20
	int numOfBomb;//炸彈數量
	int** mineSweeper;
	bool** select; //該位置是否被選過
	bool** mode2;
public:

	int getRow();
	int getColumn();
	void setMode2(int, int);
	void selectMode1(int, int);
	void selectMode2(int, int);
	void poi(int, int);//不知道要取甚麼名字...反正是當選擇的位置為零時，翻開附近的牌
	bool isWin();//檢查是否勝利
	void selectBomb();
	void setSelect(int, int);//將該位置設定已被選過
	bool isBomb(int, int);//檢查該位置是否為炸彈 是則回傳1
	bool isSelect(int, int);//檢查該位置是否被選過 是則回傳1
	int getMineSweeperOfNum(int, int);//回傳該位置炸彈數量
	MineSweeper(int, int, int);
	void createMineSweeper(int,int);
	void createBomb(int,int);
	bool isMode2(int, int);
	void printMineSweeper();
	int checkBomb(int, int);//檢查周圍炸彈數量
	~MineSweeper();
};

