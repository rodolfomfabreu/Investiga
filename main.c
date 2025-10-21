#include "structs.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static void delay_ms(int ms);
char* story = NULL;

static void ler_linha(char* buffer, size_t tamanho) {
    if (!fgets(buffer, (int)tamanho, stdin)) return;
    size_t n = strlen(buffer);
    while (n > 0 && (buffer[n-1] == '\n' || buffer[n-1] == '\r')) {
        buffer[n-1] = '\0';
        n--;
    }
}

typedef struct RoomClues {
    char* room;
    NoPista* pistas;
    struct RoomClues* next;
} RoomClues;

static RoomClues* find_room(RoomClues* head, const char* room) {
    RoomClues* cur = head;
    while (cur) {
        if (strcmp(cur->room, room) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

static RoomClues* ensure_room(RoomClues** head, const char* room) {
    RoomClues* r = find_room(*head, room);
    if (r) return r;
    r = (RoomClues*)malloc(sizeof(RoomClues));
    r->room = str_dup(room);
    r->pistas = NULL;
    r->next = *head;
    *head = r;
    return r;
}

static void add_clue_to_room(RoomClues** head, const char* room, const char* pista) {
    RoomClues* r = ensure_room(head, room);
    inserirPista(&r->pistas, (char*)pista);
}

static void add_clue_to_room_with_desc(RoomClues** head, const char* room, const char* pista, const char* desc) {
    RoomClues* r = ensure_room(head, room);
    inserirPistaComDescricao(&r->pistas, pista, desc);
}

static void preset_basico(No** mapa_out, RoomClues** roomClues_out, char** culpado_out, char** story_out) {
    No* mapa = NULL;
    RoomClues* rc = NULL;

    inserir(&mapa, "Sala de Estar");
    inserir(&mapa, "Cozinha");
    inserir(&mapa, "Biblioteca");
    inserir(&mapa, "Corredor");
    inserir(&mapa, "Quarto");

    add_clue_to_room(&rc, "Sala de Estar", "Chave dourada");
    add_clue_to_room(&rc, "Biblioteca", "Carta rasgada");
    add_clue_to_room(&rc, "Cozinha", "Pegada molhada");

    inicializarTabela();
    inserirTabelaHash("Chave dourada", "Fernandinho");
    inserirTabelaHash("Carta rasgada", "Jorjao");
    inserirTabelaHash("Pegada molhada", "Dandan da Quebrada");

    *mapa_out = mapa;
    *roomClues_out = rc;
    if (culpado_out) {
        if (*culpado_out) free(*culpado_out);
        *culpado_out = str_dup("Dandan da Quebrada");
    }
    if (story_out) {
        if (*story_out) free(*story_out);
        *story_out = str_dup("A familia proprietaria da mansao acordou com o caos: um objeto de valor desapareceu e houve sinais de luta."
                           " A proprietaria Paulete afirma que, enquanto o marido trabalhava fora do estado, houve uma festa na noite anterior e ao amanhecer o desaparecimento foi notado."
                           " Voce sera levado aos lugares onde os acontecimentos se desenrolaram: a Sala de Estar (onde um vaso foi quebrado), a Biblioteca (livros revirados),"
                           " o Corredor (marcas de arraste) e o Quarto (um armario entreaberto).\n\n"
                           "Os tres principais suspeitos tem historias que podem explicar motivo e oportunidade:\n"
                           "- Fernandinho: antigo curador do acervo, forte e carismatico; era visto comecando investidas romanticas pela proprietaria."
                           " Ele tinha acesso livre aos objetos valiosos e, segundo rumores, desejava impressiona-la a qualquer custo, mesmo quando o marido estava ausente.\n"
                           "- Jorjao: um visitante com dividas enormes contraidas apos comprar um carro; envolveu-se com o trafico local para arrecadar dinheiro."
                           " Sua necessidade financeira lhe dava motivo para um roubo planejado — e sua presenca na festa e contatos suspeitos o colocam no radar.\n"
                           "- Dandan da Quebrada: conhecido por sua lingua afiada; discutiu feio com a proprietaria durante a festa."
                           " Testemunhas afirmam que a altercacao levou Fernandinho a intervir para protege-la, o que adiciona tensao entre os presentes.\n\n"
                           "Cada pista recolhida em um comodo pode ligar comportamento, motivo e oportunidade a um desses suspeitos. Investigue, colete declaracoes e evidencias, e descubra quem de fato teve razao e oportunidade de cometer o crime.");
    }
}

static void preset_demo(No** mapa_out, RoomClues** roomClues_out, char** culpado_out, char** story_out) {
    No* mapa = NULL;
    RoomClues* rc = NULL;

    inserir(&mapa, "Sala Principal");
    inserir(&mapa, "Laboratorio");
    inserir(&mapa, "Jardim");

    inserir(&mapa, "Sala de Cha");
    inserir(&mapa, "Corredor Lateral");

    add_clue_to_room_with_desc(&rc, "Sala Principal", "Bilhete suspeito", "Um bilhete com uma frase curta: 'voce sabe o que fez'. Papel amassado, tinta borrada.");
    add_clue_to_room(&rc, "Laboratorio", "Frasco quebrado");
    add_clue_to_room_with_desc(&rc, "Jardim", "Pegada suja", "Pegadas recem feitas, com manutencao de solado incomum; lama fresca indicando saida apressada.");

    inicializarTabela();
    inserirTabelaHash("Bilhete suspeito", "Jorginho Matador");
    inserirTabelaHash("Frasco quebrado", "Joao pe de feijao");
    inserirTabelaHash("Pegada suja", "Rafael o perseguidor da TI");

    *mapa_out = mapa;
    *roomClues_out = rc;
    if (culpado_out) {
        if (*culpado_out) free(*culpado_out);
        *culpado_out = str_dup("Rafael o perseguidor da TI");
    }
    if (story_out) {
        if (*story_out) free(*story_out);
        *story_out = str_dup("Demo: A demonstracao mostra um caso de tensao entre tres visitantes de uma recepcao privada."
               " Na Sala Principal um bilhete enigmatico foi encontrado - uma mensagem que sugere acerto de contas."
               " No Laboratorio ha sinal de um frasco quebrado e equipamentos fora do lugar, indicando que algo foi pesquisado ou escondido ali."
               " No Jardim, pegadas sujas revelam que alguem deixou o local apressadamente.\n\n"
                           "Os envolvidos deste demo sao:\n"
                           "- Jorginho Matador: aparenta ser um empresario dono de uma frota de caminhoes; por baixo dos panos e um mercenario experiente.\n"
                           "- Joao pe de feijao: carismatico e imitador, conhecido por imitar personagens; estava presente e fez-se notar durante a festa.\n"
                           "- Rafael o perseguidor da TI: farmacêutico com obsesoes, frequentemente perseguia profissionais de TI — seu comportamento desconcertante chamou atencao.\n\n"
                           "A vitima deste demo e Rodolfo, um colaborador que deixou de entregar relatorios importantes requisitados por Rafael."
                           " O motivo de Rafael, segundo rumores, era forcar Rodolfo a entregar os relatorios ou tomar decisoes por conta propria.\n\n"
                           "A demonstracao seguira a Sala Principal, o Laboratorio e o Jardim, mostrando como pequenas pistas (um bilhete, um frasco, uma pegada) podem conectar comportamentos e motivos.");
    }
}

typedef struct Player {
    No* pos;
    NoPista* coletadas;
} Player;

static void inspecionar_comodo(RoomClues* rooms, const char* room, Player* jogador) {
    RoomClues* r = find_room(rooms, room);
    if (!r || !r->pistas) {
        printf("Nenhuma pista visivel neste comodo.\n");
        return;
    }
    printf("Pistas no comodo '%s':\n", room);
    exibirPistasEmOrdem(r->pistas);
    printf("Deseja coletar alguma pista? (digite o texto exato ou deixe em branco): \n");
    char buf[256];
    ler_linha(buf, sizeof(buf));
    if (strlen(buf) == 0) return;
    NoPista* found = buscarPista(r->pistas, buf);
    if (!found) {
        printf("Pista nao encontrada neste comodo.\n");
        return;
    }
    inserirPistaComDescricao(&jogador->coletadas, found->pista, found->descricao);
    char* s = buscarTabelaHash(found->pista);
    printf("Pista coletada: %s -> Suspeito: %s\n", found->pista, s ? s : "(nao associado)");
    if (found->descricao) printf("  Descricao: %s\n", found->descricao);
}

static void coletar_clue(RoomClues* rooms, const char* room, const char* pista, Player* jogador) {
    RoomClues* r = find_room(rooms, room);
    if (!r || !r->pistas) {
        printf("Nenhuma pista visivel em %s.\n", room);
        return;
    }
    NoPista* found = buscarPista(r->pistas, pista);
    if (!found) {
        printf("Pista '%s' nao encontrada em %s.\n", pista, room);
        return;
    }
    inserirPistaComDescricao(&jogador->coletadas, found->pista, found->descricao);
    char* s = buscarTabelaHash(found->pista);
    printf("Pista coletada: %s -> Suspeito: %s\n", found->pista, s ? s : "(nao associado)");
    if (found->descricao) printf("  Descricao: %s\n", found->descricao);
}

static void modo_jogo(No* mapa, RoomClues* rooms, const char* culpado_real) {
    if (!mapa) {
        printf("Mapa vazio — crie um jogo primeiro.\n");
        return;
    }
    Player jogador = { .pos = mapa, .coletadas = NULL };
    char opc[256];
    while (1) {
        printf("\n--- Modo Jogo ---\n");
        printf("Voce esta em: %s\n", jogador.pos ? jogador.pos->nome : "(nenhum)");
    printf("1) Ir para (digite nome do comodo)\n");
        printf("2) Inspecionar comodo atual\n");
        printf("3) Ver pistas coletadas\n");
    printf("4) Acusar suspeito\n");
        printf("0) Voltar ao menu principal\n");
        printf("Escolha: ");
        ler_linha(opc, sizeof(opc));
    if (strcmp(opc, "1") == 0) {
            printf("Mapa (sala atual: %s):\n", jogador.pos ? jogador.pos->nome : "(nenhum)");
            exibirEmOrdem(mapa);
            printf("\nNome do comodo para ir: ");
            char destino[256]; ler_linha(destino, sizeof(destino));
            if (strlen(destino) == 0) continue;
            No* n = buscarNo(mapa, destino);
            if (n) jogador.pos = n;
            else printf("Comodo nao encontrado no mapa.\n");
        } else if (strcmp(opc, "2") == 0) {
            if (!jogador.pos) { printf("Posicao invalida.\n"); continue; }
            inspecionar_comodo(rooms, jogador.pos->nome, &jogador);
        } else if (strcmp(opc, "3") == 0) {
            printf("Pistas coletadas:\n");
            exibirPistasEmOrdem(jogador.coletadas);
        } else if (strcmp(opc, "4") == 0) {
            printf("Digite o nome do suspeito para acusar (ou deixe em branco para nao acusar): \n");
            char acc[256]; ler_linha(acc, sizeof(acc));
            if (strlen(acc) == 0) continue;
            if (culpado_real && strcmp(acc, culpado_real) == 0) {
                printf("Acusacao correta! %s e o culpado.\n", acc);
                printf("\n********************************************************\n");
                printf("*** PARABENS! VOCE RESOLVEU O CASO! ********************\n");
                printf("*** Obrigado por jogar - voce encontrou o culpado. *****\n");
                printf("********************************************************\n\n");
                break;
            } else {
                printf("Acusacao incorreta.\n");
            }
        } else if (strcmp(opc, "0") == 0) {
            break;
        } else printf("Opcao invalida.\n");
    }
}

static void construtor_jogo(No** mapa, RoomClues** rooms, char** culpado_out) {
    char opc[256];
    while (1) {
        printf("\n--- Construtor de Jogo ---\n");
    printf("1) Inserir comodo\n");
    printf("2) Inserir pista em comodo (descricao opcional)\n");
        printf("3) Associar pista -> suspeito\n");
        printf("4) Exibir mapa\n");
    printf("5) Definir culpado do caso\n");
    printf("6) Definir historia inicial do jogo\n");
        printf("0) Finalizar construtor\n");
        printf("Escolha: "); ler_linha(opc, sizeof(opc));
        if (strcmp(opc, "1") == 0) {
            printf("Nome do comodo: "); char nome[256]; ler_linha(nome, sizeof(nome));
            if (strlen(nome) > 0) inserir(mapa, nome);
        } else if (strcmp(opc, "2") == 0) {
            char room[256], pista[256], desc[512];
            printf("Comodo onde inserir pista: "); ler_linha(room, sizeof(room));
            printf("Texto da pista: "); ler_linha(pista, sizeof(pista));
            printf("Descricao opcional da pista (ou deixe em branco): "); ler_linha(desc, sizeof(desc));
            if (strlen(room) > 0 && strlen(pista) > 0) {
                if (strlen(desc) > 0) add_clue_to_room_with_desc(rooms, room, pista, desc);
                else add_clue_to_room(rooms, room, pista);
            }
        } else if (strcmp(opc, "3") == 0) {
            char pista[256], suspeito[256];
            printf("Pista: "); ler_linha(pista, sizeof(pista));
            printf("Suspeito: "); ler_linha(suspeito, sizeof(suspeito));
            if (strlen(pista) > 0 && strlen(suspeito) > 0) inserirTabelaHash(pista, suspeito);
        } else if (strcmp(opc, "4") == 0) {
            printf("Mapa (em ordem):\n"); exibirEmOrdem(*mapa); printf("\n");
        } else if (strcmp(opc, "5") == 0) {
            char nome[256];
            printf("Nome do culpado: "); ler_linha(nome, sizeof(nome));
            if (strlen(nome) > 0 && culpado_out) {
                if (*culpado_out) free(*culpado_out);
                *culpado_out = str_dup(nome);
                printf("Culpado definido: %s\n", *culpado_out);
            }
        } else if (strcmp(opc, "6") == 0) {
            char buf[1024];
            printf("Escreva a historia inicial do seu jogo (max 1023 chars):\n");
            ler_linha(buf, sizeof(buf));
            if (strlen(buf) > 0) {
                extern char* story; 
                if (story) free(story);
                story = str_dup(buf);
                printf("Historia personalizada definida.\n");
            }
        } else if (strcmp(opc, "0") == 0) break;
        else printf("Opcao invalida.\n");
    }
}

int main() {
    No* mapa = NULL;
    RoomClues* rooms = NULL;
    char* culpado = NULL;
    inicializarTabela();

    /* helper to free all game state */
    void freeNoTree(No* raiz) {
        if (!raiz) return;
        freeNoTree(raiz->esquerda);
        freeNoTree(raiz->direita);
        if (raiz->nome) free(raiz->nome);
        free(raiz);
    }

    void freePistas(NoPista* r) {
        if (!r) return;
        freePistas(r->esquerda);
        freePistas(r->direita);
        if (r->pista) free(r->pista);
        if (r->descricao) free(r->descricao);
        free(r);
    }

    void freeRoomClues(RoomClues* head) {
        RoomClues* cur = head;
        while (cur) {
            RoomClues* next = cur->next;
            if (cur->room) free(cur->room);
            freePistas(cur->pistas);
            free(cur);
            cur = next;
        }
    }

    void clear_game_state() {
        /* free current state */
        freeRoomClues(rooms);
        rooms = NULL;
        freeNoTree(mapa);
        mapa = NULL;
        if (culpado) { free(culpado); culpado = NULL; }
        limparTabela();
        if (story) { free(story); story = NULL; }
    }

    char opt[32];
    while (1) {
        printf("\n=== Menu Principal ===\n");
        printf("1) Novo jogo\n");
        printf("2) Criar jogo personalizado (construtor)\n");
        printf("3) Jogar\n");
        printf("4) Demo automatica (exemplo rapido)\n");
        printf("0) Sair\n");
        printf("Escolha: "); ler_linha(opt, sizeof(opt));
        if (strcmp(opt, "1") == 0) {
            clear_game_state();
            preset_basico(&mapa, &rooms, &culpado, &story);
            printf("Jogo criado com preset basico. Use 'Jogar' para comecar.\n");
        } else if (strcmp(opt, "2") == 0) {
            /* clear previous state before entering constructor */
            clear_game_state();
            construtor_jogo(&mapa, &rooms, &culpado);
            printf("Construtor finalizado.\n");
        } else if (strcmp(opt, "3") == 0) {
            if (story) printf("\n%s\n\n", story);
            modo_jogo(mapa, rooms, culpado);
        } else if (strcmp(opt, "4") == 0) {
            No* demo_map = NULL; RoomClues* demo_rooms = NULL; char* demo_culpado = NULL; char* demo_story = NULL;
            preset_demo(&demo_map, &demo_rooms, &demo_culpado, &demo_story);
            printf("\n--- Demo automatica (executando acoes) ---\n");
            if (demo_story) printf("%s\n\n", demo_story);
            printf("Mapa da Mansao:\n"); exibirEmOrdem(demo_map); printf("\n");

            Player jog = { .pos = demo_map, .coletadas = NULL };

            delay_ms(700);
            printf("Indo para: Sala Principal...\n");
            No* n = buscarNo(demo_map, "Sala Principal"); if (n) jog.pos = n; delay_ms(500);
            printf("Inspecionando Sala Principal...\n"); delay_ms(600);
            coletar_clue(demo_rooms, "Sala Principal", "Bilhete suspeito", &jog);
            delay_ms(500);

            printf("Indo para: Sala de Cha...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Sala de Cha"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Sala de Cha...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Sala de Cha", &jog);
            delay_ms(500);

            printf("Indo para: Laboratorio...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Laboratorio"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Laboratorio...\n"); delay_ms(600);
            coletar_clue(demo_rooms, "Laboratorio", "Frasco quebrado", &jog);
            delay_ms(500);

            printf("Indo para: Jardim...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Jardim"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Jardim...\n"); delay_ms(600);
            coletar_clue(demo_rooms, "Jardim", "Pegada suja", &jog);
            delay_ms(500);

            printf("Indo para: Corredor Lateral...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Corredor Lateral"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Corredor Lateral...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Corredor Lateral", &jog);

            printf("\nPistas coletadas (demo):\n");
            exibirPistasEmOrdem(jog.coletadas);
            if (demo_culpado) {
                printf("\n--- Resultado da Demo ---\n");
                printf("Culpado (segundo o caso-demo): %s\n", demo_culpado);
                free(demo_culpado);
            }
            if (demo_story) free(demo_story);
        } else if (strcmp(opt, "0") == 0) {
            printf("Encerrando...\n"); break;
        } else printf("Opcao invalida.\n");
    }

    return 0;
}

static void delay_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}