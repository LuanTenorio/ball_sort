
#include <stdio.h>
#include "../config.h"

int countMapsInFile(FILE *file);
void setMapDimensions(Map *map, FILE *file);
void setMap(Map *map, FILE *file);
void readMap(Map *map, FILE *file);
Maps *loadAllMaps(const char* filename);
