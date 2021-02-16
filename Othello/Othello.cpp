/*
 * Othello.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Jason Haynberg and Tim Stumper
 *
 */

#include <iostream>
#include "Othello.hpp"
using namespace std;

Othello::Othello(){
	board_size=8;
	numplayers=0;
	p1=Player();
	p2=Player("CPU 2", 'O');
}

Othello::Othello(string st1, char c){
	board_size=8;
	numplayers=1;
	p1=Player(st1, c);

	if(c=='B')
		p2=Player("CPU", 'O');
	else
		p2=Player("CPU", 'B');
}

Othello::Othello(string st1, char c, string st2, char c2){
	board_size=8;
	numplayers=2;
	p1=Player(st1, c);
	p2=Player(st2, c2);
}

void Othello::makemat(){
	for(int i=0; i<board_size ; i++)
		for(int j=0; j<board_size; j++)
			board[i][j]='_';

	board[3][4]='B';
	board[4][3]='B';
	board[4][4]='O';
	board[3][3]='O';
}

void Othello::printmat(){
	for(int i=0; i<board_size+1 ; i++) {
		for(int j=0; j<board_size+1; j++) {
			if(i==0&&j==0)
				cout<<" "<<"\t";
			else if(i==0)
				cout<<j-1<<"\t";
			else if(j==0){
				cout<<i-1<<"\t";
			}
			else{
				cout<<board[i-1][j-1]<<"\t";
			}
		}
		cout<<endl;
	}

}

void Othello::placepiece(Player p){
	int x, y;

	do{
		cout<<"Enter the x coordinate: " <<endl;
		cin>>y;
		cout<<"Enter the y coordinate: "<<endl;
		cin>>x;
	}while(x<0 || x>7 || y<0 || y>7 || board[x][y]!='_');

	board[x][y]=p.color;


	if(countandflippieces(x, y, p, true)==0){
		cout<<"Player forfeits turn"<<endl;
		board[x][y]='_';
	}


}

int Othello::countandflippieces(int x, int y, Player p, bool flip_or_not){
	int flippedPieces=0;
	char oppositeColor;

	if(p.color=='B')
		oppositeColor='O';
	else
		oppositeColor='B';

	if(canFlip(x,y, "right")){
		for(int i = (y+1); board[x][i]==oppositeColor ; i++) {
			if(flip_or_not)
				board[x][i]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "left")){
		for(int i = (y-1); board[x][i]==oppositeColor ; i--) {
			if(flip_or_not)
				board[x][i]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "up")){
		cout<<endl;
		for(int i = (x-1); board[i][y]==oppositeColor ; i--) {
			if(flip_or_not)
				board[i][y]=p.color;
			flippedPieces++;
		}

	}

	if(canFlip(x,y, "down")){
		for(int i = (x+1); board[i][y]==oppositeColor ; i++) {
			if(flip_or_not)
				board[i][y]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "upleftdiag")){
		for(int i=(x-1), j = (y-1); board[i][j]==oppositeColor ; i--, j--) {
			if(flip_or_not)
				board[i][j]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "downrightdiag")){
		for(int i=(x+1), j = (y+1); board[i][j]==oppositeColor ; i++, j++) {
			if(flip_or_not)
				board[i][j]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "uprightdiag")){
		for(int i=(x-1), j = (y+1); board[i][j]==oppositeColor ; i--, j++) {
			if(flip_or_not)
				board[i][j]=p.color;
			flippedPieces++;
		}
	}

	if(canFlip(x,y, "downleftdiag")){
		for(int i=(x+1), j = (y-1); board[i][j]==oppositeColor ; i++, j--) {
			if(flip_or_not)
				board[i][j]=p.color;
			flippedPieces++;
		}
	}

	return flippedPieces;
}

bool Othello::canFlip(int x2, int y2, string d){
	bool canFlip=false;


	if(d=="right"){
		for(int i = (y2+1); i < board_size; i++){
			if(board[x2][y2] == board[x2][i])
				canFlip=true;
		}
	}

	if(d=="left"){
		for(int j = (y2-1); j >= 0; j--){
			if(board[x2][y2] == board[x2][j])
				canFlip=true;
		}
	}

	if(d=="up"){
		for(int i = (x2-1); i>=0; i--){
			if(board[x2][y2] == board[i][y2])
				canFlip=true;
		}
	}

	if(d=="down"){
		for(int j = (x2+1); j<board_size ; j++){
			if(board[x2][y2] == board[j][y2])
				canFlip=true;
		}
	}

	if(d=="upleftdiag"){
		for(int i=(x2-1), j = (y2-1); i>=0 ; i--, j--){
			if(board[x2][y2] == board[i][j])
				canFlip=true;
		}
	}


	if(d=="downrightdiag"){
		for(int i=(x2+1), j = (y2+1); i<board_size ; i++, j++){
			if(board[x2][y2] == board[i][j])
				canFlip=true;
		}
	}

	if(d=="uprightdiag"){
		for(int i=(x2-1), j = (y2+1); j<board_size ; i--, j++){
			if(board[x2][y2] == board[i][j])
				canFlip=true;
		}
	}

	if(d=="downleftdiag"){
		for(int i=(x2+1), j = (y2-1); i<board_size ; i++, j--){
			if(board[x2][y2] == board[i][j])
				canFlip=true;
		}
	}


	return canFlip;
}

void Othello::ckwin(){
	int countB = 0, countO = 0;

	for(int i = 0; i < board_size; i ++){
		for(int j = 0; j < board_size; j++){
			if(board[i][j] == 'B')
				countB++;
			else if(board[i][j] == 'O')
				countO++;
		}
	}

	if(countB > countO && p1.color == 'B')
		cout << p1.name << "("<<p2.color<<") won with: " << countB << " versus " << countO << endl;
	else if(countO > countB && p1.color == 'O')
		cout << p1.name <<"("<<p2.color<<")  won with: " << countO << " versus " << countB << endl;

	if(countB > countO && p2.color == 'B')
		cout << p2.name << "("<<p2.color<<") won with: " << countB << " versus " << countO << endl;
	else if(countO > countB && p2.color == 'O')
		cout << p2.name << "("<<p2.color<<") won with: " << countO << " versus " << countB << endl;
}

void Othello::compplacepiece(Player p){
	int maxFlips=0, currentFlips, max_x, max_y;

	for(int i=0; i<board_size; i++){
		for(int j=0; j<board_size; j++){
			if(board[i][j]=='_') {
				board[i][j]=p.color;
				currentFlips=countandflippieces(i, j, p, false);
				if(currentFlips>=maxFlips){
					maxFlips=currentFlips;
					max_x=i;
					max_y=j;

				}
				board[i][j]='_';
			}
		}
	}


	board[max_x][max_y]=p.color;
	countandflippieces( max_x,max_y, p, true);
}

void Othello::playGame(){
    makemat();
    printmat();
    bool play = true;
    int fullsqrs = 0;
    Player p = p1;
    bool whichp = true;
    bool turn = true;

    if (rand()%2 == 0) {  // p1 plays first
    	p = p2;
    	turn = false;
    	whichp = false;
    }


    while ((play) && (fullsqrs < 60)){
    	cout << endl << p.name <<" ("<<p.color<<") choose your square: "<<endl;
        if ((numplayers == 2) || ((numplayers == 1) && turn)){
            placepiece(p);
        }
        else if ((numplayers == 0) || ((numplayers == 1) && (turn == false))){
            compplacepiece(p);

        }
        turn = !turn;
        printmat();
        if (whichp) {
        	p = p2;
        	whichp = false;
        }
        else {
            p=p1;
            whichp = true;
        }
        fullsqrs+=1;
    }

    ckwin();
}
