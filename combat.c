#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "menu.h"
#include "combat.h"
#include <time.h>

struct SUPEMON generate_wild(struct SUPEMON *player) {
    struct SUPEMON wild;
    int choice = rand() % 3;
    wild.level = 1;

    switch (choice) {
        case 0:
            strcpy(wild.name, "Supmander");
            wild.HP = 10 * wild.level;
            wild.Max_HP = 2 * wild.HP;
            wild.attack = 1;
            wild.defense = 1;
            wild.evasion = 1;
            wild.accuracy = 2;
            wild.speed = 1;
            wild.nb_moves = 2;

            strcpy(wild.moves[0].name, "Scratch");
            wild.moves[0].damage = 3;
            wild.moves[0].attack_boost = 0;
            wild.moves[0].defense_boost = 0;
            wild.moves[0].evasion_boost = 0;

            strcpy(wild.moves[1].name, "Grawl");
            wild.moves[1].damage = 0;
            wild.moves[1].attack_boost = 1;
            wild.moves[1].defense_boost = 0;
            wild.moves[1].evasion_boost = 0;
            break;

        case 1:
            strcpy(wild.name, "Supasaur");
            wild.HP = 9 * wild.level;
            wild.Max_HP = 2 * wild.HP;
            wild.attack = 1;
            wild.defense = 1;
            wild.evasion = 3;
            wild.accuracy = 2;
            wild.speed = 2;
            wild.nb_moves = 2;

            strcpy(wild.moves[0].name, "Pound");
            wild.moves[0].damage = 2;
            wild.moves[0].attack_boost = 0;
            wild.moves[0].defense_boost = 0;
            wild.moves[0].evasion_boost = 0;

            strcpy(wild.moves[1].name, "Foliage");
            wild.moves[1].damage = 0;
            wild.moves[1].attack_boost = 0;
            wild.moves[1].defense_boost = 0;
            wild.moves[1].evasion_boost = 1;
            break;

        case 2:
            strcpy(wild.name, "Supirtle");
            wild.HP = 11 * wild.level;
            wild.Max_HP = 2 * wild.HP;
            wild.attack = 1;
            wild.defense = 2;
            wild.evasion = 2;
            wild.accuracy = 1;
            wild.speed = 2;
            wild.nb_moves = 2;

            strcpy(wild.moves[0].name, "Pound");
            wild.moves[0].damage = 2;
            wild.moves[0].attack_boost = 0;
            wild.moves[0].defense_boost = 0;
            wild.moves[0].evasion_boost = 0;

            strcpy(wild.moves[1].name, "Shell");
            wild.moves[1].damage = 0;
            wild.moves[1].attack_boost = 0;
            wild.moves[1].defense_boost = 1;
            wild.moves[1].evasion_boost = 0;
            break;
    }
    return wild;
}

int calculate_damage(struct SUPEMON *attacker, struct SUPEMON *target, struct MOVE *move) {
    int numerator = attacker->attack * move->damage;
    int denominator = target->defense;
    int damage;
    if (denominator == 0) denominator = 1;
    damage = numerator / denominator;
    if (numerator % denominator != 0) {
        if (rand() % 2 == 0) {
            damage += 1;
        }
    }
    attacker->attack += move->attack_boost;
    target->defense += move->defense_boost;
    target->evasion += move->evasion_boost;
    if (damage < 0) damage = 0;
    return damage;
}

int player_turn(struct SUPEMON *player) {
    int choice = 0;
    printf("This is player's turn !\n");
    printf("Your Supemon %s has %d HP \n", player->name, player->HP);
    printf("Choose your move : \n");
    printf("+----------------------------+\n");
    printf("|     1 - Move               |\n");
    printf("|     2 - Change Supemon     |\n");
    printf("|     3 - Use Item           |\n");
    printf("|     4 - Run                |\n");
    printf("|     5 - Capture            |\n");
    printf("+----------------------------+\n");
    while (choice < 1 || choice > 5) {
        printf("Enter a number between 1 and 5 : "); scanf("%d", &choice);
        if (choice < 1 || choice > 5) {
            printf("Invalid, please enter a number between 1 and 5\n");
        }
    return choice;
    }

}

void player_move(struct SUPEMON *attacker, struct SUPEMON *target) {
    int choix = 0;
    printf("Choose a move for your Supemon %s : \n", attacker->name);
    for (int i = 0; i < attacker->nb_moves; i++) {
        printf("%d - %s \n", i + 1, attacker->moves[i].name);
    }

    while (choix < 1 || choix > attacker->nb_moves) {
        printf("Enter the move number : "); scanf("%d", &choix);
    }

    struct MOVE *move = &attacker->moves[choix - 1];
    if (move->damage > 0) {
        int damage = calculate_damage(attacker, target, move);
        target->HP -= damage;
        printf("%s used %s and it made %d damage on %s ! He has now %d HP left\n", attacker->name, move->name, damage, target->name, target->HP);
    }
    if (move->attack_boost > 0) {
        attacker->attack += move->attack_boost;
        printf("%s's attack increased by %d!\n", attacker->name, move->attack_boost);
    }
    if (move->defense_boost > 0) {
        attacker->defense += move->defense_boost;
        printf("%s's defense increased by %d!\n", attacker->name, move->defense_boost);
    }
    if (move->evasion_boost > 0) {
        attacker->evasion += move->evasion_boost;
        printf("%s's evasion increased by %d!\n", attacker->name, move->evasion_boost);
    }
}


int change_supemon(struct SUPEMON *player_supemons, int nb_supemons) {
    if (nb_supemons < 2) {
        printf("You only have one Supemon, you can't change!\n");
        return -1;
    }
    int choix = 0;
    printf("Choose a Supemon to switch to : \n");
    for (int i = 0; i < nb_supemons; i++) {
        printf("%d - %s (HP: %d)\n", i+1, player_supemons[i].name, player_supemons[i].HP);
    }
    while (choix < 1 || choix > nb_supemons) {
        printf("Enter the number of the Supemon you want to switch to : "); scanf("%d", &choix);
        if (choix < 1 || choix > nb_supemons) {
            printf("Invalid, choose a number between 1 and %d\n", nb_supemons);
        }
    }
    return choix - 1;
}


void use_item() {
    printf("Not implemented yet ! \n");
}

void run_away(struct JOUEUR *player) {
    printf("You ran away successfully ! \n");
    printf("Where do you want to go now ? \n");
    game_loop(player);

}

int capture(struct SUPEMON *enemy, struct JOUEUR *player) {
    float chance_capture = (float)(enemy->Max_HP - enemy->HP) / enemy->Max_HP - 0.5f;
    if (chance_capture < 0) chance_capture = 0;
    if (chance_capture > 0.99) chance_capture = 0.99;

    int valeur_random = rand() % 100;
    if (valeur_random < (int)(chance_capture * 100)) {
        printf("You captured %s !\n", enemy->name);
        if (player->nb_supemons < MAX_SUPEMON) {
            player->supemons[player->nb_supemons] = *enemy;
            player->nb_supemons += 1;
        } else {
            printf("You have the Max Capacity of Supemon so you can't capture %s\n", enemy->name);
        }
        return 1;
    } else {
        printf("Captured Failed!\n");
        return 0;
    }
}




void fight(struct SUPEMON *player_supemon, struct JOUEUR *player) {
    struct SUPEMON wild_supemon = generate_wild(player_supemon);
    printf("A wild %s appeared !\n", wild_supemon.name);
    int current_player_index = 0;
    int who_starts;
    if (player_supemon->speed >  wild_supemon.speed) {
        who_starts = 1;
    } else if (player_supemon->speed < wild_supemon.speed) {
        who_starts = 0;
    } else {
        who_starts = rand() % 2;
    }

    while (player_supemon->HP > 0 && wild_supemon.HP > 0) {
        if (who_starts == 1) {
            int action = player_turn(player_supemon);
            switch (action) {
                case 1:
                    player_move(player_supemon, &wild_supemon);
                    break;
                case 2:
                    {
                        int new_index = change_supemon(player->supemons, player->nb_supemons);
                        if (new_index != -1) {
                            player_supemon = &player->supemons[new_index];
                            printf("You switched to %s ! \n", player_supemon->name);
                        }
                    }
                    break;
                case 3:
                    printf("Use Item, not implemented yet ! \n");
                    break;
                case 4:
                    run_away(player);
                    break;
                case 5:
                    capture(&wild_supemon, player);
                    break;
            }
        } else {
            int move_index = rand() % wild_supemon.nb_moves;
            struct MOVE *move = &wild_supemon.moves[move_index];
            int damage = calculate_damage(&wild_supemon, player_supemon, move);
            player_supemon->HP -= damage;

            printf("\n--- ENEMY TURN ---\n");
        printf("The wild %s used %s!\n", wild_supemon.name, move->name);
        printf("It dealt %d damage to your %s.\n", damage, player_supemon->name);
        printf("------------------\n\n");
        }
        who_starts = !who_starts;
    }
    if (player_supemon->HP <= 0) {
        printf("Your Supemon %s fainted! You lost the fight.\n", player_supemon->name);
        printf("Where do you want to do now ?\n");
        printf("1 - Change Supemon\n");
        printf("2 - Go to the Supemon Center and leave the fight\n");
        int choice_suite = 0;
        while (choice_suite < 1 || choice_suite > 2) {
            printf("Enter 1 or 2 : "); scanf("%d", &choice_suite);
            if (choice_suite < 1 ||choice_suite > 2) {
                printf("Invalid choice, please enter a number between 1 and 2.\n");
            }
            if (choice_suite == 1) {
                if (player->nb_supemons < 2) {
                    printf("You have no other Supemon, you have to go to the Supemon Center.\n");
                }
                int new_index = change_supemon(player->supemons, player->nb_supemons);
                if (new_index != -1) {
                    player_supemon = &player->supemons[new_index];
                    printf("You switched to %s ! \n", player_supemon->name);
                    fight(player_supemon, player);
                }
            } else {
                printf("You chose to go to the Supemon Center. Your Supemon will be healed there.\n");
                // besoin d'ajouter l'appel de la fonction Supemon center quand sera finie.
            }
        }
    } else {
        printf("You defeated the wild %s!\n", wild_supemon.name);
        player->Supecoins += 100;
        printf("You won 100 Supecoins! You now have %d Supecoins. \n", player->Supecoins);
        game_loop(player);
    }
}