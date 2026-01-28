#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_SUPEMON 6
#define MAX_ITEMS 10
#define MAX_MOVES 4

struct MOVE {
    char name[30];
    int damage;
    int attack_boost;
    int defense_boost;
    int evasion_boost;
};

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
    int evasion;
    int base_evasion;
    struct MOVE moves[MAX_MOVES];
    int nb_moves;
};

struct JOUEUR {
    char name_player[30];
    int Supecoins;
    struct SUPEMON supemons[MAX_SUPEMON];
    int nb_supemons;
    char items[MAX_ITEMS][30];
    int nb_items;
};

#endif