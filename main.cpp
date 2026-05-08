/*
Programa para gerir multiplos ativos financeiros
Autor: Pedro Mattos
*/

#include <iostream>
#include <string>
#include <vector>
#include "registro.h"
#include "ativo.h"
#include "sistema.h"

using namespace std;

int opcao;

void menu(){
    cout << "========= GESTOR FINANCEIRO =========" << endl;
    cout << "\n1 - Inserir novo ativo" << endl;
    cout << "2 - Inserir novo registro de valor (ativo existente)" << endl;
    cout << "3 - Calcular Media Movel " << endl;
    cout << "4 - Exibir ativos ordenados por Media Movel" << endl;
    cout << "5 - Previsao do proximo valor de ativo" << endl;
    cout << "0 - Sair" << endl;
    cout << "=====================================" << endl;
    cout << "\nEscolha uma opcao: " << endl;
    cin >> opcao;
};

int main(){

    RegistroValor novoValor;
    SistemaFinanceiro sistema;

    do {
        menu();

        switch (opcao){
            case 1:{
                
                cout << "\n1 - Inserir novo ativo" << endl;
                cout << "\nNome do ativo: " << endl;
                
                Ativo novoAtivo;
                string nomeAtivo;
                cin >> nomeAtivo;
                novoAtivo.setNome(nomeAtivo);

                sistema.armazenar(novoAtivo.getNome(), novoAtivo.createAsset());
                cout << "\nAtivo cadastrado!" << endl;
                sistema.exibirStatus();

                break;
            }
            case 2:{
                
                cout << "\n2 - Inserir novo registro de valor (ativo existente)" << endl;
                cout << "Ativo a ser alterado: " << endl;

                string nomeRegistro;
                cin >> nomeRegistro;
                vector<double>* ptrVetor = sistema.getVetor(nomeRegistro);

                if (ptrVetor != NULL) {
                    cout << "Cotacao atual: " << endl;
                    double cotacao;
                    cin >> cotacao;

                    // conteudo de *ptrVetor como referência para novoValor
                    novoValor.setValue(*ptrVetor, cotacao);
                    cout << "Valor cadastrado!" << endl;
                    sistema.exibirStatus();
                } 
                else {
                    cout << "\nErro: Ativo ainda nao foi criado!" << endl << endl;
                }

                break;
            }
            case 3:{
                cout << "3 - Calcular Media Movel " << endl;
                cout << "Escolha o ativo: " << endl;
                string nome;
                cin >> nome;

                double media = sistema.mediaMovel(nome);
                
                if (media > 0) {
                    cout << "Media Movel (N=3) de " << nome << ": " << media << endl << endl;
                } 
                else {
                    cout << "Nao foi possivel calcular a media para " << nome << endl << endl;
                }
                
                break;
            }
            case 4:{

                cout << "4 - Exibir ativos ordenados por Media Movel" << endl;
                sistema.processarRanking();

                break;
            }
            case 5:{
                
                cout << "5 - Previsao do proximo valor de ativo" << endl;
                cout << "Escolha o ativo: " << endl;
                string nome;
                cin >> nome;
                sistema.preverProximoValor(nome);

                break;
            }
            case 0:{
                cout << "\nSaindo do programa..." << endl;
                break;
            }
            default:
                cout << "\nOpcao invalida! Tente novamente.\n" << endl;
        }
    } while (opcao != 0);

    return 0;
}