#ifndef _GENETICMLPTUNING_H_
#define _GENETICMLPTUNING_H_

#include <string>
#include <vector>

using namespace std;

struct MLPParameters {
	vector<int> layers;
	string activation_function;
};

class GeneticMLPTuning {
	
	MLPParameters current_archtecture;
	int input_layer_size, output_layer_size;
	int min_layers, max_layers;
	int min_neurons, max_neurons;
	vector<string> activation_functions;

	int max_epoch;
	int population_size;
	float mutation_rate;

	vector<MLPParameters *> population;
	float *fitness;

	public:

		GeneticMLPTuning(int max_e, int pop_size);
		GeneticMLPTuning(int max_e, int pop_size, float mut_rate);

		void set_input_layer_size(int size);
		int get_input_layer_size();

		void set_output_layer_size(int size);
		int get_output_layer_size();

		void set_layer_range(int min, int max);
		int *get_layer_range();

		void set_neurons_range(int min, int max);
		int *get_neurons_range();

		void set_activation_options(vector<string> options);
		vector<string> get_activation_options();

		void init_population();
		vector<MLPParameters *> select_parents();
		void crossover();
		void mutate();
		void run();

		void configuration();
		void show_population();
};

#endif