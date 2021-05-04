#include "MineSweeper.h"

MineSweeper::MineSweeper(int column, int row, int bomb)
{
	this->numOfBomb = bomb;
	this->row = row;
	this->column = column;
	createMineSweeper();
}

MineSweeper::~MineSweeper()
{
	for (int i = 0; i < column; i++)
		delete[] mineSweeper[i];
	delete[] mineSweeper;
}

void MineSweeper::createMineSweeper()
{
	mineSweeper = new int*[column];
	for (int i = 0; i < column; i++)
		mineSweeper[i] = new int[row];
	for (int i = 0; i < column; i++) //mineSweeper歸零
	{
		for (int j = 0; j < row; j++)
		{
			mineSweeper[i][j] = 0;
		}
		cout << endl;
	}
	createBomb();
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			mineSweeper[i][j]=checkBomb(i, j);

}

void MineSweeper::createBomb()
{
	srand(time(NULL));
	int count = 0;
	while (count <= numOfBomb)
	{
		for (int i = 0; i < column; i++) 
		{
			for (int j = 0; j < row; j++)
			{

				if (rand() % (row * column / numOfBomb) == 0)
				{
					mineSweeper[i][j] = -1;
					count++;
				}
				if (count == numOfBomb)
					return;
			}
			cout << endl;
		}
	}


}

void MineSweeper::printMineSweeper()
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cout << mineSweeper[i][j] << " ";
		}
		cout << endl;
	}
}

int MineSweeper::checkBomb(int column, int row)
{
	if (mineSweeper[column][row] == -1)
		return -1;
	else
	{
		int tot=0;
		for(int i=column-1;i<=column+1;i++)
			for (int j = row - 1; j <= row + 1; j++)
			{
				if (i < 0 || j <0 ||i>=this->column||j>=this->row)
					break;
				else if(mineSweeper[i][j] == -1)
					tot++;
			}
		return tot;
	}
}
