### Aprendizado Supervisionado
Em suma, neste tipo o algoritmo aprende a partir de exemplos, i.e., ao receber dados rotulados, o algoritmo irá reconhecer os padrões de cada classe a partir de um vetor de atributos.

É  necessário se atentar à eficácia do modelo, logo que há situações onde o modelo memoriza os padrões e não aprende de fato.

A divisão dos dados no aprendizado supervisionado
* Conjunto de Treinamento
	* Treinamento = têm como objetivo ensinar padrões para o modelos(parâmetros)
	* Validação =  orientam o ajuste fino(hiper parâmetros) e verifica se o modelos não está decorando os dados(overfitting)
* Conjunto de Tese
	* Tese = os dados desta fase precisam ser inéditos para o algoritmo. Nesta fase, é feita a validação.

O objetivo é ajustar um modelo preditivo e partir de um conjunto de exemplos de modo que o modelo seja capaz de prever dados não observados. Assim, o modelo preditivo são funções que, dado um conjunto de exemplos rotulados, constrói um estimador dado por:
$$
y = f(x) + \in
$$

#### Classificação
Def: 
Dado um conjunto de observações:
$$
D = ({X_i, Y_i}), i=1,...,N
$$
$F(.)$ representa uma função desconhecida (função objetivo)
Essa função mapeia as entradas nas saídas correspondentes.
O Algoritmo preditivo aprende a aproximação, que permite estimar valor de $f(.)$ para novos valores de X
$$ Y_i \in {(C_1, C_2, ...C_n)} $$
#### Regressão
Dado um conjunto de observações: 
$$D = {X_i,y_i}, i+1,;;,N$$
$f(.)$ representa uma função desconhecida -> uma função objetivo
$$y_i = f(X_i, theta) + \epsilon_i$$
Essa função mapeia as entradas nas saídas correspondentes. O algoritmo preditivo aprende a aproximação, que permite estimar os valores de $f(.)$ para novos valores de $X$.
$$y_i \in \mathbb{R}$$

### Aprendizado Não Supervisionado

* modelos descritivos
* O objetivo é agrupar um conjunto de objetos de acordo com a similaridade entre eles, de forma a minimizar a função custo.
Dado um conjunto de objetos descritos por múltiplos valores(atributos). Queremos:
1. Atribuir grupos(clusters) aos objetos particionando-os objetivamente me grupos homogêneos de maneira a:
	* Maximizar as similaridade de objetos dentro de um mesmo grupo
	* Minimizar a similaridade de objetos entre grupos distintos
2. Atribuir uma descrição para cada grupo formado 

Estágios para o agrupamento de dados:
* Seleção de atributos: Os atributos devem ser selecionados de modo que ocorra o mínimo de redundância entre eles. Ex: aplicação de pca
* Medida de proximidade: Esta medida deve quantificar o quão similar ou dissimilar são os objetos.
* Critérios de clusterização: Consiste de uma função custo ou algum tipo de regra.
* Algoritmo de clusterização: Consiste de um conjunto de passos para revelar a estrutura dos dados, baseados na medida de similaridade e no critério adotado.
* Validação do resultados
* Interpretar os resultados.

### Aprendizado com Reforço 
É um algoritmo condicionado a receber uma recompensa a cada acerto. 