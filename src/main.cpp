#include <iostream>
#include <fstream>  
#include <string>
#include <vector>

#include "GeneticMLPTuning.h"

using namespace std;

int main(){
	vector<string> options;
    options.push_back("sgd");
    options.push_back("adam");
    options.push_back("lbfgs");

	// 1. Defining the tuner
	cout << "Initialising the tuner\n";
	GeneticMLPTuning tuner(200,10,0.2);
	tuner.set_input_layer_size(4);
	tuner.set_output_layer_size(1);
	tuner.set_layer_range(2, 6);
	tuner.set_neurons_range(2, 10);
	tuner.set_activation_options(options);

	// 2. Printing the tuner parameters
	tuner.configuration();
	
	// 3. Initialising and showing the current population
	cout << "Initialising the population\n";
	tuner.init_population();
	//tuner.show_population();

	// 4. Running the Genetic Algorithm Tuner
	ofstream outfile ("fitness.csv");
	tuner.run(0.00001);

	return 0;
}