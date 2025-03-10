#ifndef _TYPES
#define _TYPES

// Fancy names
#define K 12
#define Q 11
#define J 10
#define A 0
#define CLUBS 1
#define SPADES 2
#define HEARTS 3
#define DIAMONDS 4

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

struct Card {
    int value;
    int suit;
};

struct Deck {
    struct Card *cards;
    int size;
    int drawn;
};

struct Score {
    long long chips;
    long long mult;
    uint8_t hands;
    uint8_t discards;
};

struct Hand {
    struct Card cards[5];
    int played;
};

struct Held {
    struct Card cards[16];
    int handsize;
};

struct Joker {
    int type;
    int id;
    int placement;
};

#endif