#pragma once
#include"Player.h"
#include"Board.h"
class Connect_Four_Game
{
public:
	Connect_Four_Game() :p1("X"), p2("0") {};
	~Connect_Four_Game() {};


private:
	Player p1;
	Player p2;

	Board b;
};

