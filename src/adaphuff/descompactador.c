#include "descompactador.h"
#include "arvoreHuffman.h"

void descompactar(char *nomeArquivoCompactado)
{
	//Variáveis para manipulação dos arquivos.
	FILE *arquivoCompactado, 
		 *arquivoTemp, 
		 *arquivoDestino;
	
	char nomeArquivoDestino[FILENAME_MAX] = "";
	int i, j;

	//Estrutura para geração de relatórios.
	struct rel
	{
		fpos_t f_inicio, f_fim;

		float tamanhoCompactado;
		float tamanhoOriginal;

		clock_t t_inicio, t_fim;
		clock_t tempoDescompactacao;	

		float porcentagemCompactacao;
	}rel;
	
	//Variáveis para extração da extensão do arquivo compactado.
	unsigned char *ext, extensao[3] = "", byte, ch; 
	
	//Variáveis para manipulação da árvore.
	AHA arvore;
	no* noAtual;
	
	
/***************ABERTURA E CRIAÇÃO DOS ARQUIVOS********************************/

	//Início da descompactação.
	rel.t_inicio = clock();

	puts("\n\n");
	printf("Descompactando... ");

	//Abre o arquivo compactado.
	arquivoCompactado = fopen(nomeArquivoCompactado, "rb");
  	
  	if(arquivoCompactado == NULL)
  	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeArquivoCompactado);
		puts("\n\n");
		
		exit(0);
	}

	//Calcula o tamanho total do arquivo compactado.

	//Marca o início do arquivo.
	fgetpos(arquivoCompactado,&rel.f_inicio);

	//Vai até o fim do arquivo.
	fseek(arquivoCompactado, 0, SEEK_END);

	//Marca o fim do arquivo.
	fgetpos(arquivoCompactado,&rel.f_fim);

	//Retorna ao início.
	fsetpos (arquivoCompactado,&rel.f_inicio);

	
	//Cria arquivo temporário.
	arquivoTemp = tmpfile();
  	
  	if(arquivoTemp == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar arquivo temporario.");
		puts("\n\n");
		
		exit(0);
	}
	
	//Recupera a extensão do arquivo compactado.
	for(i=0; i<3; i++)
	{			
		//Lê 1 byte.
		fread(&byte, sizeof(unsigned char), 1, arquivoCompactado);
		
		ch = 0;
		
		for(j=7; j>=0; j--)
		{	
			ch += pow(2,j)* (byte % 2);
			byte /= 2;
		}
		
		extensao[i] = ch;
	}
	
	//Insere o caractere de fim de string.
	extensao[3] = '\0';
	
	//Procura a última incidência de '.' .
	ext = strrchr(nomeArquivoCompactado,'.');
	
	//Muda a extensão do arquivo compactado.
	strncpy(nomeArquivoDestino, nomeArquivoCompactado, 
			strlen(nomeArquivoCompactado)- strlen(ext));
			
	//Adiciona o sufixo "_compactado" ao nome do arquivo descompactado.
	strcat(nomeArquivoDestino,"_descompactado.");

	//Adiciona a extensão original do arquivo.
	strcat(nomeArquivoDestino,extensao);
	
	//Lê o arquivo compactado até o final e converte os bytes em bits (como caracteres).
	while(!feof(arquivoCompactado))
	{
		unsigned char byteInverso;
		unsigned char byte[8];
		
		//Lê 1 byte para decompô-lo.
		fread(&byteInverso, sizeof(unsigned char), 1, arquivoCompactado);
		
		if(!feof(arquivoCompactado))
		{
			int i;
			
			//Decompõe o byte em bits.
			for(i=7; i>=0; i--)
			{	
				byte[i] = byteInverso % 2;
				byteInverso /= 2;
			}
			
			//Grava os bits no arquivo temporário.
			for(i=0; i<8; i++)
				fwrite(&byte[i], sizeof(unsigned char), 1, arquivoTemp);
		}
	}

	//Fecha o arquivo compactado.
	fclose(arquivoCompactado);

	//Volta ao início do arquivo temporário.
	rewind(arquivoTemp);
	
	//Cria o arquivo de destino onde os dados descompactados serão restaurados.
	arquivoDestino = fopen(nomeArquivoDestino, "wb");
	if(arquivoDestino == NULL)
  	{
		puts("\n\n");
		printf("Erro ao abrir %s para gravacao.", nomeArquivoDestino);
		puts("\n\n");
		
		exit(0);
	}
	
/************************** DESCOMPACTAÇÃO ************************************/

	//Cria uma árvore
	criarArvore(&arvore);
	
	//Insere o PSEUDO_EOF.
	noAtual = (no*)inserirNaArvore(&arvore, PSEUDO_EOF);
	atualizarArvore(&arvore, noAtual);
	
	//Lê os dados até o final do arquivo temporário.
	while(!feof(arquivoTemp))
	{
		int i;
		unsigned char bit;
		unsigned short caractere;
		
		//Se é um novo caractere.
		if(noAtual->caractere == NYT)
		{
			caractere = 0;
			
			//Recupera o caractere do arquivo.
			for(i=7; i>=0; i--)
			{
				fread(&bit, sizeof(unsigned char), 1, arquivoTemp);
				caractere += pow(2,i)*bit;
			}
			
			//Escreve o novo caractere no arquivo de destino.		
			fwrite(&caractere, sizeof(unsigned char), 1, arquivoDestino);
			
			
			//Desloca o valor do caractere para inserir na árvore.
			caractere += DESLOCAMENTO;
			
			//Insere o novo caractere na árvore e a atualiza.
			noAtual = (no*)inserirNaArvore(&arvore, caractere);
			atualizarArvore(&arvore, noAtual);	

			//Retorna ao nó raiz
			noAtual = arvore.raiz;
		}
		//Se é um caractere já existente.
		else
		{
			//Lê bit a bit para percorrer a árvore, até chegar a um nó folha.
			do
			{
				fread(&bit, sizeof(bit), 1, arquivoTemp);
				noAtual = (no*)percorrerArvore(noAtual, bit);
					
			} while(!ehFolha(noAtual));
			
			//Se alcançou o nó PSEUDO_EOF, finaliza a descompactação.
			if(noAtual->caractere == PSEUDO_EOF)
				break;
			
			//Desfaz o deslocamendo do caractere.
			caractere = noAtual->caractere - DESLOCAMENTO;
			
			//Se não é um novo nó.
			if(noAtual->caractere != NYT)
			{
				//Escreve o caractere no arquivo de destino.
				fwrite(&caractere, sizeof(unsigned char), 1, arquivoDestino);
				
				//Atualiza a árvore, incrementando o peso do novo nó e fazendo
				//sua atualização
				atualizarArvore(&arvore, noAtual);
			}
			//Se é um novo nó volta para o início, inserindo-o.
			else continue;
			
			//Retorna ao nó raiz.
			noAtual = arvore.raiz;
		}
		
	};
	
	printf("Terminado!\n\n");
	
	//Fecha o arquivos temporário.
	fclose(arquivoTemp);
	
	//Fim da descompactação.
	rel.t_fim = clock();

/*********************** RELATÓRIO ******************************************/

	//Grava o tamanho do arquivo compactado.
	rel.tamanhoCompactado = rel.f_fim - rel.f_inicio;
	
	//Retorna ao início do arquivo de destino para calcular seu tamanho.
	rewind(arquivoDestino);

	//Marca o início do arquivo.
	fgetpos(arquivoDestino,&rel.f_inicio);

	//Vai até o fim do arquivo.
	fseek(arquivoDestino, 0, SEEK_END);

	//Marca o fim do arquivo.
	fgetpos(arquivoDestino,&rel.f_fim);

	//Fecha o arquivo.
	fclose(arquivoDestino);

	//Grava o tamanho do arquivo descompactado.
	rel.tamanhoOriginal = rel.f_fim - rel.f_inicio;	
	
	//Grava o tempo gasto para compactação.
	rel.tempoDescompactacao = rel.t_fim - rel.t_inicio;
	
	//Calcula a porcentagem de compactação.
	rel.porcentagemCompactacao = 100 -
							(rel.tamanhoCompactado * 100) / rel.tamanhoOriginal;

	puts("****************** Descompactacao *******************");

	printf("Tamanho do arquivo compactado: %.0f bytes.\n",rel.tamanhoCompactado);

	printf("Tamanho original do arquivo: %.0f bytes.\n",rel.tamanhoOriginal);

	printf("Porcentagem de compactacao: %.2f%%.\n", rel.porcentagemCompactacao);
	
	printf("Razao de compactacao: 1:%.2f.\n",
									rel.tamanhoOriginal/rel.tamanhoCompactado);

	printf("Tempo de descompactacao: %.2lf segundo(s).\n", 
							(double) rel.tempoDescompactacao / CLOCKS_PER_SEC);

	puts("\n");
}
