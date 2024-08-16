#pragma once
#include<string>


class Player		//Represent a single player
{
public:
	Player(const std::string& n, const char ch) :name(n), move_count(0), input_char(ch) {};	//constructor
	~Player() {};		//destructor

	std::string getName() const;		//return name of player
	int getMovesCount() const;		//return number of moves
	void incremetMove();			//increment number of moves

	std::string convertToString() const;	//convert the attributes of player object in a single string
private:
	const std::string name;
	int move_count;
	const char input_char;
};


