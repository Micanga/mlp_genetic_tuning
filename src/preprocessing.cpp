#include <iostream> // input/output
#include <fstream> // manipulação de arquivos

/*
!TODO
X: input matrix
Y: output matrix

Train/test split
X_train X_test
Y_train Y_test
*/


using namespace std;

int **read_dataset(string path){
    ifstream file(path);
    string result;

    if(file){
        while(getline(file,result)){
            cout << result[0];
        }
    }else{
        cout << "File not found!";
    }

    return NULL;
}



int main(int argc, char const *argv[]){
    read_dataset("../data/semeion.data");
    return 0;
}