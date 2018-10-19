#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void Init_board(char arr[ROW][COL], char arr2[ROW][COL], int row, int col)//填充棋盘
{
	memset(arr,'0',row*col * sizeof(arr[0][0]));
	memset(arr2, '*', row*col * sizeof(arr[0][0]));
}
void set_mine(char arr[ROW][COL])//布雷
{
	int x = 0;
	int y = 0;
	int count = MINE;
	while (count)
	{
		x = rand() % (ROW-2) + 1;
		y = rand() % (COL-2) + 1;
		if (arr[x][y] == '0')
		{
			arr[x][y] = '1';
			count--;
		}
	}
}
void print_board(char arr[ROW][COL])//打印棋盘
{
	int i = 0;
	int j = 0;
	printf("   ");
	for (i = 1; i < COL-1; i++)
		printf("%4d", i);
	printf("\n");
	for (i = 1; i < COL-1; i++)
		printf("----");
	printf("----");
	printf("\n");
	for (i = 1; i < ROW-1; i++)
	{
		printf("%-2d|", i);
		for (j = 1; j < COL-1; j++)
			printf("%4c", arr[i][j]);
		printf("\n");
	}
}
void re_mine(char arr[ROW][COL],int x,int y)//重新布雷
{
	arr[x][y] = '0';
	int x1;
	int y1;
	while (1)
	{
		x1 = (rand() % (ROW-2) + 1);
		y1 = (rand() % (COL-2) + 1);
		if (arr[x1][y1] == '0' && (x1 != x || y1 != y))
		{
			arr[x1][y1] = '1';
			break;
		}
	}
}
int get_mine(char arr[ROW][COL],char arr2[ROW][COL], int x, int y)//判断下，y周围雷数,并扩展
{

		int ret = 0;
		if ((x >= 1) && (y >= 1) && (x < ROW - 1) && (y < COL - 1) && arr2[x][y] == '*')
		{
			for (int i = -1; i <= 1; i++)
				for (int j = -1; j <= 1; j++)
				{
					if (arr[x + i][y + j] == '1')
						ret++;
				}
			if (ret == 0)
			{
				arr2[x][y] = ' ';
				for (int i1 = -1; i1 <= 1; i1++)
					for (int j1 = -1; j1 <= 1; j1++)
						if (i1 != 0 || j1 != 0)
						{
							get_mine(arr, arr2, x + i1, y + j1);
						}
			}
			else
			{
				arr2[x][y] = ret + 48;
				return 0;
			}
		}
		return 0;

}
//void expand(char arr[ROW][COL], int x, int y)//展开
//{
//	for (int i = -1; i <= 1; i++)
//		for (int j = -1; j <= 1; j++)
//		{
//			arr[x + i][y + j] = '+';
//				
//		}
//}
int Win(char arr[ROW][COL])//判断赢函数
{
	int num = 0;
	for(int i=1;i<ROW-1;i++)
		for (int j = 1; j < COL - 1; j++)
		{
			if (arr[i][j] == '*')
				num++;
		}
	return num;
}
int jud_mine(char arr[ROW][COL], char arr2[ROW][COL])//扫雷
{
	int x;
	int y; 
	//int count = 0;
	int flag = 0;
	while (Win(arr2)>10)
	{
		printf("请输入坐标：");
		scanf("%d %d", &x, &y);
		if ((x >= 1) && (y >= 1) && (x < ROW-1) && (y < COL-1))
		{
			 flag++;
			if (arr[x][y] == '1'&&flag == 1)
			{
				re_mine(arr, x, y);
				get_mine(arr,arr2, x, y);
				print_board(arr2);

			}
			else if (arr[x][y] == '1')
			{
				printf("你被炸死了\n");
				print_board(arr);
				return 0;
			}
			else
			{
				get_mine(arr,arr2, x, y);
				print_board(arr2);

			}
		}
		else printf("坐标有误，请重新输入：");
	}
	printf("YOU WIN\n");
	print_board(arr);
	return 0;
}