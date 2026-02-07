#ifndef COMBAT_H
#define COMBAT_H

#include "types.h"

int fight(struct SUPEMON *player_supemon, struct JOUEUR *player);
struct SUPEMON generate_wild(struct SUPEMON *player_supemon);
int calculate_damage(struct SUPEMON *attacker, struct SUPEMON *target, struct MOVE *move);
int player_turn(struct SUPEMON *player_supemon);
void player_move(struct SUPEMON *attacker, struct SUPEMON *target);
int change_supemon(struct SUPEMON *player_supemons, int nb_supemons, struct JOUEUR *player);
void use_item(struct JOUEUR *player, int *items_used);
int run_away(struct JOUEUR *player, struct SUPEMON *wild_supemon);
int capture(struct SUPEMON *enemy, struct JOUEUR *player);

#endif