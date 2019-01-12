
#include"Operation System.h"

pPCB BuyNode(char n, int arriveTime, int serveTime)
{
	PCB* NewNode = (PCB *)malloc(sizeof(PCB));
	if (NewNode == NULL)
	{
		assert("malloc:BuyNode");
		return NULL;
	}
	NewNode->next = NULL;
	NewNode->_name = n;
	NewNode->_arriveTime = arriveTime;
	NewNode->_serveTime = serveTime;
	return NewNode;
}
void InitList(pPCB* head)
{
	assert(head);
	(*head) = NULL;
}
void FifoInsertList(pPCB* head, char n, int arriveTime, int serveTime)
{
	PCB* pCur = (*head);
	PCB* pNew = NULL;
	PCB* pPre = NULL;
	if ((*head) == NULL)
	{
		(*head) = BuyNode(n, arriveTime, serveTime);
	}
	else
	{
		if (pCur->_arriveTime > arriveTime)
		{
			pNew = BuyNode(n, arriveTime, serveTime);
			pNew->next = pCur;
			(*head) = pNew;
			return;
		}
		while (pCur != NULL && arriveTime >= pCur->_arriveTime)
		{
			pPre = pCur;
			pCur = pCur->next;
		}
		pNew = BuyNode(n, arriveTime, serveTime);
		pNew->next = pCur;
		pPre->next = pNew;
	}

}

//void FifoDelList(pPCB* head)
//{
//	PCB* pDel = NULL;
//	if (*head == NULL)
//		return;
//	pDel = (*head);
//	(*head) = pDel->next;
//	free(pDel);
//}

void CreatList(pPCB* head)
{
	int num, i;
	char n;
	int arriveTime;
	int serveTime;
	InitList(head);
	printf("请输入进程个数:");
	scanf_s("%d", &num);
	printf("进程名、到达时间、服务时间\n");
	for (i = 0; i < num; i++)
	{
		scanf(" %c,%d,%d",&n, &arriveTime, &serveTime);
		FifoInsertList(head, n, arriveTime, serveTime);

	}

}

void Running(pPCB* head)
{
	PCB* pCur = *head;
	if ((*head) == NULL)
		return;
	pCur->_beginTime = pCur->_arriveTime;
	while (pCur)
	{
		
		pCur->_finishTime = pCur->_beginTime + pCur->_serveTime;
		pCur->_revolveTime = pCur->_finishTime - pCur->_arriveTime;
		pCur->_valueRevolveTime = ((float)pCur->_revolveTime / pCur->_serveTime);
		numRevolveTime += pCur->_valueRevolveTime;
		numTime += 1;
		if (pCur->next) {
			pCur->next->_beginTime = pCur->_finishTime;
			
		}
		pCur = pCur->next;
	}
}
void print(PCB* head)
{
	int n = 0;
	printf("进程名\t到达时间 | 服务时间 | 开始执行时间 | 完成时间 | 周转时间 | 带权周转时间\n");
	while (head != NULL)
	{

		printf(" %c\t  %d\t   %d\t\t %d\t\t %d\t  %d\t\t %f\t\n",
			head->_name, head->_arriveTime, head->_serveTime, head->_beginTime, head->_finishTime, head->_revolveTime, head->_valueRevolveTime);
		head = head->next;
		n++;
	}
	averageTime = (numRevolveTime / n);
	printf("*********平均带权周转时间***********\n");
	printf("\t %f\n", averageTime);
}

void FIFOServe()
{
	PCB* head;
	CreatList(&head);
	Running(&head);
	print(head);
}

void RunningTime(pPCB* head,int time)
{
	PCB *pCur = *head;
	PCB *pT = *head;
	int t = pCur->_beginTime = pCur->_arriveTime;
	int arr[10];
	int n = 0, n1 = 0;
	while (pT)
	{
		arr[n] = pT->_serveTime;
		if (pT->next)
		{
			pT->next->_beginTime = time + pT->_beginTime;
		}
		
		pT = pT->next;
		n++;
	}
	while (n)
	{
		int i = 0;
		pT = pCur;
		while (pT )
		{
			if (pT->_serveTime > 0 && pT->_arriveTime <= t)
			{
				i++;
				pT->_serveTime = pT->_serveTime - time;
				t += time;
				if (pT->_serveTime <= 0)
				{
					t = t + pT->_serveTime;
					pT->_finishTime = t;
					n--;
				}
			}
			pT = pT->next;
		}
		if (i == 0) {
			pT = pCur;
			while (pT)
			{
				if (pT->_serveTime >= 0)
				{
					t = pT->_arriveTime;
					pT->_beginTime = t;
					break;
				}
				pT = pT->next;
			}
		}
	}
	while (pCur)
	{
		pCur->_serveTime = arr[n1++];
		pCur->_revolveTime = pCur->_finishTime - pCur->_arriveTime;
		pCur->_valueRevolveTime = (float)pCur->_revolveTime / pCur->_serveTime;
		numRevolveTime += pCur->_valueRevolveTime;
		numTime += 1;
		pCur = pCur->next;
	}


}

void TimeRevolve(int time)
{
	PCB* head;
	CreatList(&head);
	RunningTime(&head,time);
	print(head);
}

void setPriority(PCB* head) {
	int p = 0;
	printf("请输入下面进程的优先级:\n");
	PCB* pCur = head;
	while (pCur) {
		printf("%c->", pCur->_name);
		scanf("%d", &pCur->_priority);
		printf("\n");
		pCur->flage = 0;
		pCur = pCur->next;
	}
}

void RunPriority(PCB* head) {
	PCB* pCur = head;
	PCB* newHead = NULL;
	int num = 0;
	int t = pCur->_arriveTime;
	int minPri;
	while (pCur)
	{
		num++;
		pCur = pCur->next;
	}
	while (num--)
	{
		pCur = head;
		int n = 0;
		while (pCur && pCur->_arriveTime <= t)
		{
			if (n == 0 && pCur->flage == 0)
			{
				minPri = pCur->_priority;
				newHead = pCur;
				n++;
			}
			if (pCur->_priority < minPri && pCur->flage == 0)
			{
				newHead = pCur;
				minPri = newHead->_priority;
			}
			pCur = pCur->next;
		}
		newHead->_beginTime = t;
		newHead->_finishTime = newHead->_beginTime + newHead->_serveTime;
		newHead->_revolveTime = newHead->_finishTime - newHead->_arriveTime;
		newHead->_valueRevolveTime = ((float)newHead->_revolveTime / newHead->_serveTime);
		newHead->flage = 1;
		numRevolveTime += newHead->_valueRevolveTime;
		numTime++;
		t = newHead->_finishTime;
	}
}

void Priority() {
	PCB* head;
	int n = 0;
	CreatList(&head);
	setPriority(head);
	RunPriority(head);
	printf("进程名\t到达时间 | 服务时间 |   优先数   | 开始执行时间 | 完成时间 | 周转时间 | 带权周转时间\n");
	while (head != NULL)
	{

		printf(" %c\t  %d\t     %d\t\t %d\t\t%d\t     %d\t       %d\t  %f\t\n",
			head->_name, head->_arriveTime, head->_serveTime, head->_priority,head->_beginTime, head->_finishTime, head->_revolveTime, head->_valueRevolveTime);
		head = head->next;
		n++;
	}
	averageTime = (numRevolveTime / n);
	printf("*********平均带权周转时间***********\n");
	printf("\t %f\n", averageTime);
}