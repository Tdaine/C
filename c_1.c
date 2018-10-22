//打印100~200 之间的素数
//#include<stdio.h>
//int main()
//{
//	int i = 100;
//	int j,n;
//	printf("100-200之间的素数是：\n");
//	for (i = 100; i <= 200; i++)
//	{
//		for (j = 2; j <= i / 2; j++)
//		{
//			if (i%j == 0)
//				break;
//		}
//		if(j > i / 2)
//		printf("%5d", i);
//	}
//	printf("\n");
//	getchar();
//	return 0;
//}
//输出乘法口诀表
//#include<stdio.h>
//int main()
//{
//	int i, j;
//	for (i = 1; i <= 9; i++)
//		for (j = 1; j <= 9; j++)
//		{
//			printf("%2d*%d=%2d", j, i, i*j);
//			if (i == j)
//			{
//				printf("\n");
//				break;
//			}
//
//		}
//	getchar();
//	return 0;
//}
//判断1000年---2000年之间的闰年
#include<stdio.h>
int main()
{
	int year;
	printf("1000年---2000年之间的闰年为:\n");
	for (year = 1000; year <= 2000; year++)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			printf("%10d",year);
	}
	getchar();
	return 0;
}