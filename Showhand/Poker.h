#pragma once

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>


typedef struct POKER		//扑克结构体
{
	int porkNum;			//扑克的值，用于比较
	char porkPip[3];		//扑克的牌面
	char porkSuit;			//扑克的花色
	int porkSuitNum;		//扑克花色大小 黑桃为4，红桃为3，草花为2，方片为1
}Poker;

void WashPoker(int **pokerPack);		//洗牌
void Deal(int *pokerPack, Poker *pok, int step);	//发牌
void SortPoker(Poker **poker);			//排序