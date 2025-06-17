#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//  Estrutura das paradas de Ônibus - Grafo
typedef struct Ponto{
    int destino;
    struct Ponto *proximo;
}Ponto;

//  Constantes
#define QNTD_PONTOS 700000
#define QNTD_FILA 700000
#define TAM_LINHA 100
#define ARQUIVO_CONEXOES "conexoes_grafo_bfs.csv"

//  Variáveis Globais
Ponto* paradasOnibus[QNTD_PONTOS] = {NULL};
int filaBFS[QNTD_FILA];
int inicioFila, fimFila;

//  Protótipos
void criarTrajeto(int origem, int destino);
void lerConexoesCSV(const char* nome_arquivo);
void mostrarParadasValidas(int quantidade);
void inicializarFila();
void enfileirar(int valor);
int desenfileirar();
int filaVazia();
void buscaEmLargura(int origem, int destino);
void liberarMemoria();

int main(){
    lerConexoesCSV(ARQUIVO_CONEXOES);

    int escolha = 0;
    do{
        printf("\n =>> Rotas de Onibus de Curitiba <<= \n");
        printf("\n[1] Achar menor trajeto entre dois pontos\n[2] Mostrar rotas disponiveis\n[3] Sair\n\nOpcao: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                system("cls");

                int pOrigem, pDestino;
                printf("Insira a parada de origem: ");
                scanf("%d", &pOrigem);
                printf("Insira a parada de destino: ");
                scanf("%d", &pDestino);

                buscaEmLargura(pOrigem, pDestino);

                printf("\n\nAperte qualquer tecla para retornar...");
                getch();
                system("cls");
                break;
            case 2:
                system("cls");

                int quantidade;
                printf("Insira a quantidade de rotas para visualizacao (1 - %d): ", QNTD_PONTOS);
                scanf("%d", &quantidade);

                while(quantidade <= 0 || quantidade > QNTD_PONTOS){
                    printf("Insira uma quantidade valida: ");
                    scanf("%d", &quantidade);
                }

                mostrarParadasValidas(quantidade);

                printf("\n\nAperte qualquer tecla para retornar...");
                getch();
                system("cls");
                break;
            case 3:
                liberarMemoria();
                printf("Memoria liberada com sucesso!\nEncerrando...");
                break;
            default:
                printf("Opcao invalida, tente novamente...");
                break;
        }
    }while(escolha != 3);

    return 0;
}

//  Funções e Procedimentos
void criarTrajeto(int origem, int destino){
    Ponto* novoPonto = (Ponto*) malloc(sizeof(Ponto));

    if(novoPonto == NULL){
        printf("Alocação mal sucedida\nEncerrando...");
        exit(EXIT_FAILURE);
    }

    novoPonto->destino = destino;
    novoPonto->proximo = paradasOnibus[origem];
    paradasOnibus[origem] = novoPonto;
}

void lerConexoesCSV(const char* nome_arquivo){
    FILE* arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo\nSaindo...");
        exit(EXIT_FAILURE);
    }

    char linha[TAM_LINHA];
    int origem, destino;

    fgets(linha, sizeof(linha), arquivo);           //  Pula a primeira linha ("origem destino")

    while(fgets(linha, sizeof(linha), arquivo)){
        if(sscanf(linha, "%d,%d", &origem, &destino) == 2){
            criarTrajeto(origem, destino);          //  Cria a aresta do grafo
        }
    }

    fclose(arquivo);
}

void mostrarParadasValidas(int quantidade){
    if(quantidade <= 0 || quantidade > QNTD_PONTOS){
        printf("Quantidade invalida\n");
        return;
    }

    int mostrados = 0;

    for(int i = 0; i < QNTD_PONTOS && mostrados < quantidade; i++){
        if(paradasOnibus[i] != NULL){
            printf("Ponto %d => ", i);
            Ponto* atual = paradasOnibus[i];
            while(atual != NULL){
                printf("%d ", atual->destino);
                atual = atual->proximo;
            }
            printf("\n");
            mostrados++;
        }
    }
}

void inicializarFila(){
    inicioFila = 0;
    fimFila = 0;
}

void enfileirar(int valor){
    if(fimFila >= QNTD_FILA){
        printf("Erro: fila cheia\n");
        return;
    }
    filaBFS[fimFila++] = valor;
}

int desenfileirar(){
    if(filaVazia() == 1){
        printf("Nao e possivel desenfileirar uma fila vazia.\n");
        return -1;
    }
    return filaBFS[inicioFila++];
}

int filaVazia(){
    return inicioFila == fimFila;
}

void buscaEmLargura(int origem, int destino){
    if(paradasOnibus[origem] == NULL){
        printf("O ponto %d nao existe ou nao ha rotas partindo dele", origem);
        return;
    }

    int* visitado = (int*) calloc(QNTD_PONTOS ,sizeof(int));        //  Alocação das estruturas da bfs
    int* anterior = (int*) malloc(QNTD_PONTOS * sizeof(int));

    if(visitado == NULL || anterior == NULL){                       //  Caso dê erro na alocação
        printf("Erro na alocacao.\n");
        free(visitado);
        free(anterior);
        return;
    }

    for(int i = 0; i < QNTD_PONTOS; i++){
        anterior[i] = -1;
    }

    inicializarFila();
    enfileirar(origem);
    visitado[origem] = 1;

    //  BFS
    while(!filaVazia()){
        int atual = desenfileirar();

        if(atual == destino){
            int* trajeto = (int*) malloc(QNTD_PONTOS*sizeof(int));

            if(trajeto == NULL){                                    //  Caso dê erro na alocação
                printf("Erro na alocacao de memoria para o trajeto.\n");
                free(visitado);
                free(anterior);
                return;
            }

            int tamanho = 0;
            int noAtual = destino;

            while(noAtual != -1){
                trajeto[tamanho++] = noAtual;
                noAtual = anterior[noAtual];
            }

            printf("\nMenor caminho entre a origem e o destino:\n");
            for(int i = tamanho -1; i>=0; i--){
                printf("%d", trajeto[i]);
                if(i != 0){
                    printf(" => ");
                }
            }

            printf("\nTotal de paradas: %d\n", tamanho-1);

            free(trajeto);
            free(visitado);
            free(anterior);
            return;
        }

        //  Verifica vizinhos
        Ponto* vizinho = paradasOnibus[atual];
        while(vizinho != NULL){
            int proximo = vizinho->destino;

            if(proximo >= 0 && proximo < QNTD_PONTOS && !visitado[proximo]){
                visitado[proximo] = 1;
                anterior[proximo] = atual;
                enfileirar(proximo);
            }
            vizinho = vizinho->proximo;
        }
    }

    printf("Nao foi possivel encontrar a menor rota entre %d e %d", origem, destino);

    free(visitado);
    free(anterior);

}

void liberarMemoria(){
    for(int i = 0; i < QNTD_PONTOS; i++){
        Ponto* atual = paradasOnibus[i];
        while(atual != NULL){
            Ponto* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        paradasOnibus[i] = NULL;
    }
}