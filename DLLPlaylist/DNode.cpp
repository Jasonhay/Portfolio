/*
 * DNode.cpp
 *
 *  Created on: Oct 12, 2020
 *      Author: haynb
 */

#include "DNode.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

DNode::DNode(){
	song = new Song();
	prev = NULL;
	next = NULL;
}

DNode::DNode(string s, string a, int lenmin, int lensec){
	song = new Song(s, a, lenmin, lensec);
	next = NULL;
	prev = NULL;
}





