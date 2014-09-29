#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "Poker.h"
#include "Judge.h"
#include "Main.h"
#include "ComputerIntel.h"

typedef struct DRAWARGUMENT
{
	bool playerWin;						//玩家是否胜
	bool computerHome;					//机器是否是庄家
	int money;							//开局的金钱给玩家
	int comMoney;						//开局的金钱给机器
	int moneyTogether;					//金钱池
	int step;							//记录当前的牌的位置
	int *pokerPack;						//整副扑克
	Poker **pokPlayer;					//玩家的牌
	Poker **pokComput;					//机器的牌
}DrawArgument;

void DrawWelcome();					//画开始界面
void DrawCard(Poker **poker);		//画一张牌
void DrawPlayingFrame();			//画玩的界面
char DrawEnd(DrawArgument *drawArg);			//画结束界面
int PlayerCall(DrawArgument *drawArg);			//玩家下注时界面
int ComputerCall(DrawArgument *drawArg);;		//机器下注时界面
void Run();							//游戏入口
void DrawAbout();