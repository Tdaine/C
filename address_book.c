#define _CRT_SECURE_NO_WARNINGS 1

#include"address_book.h"

//void save(padd ph)
//{
//	FILE *fp;
//	if ((fp = fopen("address.txt", "w")) == NULL)
//	{
//		perror("write file:");
//		fclose(fp);
//		exit(EXIT_FAILURE);
//	}
//	address *cur = ph;
//	while (cur != NULL)
//	{
//		if (fprintf(fp,"%s,%s,%s,%s\n", cur->name,cur->cell_phone,cur->phone,cur->relation) != 1)
//			printf("file write error\n");
//		cur = cur->next;
//	}
//	fclose(fp);
//}
//
//void load(padd *ph)
//{
//	FILE *fp = fopen("address.txt", "r");
//	if (fp == NULL)
//	{
//		return;
//	}
//	while (!feof(fp))
//	{
//		address *cur = malloc(sizeof(address));
//		fscanf(fp, "%s,%s,%s,%s\n", cur->name, cur->cell_phone, cur->phone, cur->relation);
//		cur->next = NULL;
//		cur->next = *ph;
//		*ph = cur;
//	}
//	fclose(fp);
//}


void save(padd ph)
{
	FILE *fp;
	if ((fp = fopen("address.txt", "w")) == NULL)
	{
		perror("write file:");
		fclose(fp);
		exit(EXIT_FAILURE);
	}
	address *cur = ph;
	while (cur != NULL)
	{
		if (fwrite(cur, sizeof(address), 1, fp) != 1)
			printf("file write error\n");
		cur = cur->next;
	}
	fclose(fp);
}

void load(padd *ph)
{
	FILE *fp = fopen("address.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	while (1)
	{
		address *cur = malloc(sizeof(address));
		if (fread(cur, sizeof(address), 1, fp) != 1)
			break;
		cur->next = NULL;
		cur->next = *ph;
		*ph = cur;
	}
	fclose(fp);
}

void insert(padd *ph)
{
	padd p = malloc(sizeof(address));
	printf("name:");
	scanf("%s", p->name);
	printf("cell_phone:");
	scanf("%s", p->cell_phone);
	printf("phone:");
	scanf("%s", p->phone);
	printf("relation:");
	scanf("%s", p->relation);
	p->next = NULL;

	if (*ph == NULL)
		*ph = p;
	else {
		address *cur = *ph;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = p;
	}
}

void show(padd ph)
{
	if (ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	while (ph != NULL)
	{
		printf("%s  %s   %s   %s\n", ph->name, ph->cell_phone, ph->phone, ph->relation);
		ph = ph->next;
	}
}

void earse(padd *ph)
{
	if (*ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	char name[10];
	printf("请输入想要删除的人:");
	scanf("%s", name);
	address *pre = NULL;
	address *cur = *ph;
	while (cur != NULL)
	{
		if (strcmp(cur->name, name) == 0)
			break;
		pre = cur;
		cur = cur->next;
	}
	if (pre == NULL) {//第一个节点
		*ph = cur->next;
		free(cur);
		printf("删除成功\n");
	}
	else {//不是第一个节点
		if (cur != NULL)//防止没有找到
		{
			pre->next = cur->next;
			free(cur);
			printf("删除成功\n");
		}
		else
			printf("没有这个人\n");
	}
}

void find(padd ph)
{
	if (ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	printf("姓名:");
	char name[10];
	int flag = 0;
	scanf("%s", name);
	address *cur = ph;
	while (cur != NULL)
	{
		if (strcmp(cur->name, name) == 0) {
			printf("%s  %s  %s  %s", cur->name, cur->cell_phone, cur->phone, cur->relation);
			flag = 1;
		}
		cur = cur->next;
	}
	if (flag == 0) {
		printf("查无此人\n");
	}
}

void change(padd ph)
{
	if (ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	int flag = 0;
	printf("请输入要更改的人名：");
	char name[20];
	scanf("%s", name);
	address *cur = ph;
	while (cur != NULL)
	{
		if (strcmp(cur->name, name) == 0)
		{
			printf("%s  %s  %s  %s", cur->name, cur->cell_phone, cur->phone, cur->relation);
			printf("请输入更改后的信息：\n");
			printf("name:");
			scanf("%s", cur->name);
			printf("cell_phone:");
			scanf("%s", cur->cell_phone);
			printf("phone:");
			scanf("%s", cur->phone);
			printf("relation:");
			scanf("%s", cur->relation);
			flag = 1;
		}
		cur = cur->next;
	}
	if (flag == 0)
		printf("没有这个人,请确认信息后更改\n");
}

void empty(padd *ph)
{
	if (*ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	address *pre = NULL;
	address *cur = *ph;
	while (cur != NULL)
	{
		pre = cur;
		cur = cur->next;
		free(pre);
	}
	*ph = NULL;
}

void sort_name(padd ph)
{
	if (ph == NULL)
	{
		printf("通讯录为空\n");
		return;
	}
	//address *pp = NULL;
	//address *pre = NULL;
	address *cur = ph;
	while (cur->next != NULL)
	{
		if (strcmp(cur->name, cur->next->name) > 0)
		{
			char tmp[20];
			strcpy(tmp, cur->next->name);//姓名拷贝
			strcpy(cur->next->name, cur->name);
			strcpy(cur->name, tmp);
			strcpy(tmp, cur->next->cell_phone);//手机号
			strcpy(cur->next->cell_phone, cur->cell_phone);
			strcpy(cur->cell_phone, tmp);
			strcpy(tmp, cur->next->phone);//座机
			strcpy(cur->next->phone, cur->phone);
			strcpy(cur->phone, tmp);
			strcpy(tmp, cur->next->relation);//关系
			strcpy(cur->next->relation, cur->relation);
			strcpy(cur->relation, tmp);
		}
		cur = cur->next;
	}
	printf("排序成功\n");
}