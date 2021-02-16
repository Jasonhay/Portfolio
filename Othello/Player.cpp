/*
 * Player.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Jason Haynberg and Tim Stumper
 */

#include <iostream>
#include "Player.hpp"
using namespace std;

Player::Player() {
		name="CPU 1";
		color='B';
	}

Player::Player(string name_assignment, char color_assignment){
	name = name_assignment;
	color = color_assignment;
}
