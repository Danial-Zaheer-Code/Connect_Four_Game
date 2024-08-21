#pragma once
#include<string>


class Player		//Represent a single player
{
public:
	Player(const char ch) :name("\0"), move_count(0), input_char(ch) {};	//constructor
	~Player() {};		//destructor

	void setName(const std::string& n);
	std::string getName() const;		//return name of player
	int getMovesCount() const;		//return number of moves
	char getInputChar() const;
	void incremetMove();			//increment number of moves

	std::string convertToString() const;	//convert the attributes of player object in a single string
private:
	std::string name;
	int move_count;
	char input_char;
};


