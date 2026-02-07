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

void supemon_shop(struct JOUEUR *player) {
    int choix_user = 0;
    while (choix_user != 3) {
        printf("\nWelcome to the Supemon Shop !\n");
        printf("You have %d Supecoins\n", player->Supecoins);
        printf("Your inventory : Potions %d | Super Potions %d\n", player->inventaire.nb_potions, player->inventaire.nb_super_potions);

        printf("+----------------------------------------+\n");
        printf("| 1 - Buy Potion (100 Supecoins)         |\n");
        printf("| 2 - Buy Super Potion (300 Supecoins)   |\n");
        printf("| 3 - Sell a Potion (50 Supecoins)       |\n");
        printf("| 4 - Sell a Super Potion (150 Supecoins)|\n");
        printf("| 5 - Leave The Shop                     |\n");
        printf("+----------------------------------------+\n");

        printf("Your Choice : ");
        choix_user = valid_choix_int(1, 5);
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
                if (player->inventaire.nb_potions > 0) {
                    player->Supecoins += POTION_PRICE / 2;
                    player->inventaire.nb_potions -= 1;
                    printf("You sold a Potion.\n");
                } else {
                    printf("You don't have any potions to sell.\n");
                }
                break;
            case 4:
                if (player->inventaire.nb_super_potions > 0) {
                    player->Supecoins += SUPER_POTION_PRICE / 2;
                    player->inventaire.nb_super_potions -= 1;
                    printf("You sold a Super Potion.\n");
                } else {
                    printf("You don't have any Super Potions to sell.\n");
                }
                break;
            case 5:
                printf("You chose to leave the Shop... Goodbye !\n");
                return;
            default:
                printf("Invalid Choice, please choose a number between 1 and 5.\n");
        }
    }
}