#include <iostream> // input/output
#include <fstream> // manipulação de arquivos

/*
Para informações detalhadas do conjunto de dados: /data/semeion.names
Estruturação dataset:
> X: input matrix
    x_0,0       x_0,1       ...     x_0,255       <--- Representa a primeira imagem
    x_1,0       x_1,1       ...     x_1,255       <--- Representa a segunda imagem
     ...         ...        ...       ...         
    x_1592,0    x,1592,1    ...     x_1592,255

> Y: output matrix

Train/test split (strat)
X_train X_test
Y_train Y_test
*/


using namespace std;

int **read_dataset(string path){
    string result;
    double X; //maybe double const
    double **Y;

    ifstream file(path);

    if(file){
        while(getline(file,result)){
            cout << (int)result[0] << '\n';
            break;
        }
    }else{
        cout << "File not found!\n";
    }

    file.close();

    return NULL;
}

void read(string const path){
    ifstream file;

    file.open(path);
}