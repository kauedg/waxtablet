### CAPÍTULO 3 - COMPACTAÇÃO DE DADOS  


### 3.1 Introdução  
A compactação de dados é uma técnica criada para reduzir a quantidade de caracteres necessários para se representar uma mensagem, 
eliminando redundâncias, e permitir sua recuperação posterior. Entretanto não se deve confundir compactação com compressão. 
Na compactação, as redundâncias são reduzidas sem perdas de dados, enquanto que na compressão, dados são perdidos e não podem 
ser mais recuperados (SAADE, 2008). É usada, por exemplo, em arquivos de áudio e vídeo que não precisam reproduzir detalhes que 
os sentidos humanos não percebem.  

Entretanto a compactação e a compressão de dados não são usadas somente em arquivos. Técnicas foram desenvolvidas para 
transmissão de sinais de televisão, tráfego de dados em uma rede (ARRUDA; GOES, 2003), telefonia, bancos de dados, entre outros.  

Dentre os algoritmos existentes, o algoritmo de Huffman foi escolhido para ser abordado neste trabalho, por sua eficiência e por 
servir de base para importantes algoritmos de compressão como o JPEG. Coello (1994) faz uma comparação entre vários algoritmos 
de compactação e apresenta as Tabelas 2 e 3. Percebe-se que os algoritmos de Huffman têm a melhor relação entre razão de 
compressão (coluna T/L) e tempo para arquivos grandes, como mostra a tabela superior, e que para arquivos pequenos perdem 
no mesmo quesito somente para o algoritmo LZW 12 bits. Com isso, foi escolhido o algoritmo de Huffman como objeto de estudo.  

![Tabela 2 - Comparativo entre vários algoritmos de compactação de dados aplicados a um arquivo .doc (Fonte: COELLO, 1994)](/img/tabela_2.jpg)  
Tabela 2 - Comparativo entre vários algoritmos de compactação de dados aplicados a um arquivo .doc (Fonte: COELLO, 1994)  
`T é o tamanho do arquivo original e L o tamanho do arquivo compactado, ambos em bytes.`  



  
  
![Tabela 3 - Comparativo entre vários algoritmos de compactação de dados aplicados a um arquivo .dbf (Fonte: COELLO, 1994)](/img/tabela_3.jpg)  
Tabela 3 - Comparativo entre vários algoritmos de compactação de dados aplicados a um arquivo .dbf (Fonte: COELLO, 1994)  

### 3.2 Algoritmo de Huffman
O algoritmo de Huffman foi desenvolvido por David Huffman em 1950 (BLELLOCH, 2001) e consiste na utilização de uma árvore 
binária para geração dos chamados códigos de Huffman para compactação de dados. Por ser simples e eficiente serve como base 
para softwares compactadores de arquivos e para algoritmos de compactação de imagens (GZIP e JPEG, respectivamente). 
Os código de Huffman são códigos binários criados a partir da frequência que um símbolo aparece na origem dos dados. 
Quanto maior a frequência de um símbolo menor deve ser seu código, sendo que um código nunca é prefixo de outro (CAMPOS, 1999). 
As duas formas de implementação do algoritmo são detalhadas a seguir.  


### 3.2.1 Huffman Estático
Para compactar um arquivo utilizando Huffman estático são necessárias duas leituras do arquivo: uma para calcular as frequências 
dos símbolos e outra para fazer a compactação. Durante a primeira leitura é criada uma tabela com os símbolos e suas frequências. 
Com estes dados uma árvore binária de busca é criada, em que cada nó folha representa um símbolo. Quanto mais próximo da raiz 
está o símbolo, menor é o código atribuído a ele. Nesta árvore somente os nós folha armazenam os símbolos enquanto os nós 
internos recebem a soma das frequêncis de seus nós filhos.  

Na segunda leitura, para cada símbolo lido é feita sua busca na árvore e o caminho da raiz até ele é escrito na saída dos dados. 
Supondo que se deseja compactar a sequência de caracteres "abaacba", o processo seria: 

a) Ler os dados a primeira vez e calcular as frequências (Tabela 4).

![Tabela 4 - Frequências dos símbolos no algoritmo de Huffman estático](/img/tabela_4.png)  
Tabela 4 - Frequências dos símbolos no algoritmo de Huffman estático  

b) Criar a árvore binária de Huffman. Com a lista de frequências `Lf`, o algoritmo para criá-la pode ser escrito como na 
Figura 3:

![Figura 3 - Algoritmo de criação da árvore de Huffman estático](/img/figura_3.png)  
Figura 3 - Algoritmo de criação da árvore de Huffman estático  

A Figura 4 ilustra a árvore final para a tabela do exemplo. 

![Figura 4 - Exemplo de árvore de Huffman estático](/img/figura_4.jpg)  
Figura 4 - Exemplo de árvore de Huffman estático  

c) Após a criação da árvore, volta-se ao início dos dados. Todos os símbolos são lidos novamente, agora escrevendo o caminho na 
árvore da raiz até ele, sendo “1” para percurso à direita e “0” para percurso à esquerda. O resultado desta etapa são os códigos 
da Tabela 5.

![Tabela 5 - Sequência de caracteres "abaacba" compactada: 1011100011](/img/tabela_5.png)  
Tabela 5 - Códigos gerados pelo algoritmo de Huffman estático.  

Para representar a sequência de caracteres original seriam necessários 56 bits sendo 8 bits para cada caractere. Após a 
compactação a quantidade foi reduzida para 10 bits, ou seja, houve uma diminuição de 82,15% na quantidade de bits necessários.
Para a descompactação deve ser fornecido ao algoritmo a tabela de símbolos e frequências que gerou a árvore de Huffman na 
compactação. A árvore é então recriada e a partir da sequência de bits dos dados compactados, os caracteres são extraídos. 
O algoritmo de descompactação é mostrado na Figura 5, Sendo `F` a fonte de códigos de Huffman (lida da esquerda para a direita), 
`Ah` a árvore recriada, `n` um ponteiro para os nós da árvore e `Sd` a saída dos dados descompactados.  

![Figura 5 - Algoritmo de descompactação de Huffman estático](/img/figura_5.png)  
Figura 5 - Algoritmo de descompactação de Huffman estático

Apesar da grande redução dos dados, o algoritmo de Huffman estático tem duas grandes desvantagens: ter de ler o fonte de dados 
duas vezes, uma para calcular as frequências e outra para comprimir o arquivo, e ter que enviar a tabela de símbolos e suas 
respectivas frequências junto com os dados compactados, reduzindo muito a eficiência final do algoritmo (LOW, 2000). 
Enviando os símbolos, a quantidade de vezes que cada um aparece e o resultado final da compactação tem-se a Equação 1. 

![Equação 1 - Total de bits necessários para enviar dados compactados por Huffman estático](/img/equação_1.png)  
Equação 1 - Total de bits necessários para enviar dados compactados por Huffman estático


Para o exemplo dado seriam necessários então `Tb` = (3x40) + 10, resultando em um total de 130 bits, excedendo em 132,15% a 
quantidade de bits originalmente necessária.  


### 3.2.2 Huffman Adaptativo  
Dadas as desvantagens do Huffman estático, Faller e Gallagher, e mais tarde Knuth e Vitter, desenvolveram um modo de executar o 
algoritmo de Huffman como um procedimento de uma passagem pelos dados de origem (SAYOOD, 2000 apud LOW, 2000). Neste novo 
algoritmo a criação da árvore e a geração dos códigos são feitos durante a leitura da fonte dos dados. À medida que novos 
símbolos são lidos, a árvore é remodelada, aumentando a efetividade da compactação. Aqui é explicado o método de Vitter.  

Em Huffman estático se um símbolo aparece somente uma vez, no início de um arquivo, ele será colocado em níveis mais baixos da 
árvore, recebendo um código com vários bits. Em Huffman adaptativo esse símbolo é colocado primeiro em níveis mais altos e 
recebe um código curto, e com a leitura de mais símbolos é deslocado para níveis mais baixos.  
  
  
### 3.2.2.1 Propriedades da Árvore de Huffman Adaptativo
A explicação feita a seguir é baseada em Low (2000). Cada nó de uma árvore de Huffman adaptativo deve conter o símbolo que 
armazena, seu peso (quantidade de vezes que foi lido), e a ordem do nó na árvore. Deve ainda ter três ponteiros: para o nó pai, 
para o nó filho esquerdo e para o nó filho direito. Há um nó especial chamado NYT (*Not Yet Transmitted*, ainda não transmitido) 
que deve estar presente na árvore desde sua criação, pois é onde novos símbolos são inseridos. Observando a Figura 6 nota-se as 
propriedades da árvore que devem ser mantidas enquanto ela é atualizada:

![Figura 6 - Árvore de Huffman adaptativo resultante da compactação da palavra "huffman"](/img/figura_6.jpg)  
Figura 6 - Árvore de Huffman adaptativo resultante da compactação da palavra “huffman”  

1) Todo nó tem um nó irmão;
2) Nós com maiores pesos têm maiores ordens;
3) Em cada nível da árvore o nó mais à direita tem a maior ordem, embora possam haver
outros nós com mesmo peso em um mesmo nível;
4) Nós folha sempre armazenarão símbolos, exceto o nó NYT;
5) Nós internos não armazenam símbolos e têm peso igual à soma dos pesos de seus dois
filhos;
6) Nós que têm o mesmo peso devem ter ordens consecutivas.  

A manipulação da árvore é mais complexa do que em Huffman estático, dadas as várias regras que devem ser satisfeitas. Quando 
criada, a árvore contém somente o nó NYT, que é também a raiz da árvore. Ao receber um novo símbolo é feita sua procura na 
árvore. Se não foi encontrado, o nó NYT é expandido em dois nós. O nó à direita contém o novo símbolo e o nó à esquerda se 
transforma no novo nó NYT. O antigo nó NYT é então transformado em um nó interno, recebendo peso 1 e mantendo sua ordem. 
A inserção do caractere “u” é ilustrado na Figura 7.

![Figura 7 - Expansão do nó NYT](/img/figura_7.jpg)  
Figura 7 - Expansão do nó NYT  

Se o símbolo já existir, o peso de seu nó é incrementado. Antes porém, deve ser verificado se o nó sendo atualizado é o de 
maior ordem da classe de peso. Se não é, deve ser trocado com o nó de mesmo peso mas de maior ordem da classe de peso. 
A Figura 8 mostra uma árvore que contém os caracteres `huf` na qual é inserido outro caractere `f`. 

![Figura 8 - Troca de nós durante atualização da árvore](/img/figura_8.jpg)  
Figura 8 - Troca de nós durante atualização da árvore  

Em ambos os casos, de existência ou não do símbolo na árvore, a mudança do peso de um nó folha afeta os pesos de todos os 
nós acima dele. A partir do nó que foi alterado ou inserido, deve ser conferido se o nó acima dele (seu nó pai) é o de maior 
ordem em sua classe de peso. Se não for, deve-se seguir o procedimento de troca de nós descrito no parágrafo anteriormente. 
Somente após realizado este procedimento é feita a atualização do peso do nó.  

A conferência é sempre feita subindo árvore, até chegar ao nó raiz. Na troca de nós também há regras que devem ser seguidas:
1) A raiz nunca é trocada com nenhum outro nó;
2) Um nó nunca é trocado com seu nó pai;
3) Ao fazer a troca de nós, trocar também suas ordens. A ordem não tem relação com o peso ou o símbolo de um nó, mas sim com o 
lugar ocupado por ele na árvore.

A complexidade de manipulação da árvore é compensada pela facilidade de
codificação e decodificação da origem dos dados.


### 3.2.2.2 Codificação
Por ser um algoritmo de uma passagem pelos dados, a manipulação da árvore e a codificação são feitas em conjunto. Ao ler um 
símbolo já existente o caminho da raiz até ele deve ser escrito na saída dos dados (um arquivo, por exemplo), sendo `1` para 
percurso à direita e `0` para a esquerda. Se é um novo, primeiro é escrito o caminho até o nó NYT, sinalizando uma inserção e 
em seguida, o novo símbolo é escrito na saída dos dados. Para ambos os casos o caminho deve ser escrito antes da atualização 
da árvore. O procedimento é repetido até o final da origem dos dados.  

Utilizando a mesma sequência de caracteres de exemplo da forma estática, o resultado final de sua compactação pelo método 
adaptativo é a sequência `a0b1100c011`. Convertendo os caracteres em bits (negrito) temos 
**01100001**0**01100010**1100**01100011**011 = 32 bits de dados compactados contra os 56 originais, resultando numa diminuição 
de 42,85%. A Figura 9 mostra a árvore ao final do processo.

![Figura 9 - Árvore de Huffman adaptativo resultante da compactação da sequência de caracteres "abaacba"](/img/figura_9.jpg)  
Figura 9 - Árvore de Huffman adaptativo resultante da compactação da sequência de caracteres "abaacba"  

### 3.2.2.3 Decodificação
Na decodificação não é necessário nenhum conhecimento prévio dos dados que serão lidos, pois a leitura dos dados compactados e a 
decodificação ocorrem simultaneamente. Também não é necessário fazer buscas de símbolos na árvore, pois a própria fonte de dados 
compactados “guia” o descompactador até eles. Temos na Figura 10 o algoritmo de decodificação, sendo `F` a fonte de dados 
compactados, `Aha` a árvore recriada, `n` um ponteiro para os nós da árvore e `Sd` a saída dos dados descompactados.

![Figura 10 - Algoritmo de decodificação de Huffman adaptativo](/img/figura_10.png)  
Figura 10 - Algoritmo de decodificação de Huffman adaptativo  

Portanto, apesar da complexidade de manipulação da árvore, o resultado final é melhor que o do algoritmo de Huffman estático 
por não precisar manter tabelas de frequência ou armazenar qualquer dado junto com o códigos criados, além dos próprios 
caracteres.


### 3.3 Considerações Finais
Os algoritmos de Huffman são eficientes e simples de implementar, tendo várias aplicações práticas. Embora o algoritmo de 
Huffman estático seja menos eficiente no resultado final da compactação, sua velocidade é bem maior que os outros algoritmos 
testados por Coello (1994). Já o modelo adaptativo consegue melhores resultados por não precisar previamente dos símbolos que 
serão compactados, apesar de ser um pouco mais lento. Tem ainda as vantagens de adaptabilidade dos códigos gerados e de servir 
em aplicações onde o fluxo de entrada de dados é constante.
