#include <stdio.h>
#include <libdragon.h>
#include "include/types.h"
#include "include/jokers.h"
#include "include/util.h"

int main(void)
{
    console_init();
    debug_init_usblog();
    console_set_debug(true);
    srand(1020);

    struct Score score;
    struct Hand hand;
    struct Held held;
    struct Deck deck;
    initialize_deck(&deck);
    
    for (int i = 0; i < deck.size; ++i) {
        if(deck.cards[i].value == J)
            printf("J");
        else if(deck.cards[i].value == Q)
            printf("Q");
        else if(deck.cards[i].value == K)
            printf("K");
        else
            printf("%d", deck.cards[i].value);

        if((i+1) % 13 == 0)
            printf("\n");
        else
            printf("\t");
    }
    printf("\n\n");

    hand.cards[0] = draw_card(&deck);
    hand.cards[1] = draw_card(&deck);
    hand.cards[2] = draw_card(&deck);
    hand.cards[3] = draw_card(&deck);
    hand.cards[4] = draw_card(&deck);
    hand.played = 5;

    score.chips = 0;
    score.mult = 0;

    

    
    printf("Hand: %d, %d, %d, %d, %d\n", hand.cards[0].value, hand.cards[1].value, hand.cards[2].value, hand.cards[3].value, hand.cards[4].value);
    
    printf("Suits: %d, %d, %d, %d, %d\nDetermined hand type: %d\n\n", hand.cards[0].suit, hand.cards[1].suit, hand.cards[2].suit, hand.cards[3].suit, hand.cards[4].suit, hand_decoder(&hand));

    
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    jok_misprint(&score);
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    jok_misprint(&score);
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    while(1) {}
}
