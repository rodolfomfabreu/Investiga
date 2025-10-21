#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char* nome;
    struct No* esquerda;
    struct No* direita;
    struct No* pai;
} No;

typedef struct NoPista {
    char* pista;
    char* descricao;
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;

#define TAMANHO_TABELA 100

typedef struct Item {
    char* pista;
    char* suspeito;
    struct Item* proximo;
} Item;

extern Item* tabela[TAMANHO_TABELA];

static inline char* str_dup(const char* s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

No* criarNo(const char* nome);
void inserir(No** raiz, const char* nome);
void exibirEmOrdem(No* raiz);
No* buscarNo(No* raiz, const char* nome);
No* removerNo(No* raiz, const char* nome);
No* minimoNo(No* raiz);

NoPista* criarNoPista(const char* pista);
NoPista* criarNoPistaComDescricao(const char* pista, const char* descricao);
void inserirPista(NoPista** raiz, const char* pista);
void inserirPistaComDescricao(NoPista** raiz, const char* pista, const char* descricao);
NoPista* buscarPista(NoPista* raiz, const char* pista);
NoPista* removerPista(NoPista* raiz, const char* pista);
void exibirPistasEmOrdem(NoPista* raiz);
void definirDescricaoPista(NoPista* raiz, const char* pista, const char* descricao);

unsigned int funcaoHash(const char* chave);
void inicializarTabela();
void inserirTabelaHash(const char* pista, const char* suspeito);
char* buscarTabelaHash(const char* pista);
void removerTabelaHash(const char* pista);
void limparTabela();

#endif