#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>
#include <vector>

using namespace std;

class RegistroValor{

    public:
        void setValue(vector<double>& , double cotacao);

    private:
        string preco;
        double valor;
};

#endif