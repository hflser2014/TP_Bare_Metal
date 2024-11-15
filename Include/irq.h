#ifndef IRQ_H
#define IRQ_H

#include "stm32l475xx.h"

#define MAKE_DEFAULT_HANDLER(name)\
    void __attribute__((weak)) name(void) {\
        __disable_irq();\
        while(1); \
    }

void irq_init(void);


#endif