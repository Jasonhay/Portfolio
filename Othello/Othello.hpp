/*
 * Othello.hpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Jason Haynberg and Tim Stumper
 */

#ifndef OTHELLO_HPP_
#define OTHELLO_HPP_

#include <iostream>
#include "Player.hpp"
using namespace std;

class Othello {
	char board[8][8]={};
	int board_size;
	Player p1;
	Player p2;
	int numplayers;

public:
	Othello();
	Othello(string, char);
	Othello(string, char, string, char);
	void makemat();
	void printmat();
	void placepiece(Player);
	int countandflippieces(int, int, Player, bool);
	bool canFlip(int, int, string);
	void ckwin();
	void compplacepiece(Player);
	void playGame();
};



#endif /* OTHELLO_HPP_ */
