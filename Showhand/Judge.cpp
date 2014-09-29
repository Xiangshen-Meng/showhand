/********************************************************

Copyright (C), 2010-1, XXXXXX

File name:  Main.cpp 

Author:     �����

Version:    1.00

Description: �ж���Ϸ������������������ 

History:        

�����    2010/01/27       1.0     �����ļ�

**********************************************************/

#include "Judge.h"



/***************************************************************************
//*  Function   : void Judge(Poker **poker, PokerType *pokerType)
//*  Description: �ж�5����������ͣ�����������Ե����ڴ�С�ͻ�ɫ����pokerType��
//*  Parameters :  Poker **poker
//*                ָ��5���˿˵�ָ��
//*				   PokerType *pokerType
//*				   �������ж����������С��Ԫ�ط��뵽pokerType��
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

void Judge(Poker **poker, PokerType *pokerType)//�ж�����
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
//*  Description: �ж��ķ���ʤ����true��ʾ��һ��������ʤ������ڶ���ʤ
//*  Parameters :  PokerType *pokerType1
//*                ͨ��Judge�õ���pokerType1��ָ��
//*				   PokerType *pokerType2
//*				   ͨ��Judge�õ���pokerType2��ָ��
//*  Returns    : void
//*  History    : 2010/01/27 create    
//***************************************************************************/

bool JudgeWin(PokerType *pokerType1, PokerType *pokerType2)
{
	if (pokerType1->cardType > pokerType2->cardType)						//cardType���͵�ֵ��ʹ�
	{																		//���һ��,���Կ�����Ԫ�ص�ֵ
		return true;														//���һ�������Կ�Ԫ�صĻ�ɫֵ
	}else if (pokerType1->cardType < pokerType2->cardType)					//����ֵΪtrueΪ��һ��������ʤ��ΪfalseΪ�ڶ���������ʤ
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
//*							   �ж�ͬ��˳
//***************************************************************************

bool IsTongHuaShun(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//���������Ʋ���ͬ��˳��Ϊ���������õģ���Ϊ�����̫����
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
	pokerType->cardType = TongHuaShun;								//����ͬ��˳��Ԫ��Ϊ�����ƺ��仨ɫ
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//������ֵ��pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;				//����������Ļ�ɫ��ֵ��pokerType
	return true;
}

//***************************************************************************
//*							     �ж�ͬ��
//***************************************************************************

bool IsTongHua(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//���������Ʋ���ͬ����Ϊ���������õģ���Ϊ�����̫����
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

	pokerType->cardType = TongHua;									//����Ϊͬ��
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//����ͬ����Ԫ�������������ֵ���仨ɫ�����Խ��Ƶ�ֵ��pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;				//�����Ļ�ɫ��ֵ��pokerType
	return true;
}

//***************************************************************************
//*							  �ж���֦
//***************************************************************************

bool IsTieZhi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+3) == NULL)																					//���Ų���������֦
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
	pokerType->cardType = TieZhi;																			//��֦
	pokerType->maxCardNum = (*(poker+0))->porkNum;															//��֦��4��һ�����Ƶ�ֵΪ����Ԫ��
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//��㸳����ɫ��ֵ
	return true;
}

//***************************************************************************
//*							�жϺ�«
//***************************************************************************

bool IsHuLu(Poker **poker, PokerType *pokerType)
{
	if (*(poker+4) == NULL || *(poker+3) == NULL ||*(poker+2) == NULL)																					//������ʱû�к�«�Ŀ���
	{
		return false;
	}

	if (((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+1))->porkNum) == ((*(poker+2))->porkNum) && 
		((*(poker+3))->porkNum) == (*(poker+4))->porkNum) ||
		((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+2))->porkNum) == ((*(poker+3))->porkNum) && 
		((*(poker+3))->porkNum) == (*(poker+4))->porkNum) )
	{																											//����һ��������һ�����Ǻ�«
		pokerType->cardType = HuLu;																				//��«
		pokerType->maxCardNum = (*(poker+2))->porkNum;															//��«������һ�����Ƶ�ֵΪ����Ԫ��
		pokerType->maxCardSuitNum = (*(poker+2))->porkSuitNum;													//��㸳����ɫ��ֵ
		return true;
	}else
	{
		return false;
	}
}

//***************************************************************************
//*							�ж�˳��
//***************************************************************************

bool IsShunZi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)				//���������Ʋ���˳�ӣ�Ϊ���������õģ���Ϊ�����̫����
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
	pokerType->cardType = ShunZi;								//����˳�ӵ�Ԫ��Ϊ�����ƺ��仨ɫ
	pokerType->maxCardNum = (*(poker+0))->porkNum;					//������ֵ��pokerType
	pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;			//����������Ļ�ɫ��ֵ��pokerType
	return true;
}

//***************************************************************************
//*							�ж�����
//***************************************************************************

bool IsSanTiao(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)
	{
		return false;
	}

	if ((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+1))->porkNum) == ((*(poker+2))->porkNum))
	{																											//����һ������������һ����������
		pokerType->cardType = SanTiao;																				//����
		pokerType->maxCardNum = (*(poker+0))->porkNum;															//����������һ�����Ƶ�ֵΪ����Ԫ��
		pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//��㸳����ɫ��ֵ
		return true;
	}
	return false;
}

//***************************************************************************
//*							�ж�����
//***************************************************************************

bool IsLiangDui(Poker **poker, PokerType *pokerType)
{
	if (*(poker+3) == NULL)
	{
		return false;
	}
	if ((*(poker+0))->porkNum == ((*(poker+1))->porkNum) && 
		((*(poker+2))->porkNum) == ((*(poker+3))->porkNum))
	{																											//���Ե�����
		pokerType->cardType = LiangDui;																			//����
		pokerType->maxCardNum = ((*(poker+0))->porkNum*100+((*(poker+2))->porkNum));							//���Ե���4λ������ΪҪ�ȱȽϵ�һ���ڴ�С��һ���˿��ڶ��ԣ���һ���ſ���һ�Ի�ɫ�Ĵ�С
		pokerType->maxCardSuitNum = (*(poker+0))->porkSuitNum;													//ȡ����Ķ��еĻ�ɫ��ֵ
		return true;
	}
	return false;
}

//***************************************************************************
//*							�ж϶���
//***************************************************************************

bool IsDuiZi(Poker **poker, PokerType *pokerType)
{
	if (*(poker+2) == NULL)
	{
		return false;
	}

	if((*(poker+0))->porkNum == ((*(poker+1))->porkNum))														//����Ҳ����
	{
		pokerType->cardType = DuiZi;																			//����
		pokerType->maxCardNum = (*(poker+0))->porkNum*100+((*(poker+2))->porkNum);								//����Ҳ����λ����ΪҪ�Ƚϵ�һ�ԵĴ�С����ͬ����2�����ŵĴ�С����һ������ɫ
		pokerType->maxCardSuitNum = ((*(poker+2))->porkSuitNum);												//ȡ�����ŵĻ�ɫ��ֵ
		return true;
	}
	return false;
}

//***************************************************************************
//*							�ж�ɢ��
//***************************************************************************

bool IsSanPai(Poker **poker, PokerType *pokerType)
{
	pokerType->cardType = SanPai;																				//ɢ��
	pokerType->maxCardNum = ((*(poker+0))->porkNum);															//�����ƾ��Ǿ�����Ԫ��
	pokerType->maxCardSuitNum = ((*(poker+0))->porkSuitNum);													//�����ƵĻ�ɫ��ֵ
	return true;
}