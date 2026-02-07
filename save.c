#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "menu.h"
#include "combat.h"
#include <time.h>
#include "center.h"
#include "shop.h"
#include "choix_valide.h"
#include "inventaire.h"
#include "save.h"

int load_game(struct JOUEUR *player) {
    FILE *f = fopen("save.dat", "rb");
    if (!f) {
        return 0;
    }
    fread(player, sizeof(struct JOUEUR), 1, f);
    fclose(f);
    return 1;
}

void save_game(struct JOUEUR *player) {
    FILE *f = fopen("save.dat", "wb");
    if (!f) {
        printf("Error: could not save game.\n");
        return;
    }
    fwrite(player, sizeof(struct JOUEUR), 1, f);
    fclose(f);
    printf("Game saved successfully!\n");
}