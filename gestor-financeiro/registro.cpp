#include <iostream>
#include <string>
#include <vector>
#include "registro.h"

using namespace std;

void RegistroValor::setValue(vector <double> &ativo, double cotacao){

    // caso onde o vetor ainda nao foi completamente inicializado
    for (size_t i = 0 ; i < ativo.size() ; i++){

        if (ativo[i] == 0){
            ativo[i] = cotacao;
            return; // sair da funcao pois ja preencheu o valor 
        }
    }

    // caso onde o vetor esta completo com valores anteriores
    if ((ativo.size()-1) > 0){

        for (size_t i = 0 ; i < (ativo.size()-1) ; i++){
            ativo[i] = ativo[i+1];
        }

        ativo[ativo.size()-1] = cotacao;
    }
};
