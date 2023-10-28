# Trabalho prático deselvolvido para a disciplina de Algoritmos e Estrutura de Dados III (Arvore Binaria, Arvore AVL e pesquisa sequêncial)
## Estrutura de Código AVL, Árvore Binária e Gerador de Registros

# Gerador de Registros
O gerador de registros é responsável por criar registros aleatórios e escrevê-los em arquivos de dados ordenados e desordenados. Aqui está uma descrição mais detalhada do código:

# Arquivo: gerador_de_registros.cpp
## Estruturas de Dados:
Registro: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (uma string de 1000 caracteres).
Funções:
gerarRegistroAleatorio(int chave): Gera um registro aleatório com uma chave específica e valores aleatórios para dado1 e dado2.
Funcionalidades:
Gera registros aleatórios com chaves sequenciais.
Cria arquivos com registros ordenados e desordenados, variando o número de registros propostos.
Os registros são escritos em formato CSV (chave; dado1; dado2) nos arquivos.
Como Usar:
Compile o código e execute-o.
Os arquivos de dados ordenados e desordenados são gerados com base no número de registros propostos.


# Árvore Binária de Busca
A árvore binária de busca é uma estrutura de dados que permite inserir, buscar e verificar a existência de chaves em uma árvore. 

# Arquivo: arvore_binaria.cpp
## Estruturas de Dados:
#### Tiporeg: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (uma string de 1000 caracteres).
#### No: Uma estrutura que representa um nó em uma árvore binária, com um registro, ponteiros para os nós à esquerda e à direita e uma variável para contar o número de interações durante as operações.

### Funções:
novoNo(Tiporeg pRegistro): Cria um novo nó com um registro específico e retorna o ponteiro para esse nó.
Funcionalidades:
Implementa uma árvore binária de busca.
Permite a inserção de registros na árvore.
Permite a busca de registros na árvore, retornando se uma chave foi encontrada ou não, além do número de comparações feitas.
Realiza operações de busca aleatória na árvore.

##### Como Usar:
Compile o código e execute-o.
O código lê um arquivo de dados desordenados, insere os registros em uma árvore binária e realiza buscas aleatórias.
Árvore AVL
A árvore AVL é uma árvore binária balanceada que mantém seu fator de equilíbrio. Aqui está uma descrição mais detalhada do código:

## Arquivo: arvore_avl.cpp
### Estruturas de Dados:
#### Tiporeg: Uma estrutura que representa um registro com três campos - chave (um número inteiro), dado1 (um número inteiro) e dado2 (uma string de 1000 caracteres).
#### No: Uma estrutura que representa um nó em uma árvore AVL, com um registro, ponteiros para os nós à esquerda e à direita, uma variável para contar o número de interações durante as operações e uma variável para manter a altura do nó.

### Funções:
rotacaoDireita(No* y): Realiza uma rotação à direita em um nó da árvore AVL para manter o equilíbrio.
rotacaoEsquerda(No* x): Realiza uma rotação à esquerda em um nó da árvore AVL para manter o equilíbrio.
fatorBalanceamento(No* no): Calcula o fator de balanceamento de um nó (diferença entre a altura da subárvore esquerda e da subárvore direita).
Funcionalidades:
Implementa uma árvore AVL.
Permite a inserção de registros na árvore, mantendo o equilíbrio da árvore através de rotações.
Permite a busca de registros na árvore, retornando se uma chave foi encontrada ou não, além do número de comparações feitas.
Realiza operações de busca aleatória na árvore.


### Como Usar:
Compile o código e execute-o.
O código lê um arquivo de dados ordenados, insere os registros em uma árvore AVL e realiza buscas aleatórias.


# Observações Gerais
Certifique-se de que todos os arquivos de entrada necessários estejam presentes no diretório especificado no código.
Os resultados das buscas são registrados em arquivos de saída correspondentes para posterior análise.
