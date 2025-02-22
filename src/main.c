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

    struct Score score;
    struct Hand hand;
    
    struct Card c1;
    c1.suit = SPADES;
    c1.value = K;
    struct Card c2;
    c2.suit = SPADES;
    c2.value = Q;
    struct Card c3;
    c3.suit = SPADES;
    c3.value = Q;
    struct Card c4;
    c4.suit = SPADES;
    c4.value = 9;
    struct Card c5;
    c5.suit = DIAMOND;
    c5.value = 9;

    hand.cards[0] = c1;
    hand.cards[1] = c2;
    hand.cards[2] = c3;
    hand.cards[3] = c4;
    hand.cards[4] = c5;
    hand.played = 5;

    score.chips = 50;
    score.mult = 2;

    printf("Hand: %d, %d, %d, %d, %d\nDetermined hand type: %d\n\n", c1.value, c2.value, c3.value, c4.value, c5.value, hand_decoder(&hand));

    /*
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    jok_droll_joker(&score, &hand);
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    jok_crazy_joker(&score, &hand);
    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);
    */

    while(1) {}
}
