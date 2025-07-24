#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../config.h"

int countMapsInFile(FILE *file) {
    int mapCount = 0;
    int ch;
    
    while ((ch = fgetc(file)) != EOF)
        if (ch == '-') 
            mapCount++;

    // Conta o ultimo mapa
    if(!isspace(ch)) 
        mapCount++;

    return mapCount;
}

void setMapDimensions(Map *map, FILE *file) {
    char ch;
    int totMojis = 0;

    while ((ch = fgetc(file)) != EOF && ch != '-') {
        if (isspace(ch)) continue;

        if (!isdigit(ch)) {
            totMojis++;
            continue;
        }

        int height = ch - '0';
        map->lenCollumns++;

        if (height > map->maxHeight) {
            map->maxHeight = height;
        }
    }

    map->lenVoidCollumns = (map->lenCollumns * map->maxHeight - totMojis) / map->maxHeight;
}

void setMap(Map *map, FILE *file) {
    int lenColumn = 0;
    int curColumn = -1;
    int floor;
    char ch;

    // Coloca os mojis no mapa
    while ((ch = fgetc(file)) != EOF && ch != '-' && ch != '}') {
        if (isspace(ch)) continue;

        if(lenColumn--){
            map->collumns[curColumn].mojis[lenColumn + floor] = ch;
            continue;
        }

        // Presume-se que sempre vai ser um digito caso o mapa esteja correto
        curColumn++;
        lenColumn = ch - '0';
        floor = map->maxHeight - lenColumn;

        map->collumns[curColumn].mojis = malloc(sizeof(char) * map->maxHeight);
        map->collumns[curColumn].len = lenColumn;
        map->collumns[curColumn].complete = false;
    }

    map->lenCollumns = curColumn + 1;
}

void readMap(Map *map, FILE *file) {
    *map = (Map){0};
    int mapStartPosition = ftell(file);
    int totMojis = 0;

    setMapDimensions(map, file);

    // Vai pro começo do mapa
    fseek(file, mapStartPosition, SEEK_SET);

    map->collumns = malloc(sizeof(Collumn) * map->lenCollumns);

    setMap(map, file);
}

Maps *loadAllMaps(const char* filename) {
    FILE* file = fopen(filename, "r");
    int mapCount = 0;

    if (file == NULL) {
        printf("Arquivo de entrada '%s' não encontrado.\n", filename);
        exit(1);
    }

    Maps *maps = malloc(sizeof(Maps));
    maps->len = countMapsInFile(file);

    if (!maps->len) {
        printf("Nenhum mapa encontrado no arquivo '%s'.\n", filename);
        free(maps);
        fclose(file);
        exit(1);
    }

   maps->maps = malloc(sizeof(Map) * maps->len);

    // Volta para o começo do mapa
    fseek(file, 0, SEEK_SET);

    // Lê os mapas do arquivo
    for (int i = 0; i < maps->len; i++) 
        readMap(&maps->maps[i], file);

    fclose(file);

    return maps;
}

void freeMaps(Maps *maps) {
    for (int i = 0; i < maps->len; i++) {
        for (int j = 0; j < maps->maps[i].lenCollumns; j++) {
            free(maps->maps[i].collumns[j].mojis);
        }
        free(maps->maps[i].collumns);
    }
    
    free(maps->maps);
    free(maps);
}