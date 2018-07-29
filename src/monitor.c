#include "monitor.h"
#include "types.h"

#define ROWS 25
#define COLS 80

uint8_t* video = (uint8_t*)0xb8000;

uint8_t x_screen = 0;
uint8_t y_screen = 0;

void k_clrscr() {
    for (int i = 0; i < ROWS * COLS * 2; i++) {
        video[i] = 0x0;
    }
}

void k_putc(uint8_t c, uint8_t attr) {
    video[y_screen * COLS * 2 + x_screen * 2] = c;
    video[y_screen * COLS * 2 + x_screen * 2 + 1] = attr;

    x_screen++;
    if (x_screen > 80) {
        x_screen = 0;
        y_screen++;
    }
}

void k_print(char* str, uint8_t attr) {
    for (int i = 0; str[i] != '\0'; i++) {
        k_putc((uint8_t)str[i], attr);
    }
}

void k_printdec(uint32_t a, uint8_t attr) {
    char buf[12];
    buf[11] = 0x0;

    int i = 11;

    while (1) {
        uint8_t digit = a % 10;
        buf[--i] = digit + 48;
        a /= 10;
        if (a == 0) break;
    }

    k_print(buf + i, attr);
}

void k_printhex(uint32_t a, uint8_t attr) {
    char buf[9] = "00000000\0";

    int i = 8;

    while (a >= 1) {
        uint8_t digit = a % 16;
        buf[--i] = digit < 10 ? digit + 48 : digit + 55;
        a /= 16;
    }

    k_print("0x", attr);
    k_print(buf, attr);
}