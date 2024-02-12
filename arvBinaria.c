#include <stdio.h>
#include <stdlib.h>

typedef struct _arv Arv;

struct _arv {
    int info;
    struct _arv* sae;
    struct _arv* sad;
};

Arv* criarNovoNo(int info) {
    Arv* novo = (Arv*) malloc(sizeof(Arv));
    if (novo != NULL) {
        novo->info = info;
        novo->sae = NULL;
        novo->sad = NULL;
    }
    return novo;
}

Arv* inicializa() { 
    return NULL;
}

// ordem simétrica ou "in-order"
void imprime(Arv *arv) {
    if (arv != NULL) {    
        imprime(arv->sae);
        printf("%d ", arv->info);
        imprime(arv->sad);
    }
}

Arv* busca(Arv *raiz, int elem) {
    if (raiz == NULL) return NULL;
    else if (elem < raiz->info) return busca(raiz->sae, elem);
    else if (elem > raiz->info) return busca(raiz->sad, elem);
    else return raiz;
}

Arv *insere(Arv* a, int elem) {
    if (a == NULL) {
        a = criarNovoNo(elem);
    } else if (elem < a->info) {
        a->sae = insere(a->sae, elem);
    } else if (elem > a->info) {
        a->sad = insere(a->sad, elem);
    }
    return a;            
}

Arv* remover(Arv* a, int elem) {
   if (a == NULL) {
        return NULL; 
    } else if (elem < a->info) {
        a->sae = remover(a->sae, elem);
    } else if (elem > a->info) {
        a->sad = remover(a->sad, elem);
    } else { // elemento a ser rem. encontrado
       if (a->sae == NULL && a->sad == NULL) { // a)
           free(a);
           a = NULL;
       } else if (a->sae == NULL) { // único filho à dir
            Arv* aux = a;
            a = a->sad;
            free(aux);
       } else if (a->sad == NULL) { // único filho à esq
            Arv* aux = a;
            a = a->sae;
            free(aux);
       } else { // dois filhos
            Arv* aux = a;
            Arv* f = a->sae;
            while(f->sad != NULL) {
               aux = f;
               f = f->sad;
            }
            a->info = f->info;
            f->info = elem;
            a->sae = remover(a->sae, elem);
       }
    }
   return a;
}

int main() {
    Arv *arv = inicializa();
    arv = insere(arv, 6);
    insere(arv, 2);
    insere(arv, 8);
    insere(arv, 1);
    insere(arv, 4);
    insere(arv, 3); 
    imprime(arv);
    return 0;
}
