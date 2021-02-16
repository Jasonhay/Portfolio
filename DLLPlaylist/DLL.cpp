
#include "DLL.hpp"

#include <string>
#include <stdlib.h>

#include "Song.hpp"

using namespace std;


DLL::DLL(){  // constructor - initializes an empty list
	last = NULL;
	first = NULL;
	numSongs = 0;
}
DLL::DLL(string t, string l, int m, int s){  // constructor, initializes a list with one new node with data x
	DNode *n = new DNode (t,l,m,s);
	first = n;
	last = n;
	numSongs=1;
}

DLL::~DLL(){ //destructor
	DNode *current = first;
	DNode *next;

	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}

	last=NULL;
	first=NULL;
	numSongs=0;
}

void DLL::push(string t, string a, int m, int s){
	DNode *n = new DNode(t, a, m, s);

	if(numSongs==0){
		first=n;
		last=first;
	}

	else{
		n->prev =last;
		last->next=n;
		last=n;
	}

	numSongs++;

}

void DLL::printList(){
	DNode *current=first;

	while(current!=NULL){
		current->song->printSong();
		current=current->next;
	}
}

int DLL::remove(string t){
	DNode *current = first;
	DNode *popNode;

	while(current->song->title != t){
		current = current->next;

	}

	cout << "Removing: ";
	current->song->printSong();
	cout << endl;

	if(current->prev == nullptr){ //FIRST ELEMENT
		current->next->prev = NULL;
		first = current->next;
	}
	else if(current->next == nullptr){ //FINAL ELEMENT
		pop();
	}
	else{ //MIDDLE ELEMENTS
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}

	delete current;
	return 0;
}

void DLL::pop(){
	if(first->next == nullptr){
		first = NULL;
		last = NULL;
		numSongs = 0;
	}

	last->prev->next = NULL;
	last = last->prev;
}

void DLL::moveUp(string t){
	DNode *current=first;

	while(current->song->title!=t){
		current=current->next;
	}


	if(current->prev==nullptr){ //when the selected node is first
		last->next=current;     //old last points to current
		current->next->prev=NULL; //new first points to NULL
		first=current->next;  //sets new first
		current->prev=last; //new last points to old last
		last=current;	//sets new last
		current->next=NULL; //new last points to NULL
		last->next=NULL;
	}

	else if(current->prev->prev==nullptr){ //when the selected node is second
		current->next->prev=current->prev;
		current->prev->next=current->next;
		current->next=current->prev;
		current->prev->prev=current;
		current->prev=NULL;
		first=current;
	}

	else if(current->next==nullptr){ //when the selected node is last
		current->prev->prev->next=current;
		current->prev->next=NULL;
		current->next=current->prev;

		DNode *tmp;
		tmp=current->prev->prev;
		current->prev->prev=current;

		last=current->prev;
		current->prev=tmp;

	}


	else{ //when selected node is in the middle (general case)
		current->prev->prev->next=current;

		current->next->prev=current->prev;

		current->prev->next=current->next;

		current->next=current->prev;

		DNode *tmp;
		tmp=current->prev->prev;
		current->prev->prev=current;

		current->prev=tmp;

	}
}

void DLL::moveDown(string t){
	DNode *current = first;

	while(current->song->title != t){
		current = current->next;
	}

	if(current->next == nullptr){ //FINAL ELEMENT
		current->prev->next = NULL;
		last = current->prev;
		first->prev = current;
		current->next = first;
		current->prev = NULL;
		first = current;
	}

	else if(current->next->next==nullptr){ //when the selected node is second to last
		current->prev->next=current->next;
		current->next->prev=current->prev;
		current->prev=current->next;
		current->next->next=current;
		current->next=NULL;
		last=current;
	}

	else if(current->prev==nullptr){ //when the selected node is first
		current->next->next->prev=current;
		current->next->prev=NULL;
		current->prev=current->next;

		DNode *tmp=current->next->next;

		current->next->next=current;

		current->next=tmp;
		first=current->prev;
	}

	else{ //MIDDLE ELEMENTS
		current->next->next->prev=current;

		current->prev->next=current->next;

		current->next->prev=current->prev;

		current->prev=current->next;

		DNode *tmp;
		tmp=current->next->next;
		current->next->next=current;

		current->next=tmp;
	}


}

void DLL::listDuration(int *tm, int *ts){
	DNode *current=first;

	while(current != NULL){
		*tm+=current->song->min;
		*ts+=current->song->sec;
		current = current->next;
	}
}

void DLL::makeRandom(){
	DNode *current=first;
	DNode *random;
	int randIndex;

	for(int i=0;i<numSongs;i++){ //iterates to change the reference node
		random=current;


		randIndex=(rand()%numSongs+1); //sets the amount the random node is away from current

		for(int j=0;j<randIndex;j++){ //gets a random node
			if(random->next==nullptr){
				randIndex=j;
				break;
			}
			random=random->next;

		}

		for(int l=0;l<randIndex;l++){  //moves random to the current node
			moveUp(random->song->title);
		}

	}

	randIndex=(rand()%numSongs)+1;	//randomizes the original first otherwise it would always end up being last
	for(int p=0;p<randIndex;p++){
		moveUp(current->song->title);
	}

	current=first;

	while(current->next!=nullptr) //sets last correctly
		current=current->next;
	last=current;
}







