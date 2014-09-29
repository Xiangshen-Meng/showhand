#pragma once


#include "Poker.h"
#include "Main.h"
#include "Judge.h"

int ComputerIntel(int *pokerPack, bool computerHome, int step);					//决定下注大小
int Cheak(Poker **poker1, Poker **poker2);										//决定谁先下注