#include "utils.h"
#include <fstream>
#include <string>

int *read_semeion(){
	// 0. Variables
	size_t pos = 0;
	string line, token;
	string::size_type sz;
	int img_counter = 0, pixel_counter = 0;
	int dataset[NUMBER_OF_IMAGES][SIZE_OF_IMAGES];

	// 1. Opening the file
	ifstream datafile("data/semeion.data");

	// 2. Reading the file
	if(datafile.is_open()){
	    while(getline(datafile,line)){
	    	pixel_counter = 0;

			while ((pos = line.find(' ')) != string::npos) {
				token = line.substr(0, pos);
				dataset[img_counter][pixel_counter] = stoi(token,&sz);
				line.erase(0, pos + 1);

				pixel_counter += 1;
			}
			img_counter += 1;
		}
		datafile.close();
	}

	return dataset;
}
