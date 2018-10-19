#ifndef __GAME_H__
#define __GAME_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ROW  12
#define  COL  12
#define MINE 10//雷数
void Init_board(char arr[ROW][COL], char arr2[ROW][COL], int row, int col);//填充棋盘
void set_mine(char arr[ROW][COL]);//布雷
void print_board(char arr[ROW][COL]);//打印棋盘
int jud_mine(char arr[ROW][COL] ,char arr2[ROW][COL]);//扫雷
void re_mine(char arr[ROW][COL],int x, int y);//重新布雷
int get_mine(char arr[ROW][COL], char arr2[ROW][COL],int x, int y);//判断下，y周围雷数,并扩展
//void expand(char arr[ROW][COL], int x, int y);//展开
int Win(char arr[ROW][COL]);//判断赢函数
#endif // __GAME_H__