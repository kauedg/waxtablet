# WaxTablet
Aplicação escrita em C que alia compactação de dados com o algoritmo de Huffman Adaptativo a esteganografia LSB em imagens bitmap

#### [Lista de Abreviaturas](abreviaturas.md)  
#### [Introdução](introdução.md)

#### [CAPÍTULO 1 - ESTEGANOGRAFIA: UMA VISÃO GERAL](/capitulo_1/)
1.1	Definição  
1.2 Terminologia  
1.3	Utilização  
1.4 Histórico  
1.5 Princípios  
1.6 Segurança  
1.6.1 Criptografia  
1.6.2 Confidencialidade  
1.6.3 Sobrevivência  
1.6.4 Não-Detecção  
1.6.5 Visibilidade  
1.7 Considerações Finais  

#### [CAPÍTULO 2 - MÉTODOS DE ESTEGANOGRAFIA E SUAS CLASSIFICAÇÕES](/capitulo_2/)  
2.1 Métodos de Esteganografia  
2.1.1 Sistemas de Substituição  
2.1.1.1 Substituição de Bit Menos Significativo  
2.1.1.2 Permutações Pseudo-aleatórias  
2.1.1.3 Degradação de Imagens e Canais de Cobertura  
2.1.2 Técnicas de Transformação de Domínio  
2.1.3 Espalhamento Espectral  
2.1.4 Observações Sobre os Métodos  
2.2 Classificações da Esteganografia  
2.2.1 Classificação Original  
2.2.2 Nova Classificação  
2.3 Considerações Finais  
  
#### [CAPÍTULO 3 - COMPACTAÇÃO DE DADOS](/capitulo_3/)  
3.1 Introdução  
3.2 Algoritmo de Huffman  
3.2.1 Huffman Estático  
3.2.2 Huffman Adaptativo  
3.3 Considerações Finais  
  
#### [CAPÍTULO 4 - DESENVOLVIMENTO DE UM SISTEMA DE ESTEGANOGRAFIA](/capitulo_4/)
4.1 Introdução  
4.2 Objetivos  
4.3 Estruturação Geral  
4.3.1 Biblioteca adaphuff  
4.3.2 Biblioteca stglsb  
4.4 Serviços Implementados  
4.5 Considerações Finais  
  
#### [CAPÍTULO 5 - TESTES E ANÁLISE DE RESULTADOS](/capitulo_5/)  
5.1 Configuração de Hardware  
5.2 Configuração de Software  
5.3 Testes e Análises de Resultados  
5.3.1 Biblioteca adaphuff  
5.3.1.1 Teste 1.1 – Compactação de Arquivos .exe e .txt  
5.3.1.2 Teste 1.2 – Descompactação de Arquivos .exe e .txt  
5.3.1.3 Teste 1.3 – Compactação e Descompactação de Imagens .bmp  
5.3.2 Biblioteca stglsb  
5.3.2.1 Teste 2.1 – Degradação Progressiva de Uma Imagem de Cobertura  
5.3.2.2 Teste 2.2 – Inserção e Extração de Arquivos  
5.3.3 Programa Principal  
5.3.3.1 Teste 3.1 – Inserção e Extração de Arquivo Executável  
5.3.3.2 Inserção e Extração de Arquivo de Imagem  
5.3.3.3 Inserção e Extração de Arquivo de Áudio  
5.4 Conclusões Finais  
  
#### [CAPÍTULO 6 - Conclusões e Trabalhos Futuros](/capitulo_6/)  
6.1 Conclusão  
6.2 Contribuições  
6.3 Limitações  
6.4 Trabalhos Futuros  
6.4.1 Técnica de Esteganografia Empregada  
6.4.2 Formato de Imagem de Cobertura  
6.4.3 Alteração da Implementação de Huffman Adaptativo  
6.4.4 Implementação de Algoritmos de Busca e Ordenação de Vetor

