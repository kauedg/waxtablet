#include "stglsb.h"

//Fun��o que insere um arquivo qualquer em uma imagem bitmap.
void ocultarLSB(char *nomeArquivoOrigem, char *nomeImagemOrigem)
{
	//Vari�veis para manipula��o de arquivos.
	FILE *arquivoOrigem,
		 *imagemOrigem,
		 *imagemDestino,
		 *arquivoTemp;
		 
	char nomeImagemDestino[FILENAME_MAX] = "";
	unsigned char byteImg, byteTemp;
	int i, j, bitTemp, intTemp;
	
	//Vari�veis para extra��o da extens�o do arquivo original.
	unsigned char extensao[3] = "", *ext;
	
	//Estrutura para armazenamento e c�lculo de informa��es.
	struct rel
	{
		clock_t t_inicio, t_fim;
		clock_t tempoOcultacao;
		
		fpos_t f_inicio, f_fim;
		
		//Quantidade de bits existentes na origem dos dados.
		unsigned int qtdeBitsOrigem;
		
		//Quantidade de bytes existentes na imagem original.
		unsigned int qtdeBytesImagem;
		
		//Armazena a quantidade total de bits que poder�o ser substitu�dos na
		//�rea de imagem inteira.
		unsigned int qtdeBitsImagem;
		
		//Quantidade de LSBs que ser�o substitu�dos em cada byte de imagem.
		unsigned int qtdeLSB;
		
		//Vari�veis para definir quantos bytes ser�o necess�rios para ocultar
		//o cabe�alho.
		unsigned int cabExtensao;
		unsigned int cabTamanhoOrigem;
		unsigned int cabTotal;
		
	}rel;
	
/******************************************************************************/

	//Inicia contagem do tempo de oculta��o.
	rel.t_inicio = clock();
	
	puts("\n\n");
	printf("Inserindo... ");

	//Abre o arquivo de origem dos dados.
	arquivoOrigem = fopen(nomeArquivoOrigem, "rb");
	if(arquivoOrigem == NULL)
	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeArquivoOrigem);
		puts("\n\n");
		
		exit(0);
	}
	
//Calcula quantos bits a ocultar existem no arquivo de origem.
	//Grava as posi��es de in�cio e fim dos dados de origem.
	fgetpos(arquivoOrigem, &rel.f_inicio);
	fseek(arquivoOrigem, 0, SEEK_END);
	fgetpos(arquivoOrigem, &rel.f_fim);
	
	///Retorna ao in�cio do arquivo.
	fsetpos(arquivoOrigem, &rel.f_inicio);
	
	//Grava quantos bits de dados existem no arquivo de origem.
	rel.qtdeBitsOrigem = (rel.f_fim - rel.f_inicio) * 8;
	
	
//Adiciona o sufixo "_estego" ao nome da imagem com os dados ocultos e extrai a 
//extens�o. 
	
	//Procura a �ltima ocorr�ncia de "." para encontrar a extens�o.
	ext = strrchr(nomeImagemOrigem,'.');
	
	//Se n�o for um bitmap, mostra um aviso e  finaliza o programa.
	if(strcmp(".bmp",ext))
	{
		puts("\n\n");
		printf("ERRO! Imagem informada n�o � bitmap (.bmp).");
		puts("\n\n");
		
		exit(0);
	}
	
	strncpy(nomeImagemDestino, nomeImagemOrigem, strlen(nomeImagemOrigem)- 
																   strlen(ext));
	strcat(nomeImagemDestino,"_estego.bmp");
	
	//Abre o arquivo de imagem de origem.
	imagemOrigem = fopen(nomeImagemOrigem,"rb");
	if(imagemOrigem == NULL)
	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeImagemOrigem);
		puts("\n\n");
		
		exit(0);
	}
	
	//Cria o arquivo de imagem de destino.
	imagemDestino = fopen(nomeImagemDestino,"wb");
	if(imagemDestino == NULL)
	{
		puts("\n\n");
		printf("Erro ao criar %s.", nomeImagemDestino);
		puts("\n\n");
		
		exit(0);
	}
	
	//Copia cabe�alho de imagem.
	for(i=0; i<54; i++)
	{
		fread(&byteImg, sizeof(unsigned char), 1, imagemOrigem);
		fwrite(&byteImg, sizeof(unsigned char), 1, imagemDestino);
	}
	
//Calcula quanto bytes de �rea de imagem existem.
	//Grava as posi��es de in�cio e fim dos dados de imagem.
	fgetpos(imagemOrigem, &rel.f_inicio);
	fseek(imagemOrigem, 0, SEEK_END);
	fgetpos(imagemOrigem, &rel.f_fim);
	
	//Retorna ao in�cio da �rea de dados de imagem.
	fsetpos(imagemOrigem, &rel.f_inicio);
	
	//Grava quantos bytes existem na �rea de imagem.
	rel.qtdeBytesImagem = rel.f_fim - rel.f_inicio;
	
	
	//Se a imagem n�o suportar o m�nimo de bytes necess�rios para ocultar 1 byte
	//de dado, exibe um erro e finaliza o programa.
	// qtdelsb m�xima + extensao + quantidade dados + 1 byte
	//Quantidade m�nima: 3 + 3 + 4 + 1 = 11 bytes
	if(rel.qtdeBytesImagem < 11)
	{
		puts("\n\n");
		printf("ERRO! Imagem menor que o tamanho minimo possivel para ");
		printf("realizar a ocultacao. Utilize uma imagem maior.");
		puts("\n\n");
		
		exit(0);
	}
	
//Calcula a quantidade de bits menos significativos que ser�o necess�rios para
//ocultar os dados.
	
	//Inicializa a quantidade de LSBs com 1;
	rel.qtdeLSB = 1;
	
	//Define valores para uso de 1 LSB.
	rel.cabExtensao = 24;
	rel.cabTamanhoOrigem = 32;
	rel.qtdeBitsImagem = rel.qtdeBytesImagem;
	
	// 3 bits para quantidade de bits a substituir +
	// bits necess�rios para armazenar a extens�o (3 * 8 = 24)+
	// bit necess�rios para armazenar a quantidade de dados ocultos 
	//(32 bits = 1 int).
	rel.cabTotal = 3 + rel.cabExtensao + rel.cabTamanhoOrigem;
	
	//Se a quantidade final de dados (cabecalho + dados) for maior que a 
	//quantidade de bits em �rea de imagem dispon�vel.
	while( (rel.cabTotal + rel.qtdeBitsOrigem) > rel.qtdeBitsImagem )
	{
		//Aumenta a quantidade de LSBs a substituir.
		rel.qtdeLSB++;
		
		//Atualiza a quantidade de bytes que cada parte necessitar�.		
		rel.qtdeBitsImagem = rel.qtdeBytesImagem * rel.qtdeLSB;
		
		rel.cabTotal = 3 + 
				(rel.cabExtensao + rel.cabTamanhoOrigem)/rel.qtdeLSB;
		
		//Se sobrarem bits soma um byte.
		if( ((rel.cabExtensao + rel.cabTamanhoOrigem)%rel.qtdeLSB) != 0)
			rel.cabTotal += 1;		
	}
	
	//Se 8 bits ainda n�o forem suficientes para comportar os dados, exibe um
	//aviso e encerra o programa.
	if(rel.qtdeLSB > 8)
	{
		puts("\n\n");
		
		printf("A imagem nao comporta a quantidade de dados do arquivo ");
		printf("informado. \nUtilize um arquivo menor ou uma imagem maior.\n");
		
		puts("\n\n");
		
		exit(0);
	}
	
	//Ap�s serem definidos todos os par�metros dos dados a ocultar, faz a 
	//cria��o de um arquivo tempor�rio, com os dados "binarizados".
	
	//Cria o arquivo tempor�rio.
	arquivoTemp = tmpfile();
  	if(arquivoTemp == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar arquivo temporario.");
		puts("\n\n");
		
		exit(0);
	}
	
	//Escreve a quantidade de LSBs direto no arquivo de imagem destino.
	//Somente ser�o necess�rios 3 bits, usando sempre 1 LSB.
	/*
		0|001 = 1
		0|010 = 2
		0|011 = 3
		0|100 = 4
		0|101 = 5
		0|110 = 6
		0|111 = 7
		1|000 = 8
	*/
	
	byteTemp = rel.qtdeLSB;

	for(i=0; i<3; i++)
	{
		fread(&byteImg, sizeof(unsigned char), 1, imagemOrigem);
		
		bitTemp = byteTemp % 2;
		byteTemp /= 2;
		
		byteImg >>= 1;
		byteImg <<= 1;

		byteImg += bitTemp;
		
		fwrite(&byteImg, sizeof(unsigned char), 1, imagemDestino);			
	}

	//Escreve a extens�o do arquivo oculto no arquivo tempor�rio, em bits.
	ext = strrchr(nomeArquivoOrigem,'.');
	for(i=0; i<3; i++)
	{
		byteTemp = ext[i+1];
		
		for(j=0; j<8; j++)
		{
			bitTemp = byteTemp % 2;
			byteTemp /= 2;
			
			fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
		}
	}
	
	//Escreve a quantidade de bits que ser�o lidos na extra��o.
	intTemp = rel.qtdeBitsOrigem;
	for(i=0; i<32; )
	{
		bitTemp = intTemp % 2;
		intTemp /= 2;
			
		i++;
			
		fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
	}
	
	//Se houver resto da divis�o do tamanho total do arquivo pela quantidade de
	//LSB substitu�da, complementa o restante dos bits n�o substitu�dos do byte
	//com 0. Sempre completa todos os bits para n�o colocar em um mesmo byte 
	//bits de cabe�alho e bits de dados do arquivo de origem.
	bitTemp = 0;
	if(56%rel.qtdeLSB != 0)
		//Acrescenta a diferen�a entre a quantidade de LSBs que falta e quantos
		//s�o substitu�dos.
		for(i=0; i< rel.qtdeLSB - (56%rel.qtdeLSB); i++)
			fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
	
	//Escreve todos os bits do arquivo de origem no arquivo tempor�rio.
	while(!feof(arquivoOrigem))
	{
		fread(&byteTemp, sizeof(unsigned char), 1, arquivoOrigem);
		
		if(!feof(arquivoOrigem))
		{
			for(i=0; i<8; i++)
			{
				bitTemp = byteTemp % 2;
				byteTemp /= 2;
				
				fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
			}
		}
	}
	
	//Fecha o arquivo de origem de dados.
	fclose(arquivoOrigem);
	
/****************** OCULTA��O *************************************************/

	//Retorna ao in�cio do arquivo tempor�rio.
	rewind(arquivoTemp);
	
	//Substitui os LSBs da imagem original e grava na imagem de destino.
	while(!feof(arquivoTemp))
	{
		bitTemp = 0;
		
		for(i=0; i<rel.qtdeLSB; i++)
		{
			fread(&byteTemp, sizeof(unsigned char), 1, arquivoTemp);
			bitTemp += pow(2,i) * byteTemp;
		}
		
		//L� 1 byte da imagem de origem.
		fread(&byteImg, sizeof(unsigned char), 1, imagemOrigem);

		//Substitui os LSBs.
		byteImg >>= rel.qtdeLSB;
		byteImg <<= rel.qtdeLSB;
		byteImg += bitTemp;

		//Grava o novo byte na imagem de destino.
		fwrite(&byteImg, sizeof(unsigned char), 1, imagemDestino);
	}
	
	//Se terminou de inserir e ainda houver dados de imagem, copia o restante.
	while(!feof(imagemOrigem))
	{
		fread(&byteTemp, sizeof(unsigned char), 1, imagemOrigem);
		
		if(!feof(imagemOrigem))
			fwrite(&byteTemp, sizeof(unsigned char), 1, imagemDestino);
	}

	//Fecha os arquivos utilizados
	fclose(arquivoTemp);
	fclose(imagemOrigem);
	fclose(imagemDestino);	
	
	printf("Terminado!\n\n");
	
	//Encerra contagem do tempo de oculta��o.
	rel.t_fim = clock();
/****************** RELAT�RIO *************************************************/

puts("****************** Ocultacao *********************");
printf("LSBs substituidos de cada byte: %d bit(s)\n",rel.qtdeLSB);

printf("Bits existentes na origem dos dados: %d bits.\n",
															rel.qtdeBitsOrigem);
		
printf("Bytes de area de imagem original: %d bytes.\n",
														rel.qtdeBytesImagem);

printf("Bits na imagem original para substituicao com %d LSB: ", rel.qtdeLSB);
printf("%d bits.\n", rel.qtdeBitsImagem);
		
puts("\n");
printf("Cabecalho:\n");

printf(" Extensao: %d bits.\n", rel.cabExtensao);
printf(" Tamanho da origem: %d bits.\n", rel.cabTamanhoOrigem);
printf(" Tamanho total ocupado: %d bytes.\n", rel.cabTotal);

puts("");
printf("Total de bits inseridos: %d bits.\n",rel.cabTotal + rel.qtdeBitsOrigem);

puts("");

rel.tempoOcultacao = rel.t_fim - rel.t_inicio;
printf("Tempo de ocultacao: %.2f segundo(s).\n", (double)rel.tempoOcultacao / 
																CLOCKS_PER_SEC);


printf("Utilizacao dos bits da imagem: %.2f%%.\n", 
					(((float)rel.cabTotal + (float)rel.qtdeBitsOrigem) * 100 ) / 
													(float)rel.qtdeBitsImagem);

puts("\n");
}



/******************************************************************************/

char nomeArquivoDestino[FILENAME_MAX] = "";

//Fun��o que tenta extrair de um arquivo bitmap um arquivo oculto.
char* extrairLSB(char *nomeImagemOrigem)
{
	//Vari�veis para manipula��o de arquivos.
	FILE *imagemOrigem,
		 *arquivoTemp,
		 *arquivoDestino;
		 
	char *ext;
	unsigned char byteImg, byteTemp;
	int i, j, bitTemp, temp; 
	
	//Estrutura para armazenar e calcular informa��es da extra��o.
	struct rel
	{
		//Vari�veis para calcular o tempo de extra��o.
		clock_t t_inicio, t_fim;
		clock_t tempoOcultacao;
		
		//Vari�veis para calcular tamanho de arquivos.
		fpos_t f_inicio, f_fim;
		
		//Quantidade de bits existentes na origem dos dados.
		unsigned int qtdeBitsOrigem;
		
		//Quantidade de LSBs que ser�o substitu�dos em cada byte de imagem.
		unsigned int qtdeLSB;
		
		//Vari�veis para recuperar os dados de cabe�alho.
		unsigned char cabExtensao[3];
		unsigned int cabTamanhoOrigem;
		
	}rel;
		
/******************************************************************************/	
	
	//Inicia contagem do tempo de extra��o.
	rel.t_inicio = clock();
	
	puts("\n\n");
	printf("Extraindo... ");
	
	//Abre o arquivo de imagem de origem.
	imagemOrigem = fopen(nomeImagemOrigem,"rb");
	if(imagemOrigem == NULL)
	{
		puts("\n\n");
		printf("Erro ao abrir %s para leitura.", nomeImagemOrigem);
		puts("\n\n");
		
		exit(0);
	}
	
	//Ignorar cabe�alho (54 bytes).
	fseek(imagemOrigem, 54, SEEK_SET);
	
	//Cria o arquivo tempor�rio.
	arquivoTemp = tmpfile();
  	if(arquivoTemp == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar arquivo temporario.");
		puts("\n\n");
		
		exit(0);
	} 
	
	//Extrair a quantidade de LSBs usados em cada byte.
	rel.qtdeLSB = 0;
	for(i=0; i<3; i++)
	{
		fread(&byteTemp, sizeof(unsigned char), 1, imagemOrigem);
		rel.qtdeLSB += pow(2,i) * (byteTemp % 2);
	}
	
	//Se a quantidade de LSB for 0 converte para 8.
	if(rel.qtdeLSB == 0) rel.qtdeLSB = 8;
	
	//Extrair o estego-cabe�alho dos LSBs para o arquivo tempor�rio.
	// extensao + quantidade de bits ocultos
	// 24 + 32 = 56
	rel.cabTamanhoOrigem = 0;
	for(i=0; i<56;)
	{
		fread(&byteTemp, sizeof(unsigned char), 1, imagemOrigem);

		for(j=0; j<rel.qtdeLSB && i<56; j++)
		{
			bitTemp = byteTemp % 2;
			byteTemp /= 2;
			
			i++;
			
			fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
		}
	}
	
	//Volta ao in�cio do arquivo termpor�rio.
	rewind(arquivoTemp);

	//Extrair a extens�o original.
	for(i=0; i<3; i++)
	{
		bitTemp = 0;
		
		//L� 8 bits e transforma em um byte.
		for(j=0; j<8; j++)
		{
			fread(&byteTemp, sizeof(unsigned char), 1, arquivoTemp);
			bitTemp += pow(2,j) * byteTemp;
		}
		
		rel.cabExtensao[i] = bitTemp;
	}
	
	//Insere o caractere terminador de string.
	rel.cabExtensao[i] = '\0';
	
	
	//Extrair a quantidade de bits a ler.
	bitTemp = 0;
	for(i=0; i<32; i++)
	{
		fread(&byteTemp, sizeof(unsigned char), 1, arquivoTemp);
		bitTemp += pow(2,i) * byteTemp;	
	}
	
	//Atribui a quantidade de bits � vari�vel de relat�rio.
	rel.cabTamanhoOrigem = bitTemp;
	
//Copia todos os LSBs ocultos para o arquivo tempor�rio.
	
	//Fecha o arquivo tempor�rio.
	fclose(arquivoTemp);
	
	//Cria um novo arquivo tempor�rio.
	arquivoTemp = tmpfile();
  	if(arquivoTemp == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar arquivo temporario.");
		puts("\n\n");
		
		exit(0);
	} 
	
	//Atribui � vari�vel tempor�ria a quantidade total de bits a ler.
	temp = rel.cabTamanhoOrigem;
	
	//Gravar os LSBs de dados no arquivo tempor�rio.
	while(!feof(imagemOrigem) && temp > 0)
	{
		//L� 1 byte de imagem.
		fread(&byteImg, sizeof(unsigned char), 1, imagemOrigem);
		
		//Enquanto n�o chegar ao fim do arquivo, continua extraindo.
		if(!feof(imagemOrigem))
		{
			//Extrai os LSBs utilizados.
			for(i=0; i<rel.qtdeLSB && temp >0; i++)
			{
				bitTemp = byteImg % 2;
				byteImg /= 2;
				
				//Decrementa a quantidade de bits a ler.
				temp--;
				
				//Escreve o bit lido no arquivo tempor�rio.
				fwrite(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
			}
		}
	}
	
//Criar o novo arquivo, com a extens�o original do arquivo oculto.
	//Mudar a extens�o do arquivo de origem.
	ext = strrchr(nomeImagemOrigem,'.');
	strncpy(nomeArquivoDestino, nomeImagemOrigem, strlen(nomeImagemOrigem)- 
																   strlen(ext));
	strcat(nomeArquivoDestino,"_extraido.");
	strcat(nomeArquivoDestino,rel.cabExtensao);	
	
	//Cria o arquivo de destino original.
	arquivoDestino = fopen(nomeArquivoDestino,"wb");
  	if(arquivoDestino == NULL)
  	{
		puts("\n\n");
		printf("Erro ao criar %s.", nomeArquivoDestino);
		puts("\n\n");
		
		exit(0);
	}
	
	//Volta ao in�cio dos dados.
	rewind(arquivoTemp);
	
	//Grava conjuntos de 8 bits em 1 byte para recuperar as informa��es.
	while(!feof(arquivoTemp))
	{		
		byteTemp = 0;
		
		for(i=0; i<8; i++)
		{
			fread(&bitTemp, sizeof(unsigned char), 1, arquivoTemp);
			byteTemp += pow(2,i) * bitTemp;
		}	
		
		fwrite(&byteTemp, sizeof(unsigned char), 1, arquivoDestino);
	}

	//Fecha os arquivos utilizados.
	fclose(arquivoTemp);
	fclose(imagemOrigem);
	fclose(arquivoDestino);
	
	printf("Terminado!\n\n");
	
	//Encerra a contagem do tempo de extra��o.
	rel.t_fim = clock();
	
/****************** RELAT�RIO *************************************************/

puts("****************** Extracao **********************");
printf("LSBs substituidos de cada byte: %d bit(s)\n",rel.qtdeLSB);

printf("Quantidade de dados extraidos: %d bits.\n",rel.cabTamanhoOrigem);
		
rel.tempoOcultacao = rel.t_fim - rel.t_inicio;
printf("Tempo de ocultacao: %.2f segundo(s).\n", (double)rel.tempoOcultacao / 
																CLOCKS_PER_SEC);


puts("\n");

return nomeArquivoDestino;
}
