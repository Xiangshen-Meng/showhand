#pragma once

#include <stdio.h>
#include "Poker.h"
#include "Main.h"

typedef enum 		//牌面的类型
{
	TongHuaShun = 9,		//同花顺:9
	HuLu = 8,				//铁枝:8 
	TieZhi = 7,				//葫芦:7 
	TongHua = 6,			//同花:6 
	ShunZi = 5,				//顺子:5 
	SanTiao = 4,			//三条:4 
	LiangDui = 3,			//二对:3 
	DuiZi = 2,				//对子:2 
	SanPai = 1				//散牌:1
}PokerStyle;

typedef struct POKERTYPE			//判断牌面的结构体
{
	PokerStyle cardType;			//牌面类型
	int maxCardNum;					//对应能各个类型中最大的值(两对，特殊，两对的这个值是4位数，因为两对要先看2个对子的大小后年花色)
	int maxCardSuitNum;				//对应能各个类型中最大花色(也就是可以决定牌大小的花色)
}PokerType;

void Judge(Poker **poker, PokerType *pokerType);				//判断类型
bool JudgeWin(PokerType *pokerType1, PokerType *pokerType2);	//判断哪方胜

bool IsTongHuaShun(Poker **poker, PokerType *pokerType);		//同花顺
bool IsTongHua(Poker **poker, PokerType *pokerType);			//同花
bool IsTieZhi(Poker **poker, PokerType *pokerType);				//铁枝
bool IsHuLu(Poker **poker, PokerType *pokerType);				//葫芦
bool IsShunZi(Poker **poker, PokerType *pokerType);				//顺子
bool IsSanTiao(Poker **poker, PokerType *pokerType);			//三条
bool IsLiangDui(Poker **poker, PokerType *pokerType);			//两对
bool IsDuiZi(Poker **poker, PokerType *pokerType);				//对子
bool IsSanPai(Poker **poker, PokerType *pokerType);				//散牌