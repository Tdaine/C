#ifndef __COMMENT_CONVERT_H__
#define __COMMENT_CONVERT_H__
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<io.h>

enum State
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE

};


void DoCommentConvert(FILE*pfIn, FILE*pfOut);
void DoNULState(FILE*pfIn, FILE*pfOut,enum State* ps);
void DoCLState(FILE*pfIn, FILE*pfOut,enum State* ps);
void DoCppState(FILE*pfIn, FILE*pfOut,enum State* ps);



#endif