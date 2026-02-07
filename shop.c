#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "menu.h"
#include "combat.h"
#include <time.h>
#include "center.h"
#include "shop.h"

void supemon_shop(struct JOUEUR *player) {
    int choix_user = 0;
    while (choix_user != 3) {
        printf("\nWelcome to the Supemon Shop !\n");
        printf("You have %d Supecoins\n", player->Supecoins);
        printf("Your inventory : Potions %d | Super Potions %d\n", player->inventaire.nb_potions, player->inventaire.nb_super_potions);

        printf("+---------------------------------------+\n");
        printf("| 1 - Buy Potion (50 Supecoins)         |\n");
        printf("| 2 - Buy Super Potion (300 Supecoins)  |\n");
        printf("| 3 - Leave The Shop                    |\n");
        printf("+---------------------------------------+\n");

        printf("Your Choice : "), scanf("%d", &choix_user);
        switch (choix_user) {
            case 1:
                if (player->Supecoins >= POTION_PRICE) {
                    player->Supecoins -= POTION_PRICE;
                    player->inventaire.nb_potions += 1;
                    printf("You Bought a Potion.\n");
                } else {
                    printf("You don't have enough money.\n");
                }
                break;
            case 2:
                if (player->Supecoins >= SUPER_POTION_PRICE) {
                    player->Supecoins -= SUPER_POTION_PRICE;
                    player->inventaire.nb_super_potions += 1;
                    printf("You bought a Super Potion.\n");
                } else {
                    printf("You don't have enough money.\n");
                }
                break;
            case 3:
                printf("You chose to leave the Shop ... Goodbye !\n");
                game_loop(player);
                return;
            
            default:
                printf("Invalid Choice, please choose a number between 1 and 3.\n");
        }
    }
}