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
    HIGHCARD = 0b00000001,
    PAIR = 0b00000011,
    TWOPAIR = 0b00001011,
    THREEOAK = 0b00000111,
    STRAIGHT = 0b00010001,
    FLUSH = 0b00100001,
    FULLHOUSE = 0b01000111,
    FOUROAK = 0b10000111,
    STRAIGHTFLUSH = STRAIGHT | FLUSH,
    FIVEOAK = 0b10010111,
    FLUSHHOUSE = FULLHOUSE | FLUSH,
    FLUSHFIVE = FIVEOAK | FLUSH
};

struct Score {
    long long chips;
    long long mult;
};

struct Hand {
    struct Card cards[5];
    int played;
};

#endif