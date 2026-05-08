#include <string>
#include <vector>
#include "ativo.h"

using namespace std;

void Ativo::setNome(string n){
    nome = n;
};

string Ativo::getNome() const{
    return nome;
};

vector <double> Ativo::createAsset(){
    return vector<double> (7, 0.0); //especificando os valores em 0.0 para maior clareza
};