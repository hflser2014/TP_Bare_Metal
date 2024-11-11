// matrix.c
#include "matrix.h"
#include "stm32l475xx.h"

void matrix_init(){
    // activate clock by setting bit 1 and 2 of AHB2ENR
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

    // Set pc345 pb012 pa2-7 15 to output mode (01)
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1 | GPIO_MODER_MODE15_1);
    GPIOA->MODER |= (GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE15_0);

    GPIOB->MODER &= ~(GPIO_MODER_MODE0_1 | GPIO_MODER_MODE1_1 | GPIO_MODER_MODE2_1);
    GPIOB->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0);

    GPIOC->MODER &= ~(GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1);
    GPIOC->MODER |= (GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0);
 
    // Set pc345 pb012 pa2-7 15 to very high speed (11)
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7 | GPIO_OSPEEDR_OSPEED15);
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED1 | GPIO_OSPEEDR_OSPEED2);
    GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5);

    // Initialization
    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);
    init_bank0();

    // Close all rows
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);

    // Wait 150ms then set RST to 1
    for (int i=0; i<10000000; i++){
        pause(25);
    }
    RST(1);
    SB(1);
}

void pause(int time){
    // Wait time in ns
    const int sys_period = 12.5;
    for (int i=0; i<(int)(time/sys_period); i++){
        asm volatile("nop");
    }
}

void pulse_LAT(){
    // Pulse LAT
    LAT(1);
    // Wait 1 period, 1/40MHz = 25ns
    pause(25);
    LAT(0);
    pause(25);
    LAT(1);
    pause(25);
}

void pulse_SCK(){
    // Pulse SCK
    SCK(0);
    // Wait 1 period, 1/40MHz = 25ns
    pause(25);
    SCK(1);
    pause(25);
    SCK(0);
    pause(25);
}

void desactivate_rows(){
    // Close all rows
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    // Open row
    switch(row){
        case 0:
            ROW0(1);
            break;
        case 1:
            ROW1(1);
            break;
        case 2:
            ROW2(1);
            break;
        case 3:
            ROW3(1);
            break;
        case 4:
            ROW4(1);
            break;
        case 5:
            ROW5(1);
            break;
        case 6:
            ROW6(1);
            break;
        case 7:
            ROW7(1);
            break;
    }
}

void send_byte(uint8_t val){
    // Send byte
    for (int i=7; i>=0; i--){
        SDA((val>>i) & 1);
        pause(25);
        pulse_SCK();
    }

}

void mat_set_row(int row, const rgb_color* val){
    for (int i=7; i>=0; i--){
        send_byte(val[i].b);
        send_byte(val[i].r);
        send_byte(val[i].g);
        
    }
    desactivate_rows();
    pulse_LAT();
    activate_row(row);
}

void init_bank0(){
    SB(0);
    // Initialize bank 0
    for (int i=0; i<24 ; i++){
        for (int j=0; j<6; j++){
            SDA(1);
            pause(25);
            pulse_SCK();
        }
    }
    pulse_LAT();
}

void test_pixels(){
    // Test pixels
    for (int i=0; i<8; i++){
        rgb_color val[8];
        for (unsigned int j=0; j<8; j++){
            val[j].r = 32*j;
            val[j].g = 0;
            val[j].b = 0;
        }
        mat_set_row(i, val);

    }
}

void display_static_image(uint8_t *data_start, uint8_t *data_end, int data_size){
    // Display static image
    for (int i=0; i<data_size; i++){
        mat_set_row(i, (rgb_color*)data_start);
        data_start += 24;
    }
}


