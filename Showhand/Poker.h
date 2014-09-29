#pragma once

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <Windows.h>
#include <memory.h>


typedef struct POKER		//�˿˽ṹ��
{
	int porkNum;			//�˿˵�ֵ�����ڱȽ�
	char porkPip[3];		//�˿˵�����
	char porkSuit;			//�˿˵Ļ�ɫ
	int porkSuitNum;		//�˿˻�ɫ��С ����Ϊ4������Ϊ3���ݻ�Ϊ2����ƬΪ1
}Poker;

void WashPoker(int **pokerPack);		//ϴ��
void Deal(int *pokerPack, Poker *pok, int step);	//����
void SortPoker(Poker **poker);			//����