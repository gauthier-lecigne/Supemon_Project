#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "menu.h"
#include "combat.h"

void game_loop(struct JOUEUR *player) {
    int choix_dir = 0;
    printf("+------------------------------+\n");
    printf("|Where do you want to go?      |\n");
    printf("|    1 - Into the wild         |\n");
    printf("|    2 - In the shop           |\n");
    printf("|    3 - In the Supemon Center |\n");
    printf("|    4 - Leave the Game        |\n");
    printf("+------------------------------+\n");
    while (choix_dir < 1 || choix_dir > 4) {
        printf("Choose where do you want to go by typing numbers between 1 and 4 :"); scanf("%d",&choix_dir);
        if (choix_dir < 1 ||choix_dir > 4) {
            printf("Invalid choice, please write a number between 1 and 4 : ");
        }
    }
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
        printf("You chose to Leave the Game.... Goodbye !!!\n");
        break;
    }
}

void InTheWild(struct JOUEUR *player) {
    printf("You entered the wild ! \n");
     fight(&player->supemons[0], player);
    
}

void InTheShop(struct JOUEUR *player) {
    printf("Welcome to the shop ! \n");
}

void SupemonCenter(struct JOUEUR *player) {
    printf("Welcome to the Supemon Center ! \n");
}
