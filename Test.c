#include"Operation System.h"

void menu()
{
	printf("可选择方法\n");
	printf("1.FIFO\n");
	printf("2.时间片轮转\n");
	printf("3.静态优先级\n");
	printf("please choose:");
}
void test()
{
	int c;
	int time;
	menu();
	scanf_s("%d", &c);
	switch (c)
	{
	case 1:
		FIFOServe();
		break;
	case 2:
		printf("请输入时间片的单位时间：");
		scanf("%d", &time);
		TimeRevolve(time);
		break;
	case 3:
		Priority();
		break;
	default:
		printf("重新选择\n");
		test();
		break;
	}

}


int main()
{
	test();
	system("pause");
}
