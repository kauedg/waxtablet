#include "arvoreHuffman.h"

//Fun��o que cria um novo n� e retorna um ponteiro para ele.
no* criarNo()
{
	no *novoNo;
	
	//Aloca mem�ria para o novo n�.
	novoNo = malloc(sizeof(no));
	
	//Se n�o foi poss�vel alocar o novo n�, exibe mensagem de erro e sai do
	//programa.
	if(novoNo == NULL)
	{
		puts("\n\n");
		printf("Erro ao alocar memoria para um novo no.");
		puts("\n\n");
		
		exit(0);
	}
	
	//Inicializa os dados do n�.
	novoNo->caractere = 0;
	novoNo->peso = 0;
	novoNo->ordem = 0;
	
	//Inicializa os ponteiros do n�.
	novoNo->pai = NULL;
	novoNo->esquerdo = NULL;
	novoNo->direito = NULL;
	
	//Retorna o ponteiro criado.
	return novoNo;
}

//Fun��o que cria uma nova �rvore. �rvore deve ser passada como refer�ncia.
void criarArvore(AHA *novaAHA)
{
	no *novaRaiz;
	
	//Cria um novo n� que ser� a raiz da �rvore.
	novaRaiz = criarNo();
	
	//Atribui ao novo n� a ordem m�xima da �rvore.
	novaRaiz->ordem = ORDEM_MAXIMA;
	
	//Transforma o n� raiz em n� NYT.
	novaRaiz->caractere = NYT;
	
	//Ponteiro para a raiz da �rvore aponta para o novo n� criado.
	novaAHA->raiz = novaRaiz;
	
	//Inicializa o vetor auxiliar.
	inicializarVetor(novaAHA);
	
	//Inserir o n� raiz no vetor auxiliar.
	inserirEmVetor(novaAHA, novaRaiz);
}


//Fun��o que insere um novo caractere na �rvore, no n� NYT. Ao cham�-la deve-se
//saber previamente que o caractere n�o existe na �rvore ainda.
no* inserirNaArvore(AHA *aha, unsigned short caractere)
{
	int posicao;
	no *novoNYT, *antigoNYT, *novoNo;
	
	novoNo = criarNo();
	novoNYT = criarNo();

	//Procurar o n� NYT.
	posicao = procurarEmVetor(*aha, NYT);
	
	//Se n�o encontrou o n� NYT, exibe mensagem de erro e sai do programa.
	if(aha->vetor[posicao]->caractere != NYT)
	{
		puts("Inconsistencia ao procurar o no NYT durante a insercao de novo caractere.\n");
		exit(0);
	}
	
	//Aponta para o n� NYT, que ser� expandido.
	antigoNYT = aha->vetor[posicao];
	
	//Cria��o do novo n�, com o novo caractere.
	novoNo->caractere = caractere;
	novoNo->peso = 1;
	novoNo->ordem = antigoNYT->ordem - 1;
	
	//Cria��o do novo NYT.
	novoNYT->caractere = NYT;
	novoNYT->ordem = antigoNYT->ordem - 2;
	
	//Transforma o n� NYT antigo em n� interno
	antigoNYT->caractere = NO_INTERNO;
	antigoNYT->esquerdo = novoNYT;
	antigoNYT->direito = novoNo;
	
	//Atualizar os ponteiros de n�s pais.
	novoNYT->pai = antigoNYT;
	novoNo->pai = antigoNYT;
	
	//Inserir no vetor auxiliar o novo n� NYT e o n� do novo caractere.
	inserirEmVetor(aha, novoNo);
	inserirEmVetor(aha, novoNYT);
	
	//Retorna o antigo n� NYT, j� que os n�s abaixo n�o ser�o mais manipulados.
	//Esse retorno facilita ao chamar a fun��o atualizarArvore().
	return antigoNYT;
}

//Fun��o que verifica se o n� passado como par�metro deve ser trocado com outro
//n�.
no* maiorOrdemDaClasse(AHA *aha, no *pesquisado)
{
	no *tmp;
	int i;
	
	tmp = pesquisado;
	
	//Procura em todos os n�s da �rvore, pelo vetor.
	for(i=0; i<ORDEM_MAXIMA; i++)
	{
		//Se chegar ao final do vetor, o n� n�o precisa ser trocado.
		if(aha->vetor[i] != NULL)
		{
			//Se o n� pesquisado estiver na mesma classe de peso, mas ordem
			//menor do que o do n� apontado, deve fazer a troca.
			if(aha->vetor[i]->peso == tmp->peso &&
				aha->vetor[i]->ordem > tmp->ordem)
			{
				//Se n�o for pai do n� pesquisado e n�o for n� raiz, tmp recebe
				//o n� a ser trocado.
				if(aha->vetor[i] != pesquisado->pai && !ehRaiz(aha->vetor[i]))
					tmp = aha->vetor[i];
			}
		}
		else break;	
	}
	
	//Se n�o deve ser trocado, retorna NULL.
	if(tmp == pesquisado)
		return NULL;
	//Se deve, retorna o n� encontrado.
	else
		return tmp;
}

//Fun��o que atualiza os pesos e faz trocas de n�s da �rvore.
void atualizarArvore(AHA *aha, no *noInicial)
{
	no *encontrado, *noAtual;
	
	//Recebe o n� a partir do qual a �rvore ser� atualizada.
	noAtual = noInicial;
	
	//Enquanto n�o chega ao n� raiz, atualiza n� por n�.
	while(!ehRaiz(noAtual))
	{
		//Verifica se h� necessidade de fazer troca de n�s.
		encontrado = maiorOrdemDaClasse(aha, noAtual);
		
		//Se n�o retornou NULL deve trocar o noAtual com outro n�.
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
			//Se n�o forem filhos do mesmo pai.
			else
			{
				//Troca os n�s filhos.
				if(paiNo1->direito == no1)
					paiNo1->direito = no2;
				
				if(paiNo1->esquerdo == no1)
					paiNo1->esquerdo = no2;

				if(paiNo2->esquerdo == no2)
					paiNo2->esquerdo = no1;
				
				if(paiNo2->direito == no2)
					paiNo2->direito = no1;
			}
							
			//Troca os n�s pais.
			no1->pai = paiNo2;
			no2->pai = paiNo1;
				
			//Troca as ordens
			ordem = no1->ordem;
			no1->ordem = no2->ordem;
			no2->ordem = ordem;
		}
		
		//Atualiza o peso do n�.
		noAtual->peso++;
		
		//Vai para o n� pai.
		noAtual = noAtual->pai;
	}
}

//Fun��o que escreve em arquivoTemp o caminho na �rvore at� o n� com o caractere
//passado como par�metro.
void escreverCaminho(AHA aha, unsigned short caractere, FILE *arquivoTemp)
{
	int posicao, i;
	no *noAtual, *paiNoAtual;
	
	char codigo[12] = "";
	
	//Procura pela exist�ncia do caractere no vetor auxiliar.
	posicao = procurarEmVetor(aha, caractere);
	
	//Se o caractere n�o existe, procura o NYT e escreve o caminho at� ele.
	if(aha.vetor[posicao] == NULL)
		posicao = procurarEmVetor(aha, NYT);
	
	//Define o n� de onde partir� o percurso.
	noAtual = aha.vetor[posicao];

	//Enquanto n�o chegar � raiz, continua percorrendo a �rvore.
	while(!ehRaiz(noAtual))
	{
		//Armazena um ponteiro para o n� pai.
		paiNoAtual = noAtual->pai;
		
		if(noAtual == paiNoAtual->direito)
			strcat(codigo,"1");
		else
			strcat(codigo,"0");
		
		noAtual = noAtual->pai;
	}
		
	//Sendo o caminho percorrido de baixo para cima, � necess�rio fazer a 
	//invers�o da string de caminho.
	strrev(codigo);
	
	//Escreve a string no arquivo tempor�rio.
	for(i=0; codigo[i] != '\0'; i++)
		fwrite(&codigo[i], sizeof(unsigned char), 1, arquivoTemp);
		
	//Depois de escrito o caminho, escreve o caractere em bin�rio, se novo.
	
	//Aqui � desfeito o deslocamento antes de escrever, pois para escrever no
	//arquivo destino, os caracteres n�o podem ser maiores que 255(8 bits),
	//caso contr�rio seriam necess�rios mais dois bits (+3 dec) para escrever os
	//caracteres, o que diminuiria o desempenho da compacta��o.

	//NOTA: NYT, NO_INTERNO e PSEUDO_EOF n�o s�o escritos no arquivo destino,
	//somente o caminho at� o n� PSEUDO_EOF.
	
	//Se � um caractere novo, escreve os bits do caractere no arquivo.
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
	
		//Escreve os bits como caracteres no arquivo tempor�rio.
		for(i=0; i<8; i++)
			fwrite(&byte[i], sizeof(unsigned char), 1, arquivoTemp);
	}
}


//Fun��o que retorna 1 se o n� � folha e 0 se � n� interno.
int ehFolha(no *tmp)
{	
	//Se um dos n�s filhos � NULL mas o outro n�o, h� inconsist�ncia na �rvore.
	if((tmp->direito == NULL && tmp->esquerdo != NULL) ||
		(tmp->direito != NULL && tmp->esquerdo == NULL))
	{
		puts("Inconsistencia de no folha.");
		exit(0);
	}
		
	//Se ambos n�s filhos forem NULL, � folha, ent�o retorna 1.
	if(tmp->direito == NULL && tmp->esquerdo == NULL)
		return 1;
	//Se n�o for, retorna 0.
	else return 0;
}

//Fun��o que retorna 1 se o n� � raiz e 0 se n�o �.
int ehRaiz(no *tmp)
{
	//Se o n� tiver ordem de n� raiz e o ponteiro pai for NULL, � raiz.
	if(tmp->ordem == ORDEM_MAXIMA)
	{
		if(tmp->pai == NULL)
			return 1;
		//Se o n� raiz n�o tem pai NULL, h� inconsistencia na �rvore.
		else
		{
			puts("Inconsistencia de ponteiro pai do no raiz.");
			exit(0);
		}
	}
	//Se n�o � raiz retorna 0;
	else
		return 0;
}

//Fun��o que imprime os dados do n� passado como par�metro.
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

//Fun��o que conta e imprime a altura da �rvore, sendo 0 a altura m�nima.
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



/********************* Fun��es de manipula��o de vetor ************************/


//Fun��o que inicializa o vetor auxiliar.
void inicializarVetor(AHA *aha)
{
	int i;
	
	//Atribui NULO a todas as posi��es do vetor.
	for(i=0; i<=ORDEM_MAXIMA; i++)
		aha->vetor[i] = NULL;	
}

//Fun��o que insere um novo ponteiro no vetor auxiliar.
void inserirEmVetor(AHA *aha, no *novoNo)
{
	int posicao;
	
	//Recebe a primeira posi��o vazia do vetor.
	posicao = procurarEmVetor(*aha, novoNo->caractere);
	
	//Posi��o do vetor aponta para o novo n�.
	if(aha->vetor[posicao] == NULL)
		aha->vetor[posicao] = novoNo;
	else
	{
		//Se a posi��o encontrada n�o for vazia.
		puts("Inconsistencia do vetor. Posicao de insercao nao encontrada.");
		exit(0);
	}
			
}

//se o caractere existir, retorna sua posicao no vetor
//senao retorna a primeira posicao vazia

//Fun��o que faz a busca por caracteres no vetor. O deslocamento j� deve ter
//sido aplicado ao caractere.
int procurarEmVetor(AHA aha, unsigned short caractere)
{
	int i;  
	
	for(i=0; i<ORDEM_MAXIMA; i++)
	{
		//Se alcan�ou uma posi��o vazia ou encontrou o caractere, retorna a 
		//posi��o do vetor.
		if(aha.vetor[i] == NULL || aha.vetor[i]->caractere == caractere)
			return i;
	}
}

//Fun��o que imprime todos os n�s do vetor, na ordem que est�o inseridos.
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
