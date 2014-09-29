/********************************************************

Copyright (C), 2010-1, XXXXXX

File name:  Main.cpp 

Author:     真飞鸟

Version:    1.00

Description: 判断游戏中牌面属于哪种类型 

History:        

真飞鸟    2010/01/27       1.0     建立文件

**********************************************************/

#include "Judge.h"



/***************************************************************************
//*  Function   : void Judge(Poker **poker, PokerType *pokerType)
//*  Description: 判断5张牌面的类型，并将起决定性的牌在大小和花色放入pokerType中
//*  Parameters :  Poker **poker
//*                指向5张扑克的指针
//*				   PokerType *pokerType
//*				   将可以判断两个牌面大小的元素放入到pokerType中
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void Judge(Poker **poker, PokerType *pokerType)//判断牌面
{
	if(IsTongHuaShun(poker, pokerType) == true)
	{
		return;
	}else if (IsTongHua(poker, pokerType) == true)
	{
		return;
	}else if (IsTieZhi(poker,pokerType) == true)
	{
		return;
	}else if (IsHuLu(poker,pokerType) == true)
	{
		return;
	}else if (IsShunZi(poker,pokerType) == true)
	{
		return;
	}else if (IsSanTiao(poker,pokerType) == true)
	{
		return;
	}else if (IsLiangDui(poker,pokerType) == true)
	{
		return;
	}else if (IsDuiZi(poker,pokerType) == true)
	{
		return;
	}else
	{
		IsSanPai(poker,pokerType);
	}
}

/***************************************************************************
//*  Function   : int JudgeWin(PokerType *pokerType1, PokerType *poker2)
//*  Description: 判断哪方获胜返回true表示第一个参数方胜，否则第二个胜
//*  Parameters :  PokerType *pokerType1
//*                通过Judge得到的pokerType1的指针
//*				   PokerType *pokerType2
//*				   通过Judge得到的pokerType2的指针
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

bool JudgeWin(PokerType *pokerType1, PokerType *pokerType2)
{
	if (pokerType1->cardType > pokerType2->cardType)						//cardType类型的值大就大
	{																		//如果一样,可以看决定元素的值
		return true;														//如果一样，可以看元素的花色值
	}else if (pokerType1->cardType < pokerType2->cardType)					//返回值为true为第一个参数方胜，为false为第二个参数方胜
	{
		return false;
	}else
	{
		if (pokerType1->maxCardNum > pokerType2->maxCardNum)
		{
			return true;
		}else if (pokerType1->maxCardNum < pokerType2->maxCardNum)
		{
			return false;
		}else
		{
			if (pokerType1->maxCardSuitNum > pokerType2->maxCardSuitNum)
			{
				return true;
			}else
			{
				return false;
			}
		}
	}
}

//***************************************************************************
//*							   判断同花顺
//***************************************************************************

bool IsTongHuaShun(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//不到三张牌不给同花顺，为机器智能用的，因为这个数太大了
	{
		return false;
	}

	for (int i = 0; i < POKERCOUNT-1 && *(poker+i) != NULL && *(poker+i+1) != NULL;i++)
	{
		if ((*(poker+i))->porkSuitNum != (*(poker+i+1))->porkSuitNum ||
			(*(poker+i))->porkNum != ((*(poker+i+1))->porkNum+1))
		{
			return false;
		}
	}
	pokerType->cardType = TongHuaShun;								//决定同花顺的元素为最大的牌和其花色
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//将最大的值给pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;				//将最大的牌面的花色的值给pokerType
	return true;
}

//***************************************************************************
//*							     判断同花
//***************************************************************************

bool IsTongHua(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//不到三张牌不给同花，为机器智能用的，因为这个数太大了
	{
		return false;
	}
	for (int i = 0; i < POKERCOUNT-1 && *(poker+i) != NULL && *(poker+i+1);i++)
	{
		if ((*(poker+i))->porkSuitNum != (*(poker+i+1))->porkSuitNum)
		{
			return false;
		}
	}

	pokerType->cardType = TongHua;									//其它为同花
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//决定同花的元素是最大牌面在值和其花色，所以将牌的值给pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;				//将最大的花色的值给pokerType
	return true;
}

//***************************************************************************
//*							  判断铁枝
//***************************************************************************

bool IsTieZhi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+3) == NULL)																					//三张不可能是铁枝
	{
		return false;
	}
	for (int i = 0; i < POKERCOUNT-2 && *(poker+i) != NULL;i++)
	{
		if ((*(poker+i))->porkNum != (*(poker+i+1))->porkNum)
		{
			return false;
		}
	}
	pokerType->cardType = TieZhi;																			//铁枝
	pokerType->maxCardNum = (*(poker+0))->porkNum;															//铁枝的4个一样的牌的值为决定元素
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//随便赋个花色的值
	return true;
}

//***************************************************************************
//*							判断葫芦
//***************************************************************************

bool IsHuLu(Poker **poker, PokerType *pokerType)
{
	if (*(poker+4) == NULL || *(poker+3) == NULL ||*(poker+2) == NULL)																					//四张牌时没有葫芦的可能
	{
		return false;
	}

	if (((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+1))->porkNum) == ((*(poker+2))->porkNum) && 
		((*(poker+3))->porkNum) == (*(poker+4))->porkNum) ||
		((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+2))->porkNum) == ((*(poker+3))->porkNum) && 
		((*(poker+3))->porkNum) == (*(poker+4))->porkNum) )
	{																											//三个一样，两个一样的是葫芦
		pokerType->cardType = HuLu;																				//葫芦
		pokerType->maxCardNum = (*(poker+2))->porkNum;															//葫芦的三个一样的牌的值为决定元素
		pokerType->maxCardSuitNum = (*(poker+2))->porkSuitNum;													//随便赋个花色的值
		return true;
	}else
	{
		return false;
	}
}

//***************************************************************************
//*							判断顺子
//***************************************************************************

bool IsShunZi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//不到三张牌不给顺子，为机器智能用的，因为这个数太大了
	{
		return false;
	}

	for (int i = 0; i < POKERCOUNT-1 && *(poker+i) != NULL && *(poker+i+1) != NULL;i++)
	{
		if ((*(poker+i))->porkNum != ((*(poker+i+1))->porkNum+1))
		{
			return false;
		}
	}
	pokerType->cardType = ShunZi;								//决定顺子的元素为最大的牌和其花色
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//将最大的值给pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;			//将最大的牌面的花色的值给pokerType
	return true;
}

//***************************************************************************
//*							判断三条
//***************************************************************************

bool IsSanTiao(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)
	{
		return false;
	}

	if ((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+1))->porkNum) == ((*(poker+2))->porkNum))
	{																											//三个一样，后两个不一样的是三条
		pokerType->cardType = SanTiao;																				//三条
		pokerType->maxCardNum = (*(poker+0))->porkNum;															//三条的三个一样的牌的值为决定元素
		pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//随便赋个花色的值
		return true;
	}
	return false;
}

//***************************************************************************
//*							判断两对
//***************************************************************************

bool IsLiangDui(Poker **poker, PokerType *pokerType)
{
	if (*(poker+3) == NULL)
	{
		return false;
	}
	if ((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+2))->porkNum) == ((*(poker+3))->porkNum))
	{																											//两对的特殊
		pokerType->cardType = LiangDui;																			//两对
		pokerType->maxCardNum = ((*(poker+0))->porkNum*100+((*(poker+2))->porkNum));							//两对的是4位数，因为要先比较第一对在大小，一样了看第二对，还一样才看第一对花色的大小
		pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//取出大的对中的花色的值
		return true;
	}
	return false;
}

//***************************************************************************
//*							判断对子
//***************************************************************************

bool IsDuiZi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)
	{
		return false;
	}

	if((*(poker+0))->porkNum == ((*(poker+1))->porkNum))														//对子也特殊
	{
		pokerType->cardType = DuiZi;																			//对子
		pokerType->maxCardNum = (*(poker+0))->porkNum*100+((*(poker+2))->porkNum);								//对子也是四位数因为要比较第一对的大小，相同看第2个单张的大小，还一样看花色
		pokerType->maxCardSuitNum = ((*(poker+2))->porkSuitNum);												//取出单张的花色的值
		return true;
	}
	return false;
}

//***************************************************************************
//*							判断散牌
//***************************************************************************

bool IsSanPai(Poker **poker, PokerType *pokerType)
{
	pokerType->cardType = SanPai;																				//散牌
	pokerType->maxCardNum = ((*(poker+0))->porkNum);															//最大的牌就是决定的元素
	pokerType->maxCardSuitNum = ((*(poker+0))->porkSuitNum);													//最大的牌的花色的值
	return true;
}