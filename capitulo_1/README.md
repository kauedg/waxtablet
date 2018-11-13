### CAPÍTULO 1 - ESTEGANOGRAFIA: UMA VISÃO GERAL
A esteganografia é uma técnica de segurança de informação que permite que dados sejam transmitidos de modo que sua própria existência não possa ser notada. Este Capítulo é resultado do estudo da técnica e seus conceitos, sobre os quais o trabalho é estruturado.  

#### 1.1 Definição  
A palavra esteganografia tem origem grega e significa “escrita encoberta” (ANDERSON et al, 1999), podendo também ser definida como a arte da ocultação de mensagens. A técnica é baseada no uso de um objeto de cobertura, que irá receber a mensagem que se deseja transmitir. O objeto de cobertura pode ser um objeto comum qualquer ou mesmo uma outra mensagem, sendo possível extrair dela a mensagem original, sabendo-se o método de extração. Não deve haver nenhuma alteração física no objeto de cobertura que evidencie a presença do conteúdo embutido.  

A ocultação da existência de uma mensagem é necessária quando se deseja transmití-la em segurança por meios hostis. Um meio hostil é aquele em que agentes externos têm a intenção de extrair, alterar ou destruir a mensagem oculta, com a intenção de conhecer o segredo ou evitar sua recepção. Em sua forma clássica é a ocultação de uma mensagem em uma mensagem de cobertura, de modo que as características da segunda não sejam visivelmente alteradas (ANDERSON; PETITCOLAS, 1998). Na forma digital dados são inseridas em outros tipos de dados como arquivos de imagem, vídeo e som, entre outros.  

#### 1.2 Terminologia  
Com a criação e o crescente estudo da esteganografia, muitas formas de descrever suas características e componentes foram definidos, embora os autores de trabalhos muitas vezes divergiam nos termos utilizados.  

Para que houvesse um consentimento foi realizado em Cambridge, Inglaterra, o First Information Hiding Workshop, em 1996, onde Pfitzmann (1996) propôs que a nomenclatura dos termos relacionados a esteganografia e fingerprinting (marcação para reconhecimento da origem, direitos autorais e número de série) deveria seguir um padrão de sufixos e prefixos, dependendo da aplicação.

![Figura 1](/img/figura_1.jpg)  
Figura 1 - Nomenclatura dos termos usados em esteganografia (Fonte: PFITZMANN,1996).

Seguindo a proposta do autor, neste trabalho será utilizada a seguinte nomenclatura, ilustrada pela Figura 1:

\<tipo de dado\> de cobertura (*cover-\<datatype\>*):  
Nomenclatura dada a um objeto que irá receber os dados a serem escondidos. Pode-se substituir o sufixo “cobertura” por recipiente”. Exemplos: imagem de cobertura, arquivo de cobertura, objeto de cobertura, vídeo de cobertura.

\<tipo de dado\> embutido (*embedded \<datatype\>*):  
Dados que estejam esteganografados em um objeto de cobertura. Também pode-se substituir a palavra “embutido” por “oculto” ou “escondido”. Exemplos: dado embutido, mensagem embutida, imagem embutida.

estego-\<tipo de dado\> (*Stego-\<datatype\>*):  
Arquivo que contenha conteúdo esteganografado dentro de si. Também chamado de estego-objeto. Exemplos: estego-imagem, estego-áudio, estego-arquivo. 

(estego-)chave (*(stego-)key*):  
Chave utilizada para proteger os dados embutidos e permitir ou negar a extração dos dados.

#### 1.3 Utilização  
A garantia de que a mensagem oculta está bem protegida pela mídia recipiente torna a esteganografia uma técnica ideal para armazenamento e transmissão de informações importantes. Da mesma maneira que a esteganografia ajuda a manter dados em segurança, pode também auxiliar seu furto, permitindo a um espião colocar tais dados em imagens que não levantariam suspeita em um sistema de vigilância de tráfego de rede ou em uma revista de segurança.  

A esteganografia não serve somente para ocultação de mensagens. Segundo Anderson e Petitcolas (1998), marcas d'água digitais invisíveis podem ser inseridas em imagens, o que auxiliaria na identificação de alterações. Através desta mesma técnica é
possível marcar uma imagem que esteja sob direitos autorais. Mais aplicações podem ser o fingerprinting, a monitoração de propagandas em rádio, detecção de traidores e inserção dos dados de um paciente em imagens médicas DICOM (Digital Imaging and Communication in Medicine). As imagens DICOM carregam consigo os dados do paciente, a data e o nome do médico. Contudo, algumas vezes a ligação entre os dados e a imagem é perdida, portanto a inserção do nome do paciente na imagem ajudaria a manter a consistência das informações (ANDERSON; PETITCOLAS, 1998).  

Há também o temor de que terroristas utilizem a técnica para comunicação e planejamento de ataques. Em 2001 o jornalista Jack Kelley publicou, em sua coluna de tecnologia no jornal The USA Today, que Osama bin Laden teria planejado os ataques terroristas, em 11 de setembro daquele ano, ao World Trade Center, utilizando a esteganografia como forma de comunicação durante o planejamento (KELLEY, 2001). Com a descoberta da invenção dessa e de várias outras reportagens (BANVILLE, 2004) Kelley foi demitido do jornal.  

Em 2007 o traficante colombiano Juan Carlos Ramirez-Abadia, um dos mais procurados do mundo, foi preso no Brasil acusado, entre outros crimes, de lavagem de dinheiro do tráfico de drogas (TERRA, 2007). Foram encontradas em seu computador mais de 200 imagens, contendo comandos de voz e texto ocultos, direcionadas ao controle do narcotráfico. Tendo as imagens temas infantis, sua presença no computador de um traficante levantou suspeitas. Foi necessária a ajuda do departamento antidrogas dos Estados Unidos (DEA - Drug Enforcement Administration) para extrair os dados, já que aliado à esteganografia foi utilizada a criptografia (TERRA, 2008 e ZMOGINSKI, 2008). Essas notícias demonstram como a esteganografia pode ser perigosa quando utilizada para o crime.

#### 1.4 Histórico  
Um dos primeiros registros sobre a esteganografia é feito em “História”, de Heródoto (ALIGHERI et al, 1957), onde é descrito o uso de tábuas de escrita de madeira cobertas de cera (sobre as quais mensagens podiam ser escritas) e da cabeça de um escravo como meios de comunicação secreta. No primeiro método a cera era retirada e o texto a ser transmitido era escrito sobre a madeira. A cera retirada era então derretida novamente sobre a tábua com a mensagem, ocultando-a. Heródoto conta que Demerato, filho de Ariston, estava em Susa quando Xerxes decidiu liderar seu exército até a Grécia. Desejando secretamente avisar Esparta sobre o ataque, Demerato tomou duas destas tábuas, retirou a cera e escreveu sobre a madeira os planos de Xerxes. Feito isso derreteu a cera e cobriu novamente a tábua, ocultando a mensagem. Guardas que controlavam o tráfego e as cargas dos viajantes nas estradas nada viam, ao fiscalizar as encomendas, além de tábuas de escrita sem uso. Quando as tábuas chegaram à Grécia não havia ninguém que soubesse da existência e muito menos do método de revelação do segredo. Até o dia em que Gorgo, filha de Cleomenes e esposa de Leônidas, suspeitando das tábuas sem texto, retirou a cera e revelou as mensagens, possibilitando a Esparta se preparar para o ataque.  

O segundo método consistia em raspar a cabeça de um escravo e tatuar a mensagem em sua cabeça. Assim que seu cabelo crescesse novamente o escravo era enviado sabendo somente como revelar a mensagem. Tal método era prático na época pois as notícias demoravam meses para serem transmitidas entre locais distantes. Durante a história foram desenvolvidos vários outros métodos de ocultação de mensagens, a maioria destinada à comunicação durante guerras. Existem registros da Segunda Guerra Mundial sobre o uso de sucos de frutas cítricas ou de cebola, leite e vinagre como “tinta” para se escrever mensagens, sendo esta revelada ao se oxidar a solução utilizando-se uma fonte de calor (KAHN, 1996 apud BENTO; COELHO, 2004). Durante as duas Guerras Mundiais, os alemães utilizaram a tecnologia dos micropontos, que permitia que folhas inteiras de texto pudessem ser comprimidas ao tamanho de um ponto final comum ou o ponto de um “i” ou um “j”.

#### 1.5 Princípios  
O objetivo básico da esteganografia é a ocultação de uma mensagem em outra mensagem de cobertura, de modo que sua existência seja ignorada. Cole (2003) diz que três princípios centrais podem ser usados para medir a efetividade de um sistema de
esteganografia:  

• Quantidade de dados: a quantidade de dados que os sistemas de esteganografia permitem ocultar em um arquivo de cobertura pode ser utilizada para comparar suas eficiências.  

• Dificuldade de detecção: define a dificuldade de se detectar a existência de dados ocultos após a utilização da técnica. Há uma relação direta, na maioria dos sistemas, entre quantidade de dados que podem ser ocultos e sua dificuldade de detecção:
quanto maior a quantidade de dados inserida, maior é a distorção do arquivo de cobertura e conseqüentemente, a facilidade de se suspeitar da utilização da esteganografia.  

• Dificuldade de remoção: característica que define que um possível interceptador do arquivo de cobertura não deve conseguir remover a mensagem (por extração ou destruição) facilmente.  


#### 1.6 Segurança
Nesta seção é apresentada a definição, baseada nos itens descritos por Cole (2003), das características de segurança de um sistema ideal de esteganografia. Segundo o autor, a segurança de computadores e de redes devem ter certos padrões que qualquer comunicação secreta deveria alcançar. Apesar de nenhum método alcançar completamente todos os requisitos, a esteganografia satisfaz muitos deles, algumas vezes em conjunto com outras técnicas como a criptografia. Na próxima sub-seção é feita a definição da criptografia e sua diferenciação da esteganografia e em seguida, as características definidas por Cole.


#### 1.6.1 Criptografia
De acordo com Simon (1999, apud CHIARAMONTE et al):
> “A criptografia pode ser entendida como um conjunto de métodos e
técnicas para cifrar ou codificar informações legíveis por meio de um
algoritmo, convertendo um texto original em um texto ilegível, sendo
possível mediante o processo inverso, recuperar as informações
originais.”  

Existem dois métodos de criptografia: por código e por cifra. Na criptografia por código, as letras da mensagem são substituídas por códigos ou símbolos predefinidos, o que obriga o emissor e o receptor a manterem uma tabela de correspondência entre as letras e os códigos. Na cifragem, a transposição e a substituição eliminam a necessidade de manter essa correspondência, sendo necessário somente o conhecimento do processo de cifragem/decifragem. Neste método é utilizado o conceito de chaves.  

Em transposição a mensagem é cifrada aplicando-se um desvio da posição de suas letras. Aplicando um desvio de quatro posições na palavra “CIFRA” sua cifragem resultaria na cifra “GMJVE”. Encriptação é a definição dada ao processo de transformar um texto legível em um texto ilegível, sendo a decriptação a transformação inversa. Para encriptar um texto utilizando a cifragem é necessário fornecer ao algoritmo um domínio de números ou símbolos que servirão para proteger a informação cifrada (CHIARAMONTE et al 2005). Esse domínio é chamado de chave. Somente com a utilização da chave é possível fazer a decriptação da
mensagem.  


O funcionamento de um algoritmo por cifragem é análogo ao de uma porta com fechadura. O funcionamento do algoritmo (que seria a fechadura) é público sendo a segurança do sistema baseado em sua chave. Foi provado historicamente que não existe um algoritmo que não possa ser quebrado (CHIARAMONTE et al, 2005), portanto seria imprudente confiar a segurança dos dados à restrição do conhecimento de seu funcionamento. A confiança do método é baseada no uso das chaves corretas.
As chaves criptográficas podem ser classificadas em simétricas ou assimétricas. Na criptografia de chave simétrica, a cifragem e a decifragem são feitos por meio de uma única chave, e na criptografia assimétrica, a cifragem é feita utilizando-se uma chave pública, conhecida por todos, e a decifragem por uma chave privada (gerada a partir da chave pública) de conhecimento exclusivo do receptor da mensagem. Um modelo de sistema de criptografia de simétrica feito por Brunori Junior (1999) é apresentado na Figura 2.

![Figura 2](/img/figura_2.jpg)  
Figura 2 - Criptografia simétrica (Fonte: BRUNORI JUNIOR, 1999).  

Embora façam parte de um mesmo domínio de estudo, a criptologia, os propósitos da esteganografia e da criptografia são distintos. Na criptografia, a mensagem é alterada de modo que seu significado seja ilegível e decifrável somente por meio de utilização de chaves e a segurança reside no sigilo das chaves utilizadas. Na esteganografia, a mensagem é incorporada ao objeto que a receberá, sendo a segurança confiada à manutenção das características deste objeto.  

As duas técnicas podem funcionar em conjunto, uma como complemento da outra. Ao ocultar uma mensagem em uma imagem, pode-se aplicar a criptografia à ela e, posteriormente, embutir a mensagem cifrada. Se a imagem for interceptada, será necessário que o atacante descubra que existe uma mensagem oculta e, em seguida, como extrair essa mensagem. Após a extração será ainda preciso descobrir a chave utilizada para criptografá-la, podendo este processo, dependendo do tamanho da chave, demorar mais que o tempo de duração do universo (SCHNEIER, 1996 apud CHIARAMONTE et al, 2005).  



#### 1.6.2 Confidencialidade  

Característica principal de um sistema de esteganografia, a confidencialidade da existência de informações ocultas em um objeto é essencial para que o método seja aplicável. Na maior parte das vezes que a esteganografia é aplicada, o objeto-recipiente trafega por meios de comunicação hostis onde qualquer suspeita levaria ao seu exame detalhado, facilitando a detecção, extração ou destruição da mensagem oculta. Portanto é crucial que o objeto-recipiente seja de ocorrência freqüente no meio de comunicação utilizado. Nesta característica a esteganografia é mais eficiente que a criptografia.  


#### 1.6.3 Sobrevivência
A sobrevivência é a capacidade de um sistema de esteganografia de manter as características originais da mensagem oculta, após a transmissão e extração. Dados transmitidos por redes de comunicação podem sofrer alterações causadas por ruídos da linha e campos eletromagnéticos, entre outros motivos. Uma pequena mudança em um byte dos dados pode arruinar todo o processo de extração, dependendo da técnica utilizada na ocultação. A escolha do sistema de estenganografia a ser usado deve ser feita levando-se em consideração a qualidade do canal por onde o arquivo de cobertura trafegará.  


#### 1.6.4 Não-Detecção
É de pouca valia a utilização de um objeto que não seja suspeito se um interceptador puder facilmente detectar o uso da técnica e extrair a mensagem existente. Há softwares que vasculham todo o tráfego de uma rede buscando por arquivos que possam conter dados esteganografados, sendo irrelevante suas características visuais. Portanto além de um objeto bem escolhido, é necessário que o método de esteganografia empregado seja robusto. Um método robusto é aquele em que o método de inserção é difícil de detectar e de destruir. Se um atacante descobre que há uma mensagem em um arquivo ele pode tanto tentar extraí-la quanto tentar destruí-la. Mesmo que o método utilizado seja conhecido, é necessário que seja forte o bastante para que a mensagem continue recuperável após uma tentativa de alteração do conteúdo oculto.  
  

#### 1.6.5 Visibilidade
Outro princípio básico da esteganografia, a visibilidade da mensagem oculta deve ser sempre nula. Um arquivo de áudio com muitos ruídos ou uma imagem de alta resolução que tenha cores ou formas distorcidas evidencia que o arquivo sofreu algum tipo de alteração, tornando inútil qualquer algoritmo empregado caso a imagem sofra um ataque. Há uma troca entre visibilidade e capacidade de armazenamento de dados ocultos em um arquivo. Quanto maior a quantidade de dados ocultos mais perceptível é a existência de alterações do objeto-recipiente.  


#### 1.7 Considerações Finais
A esteganografia é resultado da necessidade de extremo sigilo que alguns tipos de arquivos devem ter ao serem armazenados ou transmitidos pela Internet. É uma técnica muito eficiente e de difícil detecção por software e mais difícil ainda visualmente. As possibilidades de uso são inúmeras, servindo para proteção de arquivos pessoais, marcação de direitos autorais, detecção de alteração de arquivos, crimes virtuais e reais, entre outros. Como levantado neste capítulo observa-se que, apesar de ainda não ter padrões bem definidos, como a criptografia, é muito promissora em diversas áreas da ciência de segurança de informações.
