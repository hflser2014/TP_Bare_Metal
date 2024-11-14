#ifndef MATRIX_H
#define MATRIX_H

#define RST(x) (x ? (GPIOC->BSRR = GPIO_BSRR_BS3_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR3_Msk))
#define SB(x) (x ? (GPIOC->BSRR = GPIO_BSRR_BS5_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR5_Msk))
#define LAT(x) (x ? (GPIOC->BSRR = GPIO_BSRR_BS4_Msk) : (GPIOC->BSRR = GPIO_BSRR_BR4_Msk))
#define SCK(x) (x ? (GPIOB->BSRR = GPIO_BSRR_BS1_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR1_Msk))
#define SDA(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS4_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR4_Msk))
#define ROW0(x) (x ? (GPIOB->BSRR = GPIO_BSRR_BS2_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR2_Msk))
#define ROW1(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS15_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR15_Msk))
#define ROW2(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS2_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR2_Msk))
#define ROW3(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS7_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR7_Msk))
#define ROW4(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS6_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR6_Msk))
#define ROW5(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS5_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR5_Msk))
#define ROW6(x) (x ? (GPIOB->BSRR = GPIO_BSRR_BS0_Msk) : (GPIOB->BSRR = GPIO_BSRR_BR0_Msk))
#define ROW7(x) (x ? (GPIOA->BSRR = GPIO_BSRR_BS3_Msk) : (GPIOA->BSRR = GPIO_BSRR_BR3_Msk))

#include "typedef.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color;

void matrix_init();

void pulse_LAT();
void pulse_SCK();
void desactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val);
void mat_set_row(int row, const rgb_color* val);
void init_bank0();
void pause(int time);
void display_static_image(const uint8_t* image_start, const int image_size);

void test_pixels();
#endif