#include <iostream>
#include <string>
#include "sistema.h"

using namespace std;

void SistemaFinanceiro::armazenar(const string& nomeA, const vector<double>& vetorA){
    Registro NovoRegistro; // criando nova struct
    NovoRegistro.nome = nomeA;
    NovoRegistro.dados = vetorA;
    repositorio.push_back(NovoRegistro); // usando push_back() para adicionar mais uma struct ao vetor de structs
};

vector<double>* SistemaFinanceiro::getVetor(const string& nomeBusca){
    for (size_t i = 0; i < repositorio.size(); ++i) {
        if (repositorio[i].nome == nomeBusca) {
            return &repositorio[i].dados; // retorna o endereço do vetor especifico
        }
    }
    return NULL; // se nao achar o nome, retorna nulo
}

void SistemaFinanceiro::exibirStatus() const {
    for (size_t i = 0; i < repositorio.size(); ++i) {
        cout << "\nAtivo: " << repositorio[i].nome << " | Valores: [ ";
        
        // loop para exibir o vetor completo
        for (size_t j = 0; j < repositorio[i].dados.size(); ++j) {
            cout << repositorio[i].dados[j];
            
            // adiciona virgula entre os numeros
            if (j < repositorio[i].dados.size() - 1) {
                cout << ", ";
            }
        }
        cout << " ]" << endl << endl;
    }
};

double SistemaFinanceiro::mediaMovel(const string& nomeAtivo){
    vector<double>* dados = getVetor(nomeAtivo);
    
    // verifica se o ativo existe
    if (dados == NULL) {
        return 0.0;
    }

    double soma = 0.0;
    int valoresValidos = 0;
    int n = 3; // tamanho da janela

    // percorre o vetor de tras para frente (do mais recente para o mais antigo)
    for (int i = (int)dados->size() - 1; i >= 0; i--) {
        if ((*dados)[i] != 0.0) {
            soma += (*dados)[i];
            valoresValidos++;
        }

        // ao encontrar 3 valores válidos, encerra o loop
        if (valoresValidos == n) {
            break;
        }
    }

    // calcula a media apenas com 3 valores validos
    if (valoresValidos == n) {
        return soma / (double)n;
    }

    // saiu do loop com menos de 3 valores, retorna 0
    return 0.0;
}

void SistemaFinanceiro::processarRanking() {
    vector<DadosRanking> listaRanking;

    for (size_t i = 0; i < repositorio.size(); ++i) {
        std::vector<double>& v = repositorio[i].dados;

        // pelo menos 4 valores preenchidos para comparar media movel atual e anterior
        if (v[3] != 0.0) {
            double mediaAtual = (v[6] + v[5] + v[4]) / 3.0;
            double mediaAnterior = (v[5] + v[4] + v[3]) / 3.0;

            // guardar no historico do registro
            repositorio[i].historicoMedias.push_back(mediaAtual);

            // variacao percentual
            double variacao = (mediaAtual - mediaAnterior) / mediaAnterior;
            
            // valor absoluto
            double variacaoAbs = variacao;
            if (variacaoAbs < 0) variacaoAbs *= -1;

            DadosRanking item;
            item.nome = repositorio[i].nome;
            item.mediaAtual = mediaAtual;
            item.anormal = (variacaoAbs > 0.10); // 10%

            listaRanking.push_back(item);
        }
    }

    // ordenacao manual bubble sort por media decrescente
    if (listaRanking.size() > 1) {
        for (size_t i = 0; i < listaRanking.size() - 1; i++) {
            for (size_t j = 0; j < listaRanking.size() - i - 1; j++) {
                if (listaRanking[j].mediaAtual < listaRanking[j+1].mediaAtual) {
                    // troca manual swap
                    DadosRanking temp = listaRanking[j];
                    listaRanking[j] = listaRanking[j+1];
                    listaRanking[j+1] = temp;
                }
            }
        }
    }

    // exibir resultados
    cout << "\n--- RANKING POR MEDIA MOVEL (N=3) ---" << endl;
    if (listaRanking.empty()) {
        cout << "Dados insuficientes nos ativos para gerar ranking." << endl;
        return;
    }

    for (size_t i = 0; i < listaRanking.size(); i++) {
        cout << i + 1 << "o: " << listaRanking[i].nome 
                  << " | Media: " << listaRanking[i].mediaAtual;
        
        if (listaRanking[i].anormal) {
            cout << " [ ALERTA: VARIACAO ANORMAL > 10% ]" << endl;
        }
    }
}

void SistemaFinanceiro::preverProximoValor(const string& nomeAtivo) {
    vector<double>* dados = getVetor(nomeAtivo);
    
    if (dados == NULL) {
        cout << "Ativo nao encontrado." << endl;
        return;
    }

    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    int n = 0;

    // identificar quantos dados reais existem (ignorar zeros iniciais)
    for (size_t i = 0; i < dados->size(); ++i) {
        if ((*dados)[i] != 0.0) {
            double x = (double)n; // Tempo sequencial: 0, 1, 2...
            double y = (*dados)[i];
            
            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
            n++;
        }
    }

    // a regressao linear exige pelo menos 2 pontos para formar uma reta
    if (n < 2) {
        cout << "Dados insuficientes para regressao linear (minimo 2 cotações)." << endl;
        return;
    }

    // calcular o denominador
    double denominador = (n * sumX2) - (sumX * sumX);

    if (denominador == 0) {
        cout << "Erro critico: Divisao por zero no calculo da regressao." << endl;
        return;
    }

    // calcular coeficiente angular (a) e linear (b)
    double a = (n * sumXY - sumX * sumY) / denominador;
    double b = (sumY - a * sumX) / n;

    // estimar o próximo valor
    double proximoX = (double)n;
    double estimativa = (a * proximoX) + b;

    // exibir resultados
    cout << "\n===== PREVISAO DE REGRESSAO LINEAR: " << nomeAtivo << " =====" << endl;
    cout << "Coeficiente Angular (a): " << a << endl;
    cout << "Coeficiente Linear (b) : " << b << endl;
    cout << "Proxima Amostra Estimada: " << estimativa << endl;
    cout << "Equacao da Reta: y = " << a << "x + " << b << endl;
}
