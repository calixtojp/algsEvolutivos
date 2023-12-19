# Inspirações para projeto

## Teoria memética
Este projeto é inspirado na teoria memética de Richard Dawkins, que postula que as ideias, ou "memes" (unidades básicas de informações culturais), evoluem e se espalham através de um processo semelhante à seleção natural biológica. No contexto desta simulação, o objetivo é _modelar a evolução dos memes e de seus portadores dentro de uma população de hospedeiros_, onde os memes influenciam o comportamento dos hospedeiros e, em última análise, a sua sobrevivência.

[![Explicação](https://i3.ytimg.com/vi/MGWM74QOTaM/maxresdefault.jpg)](https://youtu.be/MGWM74QOTaM)
Clique na imagem para ver o vídeo!

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

[![Velocidade gasta energia](https://i3.ytimg.com/vi/5Pm5ji7GLlg/maxresdefault.jpg)](https://youtu.be/5Pm5ji7GLlg)
Clique na imagem para ver o vídeo!

### Disputa
As condições de _disputa serão diretamente ligadas aos memes que infectam_ determinados hosts. Por exemplo, se dois hosts agressivos se encontrarem, os dois sairão prejudicados pois provavelmente vão gastar mais energia disputando a comida do que a própria comida pode oferecer. Se dois hosts passivos encontrarem a comida, então os dois irão partilhar a comida. Se um Host fica com a energia muito baixa, então ele morre.

[![Tamanho gasta Energia](https://i3.ytimg.com/vi/tJpqZK6Y-ns/maxresdefault.jpg)](https://youtube.com/shorts/tJpqZK6Y-ns)
Clique na imagem para ver o vídeo!

### Fim da geração e fitness
Quando uma porção da população morre (por padrão 1/5), então algum algorítmo de seleção será ativado para reproduzir os Hosts a partir dos sobreviventes. _Um Host será considerado hápto se tiver mais energia restante que os demais._
### Geração de uma nova geração
Quando ocorre a reprodução, um Host gerado _irá herdar a combinação física de seus pais_ bem como _irá receber um meme oriundo da combinação dos memes_ de seus pais.

# Conclusões do projeto
## Comportamentos predominantes
Em condições normais (0.2 em todos os custos energéticos atrelados a velocidade, tamanho, etc...) a agressividade tende a convergir para 0.5 para qualquer um dos indivíduos. Em geral, indivíduos tendem a não ir muito para extremos de agressividade - isto é, para 0 ou 1. A razão disso, é o comportamento anômalo do meme em relação ao mecanismo de reprodução no que diz respeito ao comportamento de agressividade: quando hosts se encontram em uma comida, há a troca de memes entre eles.

[![Pacíficos](https://i3.ytimg.com/vi/P-D0qH5dcRE/maxresdefault.jpg)](https://youtube.com/shorts/P-D0qH5dcRE)
Clique na imagem para ver o vídeo!

Quando a agressividade converge para um valor pouco maior que 0.5, o tamanho dos hosts tende a ser maior devido a vantagem do tamanho em um ambiente com maior número de disputas. Já quando a agressividade converge para um valor pouco menor que 0.5 o tamanho tende a ser diminuto pelo menor número de disputas e pelo tamanho ser inversamente proporcional à velocidade o que faz com que o host opte por ser menor e mais rápido.

[![Agressivos](https://i3.ytimg.com/vi/8kp_reUEf9c/maxresdefault.jpg)](https://youtu.be/8kp_reUEf9c)
Clique na imagem para ver o vídeo!

## Comportamentos em escassez de alimentos
Nessa simulação, diminuímos a quantidade de comidas e diminuímos o tempo que cada comida fica disponível aos hosts. Com isso as características que consomem energia tendem a diminuir por conta das mortes que aumentarem. Portanto, hosts tendem a ser pequenos e com campo de visão menor. Esses foram os comportamentos que diminuíram o gasto energético, visto que a chance de encontrar comida é muito pequena
