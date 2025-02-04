#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN_B 11
#define LED_PIN_R 12
#define LED_PIN_G 13
#define BUTTON_PIN 5

int main()
{
    stdio_init_all();

    // Initialize the LEDs pins
    gpio_init(LED_PIN_B);
    gpio_set_dir(LED_PIN_B, GPIO_OUT);
    gpio_init(LED_PIN_R);
    gpio_set_dir(LED_PIN_R, GPIO_OUT);
    gpio_init(LED_PIN_G);
    gpio_set_dir(LED_PIN_G, GPIO_OUT);

    // Initialize the push button
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);


    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
