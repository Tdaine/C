#include"snake.h"

void SetPos(int x, int y)
{
	COORD pos = { 0 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取设备
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void Sign()
{
	SetPos(88, 27);
	printf(SIGN);
	printf("阿巴卡");
}

void WelcomeToGame()
{
	//窗口大小
	system("mode con cols=100 lines=30");
	SetPos(39, 14);
	printf("欢迎来到贪吃蛇游戏");
	Sign();
	SetPos(39, 25);
	system("pause");
	system("cls");//清屏
	SetPos(25, 14);
	printf("用↑，↓，←，→来控制蛇的移动，F1为加速，F2为减速");
	SetPos(35, 15);
	printf("提示：加速获得的分数更高");
	Sign();
	SetPos(39, 25);
	system("pause");
	system("cls");
	
}

void CreateMap()
{
	int i = 0;
	//上
	for (i = 0; i <= 58; i+=2)
	{
		SetPos(i, 0);
		printf(WALL);
	}
	//下
	for (i = 0; i <= 58; i += 2)
	{
		SetPos(i, 29);
		printf(WALL);
	}
	//左
	for (i = 1; i <= 28; i++)
	{
		SetPos(0, i);
		printf(WALL);
	}
	//右
	for (i = 1; i <= 28; i++)
	{
		SetPos(58, i);
		printf(WALL);
	}
}

pSnakeNode BuyNode()
{
	pSnakeNode NewNode = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (NewNode == NULL)
	{
		perror("BuyNode::malloc( )");
		exit(EXIT_FAILURE);
	}
	NewNode->x = 0;
	NewNode->y = 0;
	NewNode->next = NULL;
	return NewNode;
}

void InitSnake(pSnake snake)
{
	int i = 0;
	pSnakeNode Cur = NULL;
	pSnakeNode first = BuyNode();
	first->x = INIT_X;
	first->y = INIT_Y;
	for (i = 0; i < 4; i++)
	{
		Cur = BuyNode();
		Cur->x = first->x - 2;
		Cur->y = first->y;
		Cur->next = first;
		first = Cur;
	}
	while (Cur)
	{
		SetPos(Cur->x, Cur->y);
		printf(Food);
		Cur = Cur->next;
	}
	snake->_pSnake = first;
	Sign();
}

void CreateFood(pSnake snake)
{
	
	pSnakeNode pFood = NULL;
	pFood = BuyNode();
	pSnakeNode Cur = snake->_pSnake;
	pFood->y = rand() % 28 + 1;
	do 
	{
		pFood->x = rand() % 55 + 2;
	} while (pFood->x % 2 != 0);
	while (Cur)
	{
		if (Cur->x == pFood->x && Cur->y == pFood->y)
		{
			CreateFood(snake);
			return;
		}
		Cur = Cur->next;
	}
	snake->_pFood = pFood;
	SetPos(pFood->x, pFood->y);
	printf(Food);
}



void  GameStart(pSnake snake)
{
	//打印界面
	WelcomeToGame();
	
	//创建地图
	CreateMap();

	//初始化蛇
	InitSnake(snake);

	//初始化食物
	CreateFood(snake);

	snake->ToTalScore = 0;
	snake->_AddScore = 10;
	snake->_Dir = LEFT;
	snake->_SleepTime = 200;
	snake->_Status = OK;

}

void pause()
{
	while (1)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_SPACE))
			break;
	}
}

int NextHasFood(pSnakeNode pn, pSnakeNode pf)
{
	return ((pn->x == pf->x) && (pn->y == pf->y));
}

void EatFood(pSnakeNode pn,pSnake ps)
{
	pn->next = ps->_pSnake;
	ps->_pSnake = pn;
	SetPos(ps->_pSnake->x, ps->_pSnake->y);
	printf(Food);
	ps->ToTalScore += ps->_AddScore;
	CreateFood(ps);
}

void NoFood(pSnakeNode pn, pSnake ps)
{
	pSnakeNode Cur = NULL;
	pn->next = ps->_pSnake;
	ps->_pSnake = pn;
	SetPos(pn->x, pn->y);
	printf(Food);
	Cur = ps->_pSnake;
	while (Cur->next->next)
	{
		Cur = Cur->next;
		/*SetPos(Cur->x, Cur->y);
		printf(Food);*/
	}
	/*if (Cur->next->x == 0 || Cur->next->x == 58
		|| Cur->next->y == 0 || Cur->next->y == 29)
	{
		SetPos(Cur->next->x, Cur->next->y);
		printf(WALL);

	}
	else
	{*/
		SetPos(Cur->next->x, Cur->next->y);
		printf(" ");
	//}
	free(Cur->next);
	Cur->next = NULL;
}

void SnakeMove(pSnake ps)
{
	pSnakeNode pNextNode = BuyNode();
	switch (ps->_Dir)
	{
	case UP:
	{
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y - 1;
		if (NextHasFood(pNextNode, ps->_pFood))
		{
			//下一个节点是食物
			EatFood(pNextNode,ps);
		}
		else
		{
			//下一个节点不是食物
			NoFood( pNextNode, ps);
		}
	}
	break;
	case DOWN:
	{
		pNextNode->x = ps->_pSnake->x;
		pNextNode->y = ps->_pSnake->y + 1;
		if (NextHasFood(pNextNode, ps->_pFood))
		{
			//下一个节点是食物
			EatFood(pNextNode, ps);
		}
		else
		{
			//下一个节点不是食物
			NoFood(pNextNode, ps);
		}
	}break;
	case LEFT:
	{
		pNextNode->x = ps->_pSnake->x - 2;
		pNextNode->y = ps->_pSnake->y;
		if (NextHasFood(pNextNode, ps->_pFood))
		{
			//下一个节点是食物
			EatFood(pNextNode, ps);
		}
		else
		{
			//下一个节点不是食物
			NoFood(pNextNode, ps);
		}
	}break;
	case RIGHT:
	{
		pNextNode->x = ps->_pSnake->x + 2;
		pNextNode->y = ps->_pSnake->y;
		if (NextHasFood(pNextNode, ps->_pFood))
		{
			//下一个节点是食物
			EatFood(pNextNode, ps);
		}
		else
		{
			//下一个节点不是食物
			NoFood(pNextNode, ps);
		}
	}
	break;
	}
}

void PrintfHelpInfo(pSnake ps)
{
	SetPos(70, 9);
	printf("总分：%d  ", ps->ToTalScore);
	SetPos(70, 10);
	printf("单次吃食物得分：%d  ", ps->_AddScore);
	SetPos(70, 15);
	printf("用↑，↓，←，→来控制蛇的移动");
	SetPos(70, 16);
	printf("F1为加速，F2为减速");
	SetPos(70, 17);
	printf("按空格暂停");
	SetPos(70, 18);
	printf("按Esc退出");
	
}

void KillBySelf(pSnake ps)
{
	pSnakeNode Cur = NULL;
	Cur = ps->_pSnake->next;
	while (Cur)
	{
		if (ps->_pSnake->x == Cur->x && ps->_pSnake->y == Cur->y)
		{
			ps->_Status = KILL_BY_SELF;
			break;
		}
		Cur = Cur->next;
	}

}

void KillByWall(pSnake ps)
{
	if (ps->_pSnake->x == 0 || ps->_pSnake->x == 58//蛇撞墙会死
		|| ps->_pSnake->y == 0 || ps->_pSnake->y == 29)
	{
		ps->_Status = KILL_BY_WALL;
		
	}
//	pSnakeNode pn = BuyNode();
//	if (ps->_pSnake->x == 0)//撞左墙
//	{
//		
//		pn->x = ps->_pSnake->x + 56;
//		pn->y = ps->_pSnake->y;
//		if (NextHasFood(pn, ps->_pFood))
//		{
//			EatFood(pn, ps);
//		}
//		else
//		{
//			NoFood(pn, ps);
//		}
//	}
//
//	if (ps->_pSnake->x == 58)//撞右墙
//	{
//
//		pn->x = ps->_pSnake->x - 56;
//		pn->y = ps->_pSnake->y;
//		if (NextHasFood(pn, ps->_pFood))
//		{
//			EatFood(pn, ps);
//		}
//		else
//		{
//			NoFood(pn, ps);
//		}
//	}
//
//	if (ps->_pSnake->y == 0)//撞上墙
//	{
//
//		pn->x = ps->_pSnake->x;
//		pn->y = ps->_pSnake->y + 28;
//		if (NextHasFood(pn, ps->_pFood))
//		{
//			EatFood(pn, ps);
//		}
//		else
//		{
//			NoFood(pn, ps);
//		}
//	}
//
//	if (ps->_pSnake->y == 29)//撞下墙
//	{
//
//		pn->x = ps->_pSnake->x;
//		pn->y = ps->_pSnake->y - 28;
//		if (NextHasFood(pn, ps->_pFood))
//		{
//			EatFood(pn, ps);
//		}
//		else
//		{
//			NoFood(pn, ps);
//		}
//	}
//
}

void GameRun(pSnake ps)
{
	do
	{
		PrintfHelpInfo(ps);
		//确定方向
		if (GetAsyncKeyState(VK_UP) && ps->_Dir != DOWN)
			ps->_Dir = UP;
		else if (GetAsyncKeyState(VK_DOWN) && ps->_Dir != UP)
			ps->_Dir = DOWN;
		else if (GetAsyncKeyState(VK_LEFT) && ps->_Dir != RIGHT)
			ps->_Dir = LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) && ps->_Dir != LEFT)
			ps->_Dir = RIGHT;
		else if (GetAsyncKeyState(VK_SPACE))//暂停
			pause();
		else if (GetAsyncKeyState(VK_ESCAPE))//退出
		{
			ps->_Status = NORMAL_END;
			break;
		}
		else if (GetAsyncKeyState(VK_F1)) //加速
		{
			if (ps->_SleepTime >= 100)
			{
				ps->_AddScore += 2;
				ps->_SleepTime -= 20;
			}
		}
		else if (GetAsyncKeyState(VK_F2))//减速
		{
			if (ps->_SleepTime <= 300)
			{
				if (ps->_AddScore > 2)
				{
					ps->_AddScore -= 2;
				}

				ps->_SleepTime += 20;
			}
		}
		Sleep(ps->_SleepTime);
		SnakeMove(ps);
		//蛇移动
		KillBySelf(ps);
		KillByWall(ps);
	} while (ps->_Status == OK);
}


void GameEnd(pSnake ps)
{
	switch (ps->_Status)
	{
	case KILL_BY_SELF:
	{
		SetPos(24, 15);
		printf("撞身体");
		SetPos(22, 16);
		printf("GAME OVER!!!");
	}
	break;
	case KILL_BY_WALL://撞墙会死
	{
		SetPos(24, 15);
		printf("撞墙");
		SetPos(22, 16);
		printf("GAME OVER!!!");
	}
	break;
	}
	pSnakeNode Cur = ps->_pSnake;
	pSnakeNode Del = NULL;
	while (Cur)
	{
		Del = Cur;
		Cur = Cur->next;
		free(Del);
	}
	Del = NULL;
	free(ps->_pFood);
	ps->_pFood = NULL;
}