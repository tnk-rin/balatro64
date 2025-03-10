#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include <time.h>
#include "include/types.h"
#include "include/jokers.h"
#include "include/util.h"

// void displayHeld(struct Held held, char *buf) {
//     sprintf(buf, "Drawn cards:\n");
//     for (int i = 0; i < held.handsize; ++i) {
//         graphics_draw_text(disp, 20, 20, buf);
//     //     if(held.cards[i].value == J)
//     //         sprintf(buf + strlen(buf), "J  ");
//     //     else if(held.cards[i].value == Q)
//     //         sprintf(buf + strlen(buf), "Q  ");
//     //     else if(held.cards[i].value == K)
//     //         sprintf(buf + strlen(buf), "K  ");
//     //     else if (held.cards[i].value == A)
//     //         sprintf(buf + strlen(buf), "A  ");
//     //     else
//     //         sprintf(buf + strlen(buf), card_file_from_card(&held.cards[i]));
//             //sprintf(buf + strlen(buf), "%2d ", held.cards[i].value + 1);
//     }
// }

int main(void)
{
    char* buf = calloc(256, sizeof(char));
    char* fbuf = calloc(22, sizeof(char));
    console_init();
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    controller_init();
    timer_init();
    long long          start = timer_ticks();
    debug_init_usblog();
    console_set_debug(true);

    struct Score score;
    struct Hand hand;
    struct Held held;
    struct Deck deck;
    struct Joker jokers;
    srand(100);
    initialize(&deck, &held, &score, &jokers);
    
    sprite_t* jimbo = sprite_load("rom:/jokers/160.sprite");
    sprite_t* card_front = sprite_load("rom:/enhancements/34.sprite");
    
    while(1) {
        static display_context_t disp = 0;
        disp = display_get();
        graphics_fill_screen(disp, graphics_make_color(53, 101, 77, 255));
        // graphics_draw_box(disp, 100, 200, 100, 200, graphics_make_color(43, 91, 67, 255));
        // displayHeld(held, buf);
        // graphics_draw_text(disp, 20, 20, buf);
        // graphics_draw_sprite_trans(disp, 20, 40, jimbo);
        for (int i = 0; i < held.handsize; ++i) {
            card_file_from_card(fbuf, &held.cards[i]);
            sprite_t* cardSpr = sprite_load(fbuf);
            graphics_draw_box(disp, 165+(58*i), 305, 56, 75, graphics_make_color(43, 91, 67, 255));
            graphics_draw_sprite_trans (disp, 160 + (58 * i), 300, card_front);
            graphics_draw_sprite_trans (disp, 160 + (58 * i), 300, cardSpr);
            free(cardSpr);
        }
        
        display_show(disp);
    }
}
