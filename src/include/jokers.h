#ifndef _JIMBO
#define _JIMBO
#include "util.h"
#include "types.h"

// 1: +4 Mult
void jok_joker(struct Score* score) {
    score->mult += 4;
}

// 118: Played cards with Spade suit icon Spade suit give +50 Chips when scored
void jok_greedy_joker(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == DIAMONDS)
            score->mult += 3;
    }
}

// 119: Played cards with Club suit icon Club suit give +7 Mult when scored 
void jok_lusty_joker(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == HEARTS)
            score->mult += 3;
    }
}

// 119: Played cards with Club suit icon Club suit give +7 Mult when scored 
void jok_wrathful_joker(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == SPADES)
            score->mult += 3;
    }
}

// 119: Played cards with Club suit icon Club suit give +7 Mult when scored 
void jok_gluttonous_joker(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == CLUBS)
            score->mult += 3;
    }
}

// 6: +8 Mult if played hand contains a Pair
void jok_jolly_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & PAIR) {
        score->mult += 8;
    }
}

// 7: +12 Mult if played hand contains a Three of a Kind
void jok_zany_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & THREEOAK) {
        score->mult += 12;
    }
}

// 8: +10 Mult if played hand contains a Two Pair
void jok_mad_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & TWOPAIR) {
        score->mult += 10;
    }
}

// 9: +12 Mult if played hand contains a Straight
void jok_crazy_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & STRAIGHT) {
        score->mult += 12;
    }
}

// 10: +10 Mult if played hand contains a Flush
void jok_droll_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & FLUSH) {
        score->mult += 10;
    }
}

// 11: +50 Chips if played hand contains a Pair
void jok_sly_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & PAIR) {
        score->chips += 50;
    }
}

// 12: +100 Chips if played hand contains a Three of a Kind
void jok_wily_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & THREEOAK) {
        score->chips += 100;
    }
}

// 13: +80 Chips if played hand contains a Two Pair
void jok_clever_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & TWOPAIR) {
        score->chips += 80;
    }
}

// 14: +100 Chips if played hand contains a Straight
void jok_devious_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & STRAIGHT) {
        score->chips += 100;
    }
}

// 15: +80 Chips if played hand contains a Flush
void jok_crafty_joker(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & FLUSH) {
        score->chips += 80;
    }
}

// 16: +20 Mult if played hand contains 3 or fewer cards
void jok_half_joker(struct Score* score, struct Hand* hand) {
    if(hand->played <= 3)
        score->mult += 20;
}

// 27: +0-23 Random Mult
void jok_misprint(struct Score* score) {
    score->mult += rand() % 24;
}

// 31: Each played Ace, 2, 3, 5, or 8 gives +8 Mult when scored 
void jok_fibonacci(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value == 1 ||
            hand->cards[i].value == 2 ||
            hand->cards[i].value == 3 ||
            hand->cards[i].value == 5 ||
            hand->cards[i].value == 8)
            score->mult += 8;
    }
}

// 33: Played face cards give +30 Chips when scored
// TODO: Take in joker field to check for pareidolia
void jok_scary_face(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value > 10)
            score->chips += 30;
    }
}

// 39: Played cards with even rank give +4 Mult when scored 
void jok_even_steven(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value % 2 == 0)
            score->mult += 4;
    }
}

// 40: Played cards with odd rank give +31 Chips when scored 
void jok_odd_todd(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value % 2 != 0)
            score->chips += 31;
    }
}

// 41: Played Aces give +20 Chips and +4 Mult when scored 
void jok_scholar(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value == A) {
            score->chips += 20;
            score->mult += 4;
        }
    }
}

// 101: Each played 10 or 4 gives +10 Chips and +4 Mult when scored 
void jok_walkie_talkie(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value == 4 || hand->cards[i].value == 10) {
            score->chips += 10;
            score->mult += 4;
        }
    }
}

// 104: Played face cards give +5 Mult when scored
// TODO: Take in joker field to check for pareidolia
void jok_smiley_face(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value > 10)
            score->mult += 5;
    }
}

// 118: Played cards with Spade suit icon Spade suit give +50 Chips when scored
void jok_arrowhead(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == SPADES)
            score->chips += 50;
    }
}

// 119: Played cards with Club suit icon Club suit give +7 Mult when scored 
void jok_onyx_agate(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == CLUBS)
            score->mult += 7;
    }
}

// 122: X3 Mult if poker hand contains a Diamond card, Club card, Heart card, and Spade card
void jok_flower_pot(struct Score* score, struct Hand* hand) {
    bool d = false, c = false, h = false, s = false;
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == DIAMONDS)
            d = true;
        if (hand->cards[i].suit == CLUBS)
            c = true;
        if (hand->cards[i].suit == HEARTS)
            h = true;
        if (hand->cards[i].suit == SPADES)
            s = true;
    }
    score->mult *= ((d && c) && (h && s)) ? 3 : 1;
}

// 128: X2 Mult if played hand has a scoring Club card and a scoring card of any other suit 
void jok_seeing_double(struct Score* score, struct Hand* hand) {
    bool c = false, other = false;
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].suit == CLUBS)
            c = true;
        else
            other = true;
    }
    score->mult *= (c && other) ? 2 : 1;
}

// 131: X2 Mult if played hand contains a Pair
void jok_the_duo(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & PAIR) {
        score->mult *= 2;
    }
}

// 132: X3 Mult if played hand contains a Three of a Kind
void jok_the_trio(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & THREEOAK) {
        score->mult *= 3;
    }
}

// 133: X4 Mult if played hand contains a Four of a Kind
void jok_the_family(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & FOUROAK) {
        score->mult *= 4;
    }
}

// 134: X3 Mult if played hand contains a Straight
void jok_the_order(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & STRAIGHT) {
        score->mult *= 2;
    }
}

// 135: X2 Mult if played hand contains a Flush
void jok_the_tribe(struct Score* score, struct Hand* hand) {
    int handtype = hand_decoder(hand);
    if(handtype & FLUSH) {
        score->mult *= 2;
    }
}

// 147: Played Kings and Queens each give X2 Mult when scored
void jok_triboulet(struct Score* score, struct Hand* hand) {
    for(int i = 0; i < hand->played; ++i) {
        if (hand->cards[i].value > J)
            score->mult *= 2;
    }
}

#endif