#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_SUPEMON 6
#define MAX_ITEMS 10

struct SUPEMON {
    char name[30];
    int level;
    int experience;
    int HP;
    int Max_HP;
    int attack;
    int base_attack;
    int defense;
    int base_defense;
    int accuracy;
    int base_accuracy;
    int speed;
};

struct JOUEUR {
    char name_player[30];
    int Supecoins;
    SUPEMON supemons[MAX_SUPEMON];
    int nb_supemons;
    char items[MAX_ITEMS][30];
    int nb_items;
};

#endif