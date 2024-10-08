#include "Player.h"


void Player::setName(const std::string& n)
{
	name = n;
}
std::string Player::getName() const		//return name of player
{
	return name;
}
int Player::getMovesCount() const		//return number of moves
{
	return move_count;
}
void Player::incremetMove()	//increment number of moves
{
	move_count++;
}
std::string Player::convertToString() const	//convert the attributes of player object in a single string
{
	return name +" "+ std::to_string(move_count);
}


char Player::getInputChar() const
{
	return input_char;
}
