#include <stdio.h>

//  Estrutura dos Pontos de Ônibus
typedef struct Ponto{
    int destino;
    struct Ponto *proximo;
}Ponto;

#define QntdPontos 17100
#define QntdFila 17100

//  Declarado globalmente e como null para não ter lixo de memória e ficar acessível em todo o programa
Ponto* paradas[QntdPontos] = {NULL};

//  Protótipos
void criarponto(int origem, int destino);

int main(){
    return 0;
}

//  Funções e Procedimentos
void criarponto(int origem, int destino){
    Ponto* novoPonto = malloc(sizeof(Ponto));

    if(novoPonto == NULL){
        printf("Alocação mal sucedida\nEncerrando...");
        exit(0);
    }

    novoPonto->destino = destino;
    novoPonto->proximo = paradas[origem];
    paradas[origem] = novoPonto;
}