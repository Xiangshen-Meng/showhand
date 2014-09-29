/********************************************************

Copyright (C), 2010-1, �����

File name:  ComputerIntel.cpp 

Author:     �����

Version:    1.00

Description: ���ڻ������������㲢ȷ���Ƿ���ƣ��Լ��ķ�����ע

History:        

�����    2010/01/27       1.0     �����ļ�

**********************************************************/

#include "ComputerIntel.h"

/***************************************************************************
//*  Function   : int ComputerIntel(int *pokerPack, bool computerHome, int step)
//*  Description: �жϵ�ǰ�Ƿ�Ӧ�ø���
//*  Parameters :  int *pokerPack
//*                ��ǰ�������˿�
//*				   bool computerHome
//*				   �Ƿ���ׯ��
//*				   int step
//*				   Ӧ���жϼ��ţ������ڼ�����
//*  Returns    : int
//*	              Ӧ�ø�ע�Ĵ�С
//*  History    : 2010/01/27 create    
//***************************************************************************/

int ComputerIntel(int *pokerPack, bool computerHome, int step)							//�жϵ�ǰ�Ƿ�Ӧ�ø��ƣ�����Ҫ��������
{
	int returnValue = 0;																//Ҫ���ص�ֵ

	if (step == 2)																		//��Ϊ�ڶ���ʱ���Ӹ�20
	{
		return 20;
	}

	Poker **playerPoker = (Poker **)malloc(sizeof(Poker *)*6);							//װ��ҵ��ƣ�Ϊ�˴�����6���ƣ�ǰ5��Ϊ�����õ����ƣ����Ϊ�գ���Ϊ������������һ���ƣ�����Judge�ĺ�����Ҫ�Ƶ��������Ϊ��ӦΪNULL����������6��
	Poker **computPoker = (Poker **)malloc(sizeof(Poker *)*5);							//װ��������
	PokerType playerType;																//����������͵Ľṹ��
	PokerType computType;																//�����������͵Ľṹ��

	for (int i= 0; i<5;i++)																//ָ��ȫ����NULL
	{
		*(playerPoker+i) = NULL;
		*(computPoker+i) = NULL;
	}
	*(playerPoker+5) = NULL;

	int flag = 0;																		//��־����������ȡ���Ƶ�λ��

	for (int i =0; i <step; i++)														//���Ʒ������Һͻ�������ʵ�൱���Ƶĸ�������ΪҪ�����ܶ�ԭ�����ƽ��в���
	{
		*(playerPoker+i) = (Poker *)malloc(sizeof(Poker));
		*(computPoker+i) = (Poker *)malloc(sizeof(Poker));

		if (computerHome == true)														//����˳��ͬ����Ϊ˭ׯ�ȷ�˭
		{
			Deal(pokerPack, *(computPoker+i), flag++);							//����ׯ�ȸ�����
			Deal(pokerPack,*(playerPoker+i), flag++);
		}else
		{
			Deal(pokerPack,*(playerPoker+i), flag++);							//���ׯ�ȸ����
			Deal(pokerPack, *(computPoker+i), flag++);
		}
	}

	SortPoker(playerPoker+1);															//��������ƣ����������һ���ƣ���Ϊ������֪����ҵ�һ��
	SortPoker(computPoker);																//���������

	Judge(playerPoker+1,&playerType);													//�ж����ͣ����������һ���ƣ��൱���ж����ĸ��Ƶ����ͣ�������5�ŵ������ŵıȽϴ���һ���������
	Judge(computPoker,&computType);														//�ж����ͻ������Ƶ�����

	while (true)																		//Ϊ��ֻѡһ�ζ����ڱȽ���������ʹ��break,��ʹ�õ�while(true)��û����ѭ������˼
	{																					//���µıȽϾ�Ϊ������n�űȽ���ҵ�n-1��
		if (computType.cardType > playerType.cardType)									//�����������ҵĴ�����30
		{
			returnValue = 30;
			break;
		}else if (computType.cardType < playerType.cardType)							//��������С�����ʱ
		{
			if (computType.maxCardNum >= playerType.maxCardNum && step < 5)				//�������2��ʱ�������ľ�������ұ���ҵĴ󷵻�20
			{
				returnValue = 20;
				break;
			}
			else																		//���2��ʱ��ֻҪ���������Ͳ������ʱ������������0
			{
				return 0;
			}
		}else																			//���������
		{
			if (computType.maxCardNum > playerType.maxCardNum)							//�����ƴ�ʱ��ע25
			{
				returnValue = 25;
				break;
			}
			else if (computType.maxCardNum < playerType.maxCardNum)						//������С���������2�ο��Է���20
			{
				if (step < 5)
				{
					returnValue = 20;
					break;
				}else																	//������С�������2��ʱ����0����
				{
					returnValue = 0;
					break;
				}
			}else
			{
				if (computType.maxCardSuitNum > playerType.maxCardSuitNum)				//����Ҳ���ʱ�����Ҳ�󣬷���20
				{
					returnValue = 20;
					break;
				}else																	//����Ҳ���ʱ�����ɫ���󣬷���0
				{
					returnValue = 0;
					break;
				}
			}
		}
	}

	for(int i =0;i < step; i++)															//�ͷſռ�
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
//*  Description: �жϵ�ǰ˫�����ɼ�����Ĵ�С���Է���˭����ע
//*  Parameters :  Poker **poker1
//*                ��һ���Ƶ�����
//*				   Poker **poker2
//*				   �ڶ����Ƶ�����
//*  Returns    : int
//*				  ����˭����ע1Ϊ��һ��������2Ϊ�ڶ�������
//*  History    : 2010/01/27 create    
//***************************************************************************/
int Cheak(Poker **poker1, Poker **poker2)												//�жϵ�ǰ˫�����ɼ�����Ĵ�С���Է���˭����ע������Ĳ���Ӧ������һ��
{
	Poker **pokerTemp1 = (Poker **)malloc(sizeof(Poker *)*5);							//��2���Ƹ���Ҳ�����Ա�Ƚ�
	Poker **pokerTemp2 = (Poker **)malloc(sizeof(Poker *)*5);							//ͬ���溯������
	PokerType pokerType1;
	PokerType pokerType2;

	for (int i= 0; i<5;i++)
	{
		*(pokerTemp1+i) = NULL;
		*(pokerTemp2+i) = NULL;
	}

	for (int i = 0; i<4 && *(poker1+i) != NULL; i++)									//����2����
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

	if (pokerType1.cardType > pokerType2.cardType)										//��JudegeWin����һ��
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

	for(int i =0;i < 5; i++)															//�ͷ�
	{
		free(*(pokerTemp1+i));
		free(*(pokerTemp2+i));
	}
	free(pokerTemp1);
	free(pokerTemp2);
}