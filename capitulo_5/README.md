### CAPÍTULO 5 - TESTES E ANÁLISE DE RESULTADOS
Para avaliar o desempenho das bibliotecas e do programa principal desenvolvidos
neste trabalho, testes foram feitos e seus resultados foram analisados para demonstrar a
eficiência da implementação e o funcionamento das técnicas empregadas.


### 5.1 Configuração de Hardware
Os testes foram realizados em um computador com a seguinte configuração de
hardware:  

• Notebook Dell Modelo D520;  
• Processador: Intel(R) Core(TM)2 CPU T5500 @ 1.66GHz;  
• Memória : 2GB DDR2;  
• Adaptador de Vídeo: Mobile Intel(R) 945GM Express Chipset Family (256MB, PCI, PS
2.0);  
• Disco Rígido: WDC WD1200BEVS-75UST0 120GB (SATA150, 2.5", 5400rpm, NCQ,
8MB Cache);  

### 5.2 Configuração de Software
Os seguintes softwares foram utilizados para o desenvolvimento e os testes:  

• Sistema Operacional: Microsoft Windows XP (2002) Professional 5.01.2600 (Service
Pack 3);  
• IDE de Desenvolvimento: Bloodshed Dev-C++, Versão 4.9.92;  

### 5.3 Testes e Análises de Resultados
Os testes e as análises das bibliotecas e do programa principal foram feitos
separadamente. Cada sub-seção a seguir mostra os resultados obtidos em cada uma dessas
partes.  

### 5.3.1 Biblioteca adaphuff
Os testes da implementação do algoritmo de compactação de Huffman adaptativo
foram feitos com 15 arquivos, sendo 5 no formato .exe (executáveis) e 10 no .txt (texto), com
tamanhos aproximados de 1 a 5 megabytes cada.  

#### 5.3.1.1 Teste 1.1 – Compactação de Arquivos .exe e .txt
Neste teste foi feita a compactação e a posterior descompactação de arquivos
executáveis e de texto. Foram usados dois arquivos de texto diferentes: um contendo o
alfabeto (26 caracteres) repetido várias vezes e outro com caracteres aleatórios. O objetivo do
uso desses dois arquivos de texto é verificar como a frequência dos símbolos influencia na
eficiência do algoritmo. O arquivo executável é usado para demonstrar que a adaptação da
estrutura da árvore apresentada no Capítulo 4 funciona como esperado. O Gráfico 1 mostra o
tempo de compactação necessário para cada arquivo e o Gráfico 2 mostra a eficiência de
compactação.  

![Gráfico 1 - Tempo de compactação, em segundos, dos arquivos texto e executáveis](/img/gráfico_1.png)  
Gráfico 1 - Tempo de compactação, em segundos, dos arquivos texto e executáveis  


![Gráfico 2 - Eficiência, em porcentagem, da compactação de arquivos texto e executáveis](/img/gráfico_2.png)  
Gráfico 2 - Eficiência, em porcentagem, da compactação de arquivos texto e executáveis  

Nota-se pelo Gráfico 1 que tanto arquivos executáveis quanto de texto aleatório
tomam mais tempo para serem compactados do que os textos repetitivos. Isso se deve ao fato
de haver mais pesquisas por caracteres já existentes e percursos maiores feitos na árvore, para
escrever os códigos de Huffman. Ao analisar o Gráfico 2 é percebida a grande diferença de
eficiência entre a compactação de arquivos de texto e executáveis, chegando a ser negativa
para os executáveis, ou seja, o arquivo de saída é maior que o executável original. Conclui-se
que arquivos executáveis têm pouca redundância em sua estrutura, diferente de arquivos
textos que têm várias repetições, como o espaço que é dado entre palavras.  


#### 5.3.1.2 Teste 1.2 – Descompactação de Arquivos .exe e .txt
Ao fazer a descompactação dos arquivos do Teste 1.1 e analisar o tempo de
descompactação, temos os resultados mostrados no Gráfico 3.  


![Gráfico 3 - Tempo de descompactação, em segundos, dos arquivos texto e executáveis](/img/gráfico_3.png)  
Gráfico 3 - Tempo de descompactação, em segundos, dos arquivos texto e executáveis  


Por não precisar fazer buscas na árvore para saber ser o caractere já existe, a
descompactação é bem mais eficiente em tempo de processamento. A proporção de tempo
gasto entre os diferentes tipos de arquivos, em comparação com a compactação, foi mantida
na descompactação.  

É concluído então que quanto maior a quantidade de caracteres existentes em um
arquivo e menor suas repetições, mais demorado e menos eficiente é o processo de
compactação e descompactação. Para arquivos com poucos caracteres que são repetidos
várias vezes, o algoritmo de Huffman é muito eficiente, tanto em tempo de processamento
quanto na razão de compactação.  


#### 5.3.1.3 Teste 1.3 – Compactação e Descompactação de Imagens .bmp
Partindo das conclusões do teste anterior foram feitos testes com imagens bitmap
com dominância de cores e com imagens com várias cores misturadas. Para isso foram
escolhidas duas imagens, as Figuras 14 e 15.  

![Figura 14 - Imagem com várias cores e em vários tons diferentes](/img/figura_14.jpg)  
Figura 14 - Imagem com várias cores e em vários tons diferentes  

![Figura 15 - Imagem bicromática](/img/figura_15.jpg)  
Figura 15 - Imagem bicromática  


Fazendo a compactação da Figura 14 tem-se uma redução de 6,41% no seu tamanho
em 77.22 segundos, passando de 1.222.890 bytes a 1.144.530 bytes. Já com a Figura 15 foi
obtida uma compactação de 71,12% em 29,13 segundos de 742.054 bytes para 214.320 bytes.
Para fazer a descompactação da Figura 14 são gastos 37,61 segundos contra apenas
7,08 segundos para a Figura 15. Portanto, conclue-se que a repetição de cores em imagens é
tão vantajosa para a eficiência do algoritmo quanto repetições de letras em arquivos texto.


### 5.3.2 Biblioteca stglsb
Para os testes da biblioteca de esteganografia desenvolvida foram utilizados arquivos
executáveis, de imagem, documento e áudio.  

#### 5.3.2.1 Teste 2.1 – Degradação Progressiva de Uma Imagem de Cobertura
A quantidade de dados que uma imagem consegue ocultar depende das dimensões
dessa imagem e de quantos LSBs serão substituídos em cada pixel. Não se pode esquecer do
princípio da visibiliade, ou seja, as alterações que dados ocultos podem causar a uma imagem
de cobertura. Quantidades seguras de LSBs deve ser escolhidas para que não haja
interceptação da imagem e destruição, ou mesmo extração, da mensagem oculta. Neste teste
um arquivo é inserido várias vezes em uma imagem, fazendo uma substituição gradual de 1 a
8 LSBs e verificando os impactos visuais. A imagem de cobertura que foi usada em todos os
testes desta biblioteca é a Figura 16, uma imagem bitmap de resolução 1200 por 1600 pixels e
tamanho de arquivo de 5,49 MB. A quantidade total de bits que uma imagem pode ocultar é
((altura x largura) x 3) x Qlsb, sendo 3 a quantidade de bytes que representam um pixel e Qlsb
a quantidade de LSBs a substituir. Nesta imagem teríamos 5.760.000 bits disponíveis com a
substituição de apenas 1 LSB por byte. As Figuras 17 e 18 mostram os resultados da
alterações de 1 a 8 LSBs de uma imagem bitmap, de dimensões 360 por 480 pixels e 518.454
bytes de tamanho.

![Figura 16 - Imagem de cobertura "sacada.bmp"](/img/figura_16.png)  
Figura 16 - Imagem de cobertura "sacada.bmp"  
> Nota: a imagem .bmp excede o tamanho máximo permitido pelo github. Para efeito de ilustração mantive uma versão .png equivalente  

![Figura 17 - Resultados das substituições de 1 a 4 bits menos significativos](/img/figura_17.jpg)  
Figura 17 - Resultados das substituições de 1 a 4 bits menos significativos  

![Figura 18 - Resultados das substituições de 5 a 8 bits menos significativos](/img/figura_18.jpg)  
Figura 18 - Resultados das substituições de 5 a 8 bits menos significativos  


Não há qualquer indício visual de alterações na primeira e na segunda imagens da
Figura 15. Contudo, se olharmos seus histogramas e compará-los com o da imagem original,
teremos a visão da Figura 19. São verificadas alterações anormais nas cores vermelho e verde,
para 1 LSB e em todas as cores para 2 LSBs. Essa "sombra" que se nota no histograma leva à
suspeita de alteração da imagem, mesmo que não se tenha a original à disposição, abrindo a
possibildade de um ataque de extração ou de destruição da mensagem oculta.


![Figura 19 - Comparativo do histograma da imagem original com os de imagens que tiveram 1 e 2 LSBs alterados](/img/figura_19.png)  
Figura 19 - Comparativo do histograma da imagem original com os de imagens que tiveram 1 e 2 LSBs alterados  

Esta análise nos leva à conclusão de que, apesar de ser uma técnica eficiente quanto a
quantidade de armazenamento de dados, a esteganografia por LSB é frágil a ataques e
facilmente identificável.  


#### 5.3.2.2 Teste 2.2 – Inserção e Extração de Arquivos
Para garantir que a implementação do algoritmo funciona corretamente, alguns testes
simples de inserção e extração foram feitos. Foram usados nestes testes: um arquivo
executável (.exe), um documento (.doc), uma imagem (.jpg) e um arquivo de áudio (.mp3). O
arquivo bitmap usado de cobertura foi a Figura 16.  

• Arquivo executável  
Foi inserido na imagem um arquivo executável de 1.093.438 bytes, que ocupou
75,93% da imagem, com substituição de 2 LSBs, e consumiu 6,80 segundos. A extração
demorou 5,73 segundos, recuperando os 1.093.438 bits de informação oculta. A execução do
programa extraído ocorreu normalmente.  

• Arquivo de documento  
O arquivo .doc do Microsoft Word 2003 de 2.593.765 bytes levou 13,47 segundos
para ser oculto, necessitando de 4 LSBs da imagem, ocupando 90,06% de sua área. Para
recuperá-la foram necessários 12,70 segundos, extraindo corretamente o arquivo, sem falhas.  

• Arquivo de imagem  
Uma das possibilidades mais interessantes da esteganografia é a possibilidade de
embutir imagens dentro de outras imagens. Foi feita a inserção de uma imagem .jpg de
228.953 bytes na imagem de cobertura com o uso de 1 LSB, ocupando 31,08% dos bytes da
imagem em somente 2,98 segundos. A extração foi bem sucedida, levando 1.36 segundos.  

• Arquivo de áudio  
Para o teste com o arquivo de áudio foi utilizada uma música no formato .mp3 de
3.251.061 bytes de tamanho, de 2:15 minutos de duração. Com utilização de 5 LSBs foram
ocupados 90,31% da imagem em 16,38 segundos. Sua extração durou 15,98 segundos e a
música foi reproduzida sem falhas.  

A inserção e a extração funcionam da mesma maneira para qualquer tipo de arquivo,
pois suas estruturas internas são irrelevantes no processo. Os testes feitos concluem que a
biblioteca desenvolvida é capaz de operar com qualquer tipo de arquivo e proceder sua
recuperação integral, funcionando como esperado.  


### 5.3.3 Programa Principal
Como os detalhes de desempenho de cada biblioteca já foram testados e validados, o
que resta a analisar do programa principal é o funcionamento do conjunto e sua performance
de tempo. Para isso serão usados três dos tipos de arquivos já utilizados nos testes anteriores:
executável, imagem e áudio.  


#### 5.3.3.1 Teste 3.1 – Inserção e Extração de Arquivo Executável
Para o teste com esse formato foi utilizado o arquivo de 1 MB do Teste 1.1,
inserindo-o na mesma imagem de cobertura utilizada até agora. O processo de inserção foi
bem sucedido, consumindo 80,23 segundos e utilizando 2 LSBs de cada byte da imagem. A
Figura 20 mostra a estego-imagem, visivelmente inalterada.  

![Figura 20 - Estego-imagem contendo um arquivo executável de 1MB compactado](/img/figura_20.png)  
Figura 20 - Estego-imagem contendo um arquivo executável de 1MB compactado  
> Nota: a imagem .bmp excede o tamanho máximo permitido pelo github. Para efeito de ilustração mantive uma versão .png equivalente  

Para finalizar o teste foi feita a extração e o teste de funcionamento do arquivo.
Levando 41,94 segundos pra extrair, o descompactador recriou o arquivo com sua extensão e
tamanho originais. A Figura 21 mostra a instalação do software sendo executada a partir do
arquivo recuperado. Assim, o sistema funciona para arquivos executáveis, mostrando o risco
que um sistema de esteganografia pode representar se usado com propósitos criminosos, como
por exemplo, disseminação de vírus.


### 5.3.3.2 Inserção e Extração de Arquivo de Imagem
O formato .jpg foi escolhido para este teste por seu tamanho já reduzido, usando
poucos bytes da imagem de cobertura. A imagem original tem 228.953 bytes e resolução de
1600 por 1200 pixels. Por já ser um formato de imagem compactado, o arquivo compactado
teve aumento de 0,07% do tamanho original. A inserção utilizou 1 LSB de cada byte da
imagem, cobrindo um total de 31,82% da imagem de cobertura. Todo o processo durou 18,22
segundos. Na extração foram necessários somente 8,94 segundos, sendo a imagem
perfeitamente extraída (Figura 21).  


![Figura 21 - Imagem "bar.jpg" extraída da estego-imagem](/img/figura_21.jpg)  
Figura 21 - Imagem "bar.jpg" extraída da estego-imagem  


Portanto, o sistema também é capaz de inserir e extrair imagens embutidas em
arquivos bitmaps.  


### 5.3.3.3 Inserção e Extração de Arquivo de Áudio
Descrito no Capítulo 1 em utilizações da esteganografia, o uso de arquivos de
imagens inocentes para transmitir áudio foi feito por um traficante para dar ordens de
execução de rivais a comparsas. Neste teste será demonstrada essa possibilidade.  

Tomamos um arquivo .mp3 de 2.125.824 bytes, o suficiente para armazenar 1:30 de áudio de ótima
qualidade. Após passados 150,86 segundos dos processos de compactação e inserção, o
arquivo foi reduzido a 2.088.448 bytes, com compactação de 1,74% e usando 3 LSBs da
imagem de cobertura. Em seguida foi feita sua extração e descompactação, que levou 79,44
segundos, recuperando o arquivo completamente audível, levando à conclusão que o uso da
técnica pode ser utilizado também para áudio.  


### 5.4 Conclusões Finais
Ao usar a compactação de dados o sistema desenvolvido faz algo semelhante à
criptografia, que é dissimular os bits de suas sequências corretas, confundindo um possível
atacante. Além disso, também há o ganho em espaço de armazenamento, principalmente com
arquivos de texto que têm muita repetição de caracteres.  

Foi demonstrado que o sistema pode inserir e extrair qualquer tipo de arquivo em
imagens bitmap e fazer sua recuperação posterior sem erros ou falhas. Todos os objetivos
propostos foram alcançados e os testes feitos demonstraram a eficiência de um sistema
esteganográfico.
