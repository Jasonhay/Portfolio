/*
 * BST.cpp
 *
 *  Created on: Nov 4, 2020
 *      Author: haynb
 */

#include "BST.hpp"
#include <iostream>
using namespace std;


BST::BST() {
	root = NULL;
}
BST::BST(string sarr[]) {
	root = new TNode(sarr);
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}


void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}


void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}

bool BST::insert(string sarr[]){
	TNode *temp = root;
	TNode *insert = new TNode(sarr);

	if(root == NULL){
		root = insert;
		root->height=1;
		return true;
	}
	if(temp->student->last == insert->student->last){
		if(temp->student->first > insert->student->first){

			while(temp){
				if(insert->student->first < temp->student->first){
					if(temp->left)
						temp = temp->left;
					else{
						temp->left = insert;
						insert->parent = temp;
						setHeight(insert, true);
						return true;
					}
				}
				else{
					if(temp->right)
						temp = temp->right;
					else{
						temp->right = insert;
						insert->parent = temp;
						setHeight(insert, true);
						return true;
					}
				}
			}
		}
	}
	while(temp){
		if(insert->student->last < temp->student->last){
			if(temp->left)
				temp = temp->left;
			else{
				temp->left = insert;
				insert->parent = temp;
				setHeight(insert, true);
				return true;
			}
		}
		else{
			if(temp->right)
				temp = temp->right;
			else{
				temp->right = insert;
				insert->parent = temp;
				setHeight(insert, true);
				return true;
			}
		}
	}
	return false;
}

TNode *BST::find(string l, string f){
	TNode *temp = root;
	int count = 0;

	while(temp){
		if(l < temp->student->last){
			if(temp->left){
				temp = temp->left;
				count++;
			}
		}
		else if(l > temp->student->last){
			if(temp->right){
				temp = temp->right;
				count++;
			}
		}
		else{
			if(f < temp->student->first){
				if(temp->left){
					temp = temp->left;
					count++;
				}
			}
			else if(f > temp->student->first){
				if(temp->right){
					temp = temp->right;
					count++;
				}
			}
			return temp;
		}
	}
	return NULL;
}

void BST::printTreeIO(TNode *n){

	if(n!=NULL){
		printTreeIO(n->left);
		n->printNode();
		printTreeIO(n->right);
	}

}

void BST::printTreePre(TNode *n){

	if(n!=NULL){
		n->printNode();
		printTreePre(n->left);
		printTreePre(n->right);
	}

}

void BST::printTreePost(TNode *n){

	if(n!=NULL){
		printTreePost(n->left);
		printTreePost(n->right);
		n->printNode();
	}

}

TNode *BST::removeNoKids(TNode *tmp){
	TNode *trueTmp=tmp;

	if(tmp->parent->left == tmp){
			tmp->parent->left = NULL;
			if(tmp->parent->right == NULL){
				tmp->parent->height = 1;
				setHeight(tmp->parent, true);}
		}
		else{
			tmp->parent->right = NULL;
			if(tmp->parent->left == NULL){
				tmp->parent->height = 1;
				setHeight(tmp->parent, true);}
		}

		delete tmp;

		return trueTmp;
}

TNode *BST::removeOneKid(TNode *tmp, bool leftFlag){
	TNode *parent=tmp->parent;
	TNode *trueTmp=tmp;
	TNode *child;
	bool leftParentFlag;

	if(parent->student->last > tmp->student->last)
		leftParentFlag=true;
	else
		leftParentFlag=false;

	if(leftFlag){
		child=tmp->left;
		if(leftParentFlag){
			parent->left=tmp->left;
			tmp->left->parent = parent;
		}
		else {
			parent->right=tmp->left;
			tmp->left->parent = parent;
		}
	}

	else{
		child=tmp->right;
		if(leftParentFlag){
			parent->left=tmp->right;
			tmp->right->parent = parent;
		}
		else {
			parent->right=tmp->right;
			tmp->right->parent = parent;
		}

	}

	setHeight(parent, true);

	delete tmp;

	return trueTmp;
}

TNode *BST::remove(string s, string l){
	TNode *temp = find(s, l);
	TNode *removedNode = temp;
	TNode *replaced;

	if(temp->left == NULL && temp->right == NULL){
		removedNode = removeNoKids(temp);
	}
	else if((temp->left == NULL) ^ (temp->right == NULL)){
		if(temp->left == NULL)
			removedNode = removeOneKid(temp, false);
		else
			removedNode = removeOneKid(temp, true);
	}
	else{
		replaced = temp;
		temp=temp->left;

		while(temp->right)
			temp=temp->right;

		TNode *tmp = temp;
		removedNode = remove(temp->student->last, temp->student->first);
		replaced->student = tmp->student;
		setHeight(replaced, true);
	}
	return removedNode;
}

void BST::setHeight(TNode *n, bool needBalance){

	TNode *tmp = n;
	while(tmp != NULL)
	{
		if (tmp->left && tmp->right){
			if (tmp->right->height > tmp->left->height)
				tmp->height = tmp->right->height + 1;

			else
				tmp->height = tmp->left->height + 1;
		}

		else if (tmp->left==NULL && tmp->right==NULL)
			tmp->height = 1;

		else if (tmp->left)
			tmp->height = tmp->left->height + 1;

		else if(tmp->right)
			tmp->height = tmp->right->height + 1;


		int balance = getBalance(tmp);
		int childBalance;

		if(needBalance)
		{
			if (balance == 2)
			{
				childBalance = getBalance(tmp->left);

				if (childBalance == 1)
					rotateRight(tmp);

				else if (childBalance == -1){
					rotateLeft(tmp->left);
					rotateRight(tmp);
				}



			}
			else if (balance == -2){

				childBalance = getBalance(tmp->right);

				if (childBalance == -1)
					rotateLeft(tmp);

				else if (childBalance == 1){
					rotateRight(tmp->right);
					rotateLeft(tmp);
				}
			}
		}

	tmp = tmp->parent;

	}

}


int BST::getBalance(TNode *tmp){
	int balance=0;

	if(tmp->left&&tmp->right)
		balance = tmp->left->height - tmp->right->height;

	else if(tmp->left)
		balance = tmp->left->height;

	else if(tmp->right)
		balance = -1*tmp->right->height;

	return balance;

}


TNode *BST::rotateLeft(TNode *temp){

	TNode *child = temp->right;

	if(temp->parent){
		if(temp->parent->left == temp)
			temp->parent->left = child;
		else
			temp->parent->right = child;
	}
	else
		root = child;

	temp->right= child->left;
	child->parent = temp->parent;
	child->left = temp;
	temp->parent = child;

	if(temp->right)
		temp->right->parent = temp;

	else if (temp->right == temp->left)
		temp->height = 1;

    setHeight(temp, false);

	return temp;

}

TNode *BST::rotateRight(TNode *temp){

    TNode *child = temp->left;
	if(temp != root){
		if(temp->parent->left == temp)
			temp->parent->left = child;
		else
			temp->parent->right = child;
	}
	else
		root = child;

	temp->left= child->right;
	child->parent = temp->parent;
	child->right = temp;
	temp->parent = child;

	if(temp->left)
		temp->left->parent = temp;

	else if(temp->right == temp->left)
		temp->height = 1;

	setHeight(temp, false);

	return temp;

}




