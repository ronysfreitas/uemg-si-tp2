#include <iostream>
#include <stdio.h>
#include "cstdlib"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

const float pesoMaximo = 20.0;                              // Peso maximo da mochila
const int tamanhoItens = 29;                                // Tamanho de itens disponiveis
const int tamanhoPopulacao = 20;                            // Tamanho da população inicial
const int pontoElite = (int)(tamanhoPopulacao*0.4);         // Ponto de Elite (40% população) 
const int pontoCorte = (int)(tamanhoItens*0.4);             // Ponto de Corte (40% itens)
const float taxaCrossover = 100;                            // 100%
const float taxaMutacao = 2.0;                              // 2%
const int qntdInteracoes = 100;                             // Quantidade de Operações

struct item{
    float peso;
    float beneficio;
    string nome;
};

// Itens disponiveis
item itens[tamanhoItens];

struct individuo{
    float peso;
    float beneficio;
    int cromossomo[tamanhoItens];
};

// População Aleatoria
individuo populacao[tamanhoPopulacao];

float calcularPeso(individuo ind){
    float peso_retorno = 0;
    for (int i = 0; i < tamanhoItens; i++){
        if (ind.cromossomo[i] == 1){
            peso_retorno += itens[i].peso;
        }
    }
    return peso_retorno;
}

float calcularBeneficio(individuo ind){
    float beneficio = 0;
    for (int i = 0; i < tamanhoItens; i++){
        if (ind.cromossomo[i] == 1){
            beneficio += itens[i].beneficio;
        }
    }
    return beneficio;
}

individuo gerarIndividuo(){
    // Cria individuo para retornar
    individuo indAux;

    // Preenche aleatoriamente o vetor de cromossomo
    for (int i = 0; i < tamanhoItens; i++){
        indAux.cromossomo[i] = (rand() % 2); // 0 ou 1
    }

    // Atualiza peso e beneficio
    indAux.peso = calcularPeso(indAux);
    indAux.beneficio = (indAux.peso > pesoMaximo) ? 0 : calcularBeneficio(indAux);

    return indAux;
}

void crossover(){
    int moeda = rand() % (int)(100 / taxaCrossover);
    if(moeda == 0){
        for (int filho = pontoElite; filho < tamanhoPopulacao; filho++){
            int pai = rand() % (pontoElite); 
            int mae = rand() % (pontoElite);  
            for(int j = pontoCorte; j < tamanhoItens; j++){   
                int moeda = rand() % 2;
                if (moeda == 1){    
                    populacao[filho].cromossomo[j] = populacao[pai].cromossomo[j];
                } else {        
                    populacao[filho].cromossomo[j] = populacao[mae].cromossomo[j];
                }
            }
        }   
    }
}

void mutacao(){
    for (int filho = pontoElite; filho < tamanhoPopulacao; filho++){ 
        for(int j = 0; j < tamanhoItens; j++){
            if(taxaMutacao != 0){
                int moeda = rand() % (int)(100 / taxaMutacao);
                if(moeda == 0){ 
                    populacao[filho].cromossomo[j] = (populacao[filho].cromossomo[j] == 1) ? 0 : 1;
                }
            }  
        }
    }
}

void avaliar(){
    for (int filho = 0; filho < tamanhoPopulacao; filho++){
        populacao[filho].peso = calcularPeso(populacao[filho]);
        populacao[filho].beneficio = calcularBeneficio(populacao[filho]);
        if (populacao[filho].peso > pesoMaximo){
            populacao[filho].beneficio = 0.0;
        }
    }
}

void ordenar (){
    individuo aux;
    int i, j;

    for(i = 0; i < tamanhoPopulacao; i++){
        for (j = 0; j < tamanhoPopulacao; j++){
            if (populacao[i].beneficio > populacao[j].beneficio){
                // Trocar de lugar para ordenar
                aux = populacao[i];
                populacao[i] = populacao[j];
                populacao[j] = aux;
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    // Preenchendo itens
    itens[0] = {4, 6, "Barraca"};
    itens[1] = {3.5, 8, "Comida"};
    itens[2] = {6, 20, "Agua"};
    itens[3] = {0.10, 4, "Canivete"};
    itens[4] = {0.20, 5, "Repelente"};
    itens[5] = {0.50, 5, "Lanterna"};
    itens[6] = {0.20, 5, "GPS"};
    itens[7] = {0.40, 10, "Telefone Celular"};
    itens[8] = {0.05, 10, "Palitos de Fosforo"};
    itens[9] = {1.5, 7, "Facao"};
    itens[10] = {5, 1, "Cadeira retrátil"};
    itens[11] = {0.9, 10, "Camera fotografica"};
    itens[12] = {1.5, 2, "Roupas"};
    itens[13] = {0.2, 7, "Protetor Solar"};
    itens[14] = {1, 6, "Kit de Primeiros Socorros"};
    itens[15] = {0.2, 1, "MP3 Player"};
    itens[16] = {0.6, 1, "Tablet"};
    itens[17] = {0.4, 3, "Pilhas"};
    itens[18] = {3, 6, "Utensílios de Cozinha"};
    itens[19] = {1.5, 3, "Produtos de Higiene"};
    itens[20] = {1.3, 2, "Par de Botas extra"};
    itens[21] = {0.25, 4, "Sandália"};
    itens[22] = {1.6, 6, "cobertor"};
    itens[23] = {0.1, 10, "Mapa"};
    itens[24] = {0.4, 1, "Ursinho de Pelúcia"};
    itens[25] = {0.08, 0, "Foto da Sogra"};
    itens[26] = {0.1, 10, "Pederneira"};
    itens[27] = {1, 6, "Sinalizadores"};
    itens[28] = {1.3, 3, "Toalhas de Banho e rosto"};

    // Preenchendo e ordenando a população
    for (int i = 0; i < tamanhoPopulacao; i++){
        populacao[i] = gerarIndividuo();
    }
    ordenar();

    // Variáveis para controle
    clock_t inicio = clock();
    int interacoes = 0;
    
    // Rodar o algoritmo por menos de 1 milissegundos
    while (interacoes < qntdInteracoes){

        crossover();

        mutacao();

        avaliar();

        ordenar();

        // Acrecenta as interações do algoritmo
        interacoes++;
    }

    float tempo = (clock() - inicio) / (float) CLOCKS_PER_SEC;


    // Imprimir a melhor solução, ou seja populacao[0]
    /*
    cout<<"\nA melhor solucao possui os seguintes itens: "<<endl;
    for (int i = 0; i < tamanhoItens ; i++){
        if (populacao[0].cromossomo[i] == 1){
            cout << "\n->" << itens[i].nome;
            cout << "\n\t\tPeso: "<< itens[i].peso;
            cout << "\n\t\tBeneficio: " << itens[i].beneficio << endl;
        }
    } */

    cout << "\n";
    cout << "Peso Total: " << populacao[0].peso << endl;
    cout << "Beneficio Total: " << populacao[0].beneficio << endl;
    cout << "Tempo Gasto: " << tempo << endl;

    return 0;
}