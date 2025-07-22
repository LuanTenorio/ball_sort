void convertMapToArray();
bool startGame();
int play(int *input, int *output);
void removeMojisFromInputColumn(Map *map, int *lenMojis, char selectedMoji);
void putMojisInOutputColumn(Map *map, int lenMojis, char selectedMoji);
bool isValidSwap(Map *map, int lenMojis);
bool swapMojis(Map *map);