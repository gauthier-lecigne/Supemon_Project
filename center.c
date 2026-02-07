#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "menu.h"
#include "combat.h"
#include <time.h>
#include "center.h"
#include "shop.h"
#include "choix_valide.h"
#include "inventaire.h"

void supemon_center(struct JOUEUR *player) {
    for (int i = 0; i < player->nb_supemons; i++) {
        player->supemons[i].HP = player->supemons[i].Max_HP;
    }
    printf("All your Supemons have been healed !\n");
}