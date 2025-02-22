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

int* countFrequency(struct Hand* h) {
    int *count = calloc(13, sizeof(int));

    for (int i = 0; i < h->played; ++i) {
        ++count[h->cards[i].value - 1];
    }

    return count;
}

// TODO: Take in jokers and check for four feeners and shortcut
unsigned char hand_decoder(struct Hand* h) {
    bool isFlush = false;
    bool isStraight = false;
    bool isFullHouse = false;
    unsigned char OAK = 0, OAK2 = 0;

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

    // Pair, ThreeOAK, FourOAK, FiveOAK, Full House, still check for pairs in case of feeners
    int *count = countFrequency(h);
    for(int i = 0; i < 13; ++i) {
        //printf("%d : %d\n", i+1, count[i]);
        switch(count[i]) {
            case 2:
                OAK = PAIR;
                OAK2 = 0;

                for(int j = i + 1; j < 13; ++j) {
                    //printf("%d : %d\n", j+1, count[j]);
                    OAK2 = (count[j] == 2) ? PAIR : 
                           (count[j] == 3) ? THREEOAK : OAK2;
                    if(OAK2)
                        break;
                }

                OAK = (OAK2 == PAIR) ? TWOPAIR : 
                      (OAK2 == THREEOAK) ? FULLHOUSE : OAK;

                break;

            case 3:
                OAK = THREEOAK;
                OAK2 = 0;

                for(int j = i + 1; j < 13; ++j) {
                    OAK2 = (count[j] == 2) ? PAIR : OAK2;
                    if(OAK2)
                        break;
                }

                OAK = (OAK2 == PAIR) ? FULLHOUSE : OAK;
                break;

            case 4:
                OAK = FOUROAK;
                break;

            case 5:
                OAK = FIVEOAK;
                break;

            default:
                OAK = HIGHCARD;
                continue;
        }
        break;
    }
    free(count);

    printf("%d\n", OAK);

    // Check flags
    if (isFlush) {
        if(isStraight)
            return STRAIGHTFLUSH;
        if(OAK == FULLHOUSE)
            return FLUSHHOUSE;
        if(OAK == FIVEOAK)
            return FLUSHFIVE;
        return FLUSH;
    }

    if (isStraight)
        return STRAIGHT;

    return OAK;
}
#endif