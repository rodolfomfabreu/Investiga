#include "structs.h"


No* criarNo(const char* nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->nome = str_dup(nome);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->pai = NULL;
    return novoNo;
}

void inserir(No** raiz, const char* nome) {
    if (*raiz == NULL) {
        *raiz = criarNo(nome);
    } else {
        if (strcmp(nome, (*raiz)->nome) < 0)
        {
            inserir(&(*raiz)->esquerda, nome);
            (*raiz)->esquerda->pai = *raiz;
        }
        else
        {
            inserir(&(*raiz)->direita, nome);
            (*raiz)->direita->pai = *raiz;
        }
    }
}

void exibirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        exibirEmOrdem(raiz->esquerda);
        printf("%s ", raiz->nome);
        exibirEmOrdem(raiz->direita);
    }
}

No* buscarNo(No* raiz, const char* nome) {
    if (raiz == NULL)
        return NULL;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0) return raiz;
    if (cmp < 0) return buscarNo(raiz->esquerda, nome);
    return buscarNo(raiz->direita, nome);
}

No* minimoNo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda)
        atual = atual->esquerda;
    return atual;
}

No* removerNo(No* raiz, const char* nome) {
    if (raiz == NULL) return raiz;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp < 0) {
        raiz->esquerda = removerNo(raiz->esquerda, nome);
        if (raiz->esquerda) raiz->esquerda->pai = raiz;
    } else if (cmp > 0) {
        raiz->direita = removerNo(raiz->direita, nome);
        if (raiz->direita) raiz->direita->pai = raiz;
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz->nome);
            free(raiz);
            if (temp) temp->pai = NULL;
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz->nome);
            free(raiz);
            if (temp) temp->pai = NULL;
            return temp;
        }

        No* temp = minimoNo(raiz->direita);
    free(raiz->nome);
    raiz->nome = str_dup(temp->nome);
        raiz->direita = removerNo(raiz->direita, temp->nome);
        if (raiz->direita) raiz->direita->pai = raiz;
    }
    return raiz;
}