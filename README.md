# Inspirações para projeto

## Teoria memética
Este projeto é inspirado na teoria memética de Richard Dawkins, que postula que as ideias, ou "memes" (unidades básicas de informações culturais), evoluem e se espalham através de um processo semelhante à seleção natural biológica. No contexto desta simulação, o objetivo é modelar a evolução dos memes e de seus portadores dentro de uma população de hospedeiros, onde os memes influenciam o comportamento dos hospedeiros e, em última análise, a sua sobrevivência.
### Reprodução dos memes:
Os memes que aumentam as chances de sobrevivência e reprodução de um hospedeiro têm maior probabilidade de serem replicados e transmitidos às gerações subsequentes. Na simulação, os memes bem-sucedidos são aqueles que contribuem positivamente para a capacidade de um hospedeiro encontrar e garantir alimentos, navegar no seu ambiente e envolver-se em disputas com outros hospedeiros.
### Seleção Natural de Hospedeiros
À medida que os hospedeiros interagem com o seu ambiente, aqueles com memes que se alinham com os desafios que enfrentam têm maior probabilidade de sobreviver e reproduzir-se. A _sobrevivência dos hospedeiros está diretamente ligada ao sucesso dos memes_ que carregam.
## Teoria dos jogos
A teoria dos jogos ajuda a _modelar essas interações considerando as escolhas_ que os hospedeiros fazem, influenciadas pelas variáveis do meme. Os resultados dessas interações dependem da interação entre as características do meme e os _custos de energia associados_. Por exemplo, aumentar a agressividade leva ao maior custo energético. Desse modo, toda decisão comportamental está atrelada a um tradoff relativo.
## Equilíbrio de Nash
O equilíbrio de Nash representa um estado em que _nenhum hospedeiro individual tem um incentivo para mudar unilateralmente a sua estratégia_, dadas as estratégias escolhidas pelos outros hospedeiros. No contexto do projeto, _as estratégias são influenciadas pelas variáveis do meme_ e seus respectivos custos energéticos. O que queremos aferir é _o estado o qual há uma estabilização dos mecanismos de tomada de decisão_ dada uma condição ambiental.

# Implementação do projeto
## Arquitetura
O projeto foi desenvolvido completamente em C++, onde foram construídas as classes Host, Meme, Food e World. A Classe Host implementa a Classe Meme além de lidar com as características fundamentais do Host (como movimentação, tamanho, cor, etc...). Já a Classe Food foi construída para interagir com os hospedeiros e dar-lhes energia quando conseguem o alimento. Além disso, a classe Food também implementa o timer de cada comida e indica quando esta está sendo disputada por mais de um Host. Já à Classe World é atribuída a função de gerar a simulação bem como implementar os algoritmos evolutivos.
## Funcionamento das simulações
### População inicial
Ao longo de uma simulação será gerada uma _população inicial aleatória_ de Hosts com características físicas aleatórias e cada um com um meme aleatório em relação às características de _mecanismos de decisão_ (velocidade, agressividade, etc...). 
### Sobrevivência
Os Hosts são livres para se movimentar até que encontrem um alimento. Quando encontrarem um alimento, o Host terá um tempo determinado para comer aquele alimento, _se outro Host encontrar o mesmo alimento, então eles irão disputar aquela comida_. 
### Disputa
As condições de _disputa serão diretamente ligadas aos memes que infectam_ determinados hosts. Por exemplo, se dois hosts agressivos se encontrarem, os dois sairão prejudicados pois provavelmente vão gastar mais energia disputando a comida do que a própria comida pode oferecer. Se dois hosts passivos encontrarem a comida, então os dois irão partilhar a comida. Se um Host fica com a energia muito baixa, então ele morre.
### Fim da geração e fitness
Quando uma porção da população morre (por padrão 1/5), então algum algorítmo de seleção será ativado para reproduzir os Hosts a partir dos sobreviventes. _Um Host será considerado hápto se tiver mais energia restante que os demais._
### Geração de uma nova geração
Quando ocorre a reprodução, um Host gerado _irá herdar a combinação física de seus pais_ bem como _irá receber um meme oriundo da combinação dos memes_ de seus pais.

# Conclusões do projeto
## Comportamentos predominantes
## Comportamentos em escassez de alimentos
## Comportamentos com maior gasto energético