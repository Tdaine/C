#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void menum()
{
	printf("***********************\n");
	printf("*****1. countinue******\n");
	printf("*****0 .   end   ******\n");
	printf("***********************\n");
}
void game()
{
	char board[ROW][COL] = { 0 };
	Init_board(board, ROW, COL);//初始化棋盘
	DisplayBoard(board, ROW, COL);//打印
	while (1)
	{
		PlayerMove(board, ROW, COL);//玩家走
		DisplayBoard(board, ROW, COL);//打印
		if (Iswin(board, ROW, COL) == 'X')
		{
			printf("玩家赢\n");
			break;
		}
		if (IFull(board, ROW, COL) == 1)
		{
			printf("平局\n");
			break;
		}
		ComputerMove(board, ROW, COL);//电脑走
		DisplayBoard(board, ROW, COL);//打印
		if (Iswin(board, ROW, COL) == 'Y')
		{
			printf("电脑赢\n");
			break;
		}
		if (IFull(board,ROW,COL) == 1)
		{
			printf("平局\n");
			break;
		}
	}

}
void test()
{
	int i = 1;
	do
	{
		srand((unsigned)time(NULL));
		menum();
		printf("Please enter your choice >");
		scanf("%d",& i);
		switch (i)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入有误，请重新输入\n");
			break;
		}
	} while (i);
}
int main()
{
	test();
	system("pause");
	return 0;
}