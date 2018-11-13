### CAPÍTULO 6 - Conclusões e Trabalhos Futuros
Por fim, neste Capítulo é feita a conclusão do trabalho, expondo suas contribuições
para a área, suas deficiências e fazendo sugestões de trabalhos futuros.


### 6.1 Conclusão
Após o estudo e a implementação com sucesso de um sistema de esteganografia LSB
aliado ao algoritmo de Huffman adaptativo, é mostrada a capacidade da esteganografia em
manter confidencialidade de dados sigilosos. Ela está presente à nossa volta, mesmo que não a
reconheçamos pelo nome ou, como na maioria das vezes, não a vemos agir, já que esse é seu
propósito. As aplicações sugeridas vão desde ocultação de mensagens secretas à marcação
digital de direitos autorais invisível e detecção de adulterações eletrônicas, podendo no futuro
tornar a técnica um sinônimo de segurança e sigilo, como é a criptografia hoje.


### 6.2 Contribuições
Espera-se que este trabalho sirva como incentivo para novos estudos e que seja para
eles fonte de informações. As bibliotecas criadas também são contribuições que são deixadas
para serem reutilizadas e melhoradas por outros desenvolvedores. Que trabalhos como este
despertem a criatividade de outros estudantes e sirvam como incentivo para a criação de
novas técnicas.  


### 6.3 Limitações
Mesmo funcionando como previsto, a implementação dos algoritmos sofre de
algumas deficiências, como a ineficiente busca linear pelo vetor auxiliar, no algoritmo de
compactação de Huffman, e a utilização de imagens bitmap como imagem de cobertura, que
apesar de suas qualidades pelas quais ela foi a escolhida para este trabalho, é um formato
antigo e que é raramente usado.


### 6.4 Trabalhos Futuros
A partir das deficiências encontradas na implementação, são deixadas aqui sugestões
para a melhoria do sistema e novos estudos sobre a esteganografia.

### 6.4.1 Técnica de Esteganografia Empregada
Foi visto que apesar de eficiente em armazenamento, a técnica de esteganografia por
LSB é muito vulnerável a ataques e ruídos inerentes de linhas de transmissão. A
implementação de uma técnica mais robusta é necessária para um sistema que tenha como
objetivo garantir mais segurança aos dados ocultos e sua posterior recuperação completa.


### 6.4.2 Formato de Imagem de Cobertura
Pelas imagens bitmap não serem mais usadas, principalmente após o aparecimento
do JPEG, seria mais interessante uma implementação da técnica que utilize imagens de
formato comum na Internet, como o próprio JPEG e o TIFF ou ainda formatos de vídeo como
AVI e MPEG.

### 6.4.3 Alteração da Implementação de Huffman Adaptativo
Ao desenvolver a biblioteca de Huffman adaptativo, percebeu-se que o algoritmo
escreve o caminho até o nó NYT da árvore para sinalizar a inserção de um novo caractere.
Fica como sugestão que seja modificada essa forma de sinalização. Ao encontrar um novo
caractere, durante a compactação, é enviado o bit "1" e após ele o caractere a ser inserido. No
caso de um caractere já existente, seria enviado o bit "0" e em seguida o caminho até ele.
Dessa maneira, reduz-se a quantidade de bits usados para representar o nó NYT, visto que ele
sempre estará no nível mais baixo da árvore, consumindo sempre a maior quantidade de bits
para ser sinalizado o envio de um novo caractere.

### 6.4.4 Implementação de Algoritmos de Busca e Ordenação de Vetor
Um dos limitadores de velocidade de compactação da implementação do algoritmo
de Huffman adaptativo implementado é o vetor auxiliar. Durante as inserções nele, os nós são
colocados em sequência. Dessa maneira, para chegar ao último novo caractere inserido, é
necessário conferir posição a posição do vetor, tendo que passar por muitos nós internos, que
não têm efeito nenhum durante a busca. Por isso, seria mais eficiente implementar uma
ordenação no vetor que colocasse os nós folha nas primeiras posições.  

Além da ordenação seria também interessante a implementação de um algoritmo de
busca em vetor mais eficiente do que a busca linear. Outra forma de se implementar a busca é
a utilização de uma função recursiva, de melhor desempenho que uma busca em vetor.
