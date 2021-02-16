/*
 * HashNode.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */




#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v){
	  if(currSize >= valuesSize)
	        dblArray();
	    values[currSize] = v;
	    currSize++;
}
void hashNode::dblArray() {
	 int dblValuesSize = valuesSize*2;
	    string *dblValues = new string[dblValuesSize];

	    for(int i = 0; i < valuesSize; i++){
	        dblValues[i] = values[i];
	    }
	    delete(values);
	    valuesSize = dblValuesSize;
	    values = dblValues;
}

string hashNode::getRandValue(){
    int randomInt = rand() % currSize;
    return values[randomInt];
}
