#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _GAME_H_
#define _GAME_H_
#endif
#define ROW 3
#define COL 3
#define num 3
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
void Init_board(char arr[ROW][COL],int  row,int  col);//初始化棋盘
void DisplayBoard(char arr[ROW][COL], int  row, int  col);//打印
void PlayerMove(char arr[ROW][COL], int  row, int  col);//玩家走
void ComputerMove(char arr[ROW][COL], int  row, int  col);//电脑走
char Iswin(char arr[ROW][COL], int  row, int  col);//判断输赢
int IFull(char arr[ROW][COL], int  row, int  col);//判断满盘