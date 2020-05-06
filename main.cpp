#include <iostream>

#include "utils.h"

using namespace std;
 
int main(){
	// 0. Variables
	int *dataset;

	// 1. Reading the dataset
	dataset = read_semeion()

	// 2. 
	int i; int j;
	for(i = 0 ; i < NUMBER_OF_IMAGES ; i++){
		cout << '(' << i << ')'; 
		for(j = 0 ; j < SIZE_OF_IMAGES ; j++){
			cout << dataset[i][j];
		}
		cout << '\n';
	}
	return 0;
}