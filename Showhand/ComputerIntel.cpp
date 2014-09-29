/********************************************************

Copyright (C), 2010-1, 真飞鸟

File name:  ComputerIntel.cpp 

Author:     真飞鸟

Version:    1.00

Description: 用于机器的智能运算并确定是否跟牌，以及哪方先下注

History:        

真飞鸟    2010/01/27       1.0     建立文件

**********************************************************/

#include "ComputerIntel.h"

/***************************************************************************
//*  Function   : int ComputerIntel(int *pokerPack, bool computerHome, int step)
//*  Description: 判断当前是否应该跟牌
//*  Parameters :  int *pokerPack
//*                当前的整副扑克
//*				   bool computerHome
//*				   是否是庄家
//*				   int step
//*				   应该判断几张，即到第几步了
//*  Returns    : int
//*	              应该跟注的大小
//*  History    : 2010/01/27 create    
//***************************************************************************/

int ComputerIntel(int *pokerPack, bool computerHome, int step)							//判断当前是否应该跟牌，返回要跟的数量
{
	int returnValue = 0;																//要返回的值

	if (step == 2)																		//当为第二次时进接跟20
	{
		return 20;
	}

	Poker **playerPoker = (Poker **)malloc(sizeof(Poker *)*6);							//装玩家的牌，为了处理，用6张牌，前5张为正常得到的牌，最后为空，因为机器看不到第一张牌，由于Judge的函数需要牌的数组如果为空应为NULL，所以用了6个
	Poker **computPoker = (Poker **)malloc(sizeof(Poker *)*5);							//装机器的牌
	PokerType playerType;																//玩家牌面类型的结构体
	PokerType computType;																//机器牌面类型的结构体

	for (int i= 0; i<5;i++)																//指针全部置NULL
	{
		*(playerPoker+i) = NULL;
		*(computPoker+i) = NULL;
	}
	*(playerPoker+5) = NULL;

	int flag = 0;																		//标志从整副牌中取出牌的位置

	for (int i =0; i <step; i++)														//将牌分配给玩家和机器，其实相当于牌的复本，因为要排序不能对原来的牌进行操作
	{
		*(playerPoker+i) = (Poker *)malloc(sizeof(Poker));
		*(computPoker+i) = (Poker *)malloc(sizeof(Poker));

		if (computerHome == true)														//发牌顺序不同，因为谁庄先发谁
		{
			Deal(pokerPack, *(computPoker+i), flag++);							//机器庄先给机器
			Deal(pokerPack,*(playerPoker+i), flag++);
		}else
		{
			Deal(pokerPack,*(playerPoker+i), flag++);							//玩家庄先给玩家
			Deal(pokerPack, *(computPoker+i), flag++);
		}
	}

	SortPoker(playerPoker+1);															//排序玩家牌，玩家跳过第一张牌，因为机器不知道玩家第一张
	SortPoker(computPoker);																//排序机器牌

	Judge(playerPoker+1,&playerType);													//判断类型，玩家跳过第一张牌，相当于判断了四个牌的类型，机器用5张的与四张的比较带有一定的随机性
	Judge(computPoker,&computType);														//判断类型机器的牌的类型

	while (true)																		//为了只选一次而不在比较其它的了使用break,才使用的while(true)，没真下循环的意思
	{																					//以下的比较均为机器的n张比较玩家的n-1张
		if (computType.cardType > playerType.cardType)									//机器牌类比玩家的大，下汪30
		{
			returnValue = 30;
			break;
		}else if (computType.cardType < playerType.cardType)							//机器牌类小于玩家时
		{
			if (computType.maxCardNum >= playerType.maxCardNum && step < 5)				//不是最后2次时，机器的决定牌玩家比玩家的大返回20
			{
				returnValue = 20;
				break;
			}
			else																		//最后2次时，只要机器的牌型不如玩家时都放弃，返回0
			{
				return 0;
			}
		}else																			//牌类型相等
		{
			if (computType.maxCardNum > playerType.maxCardNum)							//决定牌大时下注25
			{
				returnValue = 25;
				break;
			}
			else if (computType.maxCardNum < playerType.maxCardNum)						//决定牌小，不是最后2次可以返回20
			{
				if (step < 5)
				{
					returnValue = 20;
					break;
				}else																	//决定牌小，是最后2次时返回0放弃
				{
					returnValue = 0;
					break;
				}
			}else
			{
				if (computType.maxCardSuitNum > playerType.maxCardSuitNum)				//牌面也相等时如果花也大，返回20
				{
					returnValue = 20;
					break;
				}else																	//牌面也相等时如果花色不大，返回0
				{
					returnValue = 0;
					break;
				}
			}
		}
	}

	for(int i =0;i < step; i++)															//释放空间
	{
		free(*(playerPoker+i));
		free(*(computPoker+i));
	}
	free(*(playerPoker+5));
	free(playerPoker);
	free(computPoker);

	return returnValue;
}

/***************************************************************************
//*  Function   : int Cheak(Poker **poker1, Poker **poker2)
//*  Description: 判断当前双方都可见牌面的大小，以返回谁先下注
//*  Parameters :  Poker **poker1
//*                第一组牌的数组
//*				   Poker **poker2
//*				   第二组牌的数组
//*  Returns    : int
//*				  返回谁先下注1为第一个参数，2为第二个参数
//*  History    : 2010/01/27 create    
//***************************************************************************/
int Cheak(Poker **poker1, Poker **poker2)												//判断当前双方都可见牌面的大小，以返回谁先下注，传入的参数应跳过第一张
{
	Poker **pokerTemp1 = (Poker **)malloc(sizeof(Poker *)*5);							//将2组牌复制也复本以便比较
	Poker **pokerTemp2 = (Poker **)malloc(sizeof(Poker *)*5);							//同上面函数类似
	PokerType pokerType1;
	PokerType pokerType2;

	for (int i= 0; i<5;i++)
	{
		*(pokerTemp1+i) = NULL;
		*(pokerTemp2+i) = NULL;
	}

	for (int i = 0; i<4 && *(poker1+i) != NULL; i++)									//复制2组牌
	{
		*(pokerTemp1+i) = (Poker *)malloc(sizeof(Poker));
		*(pokerTemp2+i) = (Poker *)malloc(sizeof(Poker));
		memcpy(*(pokerTemp1+i), *(poker1+i), sizeof(Poker));
		memcpy(*(pokerTemp2+i), *(poker2+i), sizeof(Poker));
	}

	SortPoker(pokerTemp1);
	SortPoker(pokerTemp2);

	Judge(pokerTemp1,&pokerType1);
	Judge(pokerTemp2,&pokerType2);

	if (pokerType1.cardType > pokerType2.cardType)										//和JudegeWin基本一样
	{
		return 1;
	}else if (pokerType1.cardType < pokerType2.cardType)
	{
		return 2;
	}else
	{
		if (pokerType1.maxCardNum > pokerType2.maxCardNum)
		{
			return 1;
		}else if (pokerType1.maxCardNum < pokerType2.maxCardNum)
		{
			return 2;
		}else
		{
			if (pokerType1.maxCardSuitNum > pokerType2.maxCardSuitNum)
			{
				return 1;
			}else
			{
				return 2;
			}
		}
	}

	for(int i =0;i < 5; i++)															//释放
	{
		free(*(pokerTemp1+i));
		free(*(pokerTemp2+i));
	}
	free(pokerTemp1);
	free(pokerTemp2);
}