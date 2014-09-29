/********************************************************

Copyright (C), 2010-1, �����

File name:  GUI.cpp 

Author:     �����

Version:    1.00

Description: ͼ���ļ���Ҫ���ڻ���ͼ��

History:        

�����    2010/01/27       1.0     �����ļ�

**********************************************************/

#include "GUI.h"



/***************************************************************************
//*  Function   : void DrawWelcome()
//*  Description: ��ӡ��ʼ���溯��
//*  Parameters : void
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/
void DrawWelcome()
{
	printf("\n\n                         �� ӭ ʹ �� �� �� С �� Ϸ !\n\n\n");
	printf("     1.     2.     3.\n\n");
	printf("     ��     ��     ��\n\n");
	printf("     ʼ     ��     ��\n\n");
	printf("     ��     ��     ��\n\n");
	printf("     Ϸ     ��     Ϸ\n\n");
	printf("\n\n\n\n\n\n                              �����ƣ��������ѣ�һ�󵽵�...\n\n");
}

/***************************************************************************
//*  Function   : void DrawCard(Poker **poker)
//*  Description: ��ӡ���溯��
//*  Parameters : Poker **poker
//*               �˿�����
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void DrawCard(Poker **poker)												//���˿��������м�����ʱ��ӡ����
{
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ��������");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ��    ��");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ��%s%c ��", (*(poker+i))->porkPip, (*(poker+i))->porkSuit);
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ��    ��");
	}
	printf("\n");
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)
	{
		printf("  ��������");
	}
	printf("\n");
}

/***************************************************************************
//*  Function   : void DrawPlayingFrame()
//*  Description: ��ӡ��Ϸʱ��������ĺ���
//*  Parameters : 
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void DrawPlayingFrame()
{
	DrawArgument drawArg;

	int money = MONEYINFIRST;					//�����ֵĽ�Ǯ�����
	int comMoney = MONEYINFIRST;				//�����ֵĽ�Ǯ������
	int *pokerPack = NULL;						//
	Poker *pokPlayer[5] = {NULL};
	Poker *pokComput[5] = {NULL};
	char ope = 0;																//��ȡ����������
	char storeFirstCardFace[3];													//Ϊ�˲���ӡ������һ���� ��ʱ����Ƭ���Ƶ�����
	char storeFirstCardSuit;													//Ϊ�˲���ӡ������һ���� ��ʱ����Ƭ���ƵĻ�ɫ
	bool computerHome = true;													//��¼˭��ׯ��
	bool playerWin = true;														//��¼����Ƿ�ʤ��trueΪ���ʤ
	bool playerCall = true;														//�����ע
	int step = 0;																//��¼���ƵĴ�������5�ͽ���
	int moneyTogether = 0;														//��¼1���и�����ע������
	int dealStep = 0;															//���Ƶ�λ��
	int curMoney = 0;															//�����ע��Ǯ��
	int comCurMoney = 0;														//������ע��Ǯ��

	PokerType playerType;														//��ʾ����������͵Ľṹ��
	PokerType computType;														//��ʾ�����������͵Ľṹ��
lPlay:																			//��Ϸ��ʼ�ı�־��

	if (pokerPack != NULL)														//���֮ǰ���˿ˣ����˿˽����ͷŲ���ʼ��ΪNULL
	{
		free(pokerPack);
		pokerPack = NULL;
	}

	for (int i = 0; i<5 && *(pokPlayer+i) != NULL; i++)							//���֮ǰ������ƣ�������������ͷŲ���ʼ��ΪNULL
	{
		free(*(pokPlayer+i));
		*(pokPlayer+i) = NULL;
	}

	for (int i = 0; i<5 && *(pokComput+i) != NULL; i++)							//���֮ǰ�л����ƣ�������������ͷŲ���ʼ��ΪNULL
	{
		free(*(pokComput+i));
		*(pokComput+i) = NULL;
	}

	system("cls");																//������ʼ��ӡ
	printf("                      ���� �������ӵ�н�%d  ����\n",money);
	printf("                      ���� ��������ӵ�н�%d  ����\n",comMoney);
	printf("\n\n\n���Ƿ�Ҫ��ʼ�µ�һ�֣�(Y/N)\n");

	while ((ope = getchar()) == '\n');											//���˶���Ļس�

	if (toupper(ope) != 'Y' && toupper(ope) != 'N')								//��Ϊy,n�ش�ӡǰ���
	{
		goto lPlay;
	}
	if (toupper(ope) == 'N')													//Ϊn����
	{
		return;
	}

	moneyTogether = 0;															//��ÿ�ֵ���Ǯ�����
	dealStep = 0;
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n                                   ϴ����...\n\n\n\n");
	WashPoker(&pokerPack);														//ϴ��
	Sleep(1000);



	for (step = 0;step < POKERCOUNT;step++)										//�޶�����������5��*******************************************
	{
		Sleep(500);
		system("cls");
		printf("                      ���� �������ӵ�н�%d  ����\n",money);
		printf("                      ���� ��������ӵ�н�%d  ����\n",comMoney);
		
		*(pokPlayer+step) = (Poker*)malloc(sizeof(Poker));						//����ҵ�ǰ�ƿ��ٿռ�
		*(pokComput+step) = (Poker*)malloc(sizeof(Poker));						//��������ǰ�ƿ��ٿռ�

		if (computerHome == true)												//����ׯ��***********************************************
		{
			Deal(pokerPack, *(pokComput+step), dealStep++);						//�������ȷ���
			Deal(pokerPack, *(pokPlayer+step), dealStep++);					//����ҷ���

		}else																	//�ȸ���ҷ���
		{
			Deal(pokerPack, *(pokPlayer+step), dealStep++);
			Deal(pokerPack, *(pokComput+step), dealStep++);
		}

		if (step == 0)														//��һ�εĻ��������ĵ�һ���ƵĻ�ɫ�����汣������
		{
			strcpy(storeFirstCardFace,(*(pokComput+0))->porkPip);			//�����汣����storeFirstCardFace��
			strcpy((*(pokComput+0))->porkPip,"  ");							//��������Ϊ"  "
			storeFirstCardSuit = (*(pokComput+0))->porkSuit;				//����ɫ������storeFirstCardSuit��
			(*(pokComput+0))->porkSuit = ' ';								//����ɫ��Ϊ' '
			continue;														//��һ�β���Ҫ��ע
		}

		if (Cheak(pokComput+1, pokPlayer+1) == 1)							//�ж���˭����ע����ǰ������������ע
		{
			playerCall = false;												//��������ע
		}else
		{
			playerCall = true;												//�������ע
		}

		drawArg.comMoney = comMoney;										//����Ҫ����װ��ṹ�����Ա㴫��
		drawArg.computerHome = computerHome;
		drawArg.money = money;
		drawArg.moneyTogether = moneyTogether;
		drawArg.playerWin = playerWin;
		drawArg.pokComput = pokComput;
		drawArg.pokPlayer = pokPlayer;
		drawArg.step = step;
		drawArg.pokerPack = pokerPack;

		if (playerCall == false)											//�ɻ�������ע
		{

			int temp = ComputerCall(&drawArg);
			moneyTogether = drawArg.moneyTogether;
			money = drawArg.money;
			comMoney = drawArg.comMoney;
			playerWin = drawArg.playerWin;
			if (temp == 1)							//����1 Ϊbreak ����2Ϊcontinue ����3Ϊgoto lEnd ����0Ϊreturn
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

			if (temp == 1)																//����ֵΪ1��ʾbreak
			{
				break;
			}else if(temp == 2)															//����2Ϊcontinue
			{
				continue;
			}else if (temp == 0)														//����0Ϊreturn
			{
				return;
			}else																		//����3Ϊgoto lEnd
			{
				goto lEnd;
			}
		}
	}																					//******************************************************

	strcpy((*(pokComput+0))->porkPip,storeFirstCardFace);								//��������һ���Ƶ�����Ż�
	(*(pokComput+0))->porkSuit = storeFirstCardSuit;									//��������һ���ƵĻ�ɫ�Ż�

	if(step >= POKERCOUNT)																//�����е�����ʱ��
	{
		SortPoker(pokPlayer);															//����ҵ�������
		SortPoker(pokComput);															//��������������

		Judge(pokPlayer, &playerType);													//�ж�����Ƶ�����
		Judge(pokComput, &computType);													//�жϻ����Ƶ�����

		playerWin = JudgeWin(&playerType, &computType);									//�ж�����Ƿ�ʤ��
	}
lEnd:
	computerHome = drawArg.computerHome;													//�����޸Ĺ��Ĳ����ӽṹ����ȡ���Ըı�ԭֵ

	drawArg.playerWin = playerWin;

	if (DrawEnd(&drawArg) == 'Y')														//�����������ص���'Y'�ͱ�ʾ����������'Y'���������
	{
		money = drawArg.money;
		comMoney = drawArg.comMoney;
		computerHome = drawArg.computerHome;
		goto lPlay;
	}else																				//�����˳�
	{
		return;
	}
}

/***************************************************************************
//*  Function   : char DrawEnd(DrawArgument *drawArg)
//*  Description: ��ӡ��������ĺ���
//*  Parameters : DrawArgument *drawArg
//*               װ�д�ӡʱ��Ҫ��Ϣ�Ľṹ��
//*  Returns    : char
//*               ����'Y'��'N'
//*  History    : 2010/01/27 create    
//***************************************************************************/

char DrawEnd(DrawArgument *drawArg)
{
	char ope = 0;

	if (drawArg->playerWin == true)															//1�������ɣ��������棬���ʤʱ
	{
		drawArg->money += drawArg->moneyTogether;											//����Ǯ���е�ȫ��Ǯ�����
		drawArg->computerHome = false;
	}else																					//�������
	{
		drawArg->comMoney += drawArg->moneyTogether;										//��Ǯ���е�Ǯȫ������
		drawArg->computerHome = true;														//���ֻ���ׯ
	}

lEnd:
	system("cls");
	printf("                      ���� �������ӵ�н�%d  ����\n", drawArg->money);
	printf("                      ���� ��������ӵ�н�%d  ����\n", drawArg->comMoney);
	if (drawArg->playerWin == true)															//ʤ�˴�ӡʤ
	{
		printf("\n\n��Ӯ��...\n");
	}else																					//���˴�ӡ��
	{
		printf("\n\n������...\n");
	}
	printf("������\n");
	DrawCard(drawArg->pokComput);															//��ӡ������
	printf("��ң�\n");
	DrawCard(drawArg->pokPlayer);															//��ӡ�����
	printf("\n\n\n��Ҫ����(Y/N)");

	ope = getchar();

	if (toupper(ope) != 'Y' && toupper(ope) != 'N')
	{
		goto lEnd;
	}

	if (toupper(ope) == 'Y')																//�������ַ�Ϊ'Y'�ͷ���'Y'
	{
		return 'Y';
	}else																					//���򷵻�'N'
	{
		return 'N';
	}
}

/***************************************************************************
//*  Function   : int PlayerCall(DrawArgument *drawArg)
//*  Description: ��ӡ�����ע�Ľ��溯��
//*  Parameters : DrawArgument *drawArg
//*               װ�д�ӡʱ��Ҫ��Ϣ�Ľṹ��
//*  Returns    : int
//*               ����1Ϊbreak ����2Ϊcontinue ����3Ϊgoto lEnd ����0Ϊreturn
//*  History    : 2010/01/27 create    
//***************************************************************************/

int PlayerCall(DrawArgument *drawArg)
{
	char curMoneyStr[30];																//��ʱ��������Ǯ�����ַ���
	int comCurMoney = 0;
	int curMoney = 0;
	printf("\n\n���ڷ���\n");															//���������ע
	printf("������\n");
	DrawCard(drawArg->pokComput);														//��ӡ��������
	printf("��ң�\n");
	DrawCard(drawArg->pokPlayer);														//��ӡ��ҵ���

	if (drawArg->money >20)																//��ҽ�Ǯ����20Ϊ��
	{
		printf("\n\n��������������ע(����20)��'N':������");

		do
		{
			curMoney = 0;																//ÿ�ζ�����ǰ������շ��������淨��ӡ
			while(strlen(gets(curMoneyStr)) == 0);										//�����벻�ǿմ�ʱͣ��
			sscanf(curMoneyStr, "%d",&curMoney);										//�����������תΪ����

			if (toupper(*curMoneyStr) == 'N')											//����'N'����ʾ��ҷ���
			{
				drawArg->playerWin = false;												//���������������λ��
				return 1;																//��������൱�ڷ���break
			}

			if (curMoney < 20  || curMoney > drawArg->money)							//���Ϊ���������Ǯ���ԵĻ���ʾ
			{
				printf("���Ľ�Ǯ���벻�����������룺");
			}

		}while (curMoney < 20  || curMoney > drawArg->money);							//�����жϽ�Ǯ���Ƿ���ȷ����ȷѭ��


		drawArg->money -= curMoney;														//��ҽ�Ǯ������ע��Ǯ
		drawArg->moneyTogether += curMoney;												//��Ǯ���е�Ǯ����ע��Ǯ

		comCurMoney = ComputerIntel(drawArg->pokerPack, drawArg->computerHome,(drawArg->step)+1);			//���������ж���ע����

		if (comCurMoney == 0 || drawArg->comMoney < curMoney)							//���Ϊ0��ǰ��Ǯʱ��������
		{
			printf("\n\n�����ѷ���...\n");
			Sleep(3000);																//�ӳ�����Ϊ����ҿ���
			drawArg->playerWin = true;
			return 1;																	//���������൱�ڷ���break
		}
		if (drawArg->comMoney < 20)														//������Ǯ����ʱ���ʤ
		{
			printf("�������Ʋ�...��ϲ����\n");
			system("pause >> endl");
			return 0;																	//�����Ʋ���Ϸ����,�൱����return
		}
		printf("������ע...");															//���������ע
		drawArg->comMoney -= curMoney;													//������Ǯ������ע��
		drawArg->moneyTogether += curMoney;												//��Ǯ���н�Ǯ������ע��
		return 2;
	}else																				//��ҽ�Ǯ����ʱ
	{
		printf("�Բ�����û���㹻�Ľ�Ǯ��..лл���Ĺ���..�������������Ϸѡ��\n");
		system("pause >> endl");
		return 0;																		//��ҽ�Ǯ���㣬�൱�ڷ���return
	}
}

/***************************************************************************
//*  Function   : int ComputerCall(DrawArgument *drawArg)
//*  Description: ��ӡ�����ע�Ľ��溯��
//*  Parameters : DrawArgument *drawArg
//*               װ�д�ӡʱ��Ҫ��Ϣ�Ľṹ��
//*  Returns    : int
//*               ����1Ϊbreak ����2Ϊcontinue ����3Ϊgoto lEnd ����0Ϊreturn
//*  History    : 2010/01/27 create    
//***************************************************************************/

int ComputerCall(DrawArgument *drawArg)
{
	char ope = 0;
	int comCurMoney = 0;
	int curMoney = 0;
	printf("\n\n���ڷ���\n");
	printf("������\n");
	DrawCard(drawArg->pokComput);												//��ӡ��������
	printf("��ң�\n");
	DrawCard(drawArg->pokPlayer);												//��ӡ��ҵ���
	comCurMoney = ComputerIntel(drawArg->pokerPack, drawArg->computerHome,(drawArg->step)+1);					//�������ܣ��ж��Ƿ���ƣ�������

	if(comCurMoney != 0)												//�����ǰ�������ܷ���0����ѡ�����
	{
		if (drawArg->money < 20)												//��ҵ�ǰ�����Ǯ�Բ���20������
		{
			printf("�Բ�����û���㹻�Ľ�Ǯ��..лл���Ĺ���..�������������Ϸѡ��\n");
			system("pause >> endl");
			return 0;															//��ҽ�Ǯ���㣬�൱�ڷ���return
		}
		if (drawArg->comMoney >comCurMoney)										//��ǰ�����Ľ�Ǯ�������ܵõ��Ľ�Ǯ���������ע
		{
			printf("\n\n��������ע:%d\n",comCurMoney);
			drawArg->comMoney -=comCurMoney;									//������Ǯ����ע��Ǯ
			drawArg->moneyTogether += comCurMoney;								//��Ǯ���м�����ע��Ǯ
		}else if (drawArg->comMoney < 20)										//��������Ǯ������20�������Ʋ�
		{
			printf("�����Ѿ��Ʋ�...��ϲ��...\n");
			system("pause >> endl");
			return 0;															//�����Ʋ����൱�ڷ���return
		}else																	//ֻ����20����������ϣ���Ľ�Ǯ��ʱ������ע20
		{
			printf("\n\n��������ע:20\n");
			drawArg->comMoney -=20;												//������ע20
			drawArg->moneyTogether += 20;										//��Ǯ�ؼ�20
		}
	}else
	{
		printf("\n\n�����ѷ���...\n");											//������ܵõ��������comCurMoneyΪ0
		Sleep(3000);															//�ӳ����룬Ϊ����ҿ���
		drawArg->playerWin = true;												//���ʤ
		return 1;																//���������൱�ڷ���break
	}


	printf("�Ƿ��ע��(Y/N)");

	do 
	{
		ope = getchar();
	} while (toupper(ope) != 'N' && toupper(ope) != 'Y');						//���������ַ�

	if (toupper(ope) == 'Y')													//�����ѡ���
	{
		drawArg->money -= comCurMoney;											//��ҽ�Ǯ����
		drawArg->moneyTogether += comCurMoney;									//��Ǯ���н�Ǯ����
		return 2;																//�൱�ڷ���continue
	}else
	{
		drawArg->playerWin = false;												//������ҷ���
		return 1;																//�൱�ڷ���break
	}
}

void DrawAbout()
{
	system("cls");
	printf("\n\n               ������� д�����е�C���԰����� �������\n");
	printf("\n\n          �����С��Ϸ��Ϊѧϰ֮�ã�Դ�������õ��˴����Ķ��ڴ�Ŀ��٣�\n"
		"        ����ʱ��ִ�û�ж�ÿ���ڴ��Ƿ��ͷŽ��и��ٲ��ԣ������½�(��ʵ\n        ����û����ǲ���ÿ�鶼�ͷ��ˣ�д�����ʱ���Ƕ�д���ͷ�)��"
		"����\n        Ϸ��Դ��������еı�̰����߿��ţ�ϣ���Թ��ѧϰC���Ե��ֵ���\n        �а���...\n"
		"        �����Ҷ����С��Ϸ��ʲô�õ��뷨��ϣ�����Ը����ң����ǹ�ͬ\n        ѧϰ����ͬ������\n\n"
		"        �ҵ���ϵ��ʽ��QQ:724240161\n		���䣺wqnnjm@163.com\n\n"
		"                                                    �ٴα�ʾ��л\n\n"
		"                                                    ���ߣ������\n"
		"                                                    2010��2��1��\n"
		"                                                         �ڴ���\n");
	printf("\n        ������������ϼ�ѡ��...");
	system("pause > endl");
}

/***************************************************************************
//*  Function   : void Run()
//*  Description: ��ӡ����ĺ��� ����������ӡ����
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
		printf("\n\n\n\n\n\n\n\n\n\n\n\n                                 ��л����ʹ��...\n\n\n\n");
		Sleep(1000);
		exit(0);
		break;
	default:
		goto loop;
	}
	goto loop;
}