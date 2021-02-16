#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1){

	mapSize = 31;
	map = new hashNode*[mapSize];
	for(int index = 0; index < mapSize; index++){map[index] = NULL;}
	first = "";
	numKeys = 0;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;


}
void hashMap::addKeyValue(string k, string v){

	//insert key at correct index (by calling getIndex?)

	int insertIndex = getIndex(k);

	//check 70% fullness

	float fullness = ((float)numKeys/mapSize)*100;

	if(fullness >= 70.0)
		reHash();

	//if((float)numKeys/mapSize>=.7){reHash();}
	//check insertIndex conditions

	if(map[insertIndex] == NULL){
		hashNode *insertNode = new hashNode(k, v);
		map[insertIndex] = insertNode;
		numKeys++;

	}

	else if(map[insertIndex]->keyword == k)
		map[insertIndex]->addValue(v);



}
int hashMap::getIndex(string k){

	int index;

	if(hashfn)
		index = calcHash1(k);

	else
		index = calcHash2(k);

	if(map[index] == NULL)
		return index;

	else if(map[index]->keyword == k)
		return index;

	else{

		if(collfn)
			index = coll1(1, index, k);

		else
			index = coll2(1, index, k);

		hashcoll++;
	}

	return index;

}

int hashMap::calcHash1(string k){

	int length= k.length();

	int key = ((k[0])+(27*k[length/2])+(27*27*k[length-1]));

	return key % mapSize;

}
int hashMap::calcHash2(string k){

    int length= k.length();
	int tot = ((27*k[0])+(27*k[length/2])+(27*k[length-1]));
	int key=0;

	while(tot!=0){
		key+=tot%10;
		tot=tot/10;
	}

	return key % mapSize;

}
void hashMap::getClosestPrime(){

	mapSize = mapSize*2;
	bool isPrime = false;

	while(!isPrime){
		int n = sqrt(mapSize);

		for(int i = 2; i <= n; i++){
			if(mapSize % i == 0){
				mapSize++;
				break;
			}

			if(i == n)
				isPrime = true;
		}
	}

}
void hashMap::reHash(){
	int oldMapSize=mapSize;
	hashNode **oldMap = map;
	getClosestPrime();
	hashNode **newMap = new hashNode *[mapSize];

	for(int i=0; i<mapSize; i++)
		newMap[i] = NULL;

	map=newMap;

	for(int i=0; i<oldMapSize; i++){
		if(oldMap[i] != NULL)
			addKeyValue(oldMap[i]->keyword, oldMap[i]->getRandValue());

		delete(oldMap[i]);
	}

	delete(oldMap);
}
int hashMap::coll1(int h, int i, string k){ //linear probing

	int j = i, insertIndex;

	while(j >= 0){
		if(map[j] == NULL){
			insertIndex = j;
			j = -1;
		}
		else if(map[j]->keyword==k){
			insertIndex = j;
			j=-1;
		}
		else{
			j++;
			collisions++;
		}

		if(j == mapSize)
			j = 0;
	}

	return insertIndex;
}
int hashMap::coll2(int h, int i, string k){ //quadratic probing
	int j = i, insertIndex;

	    while(j >= 0){
	        if(map[j] == NULL){
	            insertIndex = j;
	            j = -1;
	        }
	        else if(map[j]->keyword==k){
	        	 insertIndex = j;
	        	 j = -1;
	        }
	        else{
	            j += h*h;
	            h++;
	            collisions++;
	        }

	        j = j % mapSize;

	    }

	    return insertIndex;


}

int hashMap::findKey(string k){
	int index = getIndex(k);

	if(k != map[index]->keyword)
		index = -1;

	return index;
}

void hashMap::printMap() {
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";}
			cout << endl;
		}
	}
}
