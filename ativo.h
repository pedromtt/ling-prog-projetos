#ifndef ATIVO_H
#define ATIVO_H

#include <string>
#include <vector>

using namespace std;

class Ativo{

    public:
        void setNome(string n);
        string getNome() const;
        vector <double> createAsset();

    private:
        string nome;
};

#endif