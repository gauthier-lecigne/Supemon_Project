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

void inventory(struct JOUEUR *player) {
    printf("Your Inventory : \n");
    printf("Potions : %d\n", player->inventaire.nb_potions);
    printf("Super Potions : %d\n", player->inventaire.nb_super_potions);
    printf("Super Bonbons : %d\n", player->inventaire.nb_super_bonbons);
    printf("\n");
    printf("Do you want to use an item ? Type 1 for yes and 2 for no : ");
    int choix = valid_choix_int(1, 2);
    if (choix == 1) {
        use_item_inventory(player);
    } else {
        printf("You chose not to use an item.\n");
    }
}

void use_item_inventory(struct JOUEUR *player) {
    printf("\nWhat do you want to use ? \n");

    int choix_item = 0;
    int choix_supemon = 0;

    if (player->inventaire.nb_potions > 0)
        printf("1 - Potion (+%d HP) [You have %d]\n",
               POTION_HEAL, player->inventaire.nb_potions);

    if (player->inventaire.nb_super_potions > 0)
        printf("2 - Super Potion (+%d HP) [You have %d]\n",
               SUPER_POTION_HEAL, player->inventaire.nb_super_potions);

    if (player->inventaire.nb_super_bonbons > 0)
        printf("3 - Super Bonbon (+%d Level) [You have %d]\n",
               SUPER_BONBON, player->inventaire.nb_super_bonbons);

    printf("Enter the number of the item you want to use: ");
    choix_item = valid_choix_int(1, 3);

    printf("\nChoose a Supemon:\n");
    for (int i = 0; i < player->nb_supemons; i++) {
        printf("%d - %s (HP: %d/%d, Level: %d)\n",
               i + 1,
               player->supemons[i].name,
               player->supemons[i].HP,
               player->supemons[i].Max_HP,
               player->supemons[i].level);
    }

    choix_supemon = valid_choix_int(1, player->nb_supemons) - 1;
    struct SUPEMON *target = &player->supemons[choix_supemon];

    switch (choix_item) {

        case 1:
            if (player->inventaire.nb_potions <= 0) {
                printf("You don't have any Potion left !\n");
                return;
            }
            target->HP += POTION_HEAL;
            if (target->HP > target->Max_HP)
                target->HP = target->Max_HP;
            player->inventaire.nb_potions--;
            printf("You used a Potion on %s! (%d/%d HP)\n",target->name, target->HP, target->Max_HP);
            break;

        case 2:
            if (player->inventaire.nb_super_potions <= 0) {
                printf("You don't have any Super Potion left !\n");
                return;
            }
            target->HP += SUPER_POTION_HEAL;
            if (target->HP > target->Max_HP)
                target->HP = target->Max_HP;
            player->inventaire.nb_super_potions--;
            printf("You used a Super Potion on %s! (%d/%d HP)\n",target->name, target->HP, target->Max_HP);
            break;

        case 3:
            if (player->inventaire.nb_super_bonbons <= 0) {
                printf("You don't have any Super Bonbon left !\n");
                return;
            }
            target->level += SUPER_BONBON;
            player->inventaire.nb_super_bonbons--;
            printf("%s leveled up to level %d!\n",target->name, target->level);
            break;
    }
}
