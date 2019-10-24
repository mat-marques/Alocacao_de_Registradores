# Alocacao_de_Registradores
Alocação de Registradores utilizando a técnica de coloração de grafos

Implementação utilizando c++ de um programa que realiza a leitura de arquivos que contêm grafos 
de interferência e tenta alocar registradores através da técnica de coloração de grafos.

O programa deve seguir os seguintes passos:

• Build: corresponde a construção do grafo. Nesta etapa basta seguir as interferências indicadas no
grafo.

• Simplify: corresponde a etapa de remover os nós do grafo. Os nós são removidos do grafo um a um
até que todos tenham sido removidos. Lembre-se que sempre deve-se remover um nó cujo grau seja
menor que o valor de K. Nesta etapa, você deve sempre remover o nó que contiver o menor grau. Se
o seu valor de K for 4 e no grafo houver um nó com grau 3 e outro com grau 2, você deve escolher o
nó de grau 2. Se por acaso dois ou mais nós diferentes possuirem um grau que seja igual ao mı́nimo,
você deve escolher o nó de menor número do registrador virtual. Como exemplo, considere o caso
onde o valor de K é igual a 4 e no grafo o menor grau é o valor 2, o qual ocorre nos nós 77 e 99,
você deve enviar para a pilha o nó 77 pois ele possui o menor número de registrador virtual. Os nós
removidos devem ser inseridos em uma pilha. A ação de empilhar um nó deve ser indicada na saı́da
do seu programa.

• Potencial Spill: se em algum momento do processo de remoção dos nós do grafo não houver um
nó cujo grau seja menor K, deve-se escolher um nó para talvez ser enviado para a memória. O seu
programa deve escolher sempre o nó que tenha o maior grau no grafo. No caso de haver mais de
uma possibilidade de escolha, o seu programa deve selecionar como potencial spill o nó que possuir o
menor número. Suponha, por exemplo, que durante o processo de remoção dos nós, todos possuem
grau maior que K e o maior grau do grafo é 25, sendo que os nós 37, 45 e 88 possuem grau 25; o seu
programa deve remover do grafo o nó 37, pois ele possui o menor número dentre os registradores
virtuais a serem escolhidos. A ação de selecionar um nó como potencial spill deve ser indicada na
saı́da do seu programa.

• Select/Assign: esta etapa ocorre após todos os nós do grafo serem removidos. Ela irá reconstruir
o grafo e associar registradores/cores aos nós a medida em que eles são reintroduzidos no grafo, na
ordem inversa em que foram removidos. De forma a garantir um comportamento uniforme entre
diferentes implementações, toda vez que um nó for reintroduzido no grafo, o seu programa deve
atribuir ao nó a menor cor possı́vel. Suponha que, por exemplo, ao reintroduzir no grafo o nó 77 e
que o mesmo possa receber as cores 10, 15, 19, 20; a escolha deve ser pela cor de número 10 que é
a de menor número. A ação de desempilhar um nó da pilha e atribuir uma cor ao mesmo deve ser
indicada na saı́da do seu programa.

• Spill: se durante o processo de atribuição de cores aos nós do grafo, não for possı́vel colorir um
determinado nó, ele deve ser enviado para spill. Em condições normais isso implica em modificar o
programa e reiniciar o processo de coloração, mas no presente caso, como somente os grafos estão
disponı́veis, você deverá terminar o processo de alocação/coloração indicando que o grafo gerou um
spill.

Leia o pdf com a descrição do projeto para maiores informações.
