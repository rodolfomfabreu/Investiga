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
    inserir(&mapa, "Escritorio");
    inserir(&mapa, "Sala de Jantar");
    inserir(&mapa, "Lavanderia");
    inserir(&mapa, "Despensa");
    inserir(&mapa, "Quarto de Hospedes");
    inserir(&mapa, "Banheiro Principal");
    inserir(&mapa, "Sotao");
    inserir(&mapa, "Porao");
    inserir(&mapa, "Jardim Interno");
    inserir(&mapa, "Garagem");

    add_clue_to_room_with_desc(&rc, "Sala de Estar", "Chave dourada", "Uma chave dourada brilhante encontrada entre os cacos do vaso quebrado. Parece ser de um cofre ou armario especial.");
    add_clue_to_room_with_desc(&rc, "Sala de Estar", "Vaso quebrado", "Um vaso de porcelana valioso completamente quebrado no chao da sala. Os cacos estao espalhados, indicando que foi derrubado com forca.");
    add_clue_to_room_with_desc(&rc, "Biblioteca", "Carta rasgada", "Fragmentos de uma carta de amor rasgada encontrados entre os livros revirados. O papel parece ter sido arrancado com forca.");
    add_clue_to_room_with_desc(&rc, "Biblioteca", "Livros revirados", "Varios livros foram jogados no chao e estantes foram empurradas, criando uma bagunca que sugere uma busca apressada por algo.");
    add_clue_to_room_with_desc(&rc, "Cozinha", "Pegada molhada", "Pegadas molhadas no chao da cozinha, indicando que alguem passou por ali com os pes molhados, provavelmente vindo da area externa.");
    add_clue_to_room_with_desc(&rc, "Corredor", "Marcas de arraste", "Marcas no carpete do corredor sugerem que algo pesado foi arrastado da biblioteca em direcao ao quarto, deixando um rastro visivel.");
    add_clue_to_room_with_desc(&rc, "Quarto", "Armario entreaberto", "O armario do quarto principal esta entreaberto e algumas roupas estao espalhadas no chao, como se alguem tivesse revirado tudo rapidamente.");

    inicializarTabela();
    inserirTabelaHash("Chave dourada", "Fernandinho");
    inserirTabelaHash("Vaso quebrado", "Dandan da Quebrada");
    inserirTabelaHash("Carta rasgada", "Jorjao");
    inserirTabelaHash("Livros revirados", "Fernandinho");
    inserirTabelaHash("Pegada molhada", "Dandan da Quebrada");
    inserirTabelaHash("Marcas de arraste", "Jorjao");
    inserirTabelaHash("Armario entreaberto", "Fernandinho");

    *mapa_out = mapa;
    *roomClues_out = rc;
    if (culpado_out) {
        if (*culpado_out) free(*culpado_out);
        *culpado_out = str_dup("Dandan da Quebrada");
    }
    if (story_out) {
        if (*story_out) free(*story_out);
        *story_out = str_dup("*** CASO: O DESAPARECIMENTO DO ANEL DA FAMILIA ***\n\n"
                           "A madrugada de hoje trouxe um pesadelo para a prestigiosa familia Martins. A mansao da Rua das Flores,"
                           " conhecida por suas colecoes de arte e objetos de valor historico, foi palco de um crime misterioso.\n\n"
                           "A proprietaria, Dona Paulete Martins, acordou por volta das 6h da manha com um grito lancinante da empregada."
                           " Ao descer as escadas, encontrou a mansao em completo caos: o anel de familia, uma joia de 200 anos passada"
                           " de geracao em geracao, havia desaparecido do cofre da biblioteca. O objeto, avaliado em milhoes,"
                           " era o simbolo da heranca da familia e sua perda representa muito mais que valor material.\n\n"
                           "*** O CONTEXTO DA FESTA ***\n"
                           "Na noite anterior, Dona Paulete havia organizado uma festa elegante para celebrar o aniversario do marido,"
                           " Dr. Carlos Martins, que estava em viagem de negocios em Sao Paulo. A festa contou com cerca de 30 convidados"
                           " da alta sociedade, incluindo artistas, empresarios e personalidades locais. A atmosfera era de alegria"
                           " e celebracao, com musica ao vivo, champanhe frances e um buffet requintado.\n\n"
                           "*** A DESCOBERTA DO CRIME ***\n"
                           "Ao amanhecer, quando a empregada foi limpar a biblioteca, encontrou o cofre aberto e vazio. Imediatamente"
                           " chamou a proprietaria, que confirmou o roubo. A policia foi acionada, mas como voce e o detetive mais"
                           " experiente da regiao, foi designado para liderar a investigacao.\n\n"
                           "*** OS LOCAIS DA INVESTIGACAO ***\n"
                           "A mansao possui 16 comodos distribuidos em tres andares. Voce tera acesso a todos eles para uma"
                           " investigacao completa. Alguns locais apresentam evidencias claras, enquanto outros podem revelar"
                           " informacoes importantes sobre o comportamento dos suspeitos ou servir como areas de fuga.\n\n"
                           "COMODOS COM EVIDENCIAS PRINCIPAIS:\n"
                           "- Sala de Estar: O vaso de porcelana Ming foi quebrado durante uma possivel luta ou fuga apressada\n"
                           "- Biblioteca: Livros foram revirados e o cofre foi violado com precisao cirurgica\n"
                           "- Cozinha: Pegadas molhadas sugerem que alguem entrou ou saiu pela area de servico\n"
                           "- Corredor: Marcas de arraste indicam movimento de objetos pesados\n"
                           "- Quarto: O armario principal foi revirado, possivelmente em busca de algo especifico\n\n"
                           "OUTROS COMODOS DISPONIVEIS PARA INVESTIGACAO:\n"
                           "- Escritorio, Sala de Jantar, Lavanderia, Despensa, Quarto de Hospedes, Banheiro Principal,\n"
                           "  Sotao, Porao, Jardim Interno e Garagem\n\n"
                           "IMPORTANTE: Nem todos os comodos contem pistas, mas cada area pode oferecer informacoes"
                           " valiosas sobre o comportamento dos suspeitos ou servir como possivel rota de fuga do criminoso.\n\n"
                           "*** OS PRINCIPAIS SUSPEITOS ***\n\n"
                           "1. FERNANDINHO (Antigo Curador do Acervo):\n"
                           "   - Homem de 45 anos, forte e carismatico, trabalhou na mansao por 8 anos\n"
                           "   - Conhece cada objeto da colecao e tem acesso total a todas as areas\n"
                           "   - Recentemente foi visto fazendo investidas romanticas por Dona Paulete\n"
                           "   - Rumores indicam que ele planejava impressiona-la com presentes caros\n"
                           "   - Tinha motivos financeiros: salarios atrasados e dividas de jogo\n\n"
                           "2. JORJAO (Visitante com Dividas):\n"
                           "   - Homem de 38 anos, sempre bem vestido mas com ar nervoso\n"
                           "   - Contraiu dividas enormes apos comprar um BMW importado\n"
                           "   - Envolveu-se com atividades suspeitas para arrecadar dinheiro rapidamente\n"
                           "   - Foi visto conversando com pessoas de reputacao duvidosa durante a festa\n"
                           "   - Sua necessidade financeira urgente o torna um suspeito principal\n\n"
                           "3. DANDAN DA QUEBRADA (Conhecido por Brigas):\n"
                           "   - Homem de 35 anos, linguagem afiada e temperamento explosivo\n"
                           "   - Teve uma discussao acalorada com Dona Paulete durante a festa\n"
                           "   - A briga foi sobre supostas ofensas a sua familia durante eventos anteriores\n"
                           "   - Fernandinho precisou intervir para separar a confusao\n"
                           "   - Testemunhas dizem que ele saiu da festa furioso, jurando vinganca\n\n"
                           "*** SUA MISSÃO ***\n"
                           "Com 16 comodos disponiveis para investigacao, sua tarefa e mais complexa do que parece."
                           " Nem todos os locais contem evidencias diretas, mas cada area pode revelar informacoes"
                           " cruciais sobre o comportamento dos suspeitos, possiveis rotas de fuga ou motivos ocultos.\n\n"
                           "ESTRATEGIA DE INVESTIGACAO:\n"
                           "- Explore todos os comodos, mesmo aqueles que parecem vazios\n"
                           "- Alguns locais podem confirmar a inocencia de suspeitos\n"
                           "- Areas como garagem e jardim podem revelar como o criminoso entrou ou saiu\n"
                           "- O escritorio pode conter documentos que esclarecem motivos financeiros\n"
                           "- Quartos de hospedes podem revelar quem realmente conhecia a mansao\n\n"
                           "Cada pista coletada pode conectar comportamento, motivo e oportunidade a um dos suspeitos."
                           " Examine cuidadosamente as evidencias, analise as associacoes entre pistas e suspeitos,"
                           " e descubra quem realmente teve razao, oportunidade e meios para cometer este crime."
                           " O destino da familia Martins e a recuperacao do anel dependem de sua habilidade investigativa.\n\n"
                           "Boa sorte, Detetive. O tempo esta contra nos, e cada minuto perdido pode significar"
                           " a perda definitiva desta joia historica. A mansao guarda muitos segredos - encontre-os todos.");
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
    inserir(&mapa, "Recepcao");
    inserir(&mapa, "Cozinha");
    inserir(&mapa, "Banheiro Masculino");
    inserir(&mapa, "Banheiro Feminino");
    inserir(&mapa, "Area de Servico");
    inserir(&mapa, "Deposito");
    inserir(&mapa, "Escritorio Administrativo");
    inserir(&mapa, "Area de Estacionamento");
    inserir(&mapa, "Terraco");
    inserir(&mapa, "Sala de Conferencias");

    add_clue_to_room_with_desc(&rc, "Sala Principal", "Bilhete suspeito", "Um bilhete com uma frase curta: 'voce sabe o que fez'. Papel amassado, tinta borrada.");
    add_clue_to_room_with_desc(&rc, "Sala Principal", "Copo de vinho", "Um copo de vinho tinto deixado na mesa, ainda com um pouco de liquido. Parece ter sido abandonado apressadamente.");
    add_clue_to_room_with_desc(&rc, "Laboratorio", "Frasco quebrado", "Um frasco de vidro quebrado no chao do laboratorio, com restos de um liquido viscoso e escuro espalhados ao redor.");
    add_clue_to_room_with_desc(&rc, "Laboratorio", "Equipamentos baguncados", "Microscopios e equipamentos de laboratorio foram empurrados e alguns cairam no chao, criando uma bagunca que sugere uma busca apressada.");
    add_clue_to_room_with_desc(&rc, "Jardim", "Pegada suja", "Pegadas recem feitas, com manutencao de solado incomum; lama fresca indicando saida apressada.");
    add_clue_to_room_with_desc(&rc, "Jardim", "Portao entreaberto", "O portao do jardim esta entreaberto, com marcas de lama na maçaneta, indicando que alguem saiu correndo por ali.");
    add_clue_to_room_with_desc(&rc, "Sala de Cha", "Cha derramado", "Uma xicara de cha foi derramada na mesa, com o liquido ainda escorrendo para o chao, sugerindo que alguem saiu rapidamente.");
    add_clue_to_room_with_desc(&rc, "Corredor Lateral", "Relatorios espalhados", "Varios relatorios estao espalhados no chao do corredor, alguns rasgados e outros amassados, como se tivessem sido jogados com raiva.");

    inicializarTabela();
    inserirTabelaHash("Bilhete suspeito", "Jorginho Matador");
    inserirTabelaHash("Copo de vinho", "Joao pe de feijao");
    inserirTabelaHash("Frasco quebrado", "Joao pe de feijao");
    inserirTabelaHash("Equipamentos baguncados", "Rafael o perseguidor da TI");
    inserirTabelaHash("Pegada suja", "Rafael o perseguidor da TI");
    inserirTabelaHash("Portao entreaberto", "Rafael o perseguidor da TI");
    inserirTabelaHash("Cha derramado", "Jorginho Matador");
    inserirTabelaHash("Relatorios espalhados", "Rafael o perseguidor da TI");

    *mapa_out = mapa;
    *roomClues_out = rc;
    if (culpado_out) {
        if (*culpado_out) free(*culpado_out);
        *culpado_out = str_dup("Rafael o perseguidor da TI");
    }
    if (story_out) {
        if (*story_out) free(*story_out);
        *story_out = str_dup("*** CASO DEMO: O ASSASSINATO NA RECEPCAO PRIVADA ***\n\n"
                           "*** CENARIO DO CRIME ***\n"
                           "Na noite de ontem, uma recepcao privada na elegante Casa de Eventos 'Jardim Secreto' terminou em tragedia."
                           " O evento, organizado pela empresa de tecnologia 'Inovatech Solutions', reuniu cerca de 50 convidados"
                           " para celebrar o lancamento de um novo software revolucionario. A atmosfera era de festa e networking,"
                           " com coquetel premium, canapes sofisticados e apresentacoes sobre inovacao tecnologica.\n\n"
                           "*** A VITIMA ***\n"
                           "Rodolfo Mendes, 32 anos, era um dos desenvolvedores mais promissores da empresa. Conhecido por sua"
                           " dedicaao e competencia tecnica, ele havia sido designado para liderar o projeto 'Quantum Code',"
                           " um sistema de seguranca que prometia revolucionar a protecao de dados corporativos. Rodolfo era"
                           " respeitado pelos colegas, mas tambem conhecido por sua personalidade direta e, as vezes, inflexivel.\n\n"
                           "*** A DESCOBERTA DO CRIME ***\n"
                           "Por volta das 23h30, quando a maioria dos convidados ja havia partido, Rodolfo foi encontrado"
                           " morto na Sala de Cha, aparentemente vitima de envenenamento. O corpo estava sentado em uma"
                           " poltrona, com uma xicara de cha derramada ao lado. A policia foi acionada imediatamente,"
                           " e voce, como detetive especialista em crimes corporativos, foi designado para o caso.\n\n"
                           "*** OS LOCAIS DA INVESTIGACAO ***\n"
                           "A Casa de Eventos 'Jardim Secreto' possui 16 areas distribuídas em dois andares."
                           " Como detetive especialista, voce tera acesso total ao local para uma investigacao completa.\n\n"
                           "AREAS COM EVIDENCIAS PRINCIPAIS:\n"
                           "- Sala Principal: Local da festa, onde um bilhete enigmatico foi encontrado\n"
                           "- Laboratorio: Area onde equipamentos foram baguncados e um frasco suspeito foi quebrado\n"
                           "- Jardim: Local de saida, onde pegadas sujas revelam fuga apressada\n"
                           "- Sala de Cha: Cenario do crime, onde a vitima foi encontrada\n"
                           "- Corredor Lateral: Area onde relatorios importantes foram espalhados\n\n"
                           "OUTRAS AREAS DISPONIVEIS PARA INVESTIGACAO:\n"
                           "- Recepcao, Cozinha, Banheiro Masculino, Banheiro Feminino, Area de Servico,\n"
                           "  Deposito, Escritorio Administrativo, Area de Estacionamento, Terraco e Sala de Conferencias\n\n"
                           "IMPORTANTE: Nem todas as areas contem evidencias diretas, mas cada local pode oferecer"
                           " informacoes cruciais sobre o comportamento dos suspeitos, possiveis rotas de fuga,"
                           " ou motivos ocultos relacionados ao crime corporativo.\n\n"
                           "*** OS PRINCIPAIS SUSPEITOS ***\n\n"
                           "1. JORGINHO MATADOR (Empresario Suspeito):\n"
                           "   - Homem de 48 anos, aparenta ser um empresario respeitavel dono de uma frota de caminhoes\n"
                           "   - Por baixo dos panos, e conhecido como mercenario experiente com conexoes duvidosas\n"
                           "   - Estava presente na recepcao como 'convidado especial' da direcao da empresa\n"
                           "   - Foi visto conversando com Rodolfo em tom tenso durante a festa\n"
                           "   - Rumores indicam que ele tinha interesses financeiros no projeto 'Quantum Code'\n\n"
                           "2. JOAO PE DE FEIJAO (Imitador Carismatico):\n"
                           "   - Homem de 29 anos, carismatico e conhecido por imitar personagens famosos\n"
                           "   - Era o 'animador' oficial da recepcao, responsavel pelo entretenimento dos convidados\n"
                           "   - Sempre bem humorado, mas com um passado misterioso que poucos conhecem\n"
                           "   - Foi visto servindo bebidas e comidas durante toda a festa\n"
                           "   - Tinha acesso total a todas as areas do evento, incluindo a Sala de Cha\n\n"
                           "3. RAFAEL O PERSEGUIDOR DA TI (Farmaceutico Obsessivo):\n"
                           "   - Homem de 41 anos, farmaceutico com obsesoes peculiares\n"
                           "   - Frequentemente perseguia profissionais de TI, especialmente Rodolfo\n"
                           "   - Exigia relatorios detalhados sobre o progresso do projeto 'Quantum Code'\n"
                           "   - Seu comportamento desconcertante e obsessivo chamou atencao de varios colegas\n"
                           "   - Tinha acesso a substancias quimicas perigosas em seu laboratorio particular\n\n"
                           "*** O MOTIVO DO CRIME ***\n"
                           "Segundo investigacoes preliminares, Rafael estava obcecado com o controle total do projeto"
                           " 'Quantum Code'. Ele havia requisitado relatorios detalhados de Rodolfo, que sempre se"
                           " recusou a compartilhar informacoes confidenciais. A tensao entre os dois aumentou"
                           " significativamente nas ultimas semanas, culminando em confrontos verbais publicos.\n\n"
                           "*** SUA MISSÃO ***\n"
                           "Com 16 areas disponiveis para investigacao, sua tarefa e mais complexa do que parece."
                           " A Casa de Eventos 'Jardim Secreto' oferece multiplos cenarios que podem revelar"
                           " informacoes cruciais sobre o crime corporativo. Nem todos os locais contem evidencias"
                           " diretas, mas cada area pode oferecer insights importantes sobre o comportamento dos"
                           " suspeitos ou servir como possivel rota de fuga.\n\n"
                           "ESTRATEGIA DE INVESTIGACAO CORPORATIVA:\n"
                           "- Explore todas as areas, mesmo aquelas que parecem vazias\n"
                           "- Areas como Area de Estacionamento e Terraco podem revelar como o assassino entrou ou saiu\n"
                           "- O Escritorio Administrativo pode conter documentos que esclarecem motivos corporativos\n"
                           "- Banheiros e Area de Servico podem revelar preparacoes ou limpeza de evidencias\n"
                           "- A Sala de Conferencias pode ter registros de reunioes ou conversas importantes\n\n"
                           "Como detetive especialista, voce deve analisar cada pista cuidadosamente, conectando"
                           " comportamentos, motivos e oportunidades. A demonstracao seguira pelos locais principais,"
                           " mostrando como pequenas evidencias podem revelar a verdade por tras de um crime aparentemente"
                           " complexo. Cada pista coletada pode ser a chave para desvendar este misterio corporativo.\n\n"
                           "*** INSTRUCOES PARA A DEMONSTRACAO ***\n"
                           "Esta demonstracao automatica ira percorrer os locais principais, coletando pistas e"
                           " mostrando como a investigacao se desenvolve. Preste atencao nas associacoes entre"
                           " evidencias e suspeitos, pois elas revelam o padrao do crime e a identidade do culpado.\n\n"
                           "Boa investigacao, Detetive. A verdade esta nas evidencias - e elas podem estar"
                           " em qualquer lugar desta casa de eventos corporativa.");
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

static void exibir_ajuda_jogar() {
    printf("\n=== COMO JOGAR ===\n");
    printf("\nOBJETIVO:\n");
    printf("Voce e um detetive que deve resolver um caso coletando pistas e acusando o culpado correto.\n\n");
    
    printf("COMO COMEÇAR:\n");
    printf("1. Escolha 'Novo jogo' para criar um caso basico\n");
    printf("2. Ou 'Demo automatica' para ver um exemplo rapido\n");
    printf("3. Em seguida, escolha 'Jogar' para iniciar\n\n");
    
    printf("DURANTE O JOGO:\n");
    printf("- Navegue entre comodos digitando o nome do comodo\n");
    printf("- Inspecione o comodo atual para ver pistas disponiveis\n");
    printf("- Colete pistas digitando o nome exato da pista\n");
    printf("- Cada pista esta associada a um suspeito automaticamente\n");
    printf("- Revise suas pistas coletadas para analisar os suspeitos\n");
    printf("- Quando tiver evidencia suficiente, acuse o suspeito\n\n");
    
    printf("DICAS:\n");
    printf("- Leia a historia inicial com atencao para entender o contexto\n");
    printf("- Explore todos os comodos para nao perder pistas importantes\n");
    printf("- Anote os nomes dos suspeitos e suas associacoes com as pistas\n");
    printf("- A acusacao deve ser feita digitando o nome exato do suspeito\n\n");
    
    printf("Pressione Enter para voltar ao menu principal...");
    char buffer[256];
    ler_linha(buffer, sizeof(buffer));
}

static void exibir_ajuda_construtor() {
    printf("\n=== COMO CRIAR UM JOGO PERSONALIZADO ===\n");
    printf("\nPASSO A PASSO:\n\n");
    
    printf("1. CRIAR O MAPA:\n");
    printf("   - Use 'Inserir comodo' para adicionar ambientes\n");
    printf("   - Exemplo: 'Sala de Estar', 'Cozinha', 'Biblioteca'\n");
    printf("   - Visualize o mapa com 'Exibir mapa'\n\n");
    
    printf("2. ADICIONAR PISTAS:\n");
    printf("   - Use 'Inserir pista em comodo'\n");
    printf("   - Especifique o comodo, nome da pista e descricao (opcional)\n");
    printf("   - Exemplo: Comodo='Sala de Estar', Pista='Chave dourada', Descricao='Uma chave brilhante encontrada embaixo do sofa'\n\n");
    
    printf("3. ASSOCIAR PISTAS A SUSPEITOS:\n");
    printf("   - Use 'Associar pista -> suspeito'\n");
    printf("   - Digite o nome exato da pista e do suspeito\n");
    printf("   - Exemplo: Pista='Chave dourada', Suspeito='João Silva'\n\n");
    
    printf("4. DEFINIR O CULPADO:\n");
    printf("   - Use 'Definir culpado do caso'\n");
    printf("   - Digite o nome exato do suspeito que e o verdadeiro culpado\n");
    printf("   - IMPORTANTE: O nome deve ser exatamente igual ao usado nas associacoes\n\n");
    
    printf("5. CRIAR A HISTORIA:\n");
    printf("   - Use 'Definir historia inicial do jogo'\n");
    printf("   - Escreva uma narrativa que explique o caso e os suspeitos\n");
    printf("   - Maximo de 1023 caracteres\n\n");
    
    printf("DICAS IMPORTANTES:\n");
    printf("- Sempre defina o culpado antes de jogar\n");
    printf("- Certifique-se que o nome do culpado esta correto\n");
    printf("- Use nomes consistentes para suspeitos em todas as associacoes\n");
    printf("- Crie uma historia envolvente para melhor experiencia\n");
    printf("- Teste seu jogo antes de considera-lo completo\n\n");
    
    printf("Pressione Enter para voltar ao menu principal...");
    char buffer[256];
    ler_linha(buffer, sizeof(buffer));
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
        printf("5) Como jogar (ajuda)\n");
        printf("6) Como criar um jogo personalizado (ajuda)\n");
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
            printf("=== INICIANDO DEMONSTRACAO AUTOMATICA ===\n\n");
            
            printf("Indo para: Sala Principal...\n");
            No* n = buscarNo(demo_map, "Sala Principal"); if (n) jog.pos = n; delay_ms(500);
            printf("Inspecionando Sala Principal...\n"); delay_ms(600);
            printf("(Demo) Pistas encontradas na Sala Principal:\n");
            printf("- Bilhete suspeito: Um bilhete com uma frase curta: 'voce sabe o que fez'. Papel amassado, tinta borrada.\n");
            printf("- Copo de vinho: Um copo de vinho tinto deixado na mesa, ainda com um pouco de liquido. Parece ter sido abandonado apressadamente.\n");
            delay_ms(1000);
            coletar_clue(demo_rooms, "Sala Principal", "Bilhete suspeito", &jog);
            delay_ms(500);

            printf("\nIndo para: Recepcao...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Recepcao"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Recepcao...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Recepcao", &jog);
            delay_ms(500);

            printf("\nIndo para: Sala de Cha...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Sala de Cha"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Sala de Cha...\n"); delay_ms(600);
            printf("(Demo) Pistas encontradas na Sala de Cha:\n");
            printf("- Cha derramado: Uma xicara de cha foi derramada na mesa, com o liquido ainda escorrendo para o chao, sugerindo que alguem saiu rapidamente.\n");
            delay_ms(1000);
            coletar_clue(demo_rooms, "Sala de Cha", "Cha derramado", &jog);
            delay_ms(500);

            printf("\nIndo para: Cozinha...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Cozinha"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Cozinha...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Cozinha", &jog);
            delay_ms(500);

            printf("\nIndo para: Laboratorio...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Laboratorio"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Laboratorio...\n"); delay_ms(600);
            printf("(Demo) Pistas encontradas no Laboratorio:\n");
            printf("- Frasco quebrado: Um frasco de vidro quebrado no chao do laboratorio, com restos de um liquido viscoso e escuro espalhados ao redor.\n");
            printf("- Equipamentos baguncados: Microscopios e equipamentos de laboratorio foram empurrados e alguns cairam no chao, criando uma bagunca que sugere uma busca apressada.\n");
            delay_ms(1000);
            coletar_clue(demo_rooms, "Laboratorio", "Frasco quebrado", &jog);
            delay_ms(500);

            printf("\nIndo para: Escritorio Administrativo...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Escritorio Administrativo"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Escritorio Administrativo...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Escritorio Administrativo", &jog);
            delay_ms(500);

            printf("\nIndo para: Jardim...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Jardim"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Jardim...\n"); delay_ms(600);
            printf("(Demo) Pistas encontradas no Jardim:\n");
            printf("- Pegada suja: Pegadas recem feitas, com manutencao de solado incomum; lama fresca indicando saida apressada.\n");
            printf("- Portao entreaberto: O portao do jardim esta entreaberto, com marcas de lama na maçaneta, indicando que alguem saiu correndo por ali.\n");
            delay_ms(1000);
            coletar_clue(demo_rooms, "Jardim", "Pegada suja", &jog);
            delay_ms(500);

            printf("\nIndo para: Area de Estacionamento...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Area de Estacionamento"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Area de Estacionamento...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Area de Estacionamento", &jog);
            delay_ms(500);

            printf("\nIndo para: Corredor Lateral...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Corredor Lateral"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Corredor Lateral...\n"); delay_ms(600);
            printf("(Demo) Pistas encontradas no Corredor Lateral:\n");
            printf("- Relatorios espalhados: Varios relatorios estao espalhados no chao do corredor, alguns rasgados e outros amassados, como se tivessem sido jogados com raiva.\n");
            delay_ms(1000);
            coletar_clue(demo_rooms, "Corredor Lateral", "Relatorios espalhados", &jog);
            delay_ms(500);

            printf("\nIndo para: Sala de Conferencias...\n"); delay_ms(600);
            n = buscarNo(demo_map, "Sala de Conferencias"); if (n) jog.pos = n; delay_ms(400);
            printf("Inspecionando Sala de Conferencias...\n"); delay_ms(600);
            inspecionar_comodo(demo_rooms, "Sala de Conferencias", &jog);
            delay_ms(500);

            printf("\n=== DEMONSTRACAO CONCLUIDA ===\n");

            printf("\nPistas coletadas (demo):\n");
            exibirPistasEmOrdem(jog.coletadas);
            if (demo_culpado) {
                printf("\n--- Resultado da Demo ---\n");
                printf("Culpado (segundo o caso-demo): %s\n", demo_culpado);
                free(demo_culpado);
            }
            if (demo_story) free(demo_story);
        } else if (strcmp(opt, "5") == 0) {
            exibir_ajuda_jogar();
        } else if (strcmp(opt, "6") == 0) {
            exibir_ajuda_construtor();
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