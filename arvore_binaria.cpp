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

No* novoNo(Tiporeg pRegistro)
{
    No* no = new No();
    no->registro = pRegistro;
    no->esquerda = nullptr;
    no->direita = nullptr;
    return no;
}

struct ArvoreBinaria
{
    No* raiz;

    No* inserir(No* no, Tiporeg registro)
    {
        if (no == nullptr) return novoNo(registro);

        if (registro.chave < no->registro.chave)
            no->esquerda = inserir(no->esquerda, registro);
        else if (registro.chave > no->registro.chave)
            no->direita = inserir(no->direita, registro);

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

Tiporeg retornaTipoReg(string s)
{
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

int main()
{
    ArvoreBinaria arv;
    string linha;

    arv.raiz = nullptr;

    ifstream arquivo("dadosDesordenados10000.txt");

    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    while (getline(arquivo, linha))
    {
        string linhaAux = linha;
        if (linhaAux != "")
        {
            Tiporeg auxiliar = retornaTipoReg(linha);
            arv.raiz = arv.inserir(arv.raiz, auxiliar);
        }
    }

    arquivo.close();

    int chaveParaEncontrarNaArvore = 9000;
    int chaveNaoNaArvore = 10001;

    auto start_time = chrono::high_resolution_clock::now();
    bool resultado = arv.Buscar(arv.raiz, chaveParaEncontrarNaArvore);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    if (resultado)
    {
        cout << fixed << "Chave encontrada na árvore. Tempo de busca: " << setprecision(6) << elapsed_time.count() << " segundos." << endl;
    }
    else
    {
        cout << fixed << "Chave não encontrada na árvore. Tempo de busca: " << setprecision(6) << elapsed_time.count() << " segundos." << endl;
    }

    start_time = chrono::high_resolution_clock::now();
    resultado = arv.Buscar(arv.raiz, chaveNaoNaArvore);
    end_time = chrono::high_resolution_clock::now();
    elapsed_time = end_time - start_time;

    if (resultado)
    {    
        cout << fixed << "Chave (não existente) encontrada na árvore. Tempo de busca: " << setprecision(6) << elapsed_time.count() << " segundos." << endl;
    }
    else
    {
        cout << fixed << "Chave (não existente) não encontrada na árvore. Tempo de busca: " << setprecision(6) << elapsed_time.count() << " segundos." << endl;
    }

    return 0;
}