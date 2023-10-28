#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>
using namespace std;

// Declaração do tipo de registro presente em cada nó
struct Tiporeg {
    int chave;
    int dado1;
    char dado2[1000];
};

// Declaração do tipo de nó 

struct No {
    Tiporeg registro;
    No* esquerda;
    No* direita;
    int altura; // propriedade que retorna a altura do no na arvore
};

//Função para retornar a altura da arvore

int altura(No* no) {
    // essa função retorna a altura do no e é utilizada para pegar o valor máximo do lado direito e esquerdo
    if (no == nullptr) return 0;
    return no->altura;
}

// função para retornar o valor máximo entre duas variáveis
int maximo(int a, int b) {
    return (a > b) ? a : b; 
}

// Função para retornar o ponteiro para um novo nó 
No* novoNo(Tiporeg pRegistro) {
    No* no = new No();
    no->registro = pRegistro;
    no->esquerda = nullptr;
    no->direita = nullptr;
    no->altura = 1;
    return no;
}

struct Arvore_avl {
    // Nó raiz
    No* raiz;

    // inteiro para contar o número de interações ao buscar uma chave 
    int numero_interacoes = 0;

    No* rotacaoDireita(No* y) {
        // 'x' é o nó à esquerda de 'y'
        No* x = y->esquerda;

        // 'T' é a subárvore à direita de 'x'
        No* T = x->direita;

        // Fazendo a rotação à direita
        x->direita = y;
        y->esquerda = T;

        // Atualizando as alturas dos nós após a rotação
        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;

        // Retorna o novo nó que se torna a raiz da subárvore após a rotação
        return x;
    }


    No* rotacaoEsquerda(No* x) {
        // 'y' é o nó à direita de 'x'
        No* y = x->direita;

        // 'T' é a subárvore à esquerda de 'y'
        No* T = y->esquerda;

        // Fazendo a rotação à esquerda
        y->esquerda = x;
        x->direita = T;

        // Atualizando as alturas dos nós após a rotação
        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;

        // Retorna o novo nó que se torna a raiz da subárvore após a rotação
        return y;
    }


    int fatorBalanceamento(No* no) {
        // Se o nó é nulo, retorna 0 (árvore vazia tem fator de balanceamento 0)
        if (no == nullptr) return 0;
        
        // Retorna a diferença entre a altura da subárvore esquerda e a altura da subárvore direita
        return altura(no->esquerda) - altura(no->direita);
    }


    No* inserir(No* no, Tiporeg registro) {
        // Se o nó é nulo, cria um novo nó com o registro fornecido
        if (no == nullptr) return novoNo(registro);

        // Caso a chave do registro seja menor que a chave do nó atual, insere na subárvore esquerda
        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        // Caso a chave do registro seja maior que a chave do nó atual, insere na subárvore direita
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);
        // Caso a chave do registro seja igual à chave do nó atual, retorna o nó sem fazer nada (evitando duplicatas)
        else
            return no;

        // Atualiza a altura do nó atual com base na altura das subárvores esquerda e direita
        no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));

        // Calcula o fator de balanceamento para verificar se a árvore está desbalanceada
        int balance = fatorBalanceamento(no);

        // Realiza rotações para reequilibrar a árvore, se necessário
        if (balance > 1 && registro.chave < no->esquerda->registro.chave)
            return rotacaoDireita(no);

        if (balance < -1 && registro.chave > no->direita->registro.chave)
            return rotacaoEsquerda(no);

        if (balance > 1 && registro.chave > no->esquerda->registro.chave) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        if (balance < -1 && registro.chave < no->direita->registro.chave) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        // Retorna o nó atual após a inserção e as rotações (se houverem)
        return no;
    }

    bool Buscar(No* no, int chave) {
        // Se o nó é nulo, a chave não foi encontrada, retorna falso
        if (no == nullptr) {
            return false;
        }
        // Se a chave é menor que a chave do nó atual, realiza busca na subárvore esquerda
        else if (chave < no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore esquerda
            return Buscar(no->esquerda, chave);
        }
        // Se a chave é maior que a chave do nó atual, realiza busca na subárvore direita
        else if (chave > no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore direita
            return Buscar(no->direita, chave);
        }
        // Se a chave é igual à chave do nó atual, a chave foi encontrada, retorna verdadeiro
        else
            return true;
    }

};

Tiporeg retornaTipoReg(string s) {
    // Cria uma variável do tipo Tiporeg para armazenar os dados extraídos da string
    Tiporeg aux;

    // Copia a string original para uma variável auxiliar para manipulação
    string auxS = s;

    // Define o delimitador como ";"
    string delimiter = ";";

    // Encontra a posição do primeiro delimitador na string
    int pos = s.find(delimiter);

    // Extrai a substring da posição 0 até a posição do primeiro delimitador e converte para inteiro, armazenando em aux.chave
    aux.chave = stoi(s.substr(0, pos));
    // Extrai a substring da posição após o primeiro delimitador até o final da string, converte para inteiro e armazena em aux.dado1
    aux.dado1 = stoi(auxS.substr(pos + 1, s.length()));

    // Encontra a próxima posição do delimitador na string
    pos = s.find(delimiter, pos + 1);

    // Extrai a substring da posição após o segundo delimitador até o final da string e a converte para um array de caracteres, copiando para aux.dado2
    auxS = s.substr(pos + 1, s.length());
    strcpy(aux.dado2, auxS.c_str());

    // Retorna a estrutura Tiporeg com os dados extraídos da string
    return aux;
};


int main() {

    srand(static_cast<unsigned>(time(0)));

    // Cria uma instância da estrutura Arvore_avl
    Arvore_avl arv;
    
    // Variáveis para armazenar dados temporários
    string linha,nomeArquivo;
    Tiporeg registro_temp;
    
    // Variáveis de controle e armazenamento
    bool gerouTodas;
    int chaveAleatoria = 0; 
    int totalPresente = 1;
    int totalAusente = 1;
    char buffer[1000]; 
    string vetorEncontradas[15];
    string vetorNaoEncontradas[15];

    // Inicializa a raiz da árvore como nula
    arv.raiz = nullptr;

    // para especificar o nome do arquivo que vai ser aberto
    nomeArquivo = "dadosOrdenados10000.txt";
    
    ifstream arquivo("Arquivos Entrada/"+nomeArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Lê dados do arquivo e insere na árvore AVL
    while (getline(arquivo, linha)) {
        string s = linha;
        if (s != "") {
            // Converte a linha do arquivo para a estrutura Tiporeg e insere na árvore AVL
            registro_temp = retornaTipoReg(s);
            arv.raiz = arv.inserir(arv.raiz, registro_temp);
        }
    }

    // Fecha o arquivo após a leitura
    arquivo.close();

    // Realiza operações de busca aleatória na árvore AVL
    while (!gerouTodas){
        // Gera uma chave aleatória entre 0 e 19999
        if(totalAusente < 15)
            chaveAleatoria = rand() % 20000;
        else
            chaveAleatoria = rand() % 10000;

        // Reinicia o contador de interações
        arv.numero_interacoes = 0;
        
        // Inicia a contagem do tempo de busca
        auto start_time = chrono::high_resolution_clock::now();

        // Realiza a busca na árvore AVL com a chave aleatória
        bool resultadoChaveEncontrada = arv.Buscar(arv.raiz, chaveAleatoria);

        // Finaliza a contagem do tempo de busca
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_time = end_time - start_time;

        // Armazena resultados da busca em vetores
        if (resultadoChaveEncontrada) {
            if(totalPresente <= 15){
                // Formata a mensagem e armazena no vetor de chaves encontradas
                sprintf(buffer, "Chave encontrada na árvore. Tempo de busca: %.9f segundos. Interações: %d", elapsed_time.count(), arv.numero_interacoes);
                vetorEncontradas[totalPresente-1] = buffer;
                totalPresente++;
            }
        } else {
            if(totalAusente <= 15){
                // Formata a mensagem e armazena no vetor de chaves não encontradas
                sprintf(buffer, "Chave não encontrada na árvore. Tempo de busca: %.9f segundos. Interações: %d", elapsed_time.count(), arv.numero_interacoes);
                vetorNaoEncontradas[totalAusente-1] = buffer;
                totalAusente++;
            }
        }

        // Verifica se todas as chaves foram geradas e encontradas
        gerouTodas = ((totalAusente==16)&&(totalPresente==16));

    }

    // Abre o arquivo de saída "arquivo_saida.txt"
    ofstream arquivo_saida("Arquivos Saida/avl/arquivo_saida_"+nomeArquivo);

    // Verifica se o arquivo de saída foi aberto corretamente
    if (!arquivo_saida.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return 1;
    }

    // Escreve as chaves encontradas no arquivo de saída
    for (int i = 0; i < 15; i++)
        arquivo_saida << vetorEncontradas[i] << endl;

    // Escreve as chaves não encontradas no arquivo de saída
    for (int i = 0; i < 15; i++)
        arquivo_saida << vetorNaoEncontradas[i] << endl;

    // Fecha o arquivo de saída
    arquivo_saida.close();

    return 0;
}
