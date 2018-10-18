#ifndef address_book_H
#define adderss_book_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<windows.h>

typedef struct address {
	char name[10];//姓名
	char cell_phone[12];//手机号
	char phone[12];//座机号
	char relation[20];//关系
	struct address *next;
}address,*padd;

void insert(padd *ph);
void show(padd ph);
void earse(padd *ph);
void find(padd ph);
void change(padd ph);
void empty(padd *ph);
void sort_name(padd ph);

#endif