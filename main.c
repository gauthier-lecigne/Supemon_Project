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
#include "save.h"

void player_info(struct JOUEUR *player) {
    printf("Enter you player name : "); scanf("%29s", player->name_player);
    printf("Welcome in Supemon World %s !\n", player-> name_player);
    player->Supecoins = 500; player-> nb_supemons = 0; player -> nb_items = 0;
    player->inventaire.nb_potions = 3;
    player->inventaire.nb_super_potions = 1;
    player->inventaire.nb_super_bonbons = 1;
}

void starter_choice(struct SUPEMON *supemon) {
    int choix = 0;
    printf("+----------------------------+\n");
    printf("|Choose your starter Supemon:|\n");
    printf("|    1 - Supmander           |\n");
    printf("|    2 - Supasaur            |\n");
    printf("|    3 - Supirtle            |\n");
    printf("+----------------------------+\n");
    printf("Enter the number of the Supemon you want to choose : ");
    choix = valid_choix_int(1, 3);
    switch (choix)
        {
        case 1:
            strcpy(supemon->name, "Supmander");
            supemon-> level = 1;
            supemon-> HP = 10;
            supemon-> Max_HP = supemon-> HP;
            supemon-> attack = 1;
            supemon-> defense = 1;
            supemon-> evasion = 1;
            supemon-> accuracy = 2;
            supemon-> speed = 1;

            supemon->nb_moves = 2;
            strcpy(supemon->moves[0].name, "Scratch");
            supemon->moves[0].damage = 3;
            supemon->moves[0].attack_boost = 0;
            supemon->moves[0].defense_boost = 0;
            supemon->moves[0].evasion_boost = 0;

            strcpy(supemon->moves[1].name, "Grawl");
            supemon->moves[1].damage = 0;
            supemon->moves[1].attack_boost = 1;
            supemon->moves[1].defense_boost = 0;
            supemon->moves[1].evasion_boost = 0;
            break;
        case 2:
            strcpy(supemon->name, "Supasaur");
            supemon-> level = 1;
            supemon-> HP = 9;
            supemon-> Max_HP = supemon-> HP;
            supemon-> attack = 1;
            supemon-> defense = 1;
            supemon-> evasion = 3;
            supemon-> accuracy = 2;
            supemon-> speed = 2;

            supemon->nb_moves = 2;
            strcpy(supemon->moves[0].name, "Pound");
            supemon->moves[0].damage = 2;
            supemon->moves[0].attack_boost = 0;
            supemon->moves[0].defense_boost = 0;
            supemon->moves[0].evasion_boost = 0;


            strcpy(supemon->moves[1].name, "Foliage");
            supemon->moves[1].damage = 0;
            supemon->moves[1].attack_boost = 0;
            supemon->moves[1].defense_boost = 0;
            supemon->moves[1].evasion_boost = 1;
            break;
        case 3:
            strcpy(supemon->name, "Supirtle");
            supemon-> level = 1;
            supemon-> HP = 11;
            
            supemon-> attack = 1;
            supemon-> defense = 2;
            supemon-> evasion = 2;
            supemon-> accuracy = 1;
            supemon-> speed = 2;

            supemon->nb_moves = 2;
            strcpy(supemon->moves[0].name, "Pound");
            supemon->moves[0].damage = 2;
            supemon->moves[0].attack_boost = 0;
            supemon->moves[0].defense_boost = 0;
            supemon->moves[0].evasion_boost = 0;

            strcpy(supemon->moves[1].name, "Shell");
            supemon->moves[1].damage = 0;
            supemon->moves[1].attack_boost = 0;
            supemon->moves[1].defense_boost = 1;
            supemon->moves[1].evasion_boost = 0;
            break;
    }
}


int main() {
    srand(time(NULL));
    struct JOUEUR player; 
    struct SUPEMON starter;
    if (load_game(&player)) {
        printf("A saved game was found for player %s. Do you want to load it ? type 1 for yes and 2 for no : ",player.name_player);
        int choix = valid_choix_int(1, 2);
        if (choix == 1) {
            printf("Continuing your saved game...\n");
            game_loop(&player);
            return 0;
        }
    }
    player_info(&player);
    starter_choice(&starter);
    player.supemons[0] = starter;
    player.nb_supemons = 1;
    game_loop(&player);
    return 0;
}