#include <stdio.h>
#include <libdragon.h>
#include "include/types.h"
#include "include/jokers.h"

int hand_decoder(struct Hand h);

int main(void)
{
    console_init();

    debug_init_usblog();
    console_set_debug(true);

    printf("Balatro 64!\n");

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
    c3.value = J;
    struct Card c4;
    c4.suit = SPADES;
    c4.value = 10;
    struct Card c5;
    c5.suit = DIAMOND;
    c5.value = 9;

    hand.cards[0] = c1;
    hand.cards[1] = c2;
    hand.cards[2] = c3;
    hand.cards[3] = c4;
    hand.cards[4] = c5;

    score.chips = 50;
    score.mult = 2;

    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);

    jok_joker(&score);

    printf("Chips: %lld | Mult: %lld   |   Total: %lld\n", score.chips, score.mult, score.chips * score.mult);

    int handtype = hand_decoder(hand);
    
    printf("%d\n", handtype);

    while(1) {}
}
// TODO: Take in jokers and check for four feeners and shortcut
int hand_decoder(struct Hand h) {
    bool isFlush = false;
    bool isStraight = false;
    int numSame = 0;

    if(h.cards[0].suit == h.cards[1].suit && 
        h.cards[0].suit == h.cards[2].suit &&
        h.cards[0].suit == h.cards[3].suit &&
        h.cards[0].suit == h.cards[4].suit)
        isFlush = true;


    if (isFlush)
        return FLUSH;

    return HIGHCARD;
}