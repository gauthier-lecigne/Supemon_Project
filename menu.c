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

void leave_game(struct JOUEUR *player);

void game_loop(struct JOUEUR *player) {
    int choix_dir = 0;
    printf("+------------------------------+\n");
    printf("|Where do you want to go?      |\n");
    printf("|    1 - Into the wild         |\n");
    printf("|    2 - In the shop           |\n");
    printf("|    3 - In the Supemon Center |\n");
    printf("|    4 - Inventory             |\n");
    printf("|    5 - Leave the Game        |\n");
    printf("+------------------------------+\n");
    printf("Enter the number of your choice : ");
    choix_dir = valid_choix_int(1, 5);
    switch (choix_dir)
    {
    case 1:
        InTheWild(player);
        break;
    case 2:
        InTheShop(player);
        break;
    case 3:
        SupemonCenter(player);
        break;
    case 4: 
        inventory(player);
        game_loop(player);
        break;
    case 5:
        leave_game(player);
        break;
    }
}

void InTheWild(struct JOUEUR *player) {
    printf("You entered the wild ! \n");
     fight(&player->supemons[0], player);
    
}

void InTheShop(struct JOUEUR *player) {
    supemon_shop(player);
}

void SupemonCenter(struct JOUEUR *player) {
    printf("\nWelcome to the Supemon Center !\n");
    supemon_center(player);
    for (int i = 0; i < player->nb_supemons; i++) {
        printf("%s : %d/%d HP\n", player->supemons[i].name, player->supemons[i].HP, player->supemons[i].Max_HP);
    }
    printf("\n");
    game_loop(player);
}

void inventory_dir(struct JOUEUR *player) {
    printf("\nWelcome to your Inventory !\n");
    inventory(player);
}

void leave_game(struct JOUEUR *player) {
    printf("Do you want to save your game before leaving ? type 1 for yes ans 2 for no : ");
    int choix = valid_choix_int(1, 2);
    if (choix == 1) {
        save_game(player);
    }
    printf("Thank you for playing Supemon, see you next time !\n");
    exit(0);
}