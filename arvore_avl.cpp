#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>
using namespace std;

struct Tiporeg {
    int chave;
    int dado1;
    char dado2[1000];
};

struct No {
    Tiporeg registro;
    No* esquerda;
    No* direita;
    int altura;
};

int altura(No* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

No* novoNo(Tiporeg pRegistro) {
    No* no = new No();
    no->registro = pRegistro;
    no->esquerda = nullptr;
    no->direita = nullptr;
    no->altura = 1;
    return no;
}

struct Arvore_avl {
    No* raiz;

    No* rotacaoDireita(No* y) {
        No* x = y->esquerda;
        No* T = x->direita;

        x->direita = y;
        y->esquerda = T;

        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;

        return x;
    }

    No* rotacaoEsquerda(No* x) {
        No* y = x->direita;
        No* T = y->esquerda;

        y->esquerda = x;
        x->direita = T;

        x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;

        return y;
    }

    int fatorBalanceamento(No* no) {
        if (no == nullptr) return 0;
        return altura(no->esquerda) - altura(no->direita);
    }

    No* inserir(No* no, Tiporeg registro) {
        if (no == nullptr) return novoNo(registro);

        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);
        else
            return no;

        no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));

        int balance = fatorBalanceamento(no);

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

        return no;
    }

    bool Buscar(No* no, int chave) {
        if (no == nullptr) {
            return false;
        }
        else if (chave < no->registro.chave)
            return Buscar(no->esquerda, chave);
        else if (chave > no->registro.chave)
            return Buscar(no->direita, chave);
        else
            return true;
    }
};

Tiporeg retornaTipoReg(string s) {
    Tiporeg aux;
    string auxS = s;

    string delimiter = ";";
    int pos = s.find(delimiter);

    aux.chave = stoi(s.substr(0, pos));
    aux.dado1 = stoi(s.substr(pos + 1, s.length()));
    pos = s.find(delimiter, pos + 1);
    auxS = s.substr(pos + 1, s.length());

    strcpy(aux.dado2, auxS.c_str());

    return aux;
}

int main() {
    Arvore_avl arv;
    string linha;
    Tiporeg registro_temp;

    arv.raiz = nullptr;

    ifstream arquivo("dadosDesordenados10000.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    while (getline(arquivo, linha)) {
        string s = linha;
        if (s != "") {
            registro_temp = retornaTipoReg(s);
            arv.raiz = arv.inserir(arv.raiz, registro_temp);
        }
    }

    arquivo.close();

    int chaveParaEncontrarNaArvore = 9000;
    int chaveNaoNaArvore = 10001;

    auto start_time = chrono::high_resolution_clock::now();
    bool resultadoChaveEncontrada = arv.Buscar(arv.raiz, chaveParaEncontrarNaArvore);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    if (resultadoChaveEncontrada) {
        cout << "Chave encontrada na árvore. Tempo de busca: " << elapsed_time.count() << " segundos." << endl;
    }
    else {
        cout << "Chave não encontrada na árvore. Tempo de busca: " << elapsed_time.count() << " segundos." << endl;
    }

    start_time = chrono::high_resolution_clock::now();
    bool resultadoChaveNaoNaArvore = arv.Buscar(arv.raiz, chaveNaoNaArvore);
    end_time = chrono::high_resolution_clock::now();
    elapsed_time = end_time - start_time;

    if (resultadoChaveNaoNaArvore) {
        cout << "Chave (não existente) encontrada na árvore. Tempo de busca: " << elapsed_time.count() << " segundos." << endl;
    }
    else {
        cout << "Chave (não existente) não encontrada na árvore. Tempo de busca: " << elapsed_time.count() << " segundos." << endl;
    }

    return 0;
}