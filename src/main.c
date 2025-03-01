#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include "include/types.h"
#include "include/jokers.h"
#include "include/util.h"

void displayHeld(struct Held held, char *buf) {
    sprintf(buf, "Drawn cards:\n");
    for (int i = 0; i < held.handsize; ++i) {
        if(held.cards[i].value == J)
            sprintf(buf + strlen(buf), "J  ");
        else if(held.cards[i].value == Q)
            sprintf(buf + strlen(buf), "Q  ");
        else if(held.cards[i].value == K)
            sprintf(buf + strlen(buf), "K  ");
        else
            sprintf(buf + strlen(buf), "%2d ", held.cards[i].value);
    }
}

int main(void)
{
    console_init();
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    controller_init();
    debug_init_usblog();
    console_set_debug(true);
    
    srand(1010);

    struct Score score;
    struct Hand hand;
    struct Held held;
    struct Deck deck;
    struct Joker jokers;
    initialize(&deck, &held, &score, &jokers);
    
    sprite_t* jimbo = sprite_load("rom:/jimbo.sprite");
    
    while(1) {
        char* buf = calloc(256, sizeof(char));
        static display_context_t disp = 0;
        disp = display_get();
        graphics_fill_screen(disp, graphics_make_color(100, 100, 100, 255));
        displayHeld(held, buf);
        graphics_draw_text(disp, 20, 20, buf);
        graphics_draw_sprite_trans(disp, 20, 50, jimbo);
        display_show(disp);
    }
}
