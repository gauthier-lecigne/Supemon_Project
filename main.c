#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "menu.h"

void player_info(struct JOUEUR *player) {
    printf("Enter you player name : "); scanf("%29s", player->name_player);
    printf("Welcome in Supemon World %s !\n", player-> name_player);
    player->Supecoins = 500; player-> nb_supemons = 0; player -> nb_items = 0;
}

void starter_choice(struct SUPEMON *supemon) {
    int choix = 0;
    printf("+----------------------------+\n");
    printf("|Choose your starter Supemon:|\n");
    printf("|    1 - Supmander           |\n");
    printf("|    2 - Supasaur            |\n");
    printf("|    3 - Supirtle            |\n");
    printf("+----------------------------+\n");
    while(choix < 1 || choix > 3) {
        printf("Choose you starter by choosing 1, 2 or 3 : ");scanf("%d", &choix);
        if (choix < 1 || choix > 3) {
            printf("Invalid choice, plense enter the value 1, 2 or 3\n");
        }
    switch (choix)
        {
        case 1:
            printf("You chose Supmander as your starter Supemon \n");
            supemon-> level = 1;
            supemon-> HP = 10;
            supemon-> attack = 1;
            supemon-> defense = 1;
            supemon-> evasion = 1;
            supemon-> accuracy = 2;
            supemon-> speed = 1;
            printf("Your Supemon HP are %d, Attack = %d, Defense = %d, Evasion = %d, Accuracy = %d, Speed = %d\n", supemon->HP,supemon->attack,supemon->defense,supemon->evasion,supemon->accuracy,supemon->speed);
            break;
        case 2:
            printf("You choose Supasaur as your starter Supemon \n");
            supemon-> level = 1;
            supemon-> HP = 9;
            supemon-> attack = 1;
            supemon-> defense = 1;
            supemon-> evasion = 3;
            supemon-> accuracy = 2;
            supemon-> speed = 2;
            printf("Your Supemon HP are %d, Attack = %d, Defense = %d, Evasion = %d, Accuracy = %d, Speed = %d\n", supemon->HP,supemon->attack,supemon->defense,supemon->evasion,supemon->accuracy,supemon->speed);
            break;
        case 3:
            printf("You chose Supirtle as your starter Supemon \n");
            supemon-> level = 1;
            supemon-> HP = 11;
            supemon-> attack = 1;
            supemon-> defense = 2;
            supemon-> evasion = 2;
            supemon-> accuracy = 1;
            supemon-> speed = 2;
            printf("Your Supemon HP are %d, Attack = %d, Defense = %d, Evasion = %d, Accuracy = %d, Speed = %d\n", supemon->HP,supemon->attack,supemon->defense,supemon->evasion,supemon->accuracy,supemon->speed);
            break;
        }
    }
}

int main() {
    struct JOUEUR player;
    struct SUPEMON starter;
    player_info(&player);
    starter_choice(&starter);
    game_loop();
    system("pause");
}