#ifndef _GENETICMLPTUNING_H_
#define _GENETICMLPTUNING_H_

struct MLPParameters {
	int *layers;
	char *activation_function;
};

class GeneticMLPTuning {
	
	MLPParameters *current_archtecture = NULL;
	int input_layer_size = NULL, output_layer_size = NULL;
	int min_layers = NULL, max_layers = NULL;
	int min_neurons = , NULL, max_meurons = NULL;
	char **activation_functions = NULL;

	int max_epoch = NULL;
	int population_size = NULL;
	float mutation_rate = NULL;

	int population_size = NULL;
	float *fitness = NULL;

	public:

		GeneticMLPTuning(int max_e, int pop_size);
		GeneticMLPTuning(int max_e, int pop_size, float mut_rate);

		void set_input_layer_size(int size);
		int get_input_layer_size(int size);

		void set_output_layer_size(int size);
		int get_output_layer_size(int size);

		void set_layer_range(int min, int max);
		int *get_layer_range(int min, int max);

		void set_neurons_range(int min, int max);
		int *get_neurons_range(int min, int max);

		void set_activation_options(char **options);
		char **get_activation_options(char **options);

		void init_population();

}

#endif