#ifndef _UTIL
#define _UTIL
#include "types.h"

// from geeksforgeeks cause I couldnt be bothered to do this from scratch
void handSort(struct Hand* h) {
    for (int i = 0; i < h->played - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < h->played; j++) {
            if (h->cards[j].value < h->cards[min_idx].value) {
                min_idx = j;
            }
        }
        struct Card temp = h->cards[i];
        h->cards[i] = h->cards[min_idx];
        h->cards[min_idx] = temp;
    }
}

bool checkStraight(struct Hand* h) {
    for (int i = 1; i < h->played; ++i) {
        if (h->cards[i].value != h->cards[i-1].value + 1) {
            return false;
        }
    }
    return true;
}

int countFrequency(struct Hand* h, int target) {
    int count = 0;
    for (int i = 0; i < h->played; ++i) {
        if (h->cards[i].value == target)
            ++count;
    }
    return count;
}

// TODO: Take in jokers and check for four feeners and shortcut
int hand_decoder(struct Hand* h) {
    bool isFlush = false;
    bool isStraight = false;
    bool isFullHouse = false;
    int numSame = 0;

    // Sort cards by rank
    handSort(h);

    // Flush
    if(h->cards[0].suit == h->cards[1].suit && 
        h->cards[0].suit == h->cards[2].suit &&
        h->cards[0].suit == h->cards[3].suit &&
        h->cards[0].suit == h->cards[4].suit)
        isFlush = true;

    // Straight
    isStraight = checkStraight(h);

    // Pair, ThreeOAK, FourOAK, FiveOAK, Full House
    

    // Check flags
    if (isFlush) {
        if(isStraight)
            return STRAIGHTFLUSH;
        if(isFullHouse)
            return FLUSHHOUSE;
        if(numSame == 5)
            return FLUSHFIVE;
        return FLUSH;
    }

    if (isStraight)
        return STRAIGHT;

    return HIGHCARD;
}
#endif