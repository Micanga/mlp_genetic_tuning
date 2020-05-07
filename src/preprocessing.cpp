#include <iostream> // input/output
#include <fstream>	// manipulação de arquivos

/*
Para informações detalhadas do conjunto de dados: /data/semeion.names
Estruturação dataset:
> X: input matrix
    x_0,0       x_0,1       ...     x_0,255       <--- Representa a primeira imagem
    x_1,0       x_1,1       ...     x_1,255       <--- Representa a segunda imagem
     ...         ...        ...       ...         
    x_1591,0    x,1591,1    ...     x_1591,255

> Y: output matrix

Train/test split (strat)
X_train X_test
Y_train Y_test
*/

using namespace std;

class Data{
	string const path_data;
	int const feature_size, target_size, samples;

public:
	int const **X;
	int const **Y;

	// → Constructors
	Data(int feture_size, int target_size, int samples):
		feature_size{feature_size}, target_size{target_size}, samples{samples}{}

	Data(string path_data, int feture_size, int target_size, int samples):
		path_data{path_data}, feature_size{feature_size}, target_size{target_size}, samples{samples}{}

	// → Public Methods
	string get_path();
	void read_dataset(string path_data, int feture_size, int target_size, int samples);
};

string Data::get_path() { return path_data; }

void Data::read_dataset(string path_data, int feture_size, int target_size, int samples){
	int i, row, col;
	string sample;

	int X[samples][feture_size];
	int Y[samples][target_size];

	ifstream file(path_data); // construtor acossiado ao arquivo

	if (file.is_open()){
		while (getline(file, sample)){ // método do iostream que retorna a primeira linha do buffer e armazena na string destino
			row = 0;

			for (i = 0, col = 0; i < sample.length() & col < feture_size; i += 7, col++)
				X[row][col] = (int)sample[i] - 48;

			for (col = 0; i < sample.length() & col < target_size; i += 2, col++)
				Y[row][col] = (int)sample[i] - 48;

			row++;
		}
	}
	else{cout << "File not found!\n";}

	file.close();
}

int main(int argc, char const *argv[])
{
	string path = "./data/semeion.data";
	//read_dataset("./data/semeion.data",1592,256,1592,10);
	//read(path);

	Data data = Data(path,256,10,1592);

	cout << data.get_path();

	return 0;
}