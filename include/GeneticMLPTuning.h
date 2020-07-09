#ifndef _GENETICMLPTUNING_H_
#define _GENETICMLPTUNING_H_

#include <string>
#include <vector>

using namespace std;

struct MLPParameters {
	string layers;
	string activation_function;
	int nlayers;
};

class GeneticMLPTuning {
	
	MLPParameters current_archtecture;
	int epoch;
	int input_layer_size, output_layer_size;
	int min_layers, max_layers;
	int min_neurons, max_neurons;
	vector<string> activation_functions;

	int max_epoch;
	int population_size;
	float mutation_rate;

	vector<MLPParameters *> population;
	float *fitness;
	float t0, t1;

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
		vector<MLPParameters *> select_parents(string type);
		void evaluate();
		void crossover(vector<MLPParameters *> parents);
		void mutate();
		void run(float eps);

		void configuration();
		void show_population();
};

#endif