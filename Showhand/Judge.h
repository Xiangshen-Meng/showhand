#pragma once

#include <stdio.h>
#include "Poker.h"
#include "Main.h"

typedef enum 		//���������
{
	TongHuaShun = 9,		//ͬ��˳:9
	HuLu = 8,				//��֦:8 
	TieZhi = 7,				//��«:7 
	TongHua = 6,			//ͬ��:6 
	ShunZi = 5,				//˳��:5 
	SanTiao = 4,			//����:4 
	LiangDui = 3,			//����:3 
	DuiZi = 2,				//����:2 
	SanPai = 1				//ɢ��:1
}PokerStyle;

typedef struct POKERTYPE			//�ж�����Ľṹ��
{
	PokerStyle cardType;			//��������
	int maxCardNum;					//��Ӧ�ܸ�������������ֵ(���ԣ����⣬���Ե����ֵ��4λ������Ϊ����Ҫ�ȿ�2�����ӵĴ�С���껨ɫ)
	int maxCardSuitNum;				//��Ӧ�ܸ������������ɫ(Ҳ���ǿ��Ծ����ƴ�С�Ļ�ɫ)
}PokerType;

void Judge(Poker **poker, PokerType *pokerType);				//�ж�����
bool JudgeWin(PokerType *pokerType1, PokerType *pokerType2);	//�ж��ķ�ʤ

bool IsTongHuaShun(Poker **poker, PokerType *pokerType);		//ͬ��˳
bool IsTongHua(Poker **poker, PokerType *pokerType);			//ͬ��
bool IsTieZhi(Poker **poker, PokerType *pokerType);				//��֦
bool IsHuLu(Poker **poker, PokerType *pokerType);				//��«
bool IsShunZi(Poker **poker, PokerType *pokerType);				//˳��
bool IsSanTiao(Poker **poker, PokerType *pokerType);			//����
bool IsLiangDui(Poker **poker, PokerType *pokerType);			//����
bool IsDuiZi(Poker **poker, PokerType *pokerType);				//����
bool IsSanPai(Poker **poker, PokerType *pokerType);				//ɢ��