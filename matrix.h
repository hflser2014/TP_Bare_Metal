#ifndef MATRIX_H
#define MATRIX_H

#include "typedef.h"

typedef int bool;
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

void matrix_init();

void RST(bool x);
void SB(bool x);
void LAT(bool x);
void SCK(bool x);
void SDA(bool x);
void ROW0(bool x);
void ROW1(bool x);
void ROW2(bool x);
void ROW3(bool x);
void ROW4(bool x);
void ROW5(bool x);
void ROW6(bool x);
void ROW7(bool x);

void pulse_LAT();
void pulse_SCK();
void desactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val);
void mat_set_row(int row, const rgb_color* val);
void init_bank0();

void test_pixels();
#endif