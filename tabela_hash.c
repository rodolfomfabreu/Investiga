#include "structs.h"


Item* tabela[TAMANHO_TABELA] = { NULL };

unsigned int funcaoHash(const char* chave) {
    unsigned int hash = 0;
    while (*chave) {
        hash = (hash << 5) + *chave++;
    }
    return hash % TAMANHO_TABELA;
}

void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela[i] = NULL;
    }
}

void inserirTabelaHash(const char* pista, const char* suspeito) {
    unsigned int indice = funcaoHash(pista);
    Item* novoItem = (Item*)malloc(sizeof(Item));
    novoItem->pista = str_dup(pista);
    novoItem->suspeito = str_dup(suspeito);
    novoItem->proximo = tabela[indice];
    tabela[indice] = novoItem;
}

char* buscarTabelaHash(const char* pista) {
    unsigned int indice = funcaoHash(pista);
    Item* item = tabela[indice];
    while (item != NULL) {
        if (strcmp(item->pista, pista) == 0)
            return item->suspeito;
        item = item->proximo;
    }
    return NULL;
}

void removerTabelaHash(const char* pista) {
    unsigned int indice = funcaoHash(pista);
    Item* atual = tabela[indice];
    Item* anterior = NULL;
    while (atual) {
        if (strcmp(atual->pista, pista) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else tabela[indice] = atual->proximo;
            free(atual->pista);
            free(atual->suspeito);
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void limparTabela() {
    for (int i = 0; i < TAMANHO_TABELA; ++i) {
        Item* it = tabela[i];
        while (it) {
            Item* next = it->proximo;
            if (it->pista) free(it->pista);
            if (it->suspeito) free(it->suspeito);
            free(it);
            it = next;
        }
        tabela[i] = NULL;
    }
}