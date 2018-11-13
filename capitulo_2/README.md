### CAPÍTULO 2 - MÉTODOS DE ESTEGANOGRAFIA E SUAS CLASSIFICAÇÕES
Por não existir uma padronização da esteganografia como acontece com a criptografia, vários métodos foram criados, assim como definições para classificá-los. Alguns desses métodos e as classificações criadas para diferenciá-los são aqui estudados.  

### 2.1 Métodos de Esteganografia
Os métodos de esteganografia definem como e onde os dados devem ser inseridos no arquivo de cobertura. Com o crescente estudo da esteganografia várias técnicas foram desenvolvidas e aplicadas, cada uma com sua abordagem particular. Em seguida são apresentados alguns dos tipos de esteganografia existentes, segundo Katzenbeisser e Petitcolas (2000).  

### 2.1.1 Sistemas de Substituição
Sistemas deste tipo ocultam informações no arquivo de cobertura substituindo suas informações pelos bits dos dados sendo ocultados. São também chamados de ferramentas a nível de bit ou de inserção de ruído. São elas:
  

### 2.1.1.1 Substituição de Bit Menos Significativo
Na técnica LSB (Least Significant Bit, bit menos significativo) os bits menos significativos dos bytes do arquivo de cobertura são alterados para os bits da mensagem que se deseja ocultar. Utilizando uma substituição de 1 LSB são necessários 8 bytes da imagem de cobertura para cada byte a ocultar. A Tabela 1 demonstra o resultado final da inserção do caractere “A” em 8 bytes lidos de um arquivo de imagem. Os bits destacados são os que foram inseridos.  


![Tabela 1 - Processo de ocultação de um caractere usando a técnica LSB](/img/tabela_1.jpg)  
Tabela 1 - Processo de ocultação de um caractere usando a técnica LSB


A técnica permite que grande quantidade de dados sejam ocultados sem praticamente alterar perceptivelmente as características do arquivo original (KATZENBEISSER; PETITCOLAS, 2000).
  

### 2.1.1.2 Permutações Pseudo-Aleatórias
Técnica é similar à LSB, mas oculta os bits de forma diferente. Enquanto na técnica LSB os bits são embutidos nos bytes da cobertura sequêncialmente, nesta eles são espalhados em bytes escolhidos pseudo-aleatoriamente. Todos os bits da imagem de cobertura devem ser acessíveis dessa maneira. Esta técnica dificulta um ataque aos dados ocultos, pois não se sabe em qual byte da cobertura estão os bits a recuperar.
  

### 2.1.1.3 Degradação de Imagens e Canais de Cobertura
Duas imagens são utilizadas na aplicação desta técnica: uma de cobertura e a que será ocultada, ambas com as mesmas dimensões. Na inserção, para cada componente de cor da imagem de cobertura, seus 4 bits menos significativos são substituídos pelos 4 bits mais significativos da imagem sendo ocultada. Para extrair a imagem oculta, deve-se extrair os 4 bits menos significativos da estego-imagem e transformá-los em 4 bits mais significativos, que irão compor a imagem extraída.
  

### 2.1.2 Técnicas de Transformação de Domínio
Sistemas baseados em alteração de bits menos significativos podem sofrer alterações com ruídos do canal por onde trafegam ou por uma compactação com perdas da imagem de cobertura. Essas interferências podem destruir a integridade da mensagem oculta, tornando impossível sua recuperação. Com o desenvolvimento e evolução da esteganografia foi notado que é mais seguro armazenar os dados no domínio de frequência, sendo utilizado frequentemente a DCT (Discrete Cosine Transform, transformada discreta de coseno) na esteganografia em imagens.  

Técnicas que utilizam a DCT operam em áreas significantes da imagem e mesmo assim as alterações ainda ficam imperceptíveis. Estego-imagens geradas com esta técnica são mais robustas em ataques de recorte e transformações dimensionais, podendo até serem compactadas com algoritmos com perdas e serem completamente recuperadas posteriormente. Apesar da maior segurança, há diminuição na quantidade de dados que podem ser inseridos na imagem pois as alterações são feitas em áreas, não em bytes individuais. Além da DCT existem também a DFT (Discrete Fourier Transform, transformada discreta de Fourier), transformação wavelet e Echo hiding (para arquivos de áudio).
  

### 2.1.3 Espalhamento Espectral
Desenvolvida durante os anos 50 para aplicações militares, a técnica é utilizada contra interferências intencionais em radares (anti-jamming) e pela sua pouca probabilidade de interceptação. O espalhamento espectral é obtido quando se envia um sinal que ocupa uma largura de banda maior do que a necessária para a transmissão das informações (PICKHOLTZ et al, 1982 apud KATZENBEISSER; PETITCOLAS, 2000), que transforma o sinal em ruído. Esse espalhamento faz com que a energia do sinal em qualquer frequência seja baixa, dificultando sua detecção (OREBAUGH, 2004).  

O uso do espalhamento espectral em esteganografia é feito ocultando em uma imagem de cobertura uma mensagem com ruído. A mensagem secreta é modulada de modo que se pareça com ruído Gaussiano. O sinal resultante, percebido como ruído, é embutido na
imagem de cobertura, resultando na estego-imagem. Este método é robusto contra ataques de extração, mas ainda é vulnerável à perda dos dados por compressão ou processamento de imagem (OREBAUGH, 2004).
  

### 2.1.4 Observações Sobre os Métodos
Nota-se que ainda não existe um método completamente eficaz de esteganografia, sendo necessário escolher qual característica se deseja manter: confidencilidade, sobrevivência, não-detecção ou visibilidade. Quanto maior a satisfação de uma das características, maior a diminuição da eficiência quanto às demais.  

A complexidade dos algoritmos aumenta cada vez mais, o que também aumenta a dificuldade de detecção, extração e destruição do conteúdo embutido.
  

### 2.2 Classificações da Esteganografia
Cole (2003) divide os métodos em duas classificações: original e nova. Na classificação original os métodos são classificados com base na maneira como os dados são ocultos e na nova é levado em consideração também onde os dados são ocultos. Diante do aparecimento de novas técnicas, a classificação original tornou-se insuficiente para abrangê-las, sendo criada a nova classificação.
  

### 2.2.1 Classificação Original
a) Baseado em Inserção  
Algoritmos de esteganografia baseados em inserção procuram no arquivo de cobertura dados que podem ser alterados sem impacto significativo em suas características. Em todos os arquivos em que a técnica é aplicada os dados são inseridos sempre nos mesmos locais. Dependendo do tipo de arquivo, os dados podem ser inseridos, por exemplo, entre cabeçalhos, tabelas de cores e bits menos significativos. 

b) Baseado em Algoritmo  
Métodos baseados em algoritmo elegem locais apropriados no arquivo de cobertura para ocultar os dados. Diferente dos algoritmos baseados em inserção, os dados não são sempre inseridos nos mesmos pontos, podendo causar degradação da qualidade do arquivo e tornar perceptível sua alteração.  

c) Baseado em Gramática  
Nesta classificação entram os métodos que geram seu próprio arquivo de cobertura. A partir de uma gramática pré-definida um arquivo de cobertura é criado, de modo que a saída se pareça o máximo possível com a gramática. Um exemplo seria a utilização de uma gramática que contenha palavras da seção financeiro de um jornal. Um algoritmo baseado em gramática geraria um texto de saída parecido com uma reportagem financeira. Quanto maior o nível (ou complexidade) da gramática, mais parecida com a linguagem especificada será a saída.
  

### 2.2.2 Nova Classificação
a) Baseado em Inserção  
Os algoritmos de inserção da nova classificação procuram no arquivo de cobertura locais que são ignorados, pelo programa que o representa, quando é lido. Pode-se, por exemplo, inserir dados após a marcação de EOF (End of file ou fim de arquivo). Isso provoca aumento do tamanho do arquivo, que pode ser notado caso seja comparado ao arquivo de cobertura original. Nota-se que, embora estejam presentes nas duas classificações e tenham o mesmo nome, algoritmos baseados em inserção funcionam de forma distinta nas duas classificações.  

b) Baseado em Substituição  
Nesta abordagem se enquadram os algoritmos que substituem dados do aquivo de cobertura para ocultar dados, de forma que as alterações sejam imperceptíveis aos sentidos. Dessa maneira nem o tamanho nem as propriedades (visuais ou auditivas) do arquivo de cobertura são alterados. A quantidade de dados que pode ser oculta se limita à quantidade de dados existentes no arquivo de cobertura.  

c) Baseado em Geração  
Como nos métodos baseados em gramática, citados na classificação original, os métodos baseados em geração não necessitam de um arquivo de cobertura. Dessa maneira evita-se que o arquivo de cobertura original seja comparado a um que tenha os dados ocultos, podendo levar à detecção da utilização da esteganografia. A técnica mais utilizada em algoritmos baseados em geração é a criação de imagens fractais. As imagens são geradas fornecendo os dados a serem ocultos como semente para a fórmula matemática utilizada.
  

### 2.3 Considerações Finais
Ao final deste Capítulo percebe-se o quanto a esteganografia é estudada atualmente e a evolução dos métodos, de simples substituições de bits a complexas fórmulas de transformação de domínio. As técnicas LSB são vantajosas em quantidade de dados que se pode ocultar em um arquivo de cobertura e a facilidade de implementação mas têm a desvantagem de serem sucetíveis a ruídos, compactação e processamento do arquivo de cobertura. As técnicas de transformação discreta e espalhamento de espectro mantêm a informação mais protegida, porém suas eficiências de armazenamento são reduzidas. A criação de tanto material novo levou à criação de parâmetros de classificação que, embora informais, servem como referência enquanto não é feita uma padronização oficial.
