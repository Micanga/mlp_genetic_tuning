#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <sstream>

#include <unistd.h>

#include "GeneticMLPTuning.h"


using namespace std;

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = 0.0;
	epoch = 0;
	t0 = 0.0;
	t1 = 0.0;
	fitness = new float[pop_size];
};

GeneticMLPTuning::GeneticMLPTuning(int max_e, int pop_size, float mut_rate){
	max_epoch = max_e;
	population_size = pop_size;
	mutation_rate = mut_rate;
	epoch = 0;
	t0 = 0.0;
	t1 = 0.0;
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
	cout << "\tDefining the generator and distributions for the population.\n";
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
		agent->layers = to_string(input_layer_size);

		int number_of_layers = layer_distribution(generator); 
		agent->nlayers = number_of_layers;
		for (int j = 0 ; j < number_of_layers ; j++){
			int number_of_neurons = neurons_distribution(generator);
			agent->layers += (','+to_string(int(float(number_of_neurons))));
		}

		agent->layers += ','+to_string(output_layer_size);
		
		// defining the activation function
		int activation_function_index = activation_func_distributions(generator);
		agent->activation_function = activation_functions[activation_function_index];

		population.push_back(agent);
	}
	cout << "\r|||||||||| 100%\n"; 
};

void GeneticMLPTuning::evaluate(){
	cout << "Evaluating...\n";
    fstream fs;
    fs.open("scores.csv", ios::out);
    fs.close();

	for (int i = 0 ; i < population_size ; i++){
 		string command = "python3 src/mlp.py ";
    	command += population[i]->layers + ' ';
		command += population[i]->activation_function;
    	system(command.c_str());
	}

	int count = 0;
	float score;
	ifstream infile("scores.csv");
	while (infile >> score){
    	fitness[count] = score;
		count += 1;
	}
};

vector<MLPParameters *> GeneticMLPTuning::select_parents(string type){
	cout << "Selecting the parents...\n";
	vector<MLPParameters *> parents;
	t1 = 0.0;

	if(type == "random"){
		float sum_of_weight = 0;
		for(int i=0; i < population_size; i++) {
			sum_of_weight += fitness[i];
		}

		for(int i=0; i < 2; i++){
			float rnd = static_cast <float> (rand()) 
				/ (static_cast <float> (RAND_MAX/sum_of_weight));

			float cumm = 0.0;
			for(int j=0; j<population_size; j++){
				cumm += fitness[j];
				if(rnd < cumm){
					parents.push_back(population[j]);
					break;
				}
			}
		}
	}
	else{if(type == "max"){
			float max_1 = 0.0;
			int idx_1 = 0;
			for(int i=0; i < population_size; i++){
				if(max_1 < fitness[i]){
					max_1 = fitness[i];
					idx_1 = i;
				}
			}

			float max_2 = 0.0;
			int idx_2 = 0;
			for(int i=0; i < population_size; i++){
				if(max_2 < fitness[i] and i != idx_1){
					max_2 = fitness[i];
					idx_2 = i;
				}
			}
			parents.push_back(population[idx_1]);
			parents.push_back(population[idx_2]);
		}
		else{
			cout << "ParentsError\n";
			exit(1);
		}
	}
	for(int i = 0 ; i < population_size ; i++)
		t1 += fitness[i];
	t1 /= population_size;
	return parents;
};

void GeneticMLPTuning::crossover(vector<MLPParameters *> parents){
	cout << "Crossing over...\n";
	population.clear();

	for (int i = 0 ; i < population_size - 2; i++){
		unsigned int microseconds = 100000;
		usleep(microseconds);

		MLPParameters *agent = new MLPParameters;

		// building the layer architecture
		int head1 = parents[0]->nlayers;
		int head2 = parents[1]->nlayers;
		while(head1+(parents[0]->nlayers/2) > parents[0]->nlayers-1 or
		 head2+(parents[1]->nlayers/2) > parents[1]->nlayers-1){
			head1 = rand() % parents[0]->nlayers;
			usleep(microseconds);
			head2 = rand() % parents[1]->nlayers;
			usleep(microseconds);
		}
		head1 += 1;
		head2 += 1;

		agent->nlayers = 0;
		agent->layers = to_string(input_layer_size);
		agent->nlayers += 1;
		string s;
		size_t pos = 0;
		string token;
		string delimiter = ",";
		int count = 0;
		int add_layer;
		if(head1 < head2){
			count = 0;
			s = (parents[0]->layers).substr(0,(parents[0]->layers).length());
			add_layer = parents[0]->nlayers/2;//rand() % parents[0]->nlayers/2;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				if(count >= head1 and count <= head1+(add_layer)){
					agent->layers += delimiter + token;
					agent->nlayers += 1;
				}
				s.erase(0, pos + delimiter.length());
				count += 1;
			}

			count = 0;
			s = (parents[1]->layers).substr(0,(parents[1]->layers).length());
			add_layer = parents[1]->nlayers/2;//rand() % parents[1]->nlayers/2;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				if(count >= head2 and count <= head2+(add_layer)){
					agent->layers += delimiter + token;
					agent->nlayers += 1;
				}
				s.erase(0, pos + delimiter.length());
				count += 1;
			}
		}
		else{
			count = 0;
			s = (parents[1]->layers).substr(0,(parents[1]->layers).length());
			add_layer = parents[1]->nlayers/2;//rand() % parents[1]->nlayers/2;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				if(count >= head2 and count <= head2+(add_layer)){
					agent->layers += delimiter+token;
					agent->nlayers += 1;
				}
				s.erase(0, pos + delimiter.length());
				count += 1;
			}

			count = 0;
			s = (parents[0]->layers).substr(0,(parents[0]->layers).length());
			add_layer = parents[0]->nlayers/2;//rand() % parents[0]->nlayers/2;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				if(count >= head1 and count <= head1+(add_layer)){
					agent->layers += delimiter+token;
					agent->nlayers += 1;
				}
				s.erase(0, pos + delimiter.length());
				count += 1;
			}
		}
		agent->layers += delimiter+to_string(output_layer_size);
		agent->nlayers += 1;
		
		// defining the activation function
		float rnd = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		if(rnd < 0.5){
			agent->activation_function = parents[0]->activation_function.substr(0,(parents[0]->activation_function).length()) + '\0';
		}
		else{
			agent->activation_function = parents[1]->activation_function.substr(0,(parents[1]->activation_function).length()) + '\0';
		}

		population.push_back(agent);
	}
	for (int i = 0; i < 2 ; i++)
		population.push_back(parents[i]);
};

void GeneticMLPTuning::mutate(){
	cout << "Mutating...\n";
	unsigned int microseconds = 100000;
	for (int i = 0 ; i < population_size - 2; i++){		
		float rnd = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		usleep(microseconds);
		if(rnd <= mutation_rate){
			cout << "\t Random\n";
			MLPParameters *agent = new MLPParameters;
			default_random_engine generator;
			uniform_int_distribution<int> layer_distribution(min_layers,max_layers);
			uniform_int_distribution<int> neurons_distribution(min_neurons,max_neurons);
			uniform_int_distribution<int> activation_func_distributions(0,(int) activation_functions.size()-1);


			// building the layer architecture
			agent->layers = to_string(input_layer_size);

			int number_of_layers = layer_distribution(generator); 
			agent->nlayers = number_of_layers;
			for (int j = 0 ; j < number_of_layers ; j++){
				int number_of_neurons = neurons_distribution(generator);
				usleep(microseconds);
				agent->layers += (','+to_string(int(float(number_of_neurons))));
			}

			agent->layers += ','+to_string(output_layer_size);
			
			// defining the activation function
			int activation_function_index = activation_func_distributions(generator);
			agent->activation_function = activation_functions[activation_function_index];

			population[i] = agent;
		}
	}
};

void GeneticMLPTuning::run(float eps){
	// 1. Evaluating the population
	GeneticMLPTuning::evaluate();

	// 2. Select the parents for the next generation
	vector<MLPParameters *> parents = GeneticMLPTuning::select_parents("max");

	// 3. Crossing over
	GeneticMLPTuning::crossover(parents);

	// 4. Mutating
	GeneticMLPTuning::mutate();

	// 5. Checking the convergence
 	cout << t1 << ' ' << t0 << ' ' << abs(t1-t0) << ' ' << eps << '\n';


	// a. plotting the fitness curve
	string command = "python3 src/plot.py ";
	ostringstream ss;
	ss << t0;
	command += ss.str();
	system(command.c_str());

 	if(abs(t1 - t0) < eps){
 		cout << "Best architecture:\n";
 		cout << "\t" << parents[0]->layers << ' ' << parents[0]->activation_function << '\n';
 		return;
 	}
 	t0 = t1;
	epoch += 1;

 	run(eps);
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
	cout << "|#########################\n\n";
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
	cout << "|#########################\n\n";
}