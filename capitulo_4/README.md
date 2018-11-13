### CAPÍTULO 4 - DESENVOLVIMENTO DE UM SISTEMA DE ESTEGANOGRAFIA
Com o conjunto de técnicas e algoritmos estudados nos Capítulos anteriores, é dado
início ao desenvolvimento do sistema proposto.


### 4.1 Introdução
Neste trabalho é proposto o desenvolvimento de um sistema de esteganografia em
imagens, aliada à compactação de dados. Essa abordagem difere da comum, que é o uso da
criptografia e coincide com a proposta de Rocha (2003, p 79) do uso de um algoritmo de
Huffman em conjunto com a esteganografia. A intenção com a compactação dos dados é
aumentar a capacidade de ocultação do arquivo de cobertura e dificultar a detecção do uso da
técnica.  

O sistema foi desenvolvido em linguagem C, sendo composto de duas bibliotecas e
um programa principal, que as implementa. É executado por linha de comando, fornecendo os
parâmetros necessários para cada tipo de operação. A compactação de arquivos e a
esteganografia foram implementadas como bibliotecas estáticas C, para permitir avaliação
individual e reutilização do código. Todas as funções foram desenvolvidas neste projeto,
exceto as já existentes das bibliotecas padrão. Para o desenvolvimento foi utilizado o
Bloodshed Dev-C++ versão 4.9.9.2. As técnicas e formatos escolhidos para compor o sistema
são:  


• Arquivo de origem dos dados: O sistema aceita qualquer formato de arquivo a ser oculto,
pois sua estrutura não é relevante no processo de ocultação.  

• Algoritmo de compactação: O algoritmo de compactação de Huffman adaptativo foi
escolhido para este trabalho por sua eficiência e adaptabilidade.  

• Ocultação: A técnica de esteganografia LSB foi escolhida por seu funcionamento
simples e eficiente e pela facilidade de visualizar seu funcionamento.  

• Arquivo de cobertura: O formato de imagem bitmap foi escolhido por sua estrutura
simples, permitindo melhor entendimento do processo de ocultação e pelo tamanho dos
arquivos, podendo ocultar grande quantidade de dados.  

O nome escolhido para o sistema foi **WaxTablet**, em referência ao uso de tábuas de
escrita utilizadas na Grécia, como foi apresentado no histórico da esteganografia, no Capítulo 1.


### 4.2 Objetivos
O objetivo do sistema é demonstrar o funcionamento da esteganografia aliada à
compactação de dados, mantendo o tamanho do arquivo de cobertura inalterado e permitindo
a extração completa dos dados ocultos sem distorções ou falhas. Após a ocultação e extração
são apresentadas informações de desempenho para avaliação dos algoritmos implementados.  

As bibliotecas desenvolvidas também fazem parte do resultado final do trabalho e
podem ser utilizadas em outros estudos ou por outros desenvolvedores.  


### 4.3 Estruturação Geral
O sistema é composto de duas bibliotecas estáticas C e um programa principal, que
as implementa. As bibliotecas desenvolvidas funcionam independentemente para que possam
ter seus desempenhos medidos e serem reutilizadas. As partes que compõem o sistema são:  

• Biblioteca adaphuff: Implementa a compactação de arquivos, gerando um arquivo “.ahf”
com os dados compactados.  

• Biblioteca stglsb: Implementa a inserção dos dados de um arquivo nos bits menos
siginificativos das cores da imagem bitmap de cobertura.  

• Programa principal: Implementação de um sistema de esteganografia usando as duas
bibliotecas criadas.  

Em seguida são apresentadas as estruturas de dados utilizadas e os principais
problemas encontrados durante o desenvolvimento das bibliotecas e qual solução foi adotada
para contorná-las


### 4.3.1 Biblioteca adaphuff
É a biblioteca responsável pela implementação da compactação de dados por Huffman adaptativo. 
A estrutura de dados, em C, que implementa sua árvore está na Figura 11.


![Figura 11 - Estrutura de dados em C da árvore de Huffman adaptativo implementada](/img/figura_11.png)  
Figura 11 - Estrutura de dados em C da árvore de Huffman adaptativo implementada  


Todas as variáveis que compõem a estrutura no não armazenam valores negativos. A
variável caractere teve de ser alterada de unsigned char para unsigned short, para que o
compactador funcionasse com arquivos executáveis. O problema apareceu quando caracteres
não-imprimíveis eram inseridos na árvore. Como o nó NYT foi inicialmente definido tendo
valor de caractere "0" decimal, era criado um conflito ao ler um caractere com esse valor de
um arquivo executável e fazer sua inserção. Além do nó NYT foi necessário encontrar uma
representação para os nós internos e para o nó PSEUDO_EOF, que não consta no algoritmo
original mas que foi criado neste projeto para sinalizar ao descompactador o final dos dados,
pois ao extrair os dados compactados de uma imagem, bits a mais podem ser e influenciar na
descompactação. A solução foi fazer, no cabeçalho da biblioteca, a definição de constantes
que armazenariam os números reservados da estrutura da árvore (Figura 12).

![Figura 12- Declarações de constantes específicas da implementação de Huffman adaptativo feita](/img/figura_12.png)  
Figura 12 - Declarações de constantes específicas da implementação de Huffman adaptativo feita  


Essa declaração reserva os decimais de 0 a 2 para os nós específicos da
implementação da árvore. Dessa maneira são necessários pelo menos 256 (caracteres da
tabela ASCII) + 3 = 259 valores para que a árvore possa armazenar todos os caracteres mais
seus nós específicos. Como o valor 259 excede o máximo suportado pelo tipo unsigned char
(1 byte), a solução foi declarar caractere como unsigned short (2 bytes), já que não há
nenhum tipo de dado inteiro entre os dois tipos. Assim, o valor do identificador
DESLOCAMENTO é aplicado ao caracetere lido do arquivo sendo compactado e então é
inserido na árvore.   

Na descompactação o processo é inverso, sendo retirado o deslocamento
para que o caractere seja corretamente recuperado. Foram feitos testes com arquivos
executáveis no compactador e após a extração, continuavam funcionando corretamente.
As variáveis peso e ordem foram definidas como unsigned int, o que dá um alcance
de valor decimal de 0 até 4.294.967.295, ou seja, 4 gigabytes da dados, mais do que suficiente
para qualquer arquivo comum. São definidos também três ponteiros para estruturas do tipo
no, que são usadas para manter as referências aos nós filhos e pai de cada nó.

Junto com a árvore foi implementado um vetor, seguindo a proposta de Low (2008);
um vetor de ponteiros para os nós da árvore. Assim é feita uma busca linear no vetor (embora
não seja a mais eficiente) ao invés de constantes buscas recursivas na árvore. Foi então criada
a estrutura AHA (Árvore de Huffman adaptativo) que contém dois ponteiros: um para o vetor
auxiliar e outro para a raiz da árvore.  

Houve ainda um problema quanto à recuperação da extensão original do arquivo
compactado. Para solucionar o problema, na compactação, antes de escrever os dados
compactados, os caracteres da extensão são escritos no início do arquivo, mas com a ordem
dos seus bits invertidos, alterando o caractere.


### 4.3.2 Biblioteca stglsb
Para o desenvolvimento desta biblioteca não foi necessária a criação de estruturas de
dados específicas, mas sim o estudo da estrutura de arquivos bitmap. O formato bitmap foi
desenvolvido para ser o formato nativo de imagens do sistema operacional Windows, a partir
da versão 3.0. A estrutura do arquivo é bem simples para evitar erros de leitura ou
inconsistências (OLIVEIRA, 2000), e consiste de 2 cabeçalhos, uma paleta de cores
(opcional) e da área de imagem (Figura 13). Por causa de sua estrutura simples de cabeçalho e
de área de dados de imagem, e pela grande quantidade de bytes, sem compactação, que a
compõe, foi o formato escolhido para as imagens de cobertura. Os cabeçalhos armazenam
informações sobre o arquivo como suas propriedades de tamanho e profundidade de cores. As
definições de cada um são descritas em (OLIVEIRA, 2000).


![Figura 13 - Estruturas de um arquivo bitmap (Fonte: BOURKE, 1998)](/img/figura_13.png)  
Figura 13 - Estruturas de um arquivo bitmap (Fonte: BOURKE, 1998)  

A paleta de cores somente está presente em imagems com 256 cores ou menos. Como imagens bitmap com menos de 24 bits de profundidade são muito sensíveis a alterações de suas cores, não são consideradas pelo sistema. O tamanho do cabeçalho de arquivo mais o cabeçalho de informações é de 54 bytes. Como essas estruturas não têm relevância durante a
ocultação de dados, são simplesmente copiadas de um arquivo pra outro (na ocultação) ou
ignoradas (na extração). A parte que interessa é área de dados imagens.  

Em imagens bitmap de 24 bits cada pixel (picture element) é composto de 3 bytes,
um para cada cor primária, isto é, vermelho, verde e azul. A combinação desses três valores
determina a cor que o pixel exibirá. Deve-se notar que o primeiro pixel da área de dados
corresponde ao canto inferior esquerdo da imagem, e o último ao canto superior direito.  

É nos componentes de cor de cada pixel que os bits da mensagem são ocultos.
Alterando o bit menos significativo não há qualquer mudança aparente na imagem.
Dependendo da imagem as alterações só passam a ser visíveis a partir da substiuição de 3 ou 4
bits menos significativos.  

Mesmo não necessitando de estruturas de dados específicas, foi necessária a criação
um cabeçalho de dados referentes ao processo de ocultação. Neste cabeçalho, inserido antes
dos dados em si, constam a quantidade de bits menos significativos que foram substituídos, a
extensão original do arquivo oculto e a quantidade de bits a ler. Como não é possível prever a
quantidade de LSBs usados, são necessários sempre 3 bytes para armazená-la, substituindo
somente 1 LSB de cada byte. Os decimais de 1 a 8 são decompostos em bits, sendo utilizados
somente os 3 bits menos significativos resultantes. Embora a decomposição do número
decimal 8 resulte na sequência de bits “00001000”, o que necessitaria de 4 bits, seus últimos 3
bits resultariam no número 0. Como este número não está entre os possíveis, sempre que a
quantidade de LSBs usada for 0, é convertida no decimal 8. A Tabela 6 ilustra essa conversão.


![Tabela 6 - Conversão dos bits que representam a quantidade de LSBs substituídos em uma estego-imagem](/img/tabela_6.png)  
Tabela 6 - Conversão dos bits que representam a quantidade de LSBs substituídos em uma estego-imagem  

Após a quantidade de LSBs usados é escrita a extensão do arquivo original, sem o
ponto e a quantidade de bits a ler. As duas informações ocupam respectivamente 3 e 4 bytes
(3 chars mais um int), sendo necessários 7 bytes dividido pela quantidade de LSBs usados.
Caso sobrem bits a substituir no último byte (o que acontece para valores de LSB 3, 5 e 6) os
restantes são preenchidos com zero. Isso evita que bits da mensagem e do cabeçalho se
misturem, dificultando a recuperação. Após escrito o cabeçalho, o restante dos bits é escrito,
respeitando a quantidade de LSBs a substituir. Na extração esse cabeçalho é lido e o arquivo é
recuperado seguindo as instruções gravadas.  


### 4.4 Serviços Implementados
Os serviços implementados neste projeto são a compactação de dados por Huffman
adaptativo e a ocultação de arquivos em imagens bitmap por esteganografia utilizando a
técnica LSB. Os protótipos das funções e o que fazem são:  

#### Biblioteca adaphuff  
`char* compactar(char *nomeArquivoOrigem)`  
O compactador recebe um nome de arquivo como parâmetro e gera como saída um
arquivo compactado de nome igual ao original adicionado do sufixo "_compactado", e com
extensão ".ahf". A função retorna um ponteiro para o nome do arquivo criado.

`void descompactar(char *nomeArquivoCompactado)`  
Da mesma maneira, para descompactar, deve-se fornecer o nome de um arquivo
".ahf" e após feita a descompactação o arquivo original é recriado, com a adição do sufixo
"_descompactado" e com sua extensão original.


#### Biblioteca stglsb  
`void ocultarLSB(char *nomeArquivoOrigem, char *nomeImagemOrigem)`  
Para ocultar um arquivo em uma imagem é necessário passar à ferramenta de
esteganografia dois parâmetros: o arquivo que será oculto e a imagem que servirá de
cobertura. O processo cria um arquivo de mesmo nome da imagem, adicionado do sufixo
"_estego" para diferenciar da imagem original.

`char* extrairLSB(char *nomeImagemOrigem)`  
Para extrair dados esteganografados, deve-se passar como parâmetro somente a
estego-imagem da qual se deseja extrair os dados ocultos. Após a extração será recriado o
arquivo que estava oculto, de mesmo nome da estego-imagem, adicionado do sufixo
"_extraido" e com sua extensão original. A função retorna um ponteiro para o nome do
arquivo criado.  


O modo que o programa principal deve ser executado e seu funcionamento é:  

#### WaxTablet.exe –o arquivo1.xxx imagem.bmp  
Para ocultar um arquivo em uma imagem, após o nome do executável o parâmetro
"-o" deve ser fornecido, seguido do nome do arquivo que se deseja ocultar e da imagem que
servirá de cobertura. O programa faz a compactação do arquivo e depois insere o arquivo
criado pela compactação na imagem de cobertura.  

#### WaxTablet.exe –e imagem.bmp  
Para fazer a extração de dados de uma imagem, deve ser fornecido o parâmetro “-e”
seguido do nome da imagem que contém os dados. O programa faz a extração dos dados,
seguido de sua descompactação, gerando o arquivo original.

### 4.5 Considerações Finais  
Sendo terminado o estudo e a estruturação do sistema, foi feita sua implementação.
Foram desenvolvidos protótipos de cada biblioteca que foram testados e corrigidos várias
vezes até sua versão final. Após suas validações finais, o programa principal que as
implementa foi escrito e testado, chegando ao WaxTablet 1.0. Os objetivos estabelecidos
foram alcançados e testes de desempenho foram feitos, que são apresentados no próximo
Capítulo.
