#include "MLPTunningGA.h"

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = 0.0;
	fitness = new float[pop_size];
}

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size, float mut_rate){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = mut_rate;
	fitness = new float[pop_size];
}

void GeneticMLPTuning::set_input_layer_size(int size){
	input_layer_size = size;
}
int *GeneticMLPTuning::get_input_layer_size(int size){
	return input_layer_size;
}

void GeneticMLPTuning::set_output_layer_size(int size){
	output_layer_size = size;
}
int *GeneticMLPTuning::get_output_layer_size(int size){
	return output_layer_size;
}

void GeneticMLPTuning::set_layer_range(int min, int max){
	min_layers = min;
	max_layers = max;
}
int *GeneticMLPTuning::get_layer_range(int min, int max){
	int *layer_range = new int[2];
	layer_range[0] = min_layers;
	layer_range[1] = max_layers;
	return layer_range;
}

void GeneticMLPTuning::set_neurons_range(int min, int max){
	min_neurons = min;
	max_neurons = max;
}
void GeneticMLPTuning::get_neurons_range(int min, int max){
	int *neurons_range = new int[2];
	neurons_range[0] = min_neurons;
	neurons_range[1] = max_neurons;
	return neurons_range;
}

void GeneticMLPTuning::set_activation_options(char **options){
	activation_functions = options;
}
void GeneticMLPTuning::get_activation_options(char **options){
	return activation_functions;
}

void GeneticMLPTuning::init_population(){
	for (int i = 0 ; i < population_size ; i++){

	}
}