#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>
using namespace std;

struct Tiporeg
{
    int chave;
    int dado1;
    char dado2[1000];
};

struct No
{
    Tiporeg registro;
    No* esquerda;
    No* direita;
};

No* novoNo(Tiporeg pRegistro) {
    // Cria um novo nó na memória
    No* no = new No();

    // Define o registro do novo nó com o registro passado como parâmetro
    no->registro = pRegistro;

    // Inicializa os ponteiros da esquerda e direita como nulos, indicando que o novo nó é uma folha
    no->esquerda = nullptr;
    no->direita = nullptr;

    // Retorna o ponteiro para o novo nó criado
    return no;
}


struct ArvoreBinaria {
    No* raiz;               // Ponteiro para o nó raiz da árvore
    int numero_interacoes;  // Variável para contar o número de interações durante as operações

    // Função para inserir um novo nó na árvore
    No* inserir(No* no, Tiporeg registro) {
        // Se o nó atual é nulo, cria um novo nó com o registro fornecido
        if (no == nullptr) return novoNo(registro);

        // Se a chave do registro é menor que a chave do nó atual, insere na subárvore esquerda
        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        // Se a chave do registro é maior que a chave do nó atual, insere na subárvore direita
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);

        // Retorna o nó atual após a inserção
        return no;
    }

    // Função para buscar uma chave na árvore binária
    bool Buscar(No* no, int chave) {
        // Se o nó é nulo, a chave não foi encontrada na árvore
        if (no == nullptr) {
            return false;
        }
        // Se a chave é menor que a chave do nó atual, busca na subárvore esquerda
        else if (chave < no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore esquerda
            return Buscar(no->esquerda, chave);
        }
        // Se a chave é maior que a chave do nó atual, busca na subárvore direita
        else if (chave > no->registro.chave){
            // Incrementa o número de interações (comparações) realizadas durante a busca
            numero_interacoes++;
            // Chama a função de busca recursivamente na subárvore direita
            return Buscar(no->direita, chave);
        }
        // Se a chave é igual à chave do nó atual, a chave foi encontrada na árvore
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
    aux.dado1 = stoi(s.substr(pos + 1, s.length()));

    // Encontra a próxima posição do delimitador na string
    pos = s.find(delimiter, pos + 1);

    // Extrai a substring da posição após o segundo delimitador até o final da string e a converte para um array de caracteres, copiando para aux.dado2
    auxS = s.substr(pos + 1, s.length());
    strcpy(aux.dado2, auxS.c_str());

    // Retorna a estrutura Tiporeg com os dados extraídos da string
    return aux;
};

int main() {
    // Inicializa o gerador de números aleatórios com uma semente baseada no tempo atual
    srand(static_cast<unsigned>(time(0)));

    // Cria uma instância da estrutura ArvoreBinaria
    ArvoreBinaria arv;

    // Variáveis para leitura do arquivo e controle
    string linha,nomeArquivo;
    bool gerouTodas;
    int chaveAleatoria = 0; 
    int totalPresente = 1;
    int totalAusente = 1;
    string vetorEncontradas[16];
    string vetorNaoEncontradas[16];
    char buffer[1000];

    // Inicializa a raiz da árvore como nula
    arv.raiz = nullptr;

    // para especificar o nome do arquivo que vai ser aberto
    nomeArquivo = "dadosOrdenados5000.txt";

    ifstream arquivo("Arquivos Entrada/"+nomeArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Lê dados do arquivo e insere na árvore binária de busca
    while (getline(arquivo, linha)) {
        string linhaAux = linha;
        if (linhaAux != "") {
            // Converte a linha do arquivo para a estrutura Tiporeg e insere na árvore
            Tiporeg auxiliar = retornaTipoReg(linha);
            arv.raiz = arv.inserir(arv.raiz, auxiliar);
        }
    }

    // Fecha o arquivo após a leitura
    arquivo.close();

    // Realiza operações de busca aleatória na árvore binária
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

        // Realiza a busca na árvore binária com a chave aleatória
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
    ofstream arquivo_saida("Arquivos Saida/binaria/arquivo_saida_"+nomeArquivo);

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
