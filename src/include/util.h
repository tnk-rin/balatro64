#ifndef _UTIL
#define _UTIL
#include "types.h"


/* Hand Utility */

// from geeksforgeeks cause I couldnt be bothered to do this from scratch
void hand_sort(struct Hand* h) {
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

void held_sort(struct Held* h) {
    for (int i = 0; i < h->handsize - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < h->handsize; j++) {
            if (h->cards[j].value > h->cards[min_idx].value) {
                min_idx = j;
            }
        }
        struct Card temp = h->cards[i];
        h->cards[i] = h->cards[min_idx];
        h->cards[min_idx] = temp;
    }
}

bool check_straight(struct Hand* h) {
    for (int i = 1; i < h->played; ++i) {
        if (h->cards[i].value != h->cards[i-1].value + 1) {
            return false;
        }
    }
    return true;
}

int* count_frequency(struct Hand* h) {
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
    hand_sort(h);

    // Flush
    if(h->cards[0].suit == h->cards[1].suit && 
        h->cards[0].suit == h->cards[2].suit &&
        h->cards[0].suit == h->cards[3].suit &&
        h->cards[0].suit == h->cards[4].suit)
        isFlush = true;

    // Straight
    isStraight = check_straight(h);

    // Pair, ThreeOAK, FourOAK, FiveOAK, Full House, still check for pairs in case of feeners
    int *count = count_frequency(h);
    for(int i = 0; i < 13; ++i) {
        switch(count[i]) {
            case 2:
                OAK = PAIR;
                OAK2 = 0;

                for(int j = i + 1; j < 13; ++j) {
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

/* Deck Utility */

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void shuffle_deck(struct Deck *deck) {
    struct Card temp;
    for (int i = deck->size - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void initialize_deck(struct Deck *deck) {
    deck->cards = calloc(52, sizeof(struct Card));
    deck->size = 52;
    deck->drawn = 0;
    for(int i = CLUBS; i <= DIAMONDS; ++i) {
        for(int j = A; j <= K; ++j) {
            struct Card c;
            c.suit = i;
            c.value = j;
            deck->cards[(((i - 1) * 13) + j) - 1] = c;
        }
    }

    shuffle_deck(deck);
}

struct Card draw_card(struct Deck *deck) {
    return deck->cards[deck->drawn++];
}


/* General Purpose Utility */

void initialize(struct Deck *deck, struct Held *held, struct Score *score, struct Joker *jokers) {
    // Deck
    initialize_deck(deck);

    // Held
    held->handsize = 8;
    for(int i = 0; i < held->handsize; ++i)
        held->cards[i] = draw_card(deck);

    held_sort(held);

    // Score
    score->chips = 0;
    score->mult = 0;
    score->hands = 4;
    score->discards = 3;

    // Jokers
    jokers = calloc(16, sizeof(struct Joker));
}

#endif