#include<iostream>
#include <windows.h>
#include<ctime>
#include "MineSweeper.h"
using namespace std;
int column, row, bomb, mode;
int c, r;

//檢查輸入值是否合理
bool checkMineRange(int column, int row, int bomb)
{
	bool b = 1;
	if ((column <= 7 || column > 20))
	{
		cout << "列數不合理，請重新輸入";
		b = 0;
	}
	else if (row <= 8 || row > 25)
	{
		cout << "行數不合理，請重新輸入";
		b = 0;
	}
	else if (bomb <= 0 || bomb > (row - 1) * (column - 1))
	{
		cout << "炸彈數量不合理，請重新輸入";
		b = 0;
	}
	return b;
}
bool checkSelectRange(int c, int r, int mode, MineSweeper& m)
{
	bool b = 1;
	if (c >= column || c < 0)
	{
		cout << "列數不合理，請重新輸入";
		b = 0;
	}
	else if (r >= row || r < 0)
	{
		cout << "行數不合理，請重新輸入";
		b = 0;
	}
	else if (mode > 2 || mode < 0)
	{
		cout << "無此種模式，請重新輸入";
		b = 0;
	}
	else if (m.isSelect(c, r))
	{
		cout << "該位置已被選過，請重新輸入";
		b = 0;
	}
	return b;
}
void printText()
{
	cout << "mode=1:確認該點數字" << endl;
	cout << "mode=2:標記該點位置" << endl;
	cout << "請輸入列，行，mode:";
}
bool End()
{
	char a;
	cout << "要再玩一次嗎?(y/n)";
	cin >> a;
	if (a == 'y' || a == 'Y')
	{
		system("cls");
		return true;
	}
	else if (a == 'n' || a == 'N')
	{
		cout << "Thanks for playing!";
		return false;
	}
	else
	{
		cout << "無效指令";
		return false;
	}
}


int main()
{
	bool play = true;

	cout << "	歡迎遊玩踩地雷				" << endl;
	cout << "---------------------------------------" << endl;
	cout << "	遊玩方法:先輸入大小			" << endl;
	cout << "	接著輸入行列及炸彈數量		" << endl;
	cout << "	接著輸入位置				" << endl;
	cout << "---------------------------------------" << endl;
	cout << "	請輸入1繼續				" << endl;
	cout << "	若要退出					" << endl;
	cout << "	請輸入0退出遊戲:";

	int P;
	cin >> P;

	if (P == 0)
	{
		return 0;
	}

	while (play)
	{

		cout << "請輸入 列(8~20) 行(8~25) 炸彈數量(1~(列-1)*(行-1)):";

		while (cin >> column >> row >> bomb && !checkMineRange(column, row, bomb))
		{
			Sleep(1500);
			system("cls");
			cout << "請輸入 列(8~20) 行(8~25) 炸彈數量(1~(列-1)*(行-1)):";
		}
		MineSweeper m(column, row, bomb);
		time_t t1 = time(NULL);
		m.printMineSweeper();

		printText();
		cin >> c >> r >> mode;
		m.createMineSweeper(c - 1, r - 1);
		printText();
		while (cin >> c >> r >> mode)
		{
			if (!checkSelectRange(c - 1, r - 1, mode, m))
			{
				Sleep(1500);
				m.printMineSweeper();
				printText();
				continue;
			}
			if (m.isBomb(c - 1, r - 1) && mode == 1)
				break;
			if (mode == 1)
				m.selectMode1(c - 1, r - 1);
			else if (mode == 2)
				m.selectMode2(c - 1, r - 1);

			if (m.isWin())
			{
				cout << "win" << endl;;
				cout << "使用時間為:" << time(NULL) - t1 << "秒" << endl;
				return 0;
			}
			printText();
		}
		m.selectBomb();
		m.printMineSweeper();
		cout << "lose" << endl;
		play = End();
	}
}
