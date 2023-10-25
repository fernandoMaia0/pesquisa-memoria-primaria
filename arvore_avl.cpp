#include <iostream>
using namespace std;

struct Tipo_reg
{
    int chave;
    int dado1;
    char dado2[1000]; 
};


struct No
{
    Tipo_reg registro;
    No* antecessor;
    No* sucessor;
    int valorBalanceamento;
};

struct Arvore_Avl
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
            no->registro.chave = chave;
            no->sucessor = nullptr;
            no->antecessor = nullptr;
        }else if (no->registro.chave > chave){
            Inserir(no->antecessor, chave);
            setValorBalanceamento(no);
            VerificaRotacao(no);
        }else if (no->registro.chave < chave){
            Inserir(no->sucessor, chave);
            setValorBalanceamento(no);
            VerificaRotacao(no);
        }
        
    }

    bool Buscar(No* no, int chave){
        if (no == nullptr){
            return false;
        }
        else if (no->registro.chave < chave){
            Buscar(no->sucessor,chave);
        }
        else if (no->registro.chave > chave){
            Buscar(no->antecessor,chave);
        }
        else{
            return true;
        }
        
    }

    void setValorBalanceamento(No*& no) {
        int alturaEsq = altura(no->antecessor);
        int alturaDir = altura(no->sucessor);
        no->valorBalanceamento = alturaDir - alturaEsq;
    }

    int altura(No* no) {
        if (no == nullptr) {
            return 0;
        }
        return 1 + max(altura(no->antecessor), altura(no->sucessor));
    }

    void VerificaRotacao(No*& no){
        
        if(no->valorBalanceamento == 2){
            if (no->sucessor->valorBalanceamento >= 0)
            {
                
                FazRotacao(no, 'E');
            }else{
                FazRotacao(no->sucessor, 'D');
                FazRotacao(no, 'E');
            }
            
        }else if(no->valorBalanceamento == -2){
            if (no->antecessor->valorBalanceamento >= 0)
            {
                FazRotacao(no->antecessor, 'E');
                FazRotacao(no, 'D');
            }else{

                FazRotacao(no, 'D');
            }
        }
    }
    
    void FazRotacao(No*& no, char direcao) {
        No* aux = no;
        No* filho_esq = nullptr;
        No* filho_dir = nullptr;

        if (no->sucessor != nullptr) {
            filho_dir = no->sucessor;
        }
        if (no->antecessor != nullptr) {
            filho_esq = no->antecessor;
        }

        if (direcao == 'D') {
        // Rotação para a direita
            if (no->antecessor != nullptr) {
                no->antecessor = filho_esq->sucessor;
                if (filho_esq->sucessor != nullptr) {
                    filho_esq->sucessor->antecessor = no;
                }
                filho_esq->sucessor = no;
                no = filho_esq;
        }
        } else {
        // Rotação para a esquerda
            if (no->sucessor != nullptr) {
                no->sucessor = filho_dir->antecessor;
                if (filho_dir->antecessor != nullptr) {
                    filho_dir->antecessor->sucessor = no;
                }
                filho_dir->antecessor = no;
                no = filho_dir;
            }
        }

    }
};

int main(){
    Arvore_Avl arv;

    arv.Iniciar();
    arv.raiz->registro.chave = 92;

    arv.Inserir(arv.raiz, 51);
    arv.Inserir(arv.raiz, 52);
    arv.Inserir(arv.raiz, 22);
    arv.Inserir(arv.raiz, 54);
    arv.Inserir(arv.raiz, 57);
    arv.Inserir(arv.raiz, 3);
    arv.Inserir(arv.raiz, 5);
    arv.Inserir(arv.raiz, 1);
    arv.Inserir(arv.raiz, 4);
    arv.Inserir(arv.raiz, 61);
    arv.Inserir(arv.raiz, 63);
    arv.Inserir(arv.raiz, 37);
    arv.Inserir(arv.raiz, 75);
    arv.Inserir(arv.raiz, 11);
    arv.Inserir(arv.raiz, 44);
    arv.Inserir(arv.raiz, 25);
    arv.Inserir(arv.raiz, 12);
    arv.Inserir(arv.raiz, 10);

return 0;
}