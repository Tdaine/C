#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include<stdlib.h>

float averageTime;
float numRevolveTime;
int numTime;

typedef struct PCB
{
	char _name;
	int _arriveTime;
	int _serveTime;
	int _beginTime;
	int _finishTime;
	int _revolveTime;
	float _valueRevolveTime;
	int _priority;
	int flage;
	struct PCB* next;
}PCB, *pPCB;



void print(PCB* head);
void InitList(pPCB* head);
void FifoInsertList(pPCB* head, char n, int arriveTime, int serveTime);
//void FifoDelList(pPCB* head);
void FIFOServe();
void TimeRevolve(int time);
void RunningTime(pPCB* head, int time);