#include <vector>
#include <string>

#include "GeneticMLPTuning.h"

using namespace std;

void main(){
	vector<string> options;
    collection.push_back("logistic");
    collection.push_back("sigmoid");
    collection.push_back("identity");

	// 1. Defining the tuner
	GeneticMLPTuning tuner = new GeneticMLPTuning(200,500,0.3);
	tuner.set_input_layer_size(4);
	tuner.set_output_layer_size(1);
	tuner.set_layer_range(4, 16);
	tuner.set_neurons_range(2, 8);
	tuner.set_activation_options(char **options);

	// 2. Verifyigng
	cout << tuner.get_input_layer_size() << '\n';
	cout << tuner.get_output_layer_size() << '\n';
	cout << tuner.get_layer_range() << '\n';
	cout << tuner.get_neurons_range() << '\n';
	cout << tuner.get_activation_option() << '\n';
	return;
}