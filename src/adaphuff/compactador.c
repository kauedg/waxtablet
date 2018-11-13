#include "compactador.h"
#include "arvoreHuffman.h"

//Declarada fora da fun��o para poder retornar seu nome ao final.
char nomeArquivoCompactado[FILENAME_MAX] = "";

char* compactar(char *nomeArquivoOrigem)
{
	//Vari�veis para manipula��o dos arquivos.
	FILE *arquivoTemp, 
		 *arquivoOrigem, 
		 *arquivoDestino;
		
	unsigned short caractere;
	unsigned char chtemp;
	
	int i, j;

	//Estrutura para gera��o de relat�rios.
	struct rel
	{
		fpos_t f_inicio, f_fim;

		float tamanhoOriginal;
		float tamanhoCompactado;

		clock_t t_inicio, t_fim;
		clock_t tempoCompactacao;	

		float porcentagemCompactacao;
	}rel;

	
	//Vari�veis para extra��o da extens�o do arquivo original.
	unsigned char extensao[3] = "", *ext, byte[8], ch;
		
	//Vari�veis para manipula��o da �rvore.
	AHA arvore;
	int posicao;
	no *noAtual; 

/*********************** ABERTURA E CRIA��O DOS ARQUIVOS **********************/
		 
	//In�cio da compacta��o.
	rel.t_inicio = clock();
	
	puts("\n\n");
	printf("Compactando... ");
	
	//Abre arquivo de origem dos dados como leitura.
	arquivoOrigem = fopen(nomeArquivoOrigem, "rb");
  	
  	if(arquivoOrigem == NULL)
  	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeArquivoOrigem);
		puts("\n\n");
		
		exit(0);
	}
	
	//Calcula o tamanho total do arquivo de origem.
	//Marca o in�cio do arquivo.
	fgetpos(arquivoOrigem,&rel.f_inicio);

	//Vai at� o fim do arquivo.
	fseek(arquivoOrigem, 0, SEEK_END);

	//Marca o fim do arquivo.
	fgetpos(arquivoOrigem,&rel.f_fim);

	//Retorna ao in�cio.
	fsetpos (arquivoOrigem,&rel.f_inicio);

	
	//Cria o arquivo tempor�rio.
	arquivoTemp = tmpfile();
  	
  	if(arquivoTemp == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar arquivo temporario.");
		puts("\n\n");
		
		exit(0);
	}		
	
	//Extrai a extens�o do arquivo original e a escreve no arquivo tempor�rio.
		
	//Procura a �ltima ocorr�ncia de "." para encontrar a extens�o.
	ext = strrchr(nomeArquivoOrigem,'.');
	
	//Mudar a extens�o do arquivo de origem.
	strncpy(nomeArquivoCompactado, nomeArquivoOrigem, 
			strlen(nomeArquivoOrigem)- strlen(ext));
	
	strcat(nomeArquivoCompactado,"_compactado");
	strcat(nomeArquivoCompactado,".ahf");
			
	//Gravar a extens�o no in�cio do arquivo compactado.
	strncpy(extensao, ext+1 , strlen(ext));
	
	for(i=0; i<3; i++)
	{
		//Converte caractere por caractere.
		ch = extensao[i];
		
		//Decomp�e o byte do caractere em bits.
		//J� atribui como decimal 0 ou 1 (+48)
		for(j=7; j>=0; j--)
		//for(j=0; j<8; j++)
		{
			byte[j] = (ch % 2) + 48;
			ch /= 2;
		}
		
		byte[8] = '\0';
		
		//Escreve os bits como caracteres no arquivo tempor�rio.
		for(j=7; j>=0; j--)
			fwrite(&byte[j], sizeof(unsigned char), 1, arquivoTemp);
	}
	
	//Criar o arquivo onde os dados compactados ser�o finalmente escritos.
	arquivoDestino = fopen(nomeArquivoCompactado, "wb");
	
	if(arquivoDestino == NULL)
  	{
		puts("\n\n");
		printf("Erro ao abrir %s para gravacao.", nomeArquivoCompactado);
		puts("\n\n");
		
		exit(0);
	}

/*********************** COMPACTA��O ******************************************/

	//Cria �rvore vazia.
	criarArvore(&arvore);
	
	//Inserir o PSEUDO_EOF.
	noAtual = (no*)inserirNaArvore(&arvore, PSEUDO_EOF);
	atualizarArvore(&arvore, noAtual);
		
	//L� os dados at� o final do arquivo tempor�rio.
	while(!feof(arquivoOrigem))
	{			
		//Somente de 0 a 255
		fread(&chtemp,sizeof(unsigned char),1,arquivoOrigem);
		
		//Deslocamento para formata��o � representacao interna.
		caractere = chtemp + DESLOCAMENTO;
		
		if(!feof(arquivoOrigem))
		{	
			//Verifica a exist�ncia do caractere.		
			posicao = procurarEmVetor(arvore, caractere);
			
			//Escreve caminho at� o caractere, se ele j� existir, ou at� o NYT
			//se n�o existir.
			escreverCaminho(arvore, caractere, arquivoTemp);
			
			//Se for um caractere novo, insere-o na �rvore.
			if(arvore.vetor[posicao] == NULL)
				noAtual = (no*)inserirNaArvore(&arvore, caractere);
			else
				noAtual = arvore.vetor[posicao];
			
			//Atualiza os pesos e faz trocas de n�s, se necess�rio.
			atualizarArvore(&arvore, noAtual);
		}
	};
	
	//Escrever o caminho at� o PSEUDO_EOF, sinalizando fim dos dados.
	escreverCaminho(arvore, PSEUDO_EOF, arquivoTemp);	
	
	//Voltar ao in�cio do arquivo tempor�rio.
	rewind(arquivoTemp);
	
	//Converte, de 8 em 8, os 1�s e 0�s do arquivo tempor�rio em byte.
	while(!feof(arquivoTemp))
	{
		int i;
		unsigned char chtmp;
		unsigned char caractere;
		
		caractere = 0;
		
		//L� 8 "bits" e os transforma em um byte.
		for(i=7; i>=0; i--)
		{
			fread(&chtmp, sizeof(unsigned char), 1, arquivoTemp);
			
			if(!feof(arquivoTemp))
				caractere +=  pow(2,i)*(chtmp - 48);
		}
		
		//Escreve o byte obtido.
		fwrite(&caractere, sizeof(unsigned char), 1, arquivoDestino);
	};

	//Fim da compacta��o.
	rel.t_fim = clock();
	
	printf("Terminado!\n\n");
	
	//Fechar os arquivos utilizados
	fclose(arquivoOrigem);
	fclose(arquivoTemp);
	fclose(arquivoDestino);


/*********************** RELAT�RIO ******************************************/
	//Grava o tamanho do arquivo original.
	rel.tamanhoOriginal = rel.f_fim - rel.f_inicio;

	
	//Abrir o arquivo onde os dados compactados foram escritos.
	arquivoDestino = fopen(nomeArquivoCompactado, "rb");

	if(arquivoDestino == NULL)
	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeArquivoCompactado);
		puts("\n\n");

		exit(0);
	}

	//Marca o in�cio do arquivo.
	fgetpos (arquivoDestino,&rel.f_inicio);

	//Vai at� o fim do arquivo.
	fseek(arquivoDestino, 0, SEEK_END);

	//Marca o fim do arquivo.
	fgetpos(arquivoDestino,&rel.f_fim);

	//Fecha o arquivo.
	fclose(arquivoDestino);


	//Grava o tamanho do arquivo compactado.
	rel.tamanhoCompactado = rel.f_fim - rel.f_inicio;

	//Grava o tempo gasto para compacta��o.
	rel.tempoCompactacao = rel.t_fim - rel.t_inicio;
	
	//Calcula a porcentagem de compacta��o.
	rel.porcentagemCompactacao = 100 -
							(rel.tamanhoCompactado * 100) / rel.tamanhoOriginal;

	puts("****************** Compactacao *******************");
	
	printf("Tamanho original do arquivo: %.0f bytes.\n", rel.tamanhoOriginal);
	
	printf("Tamanho compactado: %.0f bytes.\n", rel.tamanhoCompactado);
	
	printf("Porcentagem de compactacao: %.2f%%.\n", rel.porcentagemCompactacao);
	
	printf("Razao de compactacao: 1:%.2f.\n",
									rel.tamanhoOriginal/rel.tamanhoCompactado);
	
	printf("Tempo de compactacao: %.2f segundo(s).\n", (double)rel.tempoCompactacao / CLOCKS_PER_SEC);
	
	puts("\n");
	
	return nomeArquivoCompactado;
}
