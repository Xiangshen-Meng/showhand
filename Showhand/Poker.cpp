/********************************************************

Copyright (C), 2010-1, 真飞鸟

File name:  Poker.cpp 

Author:     真飞鸟

Version:    1.00

Description: 扑克文件：扑克的洗牌和发牌以及将牌排序

History:        

真飞鸟    2010/01/27       1.0     建立文件

**********************************************************/

#include "Poker.h"
#include "Main.h"



/***************************************************************************
//*  Function   : void WashPoker(int **pokerPack)
//*  Description: 洗牌函数
//*  Parameters :  int **pokerPack
//*                传入数组的地址为了将其指向新生成的空间
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void WashPoker(int **pokerPack)							//洗牌函数参数为一个数组，开辟个堆空间并用参数指向
{
	int *pokerBreak= (int*)malloc(POKERSIZE*sizeof(int));		//扑克的空间用于返回给pokerPack (即打乱完所放的位置)
	int pokerSeq[POKERSIZE];									//按顺序排列的牌
	int divided = POKERSIZE;									//控制取牌
	int temp = 0;												//暂存数据

	for (int i= 0; i<POKERSIZE; i++)							//初始化顺序牌
	{
		pokerSeq[i] = i+1;
	}

	srand(GetTickCount());								//做随机数种子

	for (int i = 0; i<POKERSIZE; i++)					//打乱顺序牌采用取余的方法：随机数取52的余，得到0-51之间的数以其做为脚标取出值，放入
	{													//目标位置，并将当前最后1张牌放入当前位置，将52减1。下次取51的余，然后取50的余...
		temp = (rand()%divided);						//随机脚标
		*(pokerBreak+i) = pokerSeq[temp];				//取值放入目标位置
		pokerSeq[temp] = pokerSeq[divided-1];			//将最后的牌放入当前取也值的位置
		divided--;										//被取余的数减1
	}

	*pokerPack = pokerBreak;							//使指针指向打乱后的空间
}

/***************************************************************************
//*  Function   : void Deal(int *pokerPack, Poker *pok, int step)
//*  Description: 发牌函数
//*  Parameters :  Poker *pok
//*                表示输入的牌
//*				   int *pokerPack
//*				   将当前整副牌的数组用指针传入
//*				   int step
//*				   要发牌的位置
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void Deal(int *pokerPack, Poker *pok, int step)					//发牌：pokerPack中的数组是1-52的随机数，规定扑克按黑桃2 3 4 5 6 7 8 9 10 J Q K A 红桃2....
{														//对应数组中的元素


	if (step >= POKERSIZE)								//发牌超过52张返回
	{
		printf("发牌超数！");
		return;
	}

	pok->porkNum = (*(pokerPack+step)-1)%13+1;				//得到当前牌的值
	pok->porkSuit = (*(pokerPack+step)-1)/13 +3;			//得到花色，3为红桃，4为方片，5为草花，6为黑桃

	switch((*(pokerPack+step)-1)/13)						//得到花色的大小黑桃为4，红桃为3，草花为2，方片为1
	{
	case 0:													//为0时表示红桃
		pok->porkSuitNum = 3;								//红桃的值为3
		break;
	case 1:													//为1时表示方片
		pok->porkSuitNum = 1;								//方片的值为1
		break;
	case 2:													//为3时表示草花
		pok->porkSuitNum = 2;								//草花的值为2
		break;
	case 3:													//为2时表示黑桃
		pok->porkSuitNum = 4;								//黑桃的值为4
		break;
	}

	switch (pok->porkNum)									//给出牌面，牌的值为1表示'2'，13表示'A'
	{
	case 1:
		strcpy(pok->porkPip," 2");
		break;
	case 2:
		strcpy(pok->porkPip," 3");
		break;
	case 3:
		strcpy(pok->porkPip," 4");
		break;
	case 4:
		strcpy(pok->porkPip," 5");
		break;
	case 5:
		strcpy(pok->porkPip," 6");
		break;
	case 6:
		strcpy(pok->porkPip," 7");
		break;
	case 7:
		strcpy(pok->porkPip," 8");
		break;
	case 8:
		strcpy(pok->porkPip," 9");
		break;
	case 9:
		strcpy(pok->porkPip,"10");
		break;
	case 10:
		strcpy(pok->porkPip," J");
		break;
	case 11:
		strcpy(pok->porkPip," Q");
		break;
	case 12:
		strcpy(pok->porkPip," K");
		break;
	case 13:
		strcpy(pok->porkPip," A");
		break;
	}
}


/***************************************************************************
//*  Function   : void SortPoker(Poker **poker)
//*  Description: 排序函数
//*  Parameters :  Poker **poker
//*                牌的数组
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void SortPoker(Poker **poker)									
{
	Poker *temp = (Poker*)malloc(sizeof(Poker));				//用于交换牌
	Poker **pokerTemp = (Poker**)malloc(sizeof(Poker*)*POKERCOUNT);		//开辟指针用于指向临时存储5张牌排序后的空间
	for (int i =0; i<POKERCOUNT; i++)									//开辟5个牌的空间
	{
		*(pokerTemp+i) = (Poker*)malloc(sizeof(Poker));
	}
	int tempOffset = 0;													//用于记录临时存储区已偏移的量
	Poker *max = NULL;											//最小牌的指针
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)		//将最大的放入max中,第一次排序(选择法)排成从大到小，并花色正确
	{
		max = *(poker+i);										//初始max，把该次循环的第一个牌给max

		for (int j = i+1; j <POKERCOUNT && *(poker+j) != NULL; j++)					//找到第一次遍历时最大的
		{
			if ((*(poker+j))->porkNum > max->porkNum)			//如果当前牌牌面大于max中的，把当前的给max
			{
				max = *(poker+j);
			}
			if ((*(poker+j))->porkNum == max->porkNum && (*(poker+j))->porkSuitNum > max->porkSuitNum)		//当牌面相同时看花色，如果花色大于max，把当前的给max，即按红桃方片草花黑桃顺序
			{
				max = *(poker+j);
			}
		}
		memcpy(temp, max, sizeof(Poker));						//交换
		memcpy(max, *(poker+i), sizeof(Poker));					//两张
		memcpy(*(poker+i), temp, sizeof(Poker));				//牌
	}

	tempOffset = 0;												//初始化临时存储区偏移量

	for (int i = 0,j = 0, k =1; i<POKERCOUNT && *(poker+i) != NULL; i++)				//第2次排序分2个循环,这是第一个用于将连续的提出来并放入临时区
	{
		j = 0;													//用于表示与当前位置的偏移量
		k =	1;													//标志有几个连续的
		if (*(poker+i+j+1) != NULL && (i+j+1)<POKERCOUNT && (*(poker+i+j))->porkNum == (*(poker+i+j+1))->porkNum)		//如果是连续的就进入，判断连续的有几个
		{
			while (*(poker+i+j+1) != NULL && (i+j+1)<POKERCOUNT && (*(poker+i+j))->porkNum == (*(poker+i+j+1))->porkNum)
			{
				k++;
				j++;
			}

			for (int m = 0; m <k; m++)												//将连续的复制到临时区去，
			{
				memcpy(*(pokerTemp+tempOffset), *(poker+i+m), sizeof(Poker));		//将连续的复制以牌为单位复制
				tempOffset++;														//控制临时区该写入的位置
				(*(poker+i+m))->porkNum = 0;										//并将被复制的牌的值改为0，为后面后面循环判断哪个已经复制过做准备
			}
			i+=(k-1);											//i也相应向后移动
		}else
		{
			continue;																//如果不是连续的话直接跳过，在后面的复制时会进行复制
		}
		
	}

	for (int i= 0; i<POKERCOUNT;i++)												//将不连续的牌复制到临时区
	{
		if (*(poker+i) != NULL && (*(poker+i))->porkNum != 0)						//将没被复制过来的牌复制过来
		{
			memcpy(*(pokerTemp+tempOffset), *(poker+i), sizeof(Poker));
			tempOffset++;
		}
	}

	for (int i =0; i<POKERCOUNT && *(poker+i) != NULL; i++)							//将已经排好的临时区以牌为单位复制回去
	{
		memcpy(*(poker+i),*(pokerTemp+i),sizeof(Poker));
	}
	for (int i =0; i<POKERCOUNT; i++)									//释放5个牌的空间
	{
		free(*(pokerTemp+i));
	}
	free(temp);													//释放临时空间
	free(pokerTemp);											//释放临时空间
}