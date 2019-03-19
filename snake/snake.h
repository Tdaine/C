#pragma once
#include<Windows.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
             
#define WALL "■"
#define Food "□"
#define SIGN "＠"
#define INIT_X 30
#define INIT_Y 10

typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode,*pSnakeNode;

enum Dirction { UP = 1, DOWN, LEFT, RIGHT};
enum GameStatus { OK, NORMAL_END, KILL_BY_WALL,  KILL_BY_SELF};

typedef struct Snake
{
	pSnakeNode _pSnake;//维护蛇身
	pSnakeNode _pFood;//食物的位置
	int ToTalScore;//总分数
	int _AddScore;//每次增加分数
	int _SleepTime;//休眠时间
	enum Dirction _Dir;//方向
	enum GameStatus _Status;//游戏状态
}Snake,*pSnake;


void  GameStart(pSnake snake);
void SetPos(int x, int y);
void WelcomeToGame();
void CreateMap();
void InitSnake(pSnake snake);
void CreateFood(pSnake snake);



void GameRun(pSnake ps);
void EatFood(pSnakeNode pn, pSnake ps);
void NoFood(pSnakeNode pn, pSnake ps);
void SnakeMove(pSnake ps);
void PrintfHelpInfo(pSnake ps);
void KillBySelf(pSnake ps);
void KillByWall(pSnake ps);


void GameEnd(pSnake ps);