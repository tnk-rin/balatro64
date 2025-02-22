#ifndef _JIMBO
#define _JIMBO
#include "util.h"
#include "types.h"

// +4 Mult
void jok_joker(struct Score* score) {
    score->mult += 4;
}

// +12 Mult if Hand contains a straight
void jok_crazy_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & STRAIGHT) {
        score->mult += 12;
    }
}

// +10 Mult if Hand contains a flush
void jok_droll_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & FLUSH) {
        score->mult += 10;
    }
}


#endif