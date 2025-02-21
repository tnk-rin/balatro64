#ifndef _TYPES
#define _TYPES

// Fancy names
#define K 13
#define Q 12
#define J 11
#define A 1
#define CLUBS 1
#define SPADES 2
#define HEARTS 3
#define DIAMOND 4

struct Card {
    int value;
    int suit;
};

enum HandTypes {
    HIGHCARD,
    PAIR,
    TWOPAIR,
    THREEOAK,
    STRAIGHT,
    FLUSH,
    FULLHOUSE,
    FOUROAK,
    STRAIGHTFLUSH,
    FIVEOAK,
    FLUSHHOUSE,
    FLUSHFIVE
};

struct Score {
    long long chips;
    long long mult;
};

struct Hand {
    struct Card cards[5];
};

#endif