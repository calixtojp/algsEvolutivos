# Características principais
## Recursos finitos
Ao longo da simulação, "comidas" irão aparecer e os hospedeiros poderão capturar essa comida.
Quando um ou mais hospedeiros chegarem perto suficiente da comida, um tempo "para comer" será
iniciado. Se somente um hospedeiro conseguir chegar sozinho e comer a comida, somente esse
irá capturar a comida. Se algum outro hospedeiro chegar na comida enquanto outro hospedeiro estava
comendo, então irá acontecer uma disputa pelo recurso. Dependendo do tipo de meme que infecta o
hospedeiro, há a possibilidade de dividir totalmente ou parcialmente a comida. Quando um hospedeiro
ópta por não divir a comida, há maior probabilidade de que ambos os hospedeiros fiquem sem a comida. Quando um hospedeiro ópta pela divisão, há maior probabilidade de que esse fique com a comida. Além disso, um hospedeiro que ópta por ser mais agressivo (não dividir) terá de pagar essa operação com pontos de energia. Assim, conseguimos simular a relação de agressividade com a relação de disputa por recursos finitos.

## Comunicação entre hospedeiros
Quando dois ou mais hospedeiros chegam perto suficiente, há a possibilidade de que um meme seja passado (ou misturado) com outro meme do outro hospedeiro. Isso irá depender a viralidade do meme.

## Reprodução dos hospedeiros (sexuada ou assexuada)
(em aberto)

## Reprodução dos memes (assexuada)
(em aberto)

# Classe hospedeiro
Essa classe terá seu comportamento definito pelo "meme" que a infecta. Ou seja,
um hospedeiro será mais agressivo, ou terá maior taxa de reprodução, ou terá
mais velocidade a depender das características do parasita (meme) que a infecta.

Será representado por um retângulo na simulação (retângulos são mais "leves" computacionalmente que círculos).

## Métodos principais
Seus principais métodos estão relacionados à natureza do funcionamento de um hospedeiro.
Fazendo o paralelo humano, será como definir "movimento dos braços", "processo de digestão"
, etc... Em suma, seus métodos dizem respeito ao funcionamento intríseco do hospedeiro em questão.

## Variáveis principais
Suas principais variáveis dizem respeito às variáveis intrísecas ao funcionamento do hospedeiro.
Voltando no exemplo humano acima, enquanto o método "mover braço" deveria estar relacionado
ao movimento do braço, quem irá ditar o comprimento do braço será as variáveis do hospedeiro.

### Posição
### Cor

# Classe meme
De onde vem 'meme'? meme é um termo que surge no livro "Gene egoísta" de Richard Dawkins, em 1976.
Meme, no sentido do livro, seria uma unidade de informação com capacidade de se multiplicar 
através das crenças de indivíduo para indivíduo. Para mais informações, pesquisar sobre
"teoria memética".

Essa classe será parte de um hospedeiro. Ela deverá modelar o comportamento de um hospedeiro.
Essa classe será o alvo principal do algoritmo evolutivo. Para lidar com a evolução dos memes,
vamos simular um ambiente de concorrência por recursos finitos, de tal forma que os hospedeiros
deverão "fazer escolhas" de tal forma que aqueles que melhor escolherem alocar seus "recursos"
irão sobreviver e se reproduzir levando assim à seleção de melhores "memes".

Para simular a ideia de reprodução dos memes entre a população de hospedeiros, vamos fazer com que
esses hospedeiros tenham uma espécie de "comunicação". Quando um hospedeiro chegar perto suficiente
de outro, o meme que infecta um irá misturar com o meme que infecta o outro. Dessa forma, podemos
simular a troca de informações dentro de uma comunidade de hospedeiros.

## Métodos principais
## Variáveis principais
### Velocidade
### Tamanho
### Agressividade
### Taxa de reprodução


