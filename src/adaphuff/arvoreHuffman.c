#include "arvoreHuffman.h"

//Função que cria um novo nó e retorna um ponteiro para ele.
no* criarNo()
{
	no *novoNo;
	
	//Aloca memória para o novo nó.
	novoNo = malloc(sizeof(no));
	
	//Se não foi possível alocar o novo nó, exibe mensagem de erro e sai do
	//programa.
	if(novoNo == NULL)
	{
		puts("\n\n");
		printf("Erro ao alocar memoria para um novo no.");
		puts("\n\n");
		
		exit(0);
	}
	
	//Inicializa os dados do nó.
	novoNo->caractere = 0;
	novoNo->peso = 0;
	novoNo->ordem = 0;
	
	//Inicializa os ponteiros do nó.
	novoNo->pai = NULL;
	novoNo->esquerdo = NULL;
	novoNo->direito = NULL;
	
	//Retorna o ponteiro criado.
	return novoNo;
}

//Função que cria uma nova árvore. Árvore deve ser passada como referência.
void criarArvore(AHA *novaAHA)
{
	no *novaRaiz;
	
	//Cria um novo nó que será a raiz da árvore.
	novaRaiz = criarNo();
	
	//Atribui ao novo nó a ordem máxima da árvore.
	novaRaiz->ordem = ORDEM_MAXIMA;
	
	//Transforma o nó raiz em nó NYT.
	novaRaiz->caractere = NYT;
	
	//Ponteiro para a raiz da árvore aponta para o novo nó criado.
	novaAHA->raiz = novaRaiz;
	
	//Inicializa o vetor auxiliar.
	inicializarVetor(novaAHA);
	
	//Inserir o nó raiz no vetor auxiliar.
	inserirEmVetor(novaAHA, novaRaiz);
}


//Função que insere um novo caractere na árvore, no nó NYT. Ao chamá-la deve-se
//saber previamente que o caractere não existe na árvore ainda.
no* inserirNaArvore(AHA *aha, unsigned short caractere)
{
	int posicao;
	no *novoNYT, *antigoNYT, *novoNo;
	
	novoNo = criarNo();
	novoNYT = criarNo();

	//Procurar o nó NYT.
	posicao = procurarEmVetor(*aha, NYT);
	
	//Se não encontrou o nó NYT, exibe mensagem de erro e sai do programa.
	if(aha->vetor[posicao]->caractere != NYT)
	{
		puts("Inconsistencia ao procurar o no NYT durante a insercao de novo caractere.\n");
		exit(0);
	}
	
	//Aponta para o nó NYT, que será expandido.
	antigoNYT = aha->vetor[posicao];
	
	//Criação do novo nó, com o novo caractere.
	novoNo->caractere = caractere;
	novoNo->peso = 1;
	novoNo->ordem = antigoNYT->ordem - 1;
	
	//Criação do novo NYT.
	novoNYT->caractere = NYT;
	novoNYT->ordem = antigoNYT->ordem - 2;
	
	//Transforma o nó NYT antigo em nó interno
	antigoNYT->caractere = NO_INTERNO;
	antigoNYT->esquerdo = novoNYT;
	antigoNYT->direito = novoNo;
	
	//Atualizar os ponteiros de nós pais.
	novoNYT->pai = antigoNYT;
	novoNo->pai = antigoNYT;
	
	//Inserir no vetor auxiliar o novo nó NYT e o nó do novo caractere.
	inserirEmVetor(aha, novoNo);
	inserirEmVetor(aha, novoNYT);
	
	//Retorna o antigo nó NYT, já que os nós abaixo não serão mais manipulados.
	//Esse retorno facilita ao chamar a função atualizarArvore().
	return antigoNYT;
}

//Função que verifica se o nó passado como parâmetro deve ser trocado com outro
//nó.
no* maiorOrdemDaClasse(AHA *aha, no *pesquisado)
{
	no *tmp;
	int i;
	
	tmp = pesquisado;
	
	//Procura em todos os nós da árvore, pelo vetor.
	for(i=0; i<ORDEM_MAXIMA; i++)
	{
		//Se chegar ao final do vetor, o nó não precisa ser trocado.
		if(aha->vetor[i] != NULL)
		{
			//Se o nó pesquisado estiver na mesma classe de peso, mas ordem
			//menor do que o do nó apontado, deve fazer a troca.
			if(aha->vetor[i]->peso == tmp->peso &&
				aha->vetor[i]->ordem > tmp->ordem)
			{
				//Se não for pai do nó pesquisado e não for nó raiz, tmp recebe
				//o nó a ser trocado.
				if(aha->vetor[i] != pesquisado->pai && !ehRaiz(aha->vetor[i]))
					tmp = aha->vetor[i];
			}
		}
		else break;	
	}
	
	//Se não deve ser trocado, retorna NULL.
	if(tmp == pesquisado)
		return NULL;
	//Se deve, retorna o nó encontrado.
	else
		return tmp;
}

//Função que atualiza os pesos e faz trocas de nós da árvore.
void atualizarArvore(AHA *aha, no *noInicial)
{
	no *encontrado, *noAtual;
	
	//Recebe o nó a partir do qual a árvore será atualizada.
	noAtual = noInicial;
	
	//Enquanto não chega ao nó raiz, atualiza nó por nó.
	while(!ehRaiz(noAtual))
	{
		//Verifica se há necessidade de fazer troca de nós.
		encontrado = maiorOrdemDaClasse(aha, noAtual);
		
		//Se não retornou NULL deve trocar o noAtual com outro nó.
		if(encontrado != NULL)
		{
			no *no1, *no2, *paiNo1, *paiNo2;
			unsigned int ordem;
			
			//Atribui os ponteiros auxiliares.
			no1 = noAtual;
			no2 = encontrado;
			paiNo1 = no1->pai;
			paiNo2 = no2->pai;
			
			//Se forem filhos do mesmo pai.
			if(paiNo1 == paiNo2)
			{
				if(paiNo1->direito == no1)
				{
					paiNo1->direito = no2;
					paiNo1->esquerdo = no1;
				}
				else if(paiNo1->esquerdo == no1)
				{
					paiNo1->esquerdo = no2;
					paiNo1->direito = no1;
				}
			}
			//Se não forem filhos do mesmo pai.
			else
			{
				//Troca os nós filhos.
				if(paiNo1->direito == no1)
					paiNo1->direito = no2;
				
				if(paiNo1->esquerdo == no1)
					paiNo1->esquerdo = no2;

				if(paiNo2->esquerdo == no2)
					paiNo2->esquerdo = no1;
				
				if(paiNo2->direito == no2)
					paiNo2->direito = no1;
			}
							
			//Troca os nós pais.
			no1->pai = paiNo2;
			no2->pai = paiNo1;
				
			//Troca as ordens
			ordem = no1->ordem;
			no1->ordem = no2->ordem;
			no2->ordem = ordem;
		}
		
		//Atualiza o peso do nó.
		noAtual->peso++;
		
		//Vai para o nó pai.
		noAtual = noAtual->pai;
	}
}

//Função que escreve em arquivoTemp o caminho na árvore até o nó com o caractere
//passado como parâmetro.
void escreverCaminho(AHA aha, unsigned short caractere, FILE *arquivoTemp)
{
	int posicao, i;
	no *noAtual, *paiNoAtual;
	
	char codigo[12] = "";
	
	//Procura pela existência do caractere no vetor auxiliar.
	posicao = procurarEmVetor(aha, caractere);
	
	//Se o caractere não existe, procura o NYT e escreve o caminho até ele.
	if(aha.vetor[posicao] == NULL)
		posicao = procurarEmVetor(aha, NYT);
	
	//Define o nó de onde partirá o percurso.
	noAtual = aha.vetor[posicao];

	//Enquanto não chegar à raiz, continua percorrendo a árvore.
	while(!ehRaiz(noAtual))
	{
		//Armazena um ponteiro para o nó pai.
		paiNoAtual = noAtual->pai;
		
		if(noAtual == paiNoAtual->direito)
			strcat(codigo,"1");
		else
			strcat(codigo,"0");
		
		noAtual = noAtual->pai;
	}
		
	//Sendo o caminho percorrido de baixo para cima, é necessário fazer a 
	//inversão da string de caminho.
	strrev(codigo);
	
	//Escreve a string no arquivo temporário.
	for(i=0; codigo[i] != '\0'; i++)
		fwrite(&codigo[i], sizeof(unsigned char), 1, arquivoTemp);
		
	//Depois de escrito o caminho, escreve o caractere em binário, se novo.
	
	//Aqui é desfeito o deslocamento antes de escrever, pois para escrever no
	//arquivo destino, os caracteres não podem ser maiores que 255(8 bits),
	//caso contrário seriam necessários mais dois bits (+3 dec) para escrever os
	//caracteres, o que diminuiria o desempenho da compactação.

	//NOTA: NYT, NO_INTERNO e PSEUDO_EOF não são escritos no arquivo destino,
	//somente o caminho até o nó PSEUDO_EOF.
	
	//Se é um caractere novo, escreve os bits do caractere no arquivo.
	if(aha.vetor[posicao]->caractere == NYT)
	{
		int i;
		char byte[8];
		
		//Desfaz o deslocamento.
		caractere -= DESLOCAMENTO;
				
		//Grava os bits no vetor do bit menos pro mais significativo(invertido).
		for(i=7; i>=0; i--)
		{
			byte[i] = (caractere % 2) + 48;
			caractere /= 2;
		}
	
		//Escreve os bits como caracteres no arquivo temporário.
		for(i=0; i<8; i++)
			fwrite(&byte[i], sizeof(unsigned char), 1, arquivoTemp);
	}
}


//Função que retorna 1 se o nó é folha e 0 se é nó interno.
int ehFolha(no *tmp)
{	
	//Se um dos nós filhos é NULL mas o outro não, há inconsistência na árvore.
	if((tmp->direito == NULL && tmp->esquerdo != NULL) ||
		(tmp->direito != NULL && tmp->esquerdo == NULL))
	{
		puts("Inconsistencia de no folha.");
		exit(0);
	}
		
	//Se ambos nós filhos forem NULL, é folha, então retorna 1.
	if(tmp->direito == NULL && tmp->esquerdo == NULL)
		return 1;
	//Se não for, retorna 0.
	else return 0;
}

//Função que retorna 1 se o nó é raiz e 0 se não é.
int ehRaiz(no *tmp)
{
	//Se o nó tiver ordem de nó raiz e o ponteiro pai for NULL, é raiz.
	if(tmp->ordem == ORDEM_MAXIMA)
	{
		if(tmp->pai == NULL)
			return 1;
		//Se o nó raiz não tem pai NULL, há inconsistencia na árvore.
		else
		{
			puts("Inconsistencia de ponteiro pai do no raiz.");
			exit(0);
		}
	}
	//Se não é raiz retorna 0;
	else
		return 0;
}

//Função que imprime os dados do nó passado como parâmetro.
void imprimirNo(no *tmp)
{
	if(tmp != NULL)
	{
		printf("%c(%d) ", tmp->caractere, tmp->caractere);
		printf("p = %d |", tmp->peso);
		printf("o = %d |\n", tmp->ordem);
		
		if(tmp->direito != NULL)
		{
			printf("\t Filho direito: ");
			printf("%c(%d) ", tmp->direito->caractere, tmp->direito->caractere);
			printf("p = %d |", tmp->direito->peso);
			printf("o = %d |\n", tmp->direito->ordem);
			
			printf("\t Filho esquerdo: ");
			printf("%c(%d) ", tmp->esquerdo->caractere, tmp->esquerdo->caractere);
			printf("p = %d |", tmp->esquerdo->peso);
			printf("o = %d |\n", tmp->esquerdo->ordem);
		}
		else
			puts("\t Sem Filhos.");
	}	
}

//Função que conta e imprime a altura da árvore, sendo 0 a altura mínima.
void contarAltura(AHA aha)
{
	int posicao, niveis;
	no *noAtual;
	
	//Procura o no de insercao
	posicao = procurarEmVetor(aha, NYT);

	//Aponta para o no encontrado
	noAtual = aha.vetor[posicao];

	//Inicializa com a altura minima
	niveis = 0;
	
	//Enquanto nao chegar a raiz
	while(noAtual->pai != NULL)
	{			
		//Incrementa o nivel
		niveis++;
		
		//Vai para o no pai
		noAtual = noAtual->pai;
	}
		
	printf("Altura da arvore: %d\n",niveis);
}

no* percorrerArvore(no* noAtual, unsigned char direcao)
{
	if(noAtual->direito != NULL)
	{
		if(direcao == 1)
			noAtual = noAtual->direito;
		else if(direcao == 0)
			noAtual = noAtual->esquerdo;
	}
}



/********************* Funções de manipulação de vetor ************************/


//Função que inicializa o vetor auxiliar.
void inicializarVetor(AHA *aha)
{
	int i;
	
	//Atribui NULO a todas as posições do vetor.
	for(i=0; i<=ORDEM_MAXIMA; i++)
		aha->vetor[i] = NULL;	
}

//Função que insere um novo ponteiro no vetor auxiliar.
void inserirEmVetor(AHA *aha, no *novoNo)
{
	int posicao;
	
	//Recebe a primeira posição vazia do vetor.
	posicao = procurarEmVetor(*aha, novoNo->caractere);
	
	//Posição do vetor aponta para o novo nó.
	if(aha->vetor[posicao] == NULL)
		aha->vetor[posicao] = novoNo;
	else
	{
		//Se a posição encontrada não for vazia.
		puts("Inconsistencia do vetor. Posicao de insercao nao encontrada.");
		exit(0);
	}
			
}

//se o caractere existir, retorna sua posicao no vetor
//senao retorna a primeira posicao vazia

//Função que faz a busca por caracteres no vetor. O deslocamento já deve ter
//sido aplicado ao caractere.
int procurarEmVetor(AHA aha, unsigned short caractere)
{
	int i;  
	
	for(i=0; i<ORDEM_MAXIMA; i++)
	{
		//Se alcançou uma posição vazia ou encontrou o caractere, retorna a 
		//posição do vetor.
		if(aha.vetor[i] == NULL || aha.vetor[i]->caractere == caractere)
			return i;
	}
}

//Função que imprime todos os nós do vetor, na ordem que estão inseridos.
void imprimirVetor(AHA aha)
{
	int i;

	for(i=0; i<ORDEM_MAXIMA; i++)
	{
		if(aha.vetor[i] != NULL)
		{
			printf("vetor[%d] = ",i);
			imprimirNo(aha.vetor[i]);
			puts("");
		}
		else
			break;
	}
}
