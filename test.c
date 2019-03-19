#include"snake.h"

void test()
{
	Snake snake = { 0 };
	srand((unsigned)time(NULL));
	GameStart(&snake);
	GameRun(&snake);
	GameEnd(&snake);
}

int main()
{
	test();
	SetPos(20, 20);
	system("pause");
	return 0;
}