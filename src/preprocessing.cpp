#include <iostream> // input/output
#include <fstream>	// manipulação de arquivos
#include <vector>

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
private:
	string const path_data;
	int const feature_size, target_size, samples;

	// → Private Methods
	void read_dataset();
	void allocation_X_y();

public:
	vector<vector<int>> X, y;

	// → Constructors
	Data(int feature_size, int target_size, int samples):
		feature_size{feature_size}, target_size{target_size}, samples{samples}{allocation_X_y();}

	Data(string path_data, int feature_size, int target_size, int samples):
		path_data{path_data}, feature_size{feature_size}, target_size{target_size}, samples{samples}{
			allocation_X_y();
			//read_dataset();
		}

	// → Public Methods
	string get_path();
	//vector<vector<int>> get_X();
	//vector<vector<int>> get_y();
};

string Data::get_path() { return path_data; }
//vector<vector<int>> Data::get_X() { return X; }
//vector<vector<int>> Data::get_y() { return y; }

void Data::read_dataset(){
	int i, row, col;
	string sample;

	ifstream file(path_data); // construtor acossiado ao arquivo

	if (file.is_open()){
		while (getline(file, sample)){ // método do iostream que retorna a primeira linha do buffer e armazena na string destino
			row = 0;

			for (i = 0, col = 0; i < sample.length() & col < feature_size; i += 7, col++)
				X[row][col] = (int)sample[i] - 48;

			for (col = 0; i < sample.length() & col < target_size; i += 2, col++)
				y[row][col] = (int)sample[i] - 48;

			row++;
		}
	}
	else{cout << "File not found!\n";}

	file.close();
}

//void Data::allocation_X_y(){
//	X.resize(samples);
//	y.resize(samples);
//
//	for(int i=0; i<samples;i++){
//		X[i].resize(feature_size);
//		y[i].resize(target_size);
//	}
//}

void Data::allocation_X_y(){
	vector<vector<int>> Xx(samples);
	vector<vector<int>> yy(samples);

	for(int i=0; i<samples;i++){
		Xx[i].resize(feature_size);
		yy[i].resize(target_size);
	}

	Data::X=Xx;
	Data::y=yy;
}


int main(int argc, char const *argv[]){
	string path = "./data/semeion.data";

	Data data = Data(path,256,10,1592);

	cout << data.get_path() << '\n';
	cout << data.X[0][30] << '\n';

	static int x;

	x=2;
	x=3;

	return 0;
}