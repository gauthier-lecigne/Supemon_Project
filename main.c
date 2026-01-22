#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void player_info(struct JOUEUR *player) {
    printf("Enter you player name : "); scanf("%29s", player->name_player);
    player->Supecoins = 500; player-> nb_supemons = 0; player -> nb_items = 0;
}

int main() {
    struct JOUEUR player;
    player_info(&player);
}