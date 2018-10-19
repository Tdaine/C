#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void menu()
{
	printf("**********************************\n");
	printf("************** 1. play ***********\n");
	printf("************** 0. exit ***********\n");
	printf("**********************************\n");
}
void game()
{
	char mine[ROW][COL] = { 0 };
	char show[ROW][COL] = { 0 };
	Init_board(mine,show, ROW, COL);
	set_mine(mine);
	print_board(show);
	//print_board(mine);

	jud_mine(mine,show);
	
}
void test()
{
	int input = 0;
	do {
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			srand((unsigned)time(NULL));
			game();
			break;
		case 0:
			printf("退出成功");
			break;
		default :
			printf("请重新输入\n");
			break;
		}
	} while (input);


}
int main()
{
	test();
	system("pause");
	return 0;
}