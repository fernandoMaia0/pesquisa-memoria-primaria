#include <iostream>
using namespace std;

struct No
{
    int chave;
    No* antecessor;
    No* sucessor;
};

struct Arvore_Binaria
{
    No* raiz;

    void Iniciar(){
        raiz = new No; // Inicialize raiz como nullptr
        raiz->antecessor = nullptr;
        raiz->sucessor = nullptr;
    }

    void Inserir(No* & no, int chave){ 
        if (no == nullptr){
            no = new No;
            no->chave = chave;
            no->sucessor = nullptr;
            no->antecessor = nullptr;
        }else if (no->chave > chave){
            Inserir(no->antecessor, chave);
        }else if (no->chave < chave){
            Inserir(no->sucessor, chave);
        }
        
    }
};

int main(){
    Arvore_Binaria arv;
    arv.Iniciar();
    arv.raiz->chave = 10;
    arv.Inserir(arv.raiz, 9);
    arv.Inserir(arv.raiz, 11);
    cout << arv.raiz->chave;
    if (arv.raiz->antecessor != nullptr){
        cout << " Antecessor: " << arv.raiz->antecessor->chave;
    }
    if (arv.raiz->sucessor != nullptr){
        cout << " Sucessor: " << arv.raiz->sucessor->chave;
    }
    return 0;
}
