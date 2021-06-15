#include "MineSweeper.h"

MineSweeper::MineSweeper(int column, int row, int bomb)
{
	this->numOfBomb = bomb;
	this->row = row;
	this->column = column;
	mineSweeper = new int* [column];
	select = new bool* [column];
	mode2 = new bool* [column];
	for (int i = 0; i < column; i++)
	{
		mineSweeper[i] = new int[row];
		select[i] = new bool[row];
		mode2[i] = new bool[row];
	}
	for (int i = 0; i < column; i++) //mineSweeper歸零
	{
		for (int j = 0; j < row; j++)
		{
			select[i][j] = 0;
			mode2[i][j] = 0;
			mineSweeper[i][j] = 0;
		}
	}
}

MineSweeper::~MineSweeper()
{
	for (int i = 0; i < column; i++)
		delete[] mineSweeper[i];
	delete[] mineSweeper;
	for (int i = 0; i < column; i++)
		delete[] select[i];
	delete[] select;
	for (int i = 0; i < column; i++)
		delete[] mode2[i];
	delete[] mode2;
}

void MineSweeper::createMineSweeper(int c, int r)
{

	createBomb(c, r);
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			mineSweeper[i][j] = checkBomb(i, j);
	setSelect(c, r);
	if (getMineSweeperOfNum(c, r) == 0)
	{
		RecursionOpen(c, r);
	}


	printMineSweeper();
}

void MineSweeper::createBomb(int c, int r)
{
	srand(time(NULL));
	int count = 0;
	while (count <= numOfBomb)
	{
		for (int i = 0; i < column; i++)
		{
			for (int j = 0; j < row; j++)
			{

				if ((rand() % (row * column / numOfBomb) == 0))
				{
					if ((i >= c - 1 && i <= c + 1) && (j >= r - 1 && j <= r + 1))
					{
						continue;
					}
					mineSweeper[i][j] = -1;
					count++;
				}
				if (count == numOfBomb)
					return;
			}

		}
	}


}

void MineSweeper::printMineSweeper()
{
	system("cls");
	for (int i = 0; i < column; i++)
	{
		if (i == 0)
		{
			cout << "    ";
			for (int k = 0; k < row; k++)
			{
				cout << setw(2) << k + 1 << "  ";
			}
			cout << endl;
		}
		for (int j = 0; j < row; j++)
		{
			if (j == 0)
			{
				cout << setw(2) << i + 1 << "  ";
			}
			if (isMode2(i, j))
			{
				cout << setw(2) << "/" << "  ";
				continue;
			}
			if (isSelect(i, j))
			{
				if (isBomb(i, j))
					cout << setw(2) << "*" << "  ";

				else
					cout << setw(2) << mineSweeper[i][j] << "  ";

			}
			else
				cout << setw(2) << "-" << "  ";
		}
		cout << endl;
	}
}

int MineSweeper::checkBomb(int c, int r)
{
	if (mineSweeper[c][r] == -1)
		return -1;
	else
	{
		int tot = 0;
		for (int i = c - 1; i <= c + 1; i++)
			for (int j = r - 1; j <= r + 1; j++)
			{
				if (i < 0 || j < 0 || i >= column || j >= row)
				{
				}
				else if (mineSweeper[i][j] == -1)
					tot++;
			}
		return tot;
	}
}

bool MineSweeper::isBomb(int i, int j)
{
	return (mineSweeper[i][j] == -1) ? 1 : 0;
}

bool MineSweeper::isSelect(int i, int j)
{
	return (select[i][j]);
}

void MineSweeper::setSelect(int i, int j)
{
	select[i][j] = 1;
}

int MineSweeper::getMineSweeperOfNum(int i, int j)
{
	return mineSweeper[i][j];
}

bool MineSweeper::isWin()
{
	int tot = 0;
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			tot += select[i][j];
	if (tot == row * column - numOfBomb)
		return 1;
	else
		return 0;
}

void MineSweeper::RecursionOpen(int c, int r)
{
	if (getMineSweeperOfNum(c, r) != 0)
	{
		setSelect(c, r);
		return;
	}
	for (int i = c - 1; i <= c + 1; i++)
	{
		for (int j = r - 1; j <= r + 1; j++)
		{

			if (i < 0 || j < 0 || i >= column || j >= row || (i == c && j == r))
			{
			}
			else if (!isSelect(i, j))
			{
				setSelect(i, j);
				RecursionOpen(i, j);
			}
		}
	}
}

void MineSweeper::selectBomb()
{
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
		{
			if (isBomb(i, j))
				setSelect(i, j);
		}
}

void MineSweeper::selectMode1(int c, int r)
{
	setSelect(c, r);
	if (getMineSweeperOfNum(c, r) == 0)
	{
		RecursionOpen(c, r);
	}
	printMineSweeper();
}

void MineSweeper::selectMode2(int c, int r)
{
	setMode2(c, r);
	printMineSweeper();
}

bool MineSweeper::isMode2(int c, int r)
{

	return mode2[c][r];
}

void  MineSweeper::setMode2(int c, int r)
{
	mode2[c][r] = (!mode2[c][r]) ? 1 : 0;
}

int MineSweeper::getColumn()
{
	return column;
}

int MineSweeper::getRow()
{
	return row;
}
