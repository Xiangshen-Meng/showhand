/********************************************************

Copyright (C), 2010-1, 真飞鸟

File name:  GUI.cpp 

Author:     真飞鸟

Version:    1.00

Description: 图形文件主要用于绘制图形

History:        

真飞鸟    2010/01/27       1.0     建立文件

**********************************************************/

#include "GUI.h"



/***************************************************************************
//*  Function   : void DrawWelcome()
//*  Description: 打印开始界面函数
//*  Parameters : void
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/
void DrawWelcome()
{
	printf("\n\n                         欢 迎 使 用 梭 哈 小 游 戏 !\n\n\n");
	printf("     1.     2.     3.\n\n");
	printf("     开     关     退\n\n");
	printf("     始     于     出\n\n");
	printf("     游     作     游\n\n");
	printf("     戏     者     戏\n\n");
	printf("\n\n\n\n\n\n                              古人云：不梭则已，一梭到底...\n\n");
}

/***************************************************************************
//*  Function   : void DrawCard(Poker **poker)
//*  Description: 打印牌面函数
//*  Parameters : Poker **poker
//*               扑克数组
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void DrawCard(Poker **poker)												//当扑克数组中有几个牌时打印几张
{
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ┏━━┓");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ┃    ┃");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ┃%s%c ┃", (*(poker+i))->porkPip, (*(poker+i))->porkSuit);
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ┃    ┃");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ┗━━┛");
	}
	printf("\n");
}

/***************************************************************************
//*  Function   : void DrawPlayingFrame()
//*  Description: 打印游戏时的主界面的函数
//*  Parameters : 
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void DrawPlayingFrame()
{
	DrawArgument drawArg;

	int money = MONEYINFIRST;					//将开局的金钱给玩家
	int comMoney = MONEYINFIRST;				//将开局的金钱给机器
	int *pokerPack = NULL;						//
	Poker *pokPlayer[5] = {NULL};
	Poker *pokComput[5] = {NULL};
	char ope = 0;																//读取单个操作用
	char storeFirstCardFace[3];													//为了不打印机器第一张牌 临时保存片张牌的牌面
	char storeFirstCardSuit;													//为了不打印机器第一张牌 临时保存片张牌的花色
	bool computerHome = true;													//记录谁是庄家
	bool playerWin = true;														//记录玩家是否胜，true为玩家胜
	bool playerCall = true;														//玩家下注
	int step = 0;																//记录发牌的次数超过5就结束
	int moneyTogether = 0;														//记录1轮中各方下注的总数
	int dealStep = 0;															//发牌的位置
	int curMoney = 0;															//玩家下注的钱数
	int comCurMoney = 0;														//机器下注的钱数

	PokerType playerType;														//表示玩家牌面类型的结构体
	PokerType computType;														//表示电脑牌面类型的结构体
lPlay:																			//游戏开始的标志点

	if (pokerPack != NULL)														//如果之前有扑克，将扑克进行释放并初始化为NULL
	{
		free(pokerPack);
		pokerPack = NULL;
	}

	for (int i = 0; i<5 && *(pokPlayer+i) != NULL; i++)							//如果之前有玩家牌，将进行玩家牌释放并初始化为NULL
	{
		free(*(pokPlayer+i));
		*(pokPlayer+i) = NULL;
	}

	for (int i = 0; i<5 && *(pokComput+i) != NULL; i++)							//如果之前有机器牌，将进行玩家牌释放并初始化为NULL
	{
		free(*(pokComput+i));
		*(pokComput+i) = NULL;
	}

	system("cls");																//清屏开始打印
	printf("                      ☆☆☆ 玩家现在拥有金额：%d  ☆☆☆\n",money);
	printf("                      ☆☆☆ 机器现在拥有金额：%d  ☆☆☆\n",comMoney);
	printf("\n\n\n◎是否要开始新的一局？(Y/N)\n");

	while ((ope = getchar()) == '\n');											//过滤多余的回车

	if (toupper(ope) != 'Y' && toupper(ope) != 'N')								//不为y,n重打印前面的
	{
		goto lPlay;
	}
	if (toupper(ope) == 'N')													//为n返回
	{
		return;
	}

	moneyTogether = 0;															//将每局的总钱数清空
	dealStep = 0;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n                                   洗牌中...\n\n\n\n");
	WashPoker(&pokerPack);														//洗牌
	Sleep(1000);



	for (step = 0;step < POKERCOUNT;step++)										//限定次数最多进行5次*******************************************
	{
		Sleep(500);
		system("cls");
		printf("                      ☆☆☆ 玩家现在拥有金额：%d  ☆☆☆\n",money);
		printf("                      ☆☆☆ 机器现在拥有金额：%d  ☆☆☆\n",comMoney);
		
		*(pokPlayer+step) = (Poker*)malloc(sizeof(Poker));						//给玩家当前牌开辟空间
		*(pokComput+step) = (Poker*)malloc(sizeof(Poker));						//给机器当前牌开辟空间

		if (computerHome == true)												//机器庄家***********************************************
		{
			Deal(pokerPack, *(pokComput+step), dealStep++);						//给机器先发牌
			Deal(pokerPack, *(pokPlayer+step), dealStep++);					//给玩家发牌

		}else																	//先给玩家发牌
		{
			Deal(pokerPack, *(pokPlayer+step), dealStep++);
			Deal(pokerPack, *(pokComput+step), dealStep++);
		}

		if (step == 0)														//第一次的话将机器的第一张牌的花色和牌面保存起来
		{
			strcpy(storeFirstCardFace,(*(pokComput+0))->porkPip);			//将牌面保存在storeFirstCardFace中
			strcpy((*(pokComput+0))->porkPip,"  ");							//将牌面清为"  "
			storeFirstCardSuit = (*(pokComput+0))->porkSuit;				//将花色保存在storeFirstCardSuit中
			(*(pokComput+0))->porkSuit = ' ';								//将花色清为' '
			continue;														//第一次不需要下注
		}

		if (Cheak(pokComput+1, pokPlayer+1) == 1)							//判断由谁先下注，当前牌面大的人先下注
		{
			playerCall = false;												//机器先下注
		}else
		{
			playerCall = true;												//玩家先下注
		}

		drawArg.comMoney = comMoney;										//将必要参数装入结构体中以便传参
		drawArg.computerHome = computerHome;
		drawArg.money = money;
		drawArg.moneyTogether = moneyTogether;
		drawArg.playerWin = playerWin;
		drawArg.pokComput = pokComput;
		drawArg.pokPlayer = pokPlayer;
		drawArg.step = step;
		drawArg.pokerPack = pokerPack;

		if (playerCall == false)											//由机器先下注
		{

			int temp = ComputerCall(&drawArg);
			moneyTogether = drawArg.moneyTogether;
			money = drawArg.money;
			comMoney = drawArg.comMoney;
			playerWin = drawArg.playerWin;
			if (temp == 1)							//返回1 为break 返回2为continue 返回3为goto lEnd 返回0为return
			{
				break;
			}else if(temp == 2)
			{
				continue;
			}else if (temp == 0)
			{
				return;
			}else
			{
				goto lEnd;
			}
		}else																			//********************************************************
		{
			int temp = PlayerCall(&drawArg);

			moneyTogether = drawArg.moneyTogether;
			money = drawArg.money;
			comMoney = drawArg.comMoney;
			playerWin = drawArg.playerWin;

			if (temp == 1)																//返回值为1表示break
			{
				break;
			}else if(temp == 2)															//返回2为continue
			{
				continue;
			}else if (temp == 0)														//返回0为return
			{
				return;
			}else																		//返回3为goto lEnd
			{
				goto lEnd;
			}
		}
	}																					//******************************************************

	strcpy((*(pokComput+0))->porkPip,storeFirstCardFace);								//将机器第一张牌的牌面放回
	(*(pokComput+0))->porkSuit = storeFirstCardSuit;									//将机器第一张牌的花色放回

	if(step >= POKERCOUNT)																//当进行到最后的时候
	{
		SortPoker(pokPlayer);															//将玩家的牌排序
		SortPoker(pokComput);															//将机器的牌排序

		Judge(pokPlayer, &playerType);													//判断玩家牌的类型
		Judge(pokComput, &computType);													//判断机器牌的类型

		playerWin = JudgeWin(&playerType, &computType);									//判断玩家是否胜了
	}
lEnd:
	computerHome = drawArg.computerHome;													//将已修改过的参数从结构体中取出以改变原值

	drawArg.playerWin = playerWin;

	if (DrawEnd(&drawArg) == 'Y')														//结束函数返回的是'Y'就表示玩家输入的是'Y'，则继续玩
	{
		money = drawArg.money;
		comMoney = drawArg.comMoney;
		computerHome = drawArg.computerHome;
		goto lPlay;
	}else																				//否则退出
	{
		return;
	}
}

/***************************************************************************
//*  Function   : char DrawEnd(DrawArgument *drawArg)
//*  Description: 打印结束界面的函数
//*  Parameters : DrawArgument *drawArg
//*               装有打印时必要信息的结构体
//*  Returns    : char
//*               返回'Y'或'N'
//*  History    : 2010/01/27 create    
//***************************************************************************/

char DrawEnd(DrawArgument *drawArg)
{
	char ope = 0;

	if (drawArg->playerWin == true)															//1轮梭哈完成，结束界面，玩家胜时
	{
		drawArg->money += drawArg->moneyTogether;											//将金钱池中的全部钱给玩家
		drawArg->computerHome = false;
	}else																					//玩家输了
	{
		drawArg->comMoney += drawArg->moneyTogether;										//金钱池中的钱全给机器
		drawArg->computerHome = true;														//下轮机器庄
	}

lEnd:
	system("cls");
	printf("                      ☆☆☆ 玩家现在拥有金额：%d  ☆☆☆\n", drawArg->money);
	printf("                      ☆☆☆ 机器现在拥有金额：%d  ☆☆☆\n", drawArg->comMoney);
	if (drawArg->playerWin == true)															//胜了打印胜
	{
		printf("\n\n您赢了...\n");
	}else																					//输了打印输
	{
		printf("\n\n您输了...\n");
	}
	printf("机器：\n");
	DrawCard(drawArg->pokComput);															//打印机器牌
	printf("玩家：\n");
	DrawCard(drawArg->pokPlayer);															//打印玩家牌
	printf("\n\n\n还要玩吗？(Y/N)");

	ope = getchar();

	if (toupper(ope) != 'Y' && toupper(ope) != 'N')
	{
		goto lEnd;
	}

	if (toupper(ope) == 'Y')																//读到的字符为'Y'就返回'Y'
	{
		return 'Y';
	}else																					//否则返回'N'
	{
		return 'N';
	}
}

/***************************************************************************
//*  Function   : int PlayerCall(DrawArgument *drawArg)
//*  Description: 打印玩家下注的界面函数
//*  Parameters : DrawArgument *drawArg
//*               装有打印时必要信息的结构体
//*  Returns    : int
//*               返回1为break 返回2为continue 返回3为goto lEnd 返回0为return
//*  History    : 2010/01/27 create    
//***************************************************************************/

int PlayerCall(DrawArgument *drawArg)
{
	char curMoneyStr[30];																//暂时玩家输入的钱数的字符串
	int comCurMoney = 0;
	int curMoney = 0;
	printf("\n\n现在发牌\n");															//由玩家先下注
	printf("机器：\n");
	DrawCard(drawArg->pokComput);														//打印机器的牌
	printf("玩家：\n");
	DrawCard(drawArg->pokPlayer);														//打印玩家的牌

	if (drawArg->money >20)																//玩家金钱不足20为输
	{
		printf("\n\n您是牌面大家请下注(大于20)，'N':放弃：");

		do
		{
			curMoney = 0;																//每次都将当前的数清空否则后面会玩法打印
			while(strlen(gets(curMoneyStr)) == 0);										//当读入不是空串时停下
			sscanf(curMoneyStr, "%d",&curMoney);										//如果是数将其转为数字

			if (toupper(*curMoneyStr) == 'N')											//读入'N'，表示玩家放弃
			{
				drawArg->playerWin = false;												//玩家输了跳到结束位置
				return 1;																//玩家认输相当于返回break
			}

			if (curMoney < 20  || curMoney > drawArg->money)							//如果为数字如果金钱不对的话提示
			{
				printf("您的金钱输入不对请重新输入：");
			}

		}while (curMoney < 20  || curMoney > drawArg->money);							//用于判断金钱数是否正确不正确循环


		drawArg->money -= curMoney;														//玩家金钱减少下注的钱
		drawArg->moneyTogether += curMoney;												//金钱池中的钱加下注的钱

		comCurMoney = ComputerIntel(drawArg->pokerPack, drawArg->computerHome,(drawArg->step)+1);			//机器智能判断下注多少

		if (comCurMoney == 0 || drawArg->comMoney < curMoney)							//如果为0或当前金钱时机器放弃
		{
			printf("\n\n机器已放弃...\n");
			Sleep(3000);																//延迟三秒为了玩家看清
			drawArg->playerWin = true;
			return 1;																	//机器放弃相当于返回break
		}
		if (drawArg->comMoney < 20)														//机器金钱不足时玩家胜
		{
			printf("机器已破产...恭喜您！\n");
			system("pause >> endl");
			return 0;																	//机器破产游戏结束,相当返回return
		}
		printf("机器跟注...");															//否则机器跟注
		drawArg->comMoney -= curMoney;													//机器金钱减少下注的
		drawArg->moneyTogether += curMoney;												//金钱池中金钱增加下注的
		return 2;
	}else																				//玩家金钱不足时
	{
		printf("对不起您没有足够的金钱了..谢谢您的光临..按任意键返回游戏选单\n");
		system("pause >> endl");
		return 0;																		//玩家金钱不足，相当于返回return
	}
}

/***************************************************************************
//*  Function   : int ComputerCall(DrawArgument *drawArg)
//*  Description: 打印玩家下注的界面函数
//*  Parameters : DrawArgument *drawArg
//*               装有打印时必要信息的结构体
//*  Returns    : int
//*               返回1为break 返回2为continue 返回3为goto lEnd 返回0为return
//*  History    : 2010/01/27 create    
//***************************************************************************/

int ComputerCall(DrawArgument *drawArg)
{
	char ope = 0;
	int comCurMoney = 0;
	int curMoney = 0;
	printf("\n\n现在发牌\n");
	printf("机器：\n");
	DrawCard(drawArg->pokComput);												//打印机器的牌
	printf("玩家：\n");
	DrawCard(drawArg->pokPlayer);												//打印玩家的牌
	comCurMoney = ComputerIntel(drawArg->pokerPack, drawArg->computerHome,(drawArg->step)+1);					//机器智能，判断是否跟牌，跟多少

	if(comCurMoney != 0)												//如果当前机器智能返回0，即选择放弃
	{
		if (drawArg->money < 20)												//玩家当前如果金钱以不足20则输了
		{
			printf("对不起您没有足够的金钱了..谢谢您的光临..按任意键返回游戏选单\n");
			system("pause >> endl");
			return 0;															//玩家金钱不足，相当于返回return
		}
		if (drawArg->comMoney >comCurMoney)										//当前机器的金钱超过智能得到的金钱数则可以下注
		{
			printf("\n\n机器已下注:%d\n",comCurMoney);
			drawArg->comMoney -=comCurMoney;									//机器金钱减下注的钱
			drawArg->moneyTogether += comCurMoney;								//金钱池中加上下注的钱
		}else if (drawArg->comMoney < 20)										//当机器金钱已少于20，机器破产
		{
			printf("机器已经破产...恭喜您...\n");
			system("pause >> endl");
			return 0;															//机器破产，相当于返回return
		}else																	//只多于20，不到智能希望的金钱数时，则下注20
		{
			printf("\n\n机器已下注:20\n");
			drawArg->comMoney -=20;												//机器下注20
			drawArg->moneyTogether += 20;										//金钱池加20
		}
	}else
	{
		printf("\n\n机器已放弃...\n");											//如果智能得到想放弃即comCurMoney为0
		Sleep(3000);															//延迟三秒，为了玩家看清
		drawArg->playerWin = true;												//玩家胜
		return 1;																//机器放弃相当于返回break
	}


	printf("是否跟注？(Y/N)");

	do 
	{
		ope = getchar();
	} while (toupper(ope) != 'N' && toupper(ope) != 'Y');						//过滤无用字符

	if (toupper(ope) == 'Y')													//当玩家选择跟
	{
		drawArg->money -= comCurMoney;											//玩家金钱减少
		drawArg->moneyTogether += comCurMoney;									//金钱池中金钱增加
		return 2;																//相当于返回continue
	}else
	{
		drawArg->playerWin = false;												//否则玩家放弃
		return 1;																//相当于返回break
	}
}

void DrawAbout()
{
	system("cls");
	printf("\n\n               ☆★☆★☆★ 写给所有的C语言爱好者 ★☆★☆★☆\n");
	printf("\n\n          本梭哈小游戏仅为学习之用，源代码中用到了大量的堆内存的开辟，\n"
		"        由于时间仓促没有对每块内存是否释放进行跟踪测试，敬请谅解(其实\n        就是没检查是不是每块都释放了，写代码的时候是都写了释放)。"
		"本游\n        戏的源代码对所有的编程爱好者开放，希望对广大学习C语言的兄弟们\n        有帮助...\n"
		"        如果大家对这个小游戏有什么好的想法，希望可以告诉我，我们共同\n        学习，共同进步。\n\n"
		"        我的联系方式：QQ:724240161\n		邮箱：wqnnjm@163.com\n\n"
		"                                                    再次表示感谢\n\n"
		"                                                    作者：真飞鸟\n"
		"                                                    2010年2月1日\n"
		"                                                         于大连\n");
	printf("\n        按任意键返回上级选单...");
	system("pause > endl");
}

/***************************************************************************
//*  Function   : void Run()
//*  Description: 打印界面的函数 调用其它打印函数
//*  Parameters : 
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void Run()
{
	PokerType pokerType1;
	PokerType pokerType2;
	char ope = 0;
loop:
	system("cls");
	DrawWelcome();
	while ((ope = getchar()) == '\n');

	switch(ope)
	{
	case '1':
		DrawPlayingFrame();
		break;
	case '2':
		DrawAbout();
		break;
	case '3':
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\n\n                                 感谢您的使用...\n\n\n\n");
		Sleep(1000);
		exit(0);
		break;
	default:
		goto loop;
	}
	goto loop;
}