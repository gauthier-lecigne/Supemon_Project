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

struct SUPEMON generate_wild(struct SUPEMON *player) {
    struct SUPEMON wild;
    int choice = rand() % 3;
    wild.level = 1;

    switch (choice) {
        case 0:
            strcpy(wild.name, "Supmander");
            wild.HP = 10 * wild.level;
            wild.Max_HP = wild.HP;
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
            wild.Max_HP = wild.HP;
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
            wild.Max_HP = wild.HP;
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
    if (denominator == 0) denominator = 1;

    int damage = numerator / denominator;
    if (numerator % denominator != 0 && rand() % 2 == 0) {
        damage += 1;
    }
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
    printf("Enter the number of your choice : ");
    choice = valid_choix_int(1, 5);
    return choice;
}

void player_move(struct SUPEMON *attacker, struct SUPEMON *target) {
    int choix = 0;
    printf("Choose a move for your Supemon %s : \n", attacker->name);
    for (int i = 0; i < attacker->nb_moves; i++) {
        printf("%d - %s \n", i + 1, attacker->moves[i].name);
    }

    while (choix < 1 || choix > attacker->nb_moves) {
        printf("Enter the move number : ");
        choix = valid_choix_int(1, attacker->nb_moves);
    }

    struct MOVE *move = &attacker->moves[choix - 1]; 
    if (move->damage > 0) {
        float chance_hit =(float)attacker->accuracy/(attacker->accuracy + target->evasion)+0.1f;
    if (chance_hit > 0.95f) chance_hit = 0.95f;
    int valeur_random = rand() % 100;
    if (valeur_random >= (int)(chance_hit * 100)) {
        printf("\n %s used %s but missed !\n", attacker->name, attacker->moves[choix-1].name);
        return;
    }

    int damage = calculate_damage(attacker, target, move);
    target->HP -= damage;

    if (target->HP < 0) target->HP = 0;
        printf("\n %s used %s and it made %d damgage to %s ! He has now %d HP left.\n", attacker->name, move->name, damage, target->name, target->HP);
    }

    if (move->attack_boost > 0) {
        attacker->attack += move->attack_boost;
        printf("%s attack increased by %d !\n", attacker->name, move->attack_boost);
    }

    if (move->defense_boost > 0) {
        attacker->defense += move->defense_boost;
        printf("%s defense increased by %d !\n", attacker->name, move->defense_boost);
    }

    if (move->evasion_boost > 0) {
        attacker->evasion += move->evasion_boost;
        printf("%s evasion increased by %d !\n", attacker->name, move->evasion_boost);
    }
}






int change_supemon(struct SUPEMON *player_supemons, int nb_supemons, struct JOUEUR *player) {
    if (nb_supemons < 2) {
        printf("You only have one Supemon, you can't change!\n");
        game_loop(player);
        return -1;
    }
    int choix = 0;
    printf("Choose a Supemon to switch to : \n");
    for (int i = 0; i < nb_supemons; i++) {
        printf("%d - %s (HP: %d)\n", i+1, player_supemons[i].name, player_supemons[i].HP);
    }
    while (choix < 1 || choix > nb_supemons) {
        printf("Enter the number of the Supemon you want to switch to : ");
        choix = valid_choix_int(1, nb_supemons);
        if (choix < 1 || choix > nb_supemons) {
            printf("Invalid, choose a number between 1 and %d\n", nb_supemons);
        }
    }
    return choix - 1;
}





void use_item(struct JOUEUR *player, int *items_used) {
    if (*items_used >= 4) {
        printf("You have used the maximum number of items in a fight (4)!\n");
        return;
    }

    if (player->inventaire.nb_potions == 0 && player->inventaire.nb_super_potions == 0) {
        printf("You have no items in your inventory!\n");
        return;
    }

    int choix_item = 0;

    do {
        printf("Choose an item to use : \n");
        if (player->inventaire.nb_potions > 0)
            printf("1 - Potion (+%d HP) [You have %d]\n", POTION_HEAL, player->inventaire.nb_potions);
        if (player->inventaire.nb_super_potions > 0)
            printf("2 - Super Potion (+%d HP) [You have %d]\n", SUPER_POTION_HEAL, player->inventaire.nb_super_potions);
        
        printf("Enter the number of the item you want to use: ");
        scanf("%d", &choix_item);

        if ((choix_item == 1 && player->inventaire.nb_potions == 0) || 
            (choix_item == 2 && player->inventaire.nb_super_potions == 0) ||
            (choix_item < 1 || choix_item > 2)) {
            printf("Invalid choice, please try again.\n");
        } else {
            break;
        }
    } while (1);
    int cible_supemon = 0;
    do {
        printf("Choose a Supemon to use the item on : \n");
        for (int i = 0; i < player->nb_supemons; i++) {
            printf("%d - %s (HP: %d/%d)\n", i+1, player->supemons[i].name, player->supemons[i].HP, player->supemons[i].Max_HP);
        }
        printf("Enter Supemon number: ");
        scanf("%d", &cible_supemon);
    } while (cible_supemon < 1 || cible_supemon > player->nb_supemons);
    cible_supemon -= 1;

    int heal = 0;
    if (choix_item == 1) {
        heal = POTION_HEAL;
        player->inventaire.nb_potions--;
    } else if (choix_item == 2) {
        heal = SUPER_POTION_HEAL;
        player->inventaire.nb_super_potions--;
    }
    player->supemons[cible_supemon].HP += heal;
    if (player->supemons[cible_supemon].HP > player->supemons[cible_supemon].Max_HP)
        player->supemons[cible_supemon].HP = player->supemons[cible_supemon].Max_HP;
    printf("You used the item on %s! He healed %d HP and now has %d/%d HP\n",player->supemons[cible_supemon].name, heal,player->supemons[cible_supemon].HP, player->supemons[cible_supemon].Max_HP);
    (*items_used)++;
}


int run_away(struct JOUEUR *player, struct SUPEMON *enemy) {
    int chance_run = player->supemons[0].speed  / (float)(player->supemons[0].speed + enemy->speed);
    if (chance_run > 0.95f) chance_run = 0.95f;
    int valeur_random = rand() % 100;
    if (valeur_random >= (int)(chance_run * 100)) {
        printf("You failed to run away ! The wild %s is still there !\n", enemy->name);
        return 0;
    } else {
        printf("You successfully ran away from the wild %s !\n", enemy->name);
        return 1;
    }

}


int capture(struct SUPEMON *enemy, struct JOUEUR *player) {
    float chance_capture = (float)(enemy->Max_HP - enemy->HP) / enemy->Max_HP - 0.5f;
    if (chance_capture < 0) chance_capture = 0;
    if (chance_capture > 0.99f) chance_capture = 0.99f;

    int valeur_random = rand() % 100;
    if (valeur_random >= (int)(chance_capture * 100)) {
        printf("Czptured Failed ! The wild %s escaped !\n", enemy->name);
        return 0;
    }
    if (player->nb_supemons >= MAX_SUPEMON) {
        printf("Your team is full, you can't cature %s !\n", enemy->name);
        return 0;
    }

    player->supemons[player->nb_supemons] = *enemy;
    player->nb_supemons += 1;
    printf("You captured the wild %s ! He is now in you team !\n", enemy->name);
    return 1;
}


int fight(struct SUPEMON *player_supemon, struct JOUEUR *player) {
    struct SUPEMON wild_supemon = generate_wild(player_supemon);
    printf("A wild %s appeared !\n", wild_supemon.name);
    int current_player_index = 0;
    int items_used = 0;
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
                        int new_index = change_supemon(player->supemons, player->nb_supemons, player);
                        if (new_index != -1) {
                            player_supemon = &player->supemons[new_index];
                            printf("You switched to %s ! \n", player_supemon->name);
                        }
                    }
                    break;
                case 3:
                    use_item(player, &items_used);
                    break;
                    break;
                case 4:
                    if (run_away(player, &wild_supemon)) {
                        game_loop(player);
                        return 1;
                    }
                    break;
                case 5:
                    if (capture(&wild_supemon, player)) {
                        game_loop(player);;
                        return 1;
                    }
                    break;
            }
        } else {
            int move_index = rand() % wild_supemon.nb_moves;
            struct MOVE *move = &wild_supemon.moves[move_index];
            
            float chance_hit = (float)wild_supemon.accuracy / (wild_supemon.accuracy + player_supemon->evasion) + 0.1f;
            if (chance_hit > 0.95f) chance_hit = 0.95f;
            int valeur_random = rand() % 100;

            printf("\n--- ENEMY TURN ---\n");
            printf("The wild %s used %s :\n", wild_supemon.name, move->name);

            if (valeur_random >= (int)(chance_hit * 100)) {
                printf("His attack missed !\n");
            } else {
                int damage = calculate_damage(&wild_supemon, player_supemon, move);
                player_supemon->HP -= damage;
                if (player_supemon->HP < 0) player_supemon->HP = 0;
                printf("It made %d damage to your %s ! He has now %d HP left.\n", damage, player_supemon->name, player_supemon->HP);
            }
            printf("--- END OF ENEMY TURN --- \n\n");
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
            printf("Enter 1 or 2 : ");
            choice_suite = valid_choix_int(1, 2);
            if (choice_suite == 1) {
                if (player->nb_supemons < 2) {
                    printf("You have no other Supemon, you have to go to the Supemon Center.\n");
                }
                int new_index = change_supemon(player->supemons, player->nb_supemons, player);
                if (new_index != -1) {
                    player_supemon = &player->supemons[new_index];
                    printf("You switched to %s ! \n", player_supemon->name);
                    fight(player_supemon, player);
                }
            } else {
                printf("You chose to go to the Supemon Center. Your Supemon will be healed there.\n");
                SupemonCenter(player);
                return 1;
            }
        }
    } else {
        printf("You defeated the wild %s!\n", wild_supemon.name);
        printf("Before battle: %s is level %d with %d XP\n",player_supemon->name, player_supemon->level, player_supemon->experience);
        int recompense_supecoins = 100 + rand() % 401;
        player->Supecoins += recompense_supecoins;
        printf("You won %d Supecoins! You have now %d Supecoins.\n", recompense_supecoins, player->Supecoins);

        int exp_gain = (100 + rand()% 401) * wild_supemon.level;
        player_supemon->experience += exp_gain;
        printf("%s gained %d experience points!\n", player_supemon->name, exp_gain);
        while(1) {
            int next_level = 500 + (player_supemon->level - 1) * 1000;
            if (player_supemon->experience >= next_level) {
                player_supemon->experience -= next_level;
                player_supemon->level += 1;
                printf("%s leveled up to level %d!\n", player_supemon->name, player_supemon->level);

                float temporaire;
                temporaire = player_supemon->HP * 1.3f;
                player_supemon->HP = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);
                
                temporaire = player_supemon->Max_HP * 1.3f;
                player_supemon->Max_HP = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->attack * 1.3f;
                player_supemon->attack = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);
                
                temporaire = player_supemon->defense * 1.3f;
                player_supemon->defense = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->evasion * 1.3f;
                player_supemon->evasion = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->accuracy * 1.3f;
                player_supemon->accuracy = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->speed * 1.3f;
                player_supemon->speed = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->base_attack * 1.3f;
                player_supemon->base_attack = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->base_defense * 1.3f;
                player_supemon->base_defense = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->base_accuracy * 1.3f;
                player_supemon->base_accuracy = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                temporaire = player_supemon->base_evasion * 1.3f;
                player_supemon->base_evasion = (rand()%2) ? (int)(temporaire + 0.5f) : (int)(temporaire);

                printf("After battle: %s is level %d with %d XP\n",player_supemon->name, player_supemon->level, player_supemon->experience);
            } else {
                break;
            }
        }
        game_loop(player);
    }
}