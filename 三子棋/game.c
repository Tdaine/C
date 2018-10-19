#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void Init_board(char arr[ROW][COL], int  row, int  col)//初始化棋盘
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			arr[i][j] = ' ';
		}
	}
}
void DisplayBoard(char arr[ROW][COL], int  row, int  col)//打印
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col - 1; j++)
		{
			printf(" %c |", arr[i][j]);
		}
		printf(" %c \n", arr[i][j]);
		if (i < row - 1)
		{
			for (j = 0; j < col - 1; j++)
			{
				printf("---|");
			}
			printf("---");
		}
		printf("\n");
	}
}
void PlayerMove(char arr[ROW][COL], int  row, int  col)//玩家走
{
	int x=0, y=0;
	printf("玩家走：");
	while (1)
	{
		scanf("%d %d", &x, &y);
		if ((x >= 1 && x <= row) && (y >= 1 && y <= col))
		{
			if (arr[x - 1][y - 1] == ' ')
			{
				arr[x - 1][y - 1] = 'X';
				break;
			}
		}
		printf("请重新输入\n");
	}
}
void ComputerMove(char arr[ROW][COL], int  row, int  col)//电脑走
{
	printf("电脑走：\n");
	while (1)
	{
		int x = rand() % ROW;
		int y = rand() % COL;
		if (arr[x][y] == ' ')
		{
			arr[x][y] = 'Y';
			break;
		}
	}
}
char Iswin(char arr[ROW][COL], int  row, int  col)//判断输赢
{
	int i = 0; int j = 0;
	for (i = 0; i < row; i++)//横判断
	{
		int count = 0;
		for (j = 0; j <= col - num+1; j++)
		{
			if (arr[i][j] == arr[i][j + 1]&&arr[i][j]!=' ')
			{
				count++;
				if (count == num-1)
				{
					return arr[i][j];
				}
			}
			
		}
			
	}
	for (j = 0; j < col; j++)
	{
		int count = 0;
		for (i = 0; i <= row - num+1; i++)//判断竖
		{
			if (arr[i][j] == arr[i + 1][j] && arr[i][j] != ' ')
			{
				count++;
				if (count == num-1)
				{
					return arr[i][j];
				}
			}
		}
	}
	for (i = 0; i <= row - num; i++)
	{
		int count = 0;
		int n = i;

		for (j = 0; j <= col - num + 1; j++)//判段斜
		{
			for (int t = j; t <= col - num + 1; t++)
			{
				if (arr[n][t] == arr[n + 1][t + 1] && arr[n][t] != ' ')
				{
					n++;
					count++;
					if (count == num - 1)
					{
						return arr[n - 1][t];
					}
				}
			}
		}
	}
	for (i = 0; i <= row - num; i++)//判断斜/
	{
		int count = 0;
		int n = i;
		for (j = num - 1; j >= col-num+1; j--)
		{
			for (int t = j; t >= col-num+1; t--)
			{
				if (arr[n][t] == arr[n + 1][t - 1] && arr[n][t] != ' ')
				{
					count++; n++;
					if (count == num - 1)
					{
						return arr[n - 1][t];
					}
				}
			}
		}
	}
}

int IFull(char arr[ROW][COL], int  row, int  col)////判断满盘
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (arr[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}
//char Iswin(char arr[ROW][COL], int  row, int  col)//判断输赢
//{
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < row; i++)
//	{
//		for (j = 0; j <=col-num; j++)
//		{
//			if (arr[i][j] == arr[i][j + 1] && arr[i][j + 1] == arr[i][j + 2] && arr[i][j] != ' ')
//			{
//				return arr[i][j];
//			}
//		}
//	}
//	for (j = 0; j < col; j++)
//	{
//		for (i = 0; i <= row - num; i++)
//		{
//			if (arr[i][j] == arr[i+1][j] && arr[i+1][j] == arr[i+2][j] && arr[i][j] != ' ')
//			{
//				return arr[i][j];
//			}
//		}
//	}
//	for (i = 0; i <= row - num; i++)
//	{
//		for (j = 0; j <= col-num ; j++)
//		{
//			if (arr[i][j] == arr[i + 1][j+1] && arr[i + 1][j+1] == arr[i + 2][j+2] && arr[i][j] != ' ')
//			{
//				return arr[i][j];
//			}
//		}
//	}
//	for (i = 0; i <= row-num; i++)
//	{
//		for (j = num-1; j < col; j++)
//		{
//			if (arr[i][j] == arr[i+1][j - 1] && arr[i+1][j - 1] == arr[i+2][j - 2] && arr[i][j] != ' ')
//			{
//				return arr[i][j];
//			}
//		}
//	}
//}