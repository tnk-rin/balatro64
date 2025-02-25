#include <stdio.h>
#include <libdragon.h>
#include "include/types.h"
#include "include/jokers.h"
#include "include/util.h"

void displayHeld(struct Held held) {
    printf("Drawn cards:\n");
    for (int i = 0; i < held.handsize; ++i) {
        if(held.cards[i].value == J)
            printf("J  ");
        else if(held.cards[i].value == Q)
            printf("Q  ");
        else if(held.cards[i].value == K)
            printf("K  ");
        else
            printf("%2d ", held.cards[i].value);
    }
    printf("\n\n");
}

int main(void)
{
    console_init();
    debug_init_usblog();
    console_set_debug(true);
    srand(1010);

    struct Score score;
    struct Hand hand;
    struct Held held;
    struct Deck deck;
    struct Joker jokers;
    initialize(&deck, &held, &score, &jokers);
    
    displayHeld(held);
    
    while(1) {}
}
