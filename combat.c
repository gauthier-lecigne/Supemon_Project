#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "menu.h"

struct SUPEMON generate_wild() {
    struct SUPEMON wild;
    int choice = rand() % 3;

    switch (choice) {
        case 0:
            strcpy(wild.name, "Supmander");
            wild.level = 1;
            wild.HP = 10;
            wild.attack = 1;
            
    }
}