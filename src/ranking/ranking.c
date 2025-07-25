#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../ui/ui.h"

void pushPlayer(Player *player) {
    FILE *arquivo = fopen("ranking.bin", "ab+");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de ranking");
        exit(1);
    }else{
        printf("Arquivo de ranking aberto com sucesso.\n");
    }

    fwrite(player, sizeof(Player), 1, arquivo);
    printf("Jogador '%s' com score %d salvo com sucesso!\n", player->nickname, player->score);

    fclose(arquivo);
}

int compScores(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerB->score - playerA->score;
}

int getNumPlayers(FILE *file) {
    fseek(file, 0, SEEK_END);

    long fileSize = ftell(file);
    int numPlayers = fileSize / sizeof(Player);

    fclose(file);

    return numPlayers;
}

void readRanking() {
    FILE *file = fopen("ranking.bin", "rb");

    if (file == NULL) {
        printf("Ainda não há scores salvos.\n\n");
        return;
    }

    int numPlayers = getNumPlayers(file);

    if (numPlayers == 0) {
        printf("Nenhum jogador cadastrado\n\n");
        return;
    }

    Player players[numPlayers];
    file = fopen("ranking.bin", "rb"); 

    fread(players, sizeof(Player), numPlayers, file);
    fclose(file);

    qsort(players, numPlayers, sizeof(Player), compScores);
    showRanking(players, numPlayers);
}

void zerarRanking() {
    char confirm;
    printf("Tem certeza que deseja zerar o ranking? (s/n): ");
    scanf(" %c", &confirm);

    if(confirm != 's' && confirm != 'S') 
        return;

    FILE *file = fopen("ranking.bin", "wb");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo de ranking");
        exit(1);
    }

    printf("Ranking zerado!\n");

    fclose(file);
}

void openConfig(){
    while(1) {
        clearScreen();
        showConfig();
        char option;
        enterOption(&option);
        option -= '0';

        switch (option) {
            case CONFIG_ZERAR_RANKING:
                zerarRanking();
                break;
            case CONFIG_MODO_BLIND:
                printf("Modo Blind não implementado\n");
                break;
            case CONFIG_EDITOR_FASES:
                printf("Editor de Fases não implementado\n");
                break;
            case CONFIG_VOLTAR_MENU:
                return;
        }
    }
}
