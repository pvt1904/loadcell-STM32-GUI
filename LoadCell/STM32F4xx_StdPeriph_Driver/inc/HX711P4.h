#ifndef APPLICATION_CORE_HX711_H_
#define APPLICATION_CORE_HX711_H_

#include "stm32f4xx.h"
#include "system_timetick.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    GPIO_TypeDef *clk_gpio;
    GPIO_TypeDef *data_gpio;
    uint16_t clk_pin;
    uint16_t data_pin;
} hx711_t;

void hx711_init(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *data_gpio, uint16_t data_pin);
void delay_us(uint16_t period);
void IntToStr6(int32_t u, uint8_t *y);
int32_t Str6ToInt(const uint8_t *y);
int32_t update(hx711_t *hx711, int32_t A0, int32_t A1, int32_t M0, int32_t M1);
int32_t read_average(hx711_t *hx711, int32_t A0, int32_t A1, int32_t M0, int32_t M1, int sample_time);

#endif /* APPLICATION_CORE_HX711_H_ */