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
	bool playerWin;						//����Ƿ�ʤ
	bool computerHome;					//�����Ƿ���ׯ��
	int money;							//���ֵĽ�Ǯ�����
	int comMoney;						//���ֵĽ�Ǯ������
	int moneyTogether;					//��Ǯ��
	int step;							//��¼��ǰ���Ƶ�λ��
	int *pokerPack;						//�����˿�
	Poker **pokPlayer;					//��ҵ���
	Poker **pokComput;					//��������
}DrawArgument;

void DrawWelcome();					//����ʼ����
void DrawCard(Poker **poker);		//��һ����
void DrawPlayingFrame();			//����Ľ���
char DrawEnd(DrawArgument *drawArg);			//����������
int PlayerCall(DrawArgument *drawArg);			//�����עʱ����
int ComputerCall(DrawArgument *drawArg);;		//������עʱ����
void Run();							//��Ϸ���
void DrawAbout();