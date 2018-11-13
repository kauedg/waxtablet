#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char arquivoCompactado[FILENAME_MAX] = "";
	char arquivoDescompactado[FILENAME_MAX] = "";
	
	clock_t t_inicio, t_fim;
	
	if(argc > 4 || argc < 3)
		puts("Quantidade de parametros invalida.");
	else
	{
		if(!strcmp(argv[1],"-o") || !strcmp(argv[1],"-O"))
		{
			if(argc == 4)
			{
				t_inicio = clock();
				strcpy(arquivoCompactado,(char*)compactar(argv[2]));
				ocultarLSB(arquivoCompactado, argv[3]);
				t_fim = clock();
			}
			else
				puts("Quantidade de Parâmetros inválida.");
		}
		else if(!strcmp(argv[1],"-e") || !strcmp(argv[1],"-E"))
		{
			if(argc == 3)
			{
				t_inicio = clock();
				strcpy(arquivoDescompactado,(char*)extrairLSB(argv[2]));
				descompactar(arquivoDescompactado);
				t_fim = clock();
			}
			else 
				puts("Quantidade de Parâmetros inválida.");
		}
		
		printf("***********************************************************\n");
		printf("Tempo total do processo: %.2f segundos.\n",
								   (double)(t_fim - t_inicio) / CLOCKS_PER_SEC);

	}
  
	return 0;
}

