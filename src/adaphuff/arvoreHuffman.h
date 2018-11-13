#include <stdio.h>
#include <stdlib.h>

#define NYT 0 
#define NO_INTERNO 1
#define PSEUDO_EOF 2
#define DESLOCAMENTO 3
#define ORDEM_MAXIMA 512 + DESLOCAMENTO

//Estrutura dos n�s da �rvore.
typedef struct no
{
	unsigned short caractere;
	unsigned int peso;
	unsigned int ordem;
	
	struct no *esquerdo;
	struct no *direito;
	struct no *pai;
	
} no;

//Estrutura da �rvore de Huffman, com o vetor auxiliar e a raiz da �rvore.
typedef struct AHA
{
	no *raiz;
	no *vetor[ORDEM_MAXIMA];
} AHA;

//Fun��es de manipula��o da �rvore.
no* criarNo();
void criarArvore(AHA *novaAHA);
no* inserirNaArvore(AHA *aha, unsigned short caractere);
no* maiorOrdemDaClasse(AHA *aha, no *pesquisado);
void atualizarArvore(AHA *aha, no *noInicial);
void escreverCaminho(AHA aha, unsigned short caractere, FILE *arquivoTemp);
void imprimirNo(no *tmp);
void contarAltura(AHA aha);
no* percorrerArvore(no* noAtual, unsigned char direcao);

//Fun��es de manipula��o do vetor.
void inicializarVetor(AHA *aha);
void inserirEmVetor(AHA *aha, no *novoNo);
int procurarEmVetor(AHA aha, unsigned short caractere);
void imprimirVetor(AHA aha);
