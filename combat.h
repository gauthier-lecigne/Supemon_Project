#ifndef COMBAT_H
#define COMBAT_H

#include "types.h"

void fight(struct SUPEMON *player_supemon, struct JOUEUR *player);
struct SUPEMON generate_wild(struct SUPEMON *player_supemon);
int calculate_damage(struct SUPEMON *attacker, struct SUPEMON *target, struct MOVE *move);
int player_turn(struct SUPEMON *player_supemon);
void player_move(struct SUPEMON *attacker, struct SUPEMON *target);
int change_supemon(struct SUPEMON *player_supemons, int nb_supemons);
void use_item();
void run_away();
void capture();

#endif