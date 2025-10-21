#include "structs.h"


NoPista* criarNoPista(const char* pista) {
    NoPista* novoNo = (NoPista*)malloc(sizeof(NoPista));
    novoNo->pista = str_dup(pista);
    novoNo->descricao = NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

NoPista* criarNoPistaComDescricao(const char* pista, const char* descricao) {
    NoPista* novoNo = (NoPista*)malloc(sizeof(NoPista));
    novoNo->pista = str_dup(pista);
    novoNo->descricao = descricao ? str_dup(descricao) : NULL;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

void inserirPista(NoPista** raiz, const char* pista) {
    if (*raiz == NULL) {
        *raiz = criarNoPista(pista);
    } else {
        if (strcmp(pista, (*raiz)->pista) < 0)
            inserirPista(&(*raiz)->esquerda, pista);
        else
            inserirPista(&(*raiz)->direita, pista);
    }
}

void inserirPistaComDescricao(NoPista** raiz, const char* pista, const char* descricao) {
    if (*raiz == NULL) {
        *raiz = criarNoPistaComDescricao(pista, descricao);
    } else {
        if (strcmp(pista, (*raiz)->pista) < 0)
            inserirPistaComDescricao(&(*raiz)->esquerda, pista, descricao);
        else
            inserirPistaComDescricao(&(*raiz)->direita, pista, descricao);
    }
}

NoPista* buscarPista(NoPista* raiz, const char* pista) {
    if (raiz == NULL || strcmp(raiz->pista, pista) == 0)
        return raiz;
    if (strcmp(pista, raiz->pista) < 0)
        return buscarPista(raiz->esquerda, pista);
    return buscarPista(raiz->direita, pista);
}

NoPista* minimoPista(NoPista* raiz) {
    NoPista* atual = raiz;
    while (atual && atual->esquerda)
        atual = atual->esquerda;
    return atual;
}

NoPista* removerPista(NoPista* raiz, const char* pista) {
    if (raiz == NULL) return raiz;
    int cmp = strcmp(pista, raiz->pista);
    if (cmp < 0) {
        raiz->esquerda = removerPista(raiz->esquerda, pista);
    } else if (cmp > 0) {
        raiz->direita = removerPista(raiz->direita, pista);
    } else {
        if (raiz->esquerda == NULL) {
            NoPista* temp = raiz->direita;
            if (raiz->pista) free(raiz->pista);
            if (raiz->descricao) free(raiz->descricao);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoPista* temp = raiz->esquerda;
            if (raiz->pista) free(raiz->pista);
            if (raiz->descricao) free(raiz->descricao);
            free(raiz);
            return temp;
        }

        NoPista* temp = minimoPista(raiz->direita);
    /* copy pivot data (pista + descricao) */
    if (raiz->pista) free(raiz->pista);
    raiz->pista = str_dup(temp->pista);
    if (raiz->descricao) free(raiz->descricao);
    raiz->descricao = temp->descricao ? str_dup(temp->descricao) : NULL;
        raiz->direita = removerPista(raiz->direita, temp->pista);
    }
    return raiz;
}

void exibirPistasEmOrdem(NoPista* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        if (raiz->descricao)
            printf("%s - %s\n", raiz->pista, raiz->descricao);
        else
            printf("%s\n", raiz->pista);
        exibirPistasEmOrdem(raiz->direita);
    }
}

void definirDescricaoPista(NoPista* raiz, const char* pista, const char* descricao) {
    NoPista* p = buscarPista(raiz, pista);
    if (!p) return;
    if (p->descricao) free(p->descricao);
    p->descricao = descricao ? str_dup(descricao) : NULL;
}