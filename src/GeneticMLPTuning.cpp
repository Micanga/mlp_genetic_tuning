#include <iostream>
#include <random>
#include <vector>

#include "GeneticMLPTuning.h"

using namespace std;

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = 0.0;
	fitness = new float[pop_size];
};

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size, float mut_rate){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = mut_rate;
	fitness = new float[pop_size];
};

void GeneticMLPTuning::set_input_layer_size(int size){
	input_layer_size = size;
};
int GeneticMLPTuning::get_input_layer_size(){
	return input_layer_size;
};

void GeneticMLPTuning::set_output_layer_size(int size){
	output_layer_size = size;
};
int GeneticMLPTuning::get_output_layer_size(){
	return output_layer_size;
};

void GeneticMLPTuning::set_layer_range(int min, int max){
	min_layers = min;
	max_layers = max;
};
int *GeneticMLPTuning::get_layer_range(){
	int *layer_range = new int[2];
	layer_range[0] = min_layers;
	layer_range[1] = max_layers;
	return layer_range;
};

void GeneticMLPTuning::set_neurons_range(int min, int max){
	min_neurons = min;
	max_neurons = max;
};
int *GeneticMLPTuning::get_neurons_range(){
	int *neurons_range = new int[2];
	neurons_range[0] = min_neurons;
	neurons_range[1] = max_neurons;
	return neurons_range;
};

void GeneticMLPTuning::set_activation_options(vector<string>  options){
	activation_functions = options;
};
vector<string>  GeneticMLPTuning::get_activation_options(){
	return activation_functions;
};

void GeneticMLPTuning::init_population(){
	cout << "| Defining the generator and distributions for the population.\n";
	default_random_engine generator;
	uniform_int_distribution<int> layer_distribution(min_layers,max_layers);
	uniform_int_distribution<int> neurons_distribution(min_neurons,max_neurons);
	uniform_int_distribution<int> activation_func_distributions(0,(int) activation_functions.size()-1);

	for (int i = 0 ; i < population_size ; i++){
		if( i % (int)(0.1*population_size) == 0){
			cout << "\r"; 
			for(int j = 0 ; j < i/(0.1*population_size) ; j++)
				cout << "|"; 
			cout << " " << 10*i/(0.1*population_size) << "%";
		}
		MLPParameters *agent = new MLPParameters;

		// building the layer architecture
		agent->layers.push_back(input_layer_size);

		int number_of_layers = layer_distribution(generator); 
		for (int j = 0 ; j < number_of_layers ; j++){
			int number_of_neurons = neurons_distribution(generator);
			agent->layers.push_back(number_of_neurons);
		}

		agent->layers.push_back(output_layer_size);
		
		// defining the activation function
		int activation_function_index = activation_func_distributions(generator);
		agent->activation_function = activation_functions[activation_function_index];

		population.push_back(agent);
	}
	cout << "\r|||||||||| 100%\n"; 
};

void GeneticMLPTuning::configuration(){
	cout << "|#####\n| Genetic MLP Tuner\n|#####\n"; 
	cout << "| Input Layer Size: " << input_layer_size << '\n';
	cout << "| Output Layer Size: " << output_layer_size << '\n';
	cout << "| Layer Range: " << min_layers << ' ' << max_layers << '\n';
	cout << "| Output Layer Size: " << min_neurons << ' ' << max_neurons << '\n';
	cout << "| Activation Options:\n" ;
	for(int i = 0 ; i < (int) activation_functions.size(); i++)
		cout << "| | " << activation_functions[i] << '\n';
}

void GeneticMLPTuning::show_population(){
	cout << "|#####\n| Genetic MLP Tuner Population\n|#####\n"; 
	for(int i = 0 ; i < population_size ; i++){
		cout << "(" << i << ") ";
		for(int j = 0 ; j < (int) population[i]->layers.size()-1 ; j++)
			cout << population[i]->layers[j] << ":";
		cout << population[i]->layers[population[i]->layers.size()-1];
		cout << " (" << population[i]->activation_function << ")\n";
	}
}