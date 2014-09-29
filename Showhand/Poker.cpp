/********************************************************

Copyright (C), 2010-1, �����

File name:  Poker.cpp 

Author:     �����

Version:    1.00

Description: �˿��ļ����˿˵�ϴ�ƺͷ����Լ���������

History:        

�����    2010/01/27       1.0     �����ļ�

**********************************************************/

#include "Poker.h"
#include "Main.h"



/***************************************************************************
//*  Function   : void WashPoker(int **pokerPack)
//*  Description: ϴ�ƺ���
//*  Parameters :  int **pokerPack
//*                ��������ĵ�ַΪ�˽���ָ�������ɵĿռ�
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void WashPoker(int **pokerPack)							//ϴ�ƺ�������Ϊһ�����飬���ٸ��ѿռ䲢�ò���ָ��
{
	int *pokerBreak= (int*)malloc(POKERSIZE*sizeof(int));		//�˿˵Ŀռ����ڷ��ظ�pokerPack (�����������ŵ�λ��)
	int pokerSeq[POKERSIZE];									//��˳�����е���
	int divided = POKERSIZE;									//����ȡ��
	int temp = 0;												//�ݴ�����

	for (int i= 0; i<POKERSIZE; i++)							//��ʼ��˳����
	{
		pokerSeq[i] = i+1;
	}

	srand(GetTickCount());								//�����������

	for (int i = 0; i<POKERSIZE; i++)					//����˳���Ʋ���ȡ��ķ����������ȡ52���࣬�õ�0-51֮�����������Ϊ�ű�ȡ��ֵ������
	{													//Ŀ��λ�ã�������ǰ���1���Ʒ��뵱ǰλ�ã���52��1���´�ȡ51���࣬Ȼ��ȡ50����...
		temp = (rand()%divided);						//����ű�
		*(pokerBreak+i) = pokerSeq[temp];				//ȡֵ����Ŀ��λ��
		pokerSeq[temp] = pokerSeq[divided-1];			//�������Ʒ��뵱ǰȡҲֵ��λ��
		divided--;										//��ȡ�������1
	}

	*pokerPack = pokerBreak;							//ʹָ��ָ����Һ�Ŀռ�
}

/***************************************************************************
//*  Function   : void Deal(int *pokerPack, Poker *pok, int step)
//*  Description: ���ƺ���
//*  Parameters :  Poker *pok
//*                ��ʾ�������
//*				   int *pokerPack
//*				   ����ǰ�����Ƶ�������ָ�봫��
//*				   int step
//*				   Ҫ���Ƶ�λ��
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void Deal(int *pokerPack, Poker *pok, int step)					//���ƣ�pokerPack�е�������1-52����������涨�˿˰�����2 3 4 5 6 7 8 9 10 J Q K A ����2....
{														//��Ӧ�����е�Ԫ��


	if (step >= POKERSIZE)								//���Ƴ���52�ŷ���
	{
		printf("���Ƴ�����");
		return;
	}

	pok->porkNum = (*(pokerPack+step)-1)%13+1;				//�õ���ǰ�Ƶ�ֵ
	pok->porkSuit = (*(pokerPack+step)-1)/13 +3;			//�õ���ɫ��3Ϊ���ң�4Ϊ��Ƭ��5Ϊ�ݻ���6Ϊ����

	switch((*(pokerPack+step)-1)/13)						//�õ���ɫ�Ĵ�С����Ϊ4������Ϊ3���ݻ�Ϊ2����ƬΪ1
	{
	case 0:													//Ϊ0ʱ��ʾ����
		pok->porkSuitNum = 3;								//���ҵ�ֵΪ3
		break;
	case 1:													//Ϊ1ʱ��ʾ��Ƭ
		pok->porkSuitNum = 1;								//��Ƭ��ֵΪ1
		break;
	case 2:													//Ϊ3ʱ��ʾ�ݻ�
		pok->porkSuitNum = 2;								//�ݻ���ֵΪ2
		break;
	case 3:													//Ϊ2ʱ��ʾ����
		pok->porkSuitNum = 4;								//���ҵ�ֵΪ4
		break;
	}

	switch (pok->porkNum)									//�������棬�Ƶ�ֵΪ1��ʾ'2'��13��ʾ'A'
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
//*  Description: ������
//*  Parameters :  Poker **poker
//*                �Ƶ�����
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void SortPoker(Poker **poker)									
{
	Poker *temp = (Poker*)malloc(sizeof(Poker));				//���ڽ�����
	Poker **pokerTemp = (Poker**)malloc(sizeof(Poker*)*POKERCOUNT);		//����ָ������ָ����ʱ�洢5���������Ŀռ�
	for (int i =0; i<POKERCOUNT; i++)									//����5���ƵĿռ�
	{
		*(pokerTemp+i) = (Poker*)malloc(sizeof(Poker));
	}
	int tempOffset = 0;													//���ڼ�¼��ʱ�洢����ƫ�Ƶ���
	Poker *max = NULL;											//��С�Ƶ�ָ��
	for (int i = 0; i<POKERCOUNT && *(poker+i) != NULL; i++)		//�����ķ���max��,��һ������(ѡ��)�ųɴӴ�С������ɫ��ȷ
	{
		max = *(poker+i);										//��ʼmax���Ѹô�ѭ���ĵ�һ���Ƹ�max

		for (int j = i+1; j <POKERCOUNT && *(poker+j) != NULL; j++)					//�ҵ���һ�α���ʱ����
		{
			if ((*(poker+j))->porkNum > max->porkNum)			//�����ǰ���������max�еģ��ѵ�ǰ�ĸ�max
			{
				max = *(poker+j);
			}
			if ((*(poker+j))->porkNum == max->porkNum && (*(poker+j))->porkSuitNum > max->porkSuitNum)		//��������ͬʱ����ɫ�������ɫ����max���ѵ�ǰ�ĸ�max���������ҷ�Ƭ�ݻ�����˳��
			{
				max = *(poker+j);
			}
		}
		memcpy(temp, max, sizeof(Poker));						//����
		memcpy(max, *(poker+i), sizeof(Poker));					//����
		memcpy(*(poker+i), temp, sizeof(Poker));				//��
	}

	tempOffset = 0;												//��ʼ����ʱ�洢��ƫ����

	for (int i = 0,j = 0, k =1; i<POKERCOUNT && *(poker+i) != NULL; i++)				//��2�������2��ѭ��,���ǵ�һ�����ڽ��������������������ʱ��
	{
		j = 0;													//���ڱ�ʾ�뵱ǰλ�õ�ƫ����
		k =	1;													//��־�м���������
		if (*(poker+i+j+1) != NULL && (i+j+1)<POKERCOUNT && (*(poker+i+j))->porkNum == (*(poker+i+j+1))->porkNum)		//����������ľͽ��룬�ж��������м���
		{
			while (*(poker+i+j+1) != NULL && (i+j+1)<POKERCOUNT && (*(poker+i+j))->porkNum == (*(poker+i+j+1))->porkNum)
			{
				k++;
				j++;
			}

			for (int m = 0; m <k; m++)												//�������ĸ��Ƶ���ʱ��ȥ��
			{
				memcpy(*(pokerTemp+tempOffset), *(poker+i+m), sizeof(Poker));		//�������ĸ�������Ϊ��λ����
				tempOffset++;														//������ʱ����д���λ��
				(*(poker+i+m))->porkNum = 0;										//���������Ƶ��Ƶ�ֵ��Ϊ0��Ϊ�������ѭ���ж��ĸ��Ѿ����ƹ���׼��
			}
			i+=(k-1);											//iҲ��Ӧ����ƶ�
		}else
		{
			continue;																//������������Ļ�ֱ���������ں���ĸ���ʱ����и���
		}
		
	}

	for (int i= 0; i<POKERCOUNT;i++)												//�����������Ƹ��Ƶ���ʱ��
	{
		if (*(poker+i) != NULL && (*(poker+i))->porkNum != 0)						//��û�����ƹ������Ƹ��ƹ���
		{
			memcpy(*(pokerTemp+tempOffset), *(poker+i), sizeof(Poker));
			tempOffset++;
		}
	}

	for (int i =0; i<POKERCOUNT && *(poker+i) != NULL; i++)							//���Ѿ��źõ���ʱ������Ϊ��λ���ƻ�ȥ
	{
		memcpy(*(poker+i),*(pokerTemp+i),sizeof(Poker));
	}
	for (int i =0; i<POKERCOUNT; i++)									//�ͷ�5���ƵĿռ�
	{
		free(*(pokerTemp+i));
	}
	free(temp);													//�ͷ���ʱ�ռ�
	free(pokerTemp);											//�ͷ���ʱ�ռ�
}