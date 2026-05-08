#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>

using namespace std;

struct DadosRanking {
            string nome;
            double mediaAtual;
            bool anormal;
        };

class SistemaFinanceiro{

    public:
        void armazenar(const string& nomeA, const vector<double>& vetorA);
        vector<double>* getVetor(const string& nomeBusca);
        void exibirStatus() const;
        double mediaMovel(const string& nomeAtivo);
        void processarRanking();
        void preverProximoValor(const string& nomeAtivo);

    private:

        struct Registro{
            string nome;
            vector <double> dados;
            vector<double> historicoMedias;
        };

        vector <Registro> repositorio;
};

#endif