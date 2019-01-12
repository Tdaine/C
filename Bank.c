#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>

#define MAX 10
int n = 0;
int An = 0;
int zero = 0;
int flage = 1;
int flage_safe = 0;
int flage_i[MAX] = { 0 };
int count[MAX];
int need_cp[MAX][MAX];
int all_cp[MAX][MAX];
int request[MAX];//预分配
char name[MAX][MAX];//进程名
char safe[MAX][MAX];//安全序列
int sequence = 0;//安全序列号
int max_re[MAX];//各进程总数
int max[MAX][MAX];//最大需要
int all[MAX][MAX];//已分配
int need[MAX][MAX];//需要
int ava[MAX] = {0};//可分配
int ava_cp[MAX] = { 0 };
int fava[MAX];
int fneed[MAX];
int fall[MAX];

void Bank();
void print();
void Run();
void Request();
void menu();

void Bank()
{
	printf("请输入进程数和资源类型个数：");
	scanf("%d,%d",&n,&An);
	
	for (int i = 0; i < n; i++) 
	{
		printf("\n进程:\n");
		scanf("%s", &name[i]);
		for (int j = 0; j < An; j++)
		{
			printf("请输入当前进程对第%d种资源的Max、Allocation:", j+1);
			scanf("%d,%d", &max[i][j], &all[i][j]);
			need[i][j] = max[i][j] - all[i][j];
		}
	}
	for (int j = 0; j < An; j++)
	{
		printf("请输入第%d个资源的最大数\n", j + 1);
		scanf("%d",&max_re[j]);
	}
	for (int j = 0; j < An; j++)
	{
		int resource = 0;
		for (int i = 0; i < n; i++)
		{
			resource += all[i][j];
		}
		ava[j] = max_re[j] - resource;
		
	}
	print();
	printf("\n");
}

void Request()
{
	zero = 0;
	flage = 1;
	flage_safe = 0;
	while (flage == 1)
	{
		printf("请输入要预分配的进程：");
		scanf("%s", &request);
		for (int i = 0; i < n; i++)
		{
			if (!strcmp(name[i], request))
			{
				flage++;
				printf("输入要预分配的资源：\n");
				for (int j = 0; j < An; j++)
				{
					printf("第%d个资源：", j);
					scanf("%d", &count[j]);
				}
				for (int j = 0; j < An; j++)
				{
					if (count[j] > ava[j] || count[j] > need[i][j])
					{
						printf("不能分配\n");
						return;
					}
					else
					{
						fava[j] = ava[j] - count[j];
						fneed[j] = need[i][j] - count[j];
						fall[j] = all[i][j] + count[j];
						if (fneed[j] == 0)
							zero++;
					}
				}

				if (zero == An)
				{
					flage_safe = 1;
					printf("Avaliable：");
					for (int j = 0; j < An; j++)
					{
						ava[j] = ava[j] + all[i][j];
						ava_cp[j] = ava[j];
						
						
						//printf("%s ", safe[sequence]);
						
						printf("%d  ", ava[j]);
					}
					flage_i[i] = 1;
					strcpy(safe[sequence], name[i]);
					sequence++;
					printf("\n");
				}
				else {
					for (int j = 0; j < An; j++)
					{
						ava[j] = fava[j];
						ava_cp[j] = ava[j];
					}
				}
				for (int j = 0; j < An; j++)
				{
					need_cp[i][j] = need[i][j];
					all_cp[i][j] = all[i][j];
					need[i][j] = fneed[j];
					all[i][j] = fall[j];
				}

				break;
			}
		}
		if (flage == 1)
		{
			printf("没有这个进程\n");
		}
	}
	printf("预分配后的资源表：\n");
	print();
	Run();
}

void Run()
{
	int fase = 0;
	int in = 0;
	int in_fase = 0;
	while (sequence != n)
	{
		for (int i = 0; i < n; i++)
		{
			if (flage_i[i] == 0)
			{
				in = 0;
				for (int j = 0; j < An; j++)
				{
					if (need[i][j] <= ava[j])
					{
						in++;
						if (in == An)
						{
							fase = 0;
							printf("Avaliable：");
							for (int num = 0; num < An; num++)
							{
								ava[num] = ava[num] + all[i][num];
								printf("%d ", ava[num]);
							}
							
							strcpy(safe[sequence], name[i]);
							printf("进程：%s\n",safe[sequence] );
							
							sequence++;
							flage_i[i] = 1;
							in_fase = An;
						}
					}
					else
						break;

				}
				if (flage_i[i] != 1)
					fase++;
			}	
		}
		if (fase > n - sequence)
		{
			printf("不安全\n");
			for (int j = 0; j < An; j++)
			{
				ava[j] = ava_cp[j] + count[j] ;
				
				
					for (int i = 0; i < n; i++)
					{
						if (!strcmp(name[i], request))
						{
							if (flage_safe == 1)
							{
								ava[j] = ava[j] - all[i][j];
							}
							need[i][j] = need_cp[i][j];
							all[i][j] = all_cp[i][j];
						}
						
					}
				ava_cp[j] = ava[j];
			}
			return;
		}
	}
	printf("安全序列为：");
	for (int i = 0; i < n; i++)
	{
		if (i != n - 1)
		{
			printf("%s->", safe[i]);
		}
		else
			printf("%s\n", safe[i]);
	}
	printf("Available:");
	for (int j = 0; j < An; j++)
	{
		printf("%d  ", ava[j]);
	}
	printf("\n");
}

void print()
{
	printf("----------------------------------------------------\n");
	printf("进程\t Max\t Allocation\t Need\t Available\n");
	for (int i = 0; i < n; i++)
	{
		printf("%s\t", name[i]);
		for (int j = 0; j < An; j++)
		{
			printf("%d ", max[i][j]);
		}
		printf("     ");
		for (int j = 0; j < An; j++)
		{
			printf("%d ", all[i][j]);
		}
		printf("    \t");
		for (int j = 0; j < An; j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("    ");
		if (i == 0)
		{
			for (int j = 0; j < An; j++)
			{
				printf("%d ", ava[j]);
			}
		}
		printf("\n");
	}
	printf("----------------------------------------------------\n");
}


void menu()
{
	int ch = 1;
	Bank();
	for (int j = 0; j < An; j++)
	{
		ava_cp[j] = ava[j];
	}
	while (ch) {
		printf("*********************\n");
		printf(" 1.检查当前安全性\n");
		printf(" 2.预分配检查安全性\n");
		printf(" 0.退出\n");
		printf("*********************\n");
		printf("请选择：");
		scanf("%d", &ch);
		sequence = 0;
		for (int i = 0; i < n; i++)
		{
			int flage_need = 0;
			for (int j = 0; j < An; j++)
			{
				if(need[i][j] == 0)
					flage_need++;
			}
			if (flage_need == An)
			{
				flage_i[i] = 1;
				sequence++;
			}
			else
				flage_i[i] = 0;
		}
		
		switch (ch)
		{
		case 1:
		{
			Run();
			for (int j = 0; j < An; j++)
			{
				ava[j] = ava_cp[j];
			}
			print();
			break;
		}
			
		case 2:
		{
			Request();
			for (int j = 0; j < An; j++)
			{
				ava[j] = ava_cp[j];
			}
			print();
			break;
		}
			
		default:
			break;
		}
	}
}

int main()
{
	menu();
	system("pause");
	return 0;
}