#pragma once
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
class MineSweeper
{
private:
	int row;//行
	int column;//列
	int numOfBomb;//炸彈數量
	int** mineSweeper;
public:
	MineSweeper(int, int, int);
	void createMineSweeper();
	void createBomb();
	void printMineSweeper();
	int checkBomb(int, int);
	~MineSweeper();
};

