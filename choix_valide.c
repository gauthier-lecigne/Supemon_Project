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

int valid_choix_int(int min, int max) {
    int number;
    while (1) {
        if (scanf("%d", &number) == 1) {
            while (getchar() != '\n');
            if (number >= min && number <= max) {
                return number;
            } else {
                printf("Please enter a number between %d and %d : ", min, max);
            }
        } else {
            printf("Invalid input, please enter a number between %d and %d : ", min, max);
            while (getchar() != '\n');
        }
    }
}