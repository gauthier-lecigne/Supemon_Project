#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_SUPEMON 6
#define MAX_MOVES 4
#define POTION_HEAL 5
#define SUPER_POTION_HEAL 10
#define SUPER_BONBON 1


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


struct INVENTAIRE {
    int nb_potions;
    int nb_super_potions;
    int nb_super_bonbons;
};

struct JOUEUR {
    char name_player[30];
    int Supecoins;
    struct SUPEMON supemons[MAX_SUPEMON];
    int nb_supemons;
    int nb_items;
    struct INVENTAIRE inventaire;
};




#endif