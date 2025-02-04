#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN_B 11
#define LED_PIN_R 12
#define LED_PIN_G 13
#define BUTTON_PIN 5

bool leds_active = false; // Global variable to store the state of the LEDs

// Callback to turn off the green LED
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_G, 0);
    leds_active = false; // to allow the button to be pressed again
    return 0;
}

// Callback to turn off the red LED
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_R, 0);
    add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
    return 0;
}

// Callback to turn off the blue LED
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_B, 0);
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);
    return 0;
}

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

         if (gpio_get(BUTTON_PIN) == 0 && !leds_active) {
            sleep_ms(50); // Debounce
            if (gpio_get(BUTTON_PIN) == 0) {
                leds_active = true;
                gpio_put(LED_PIN_B, 1);
                gpio_put(LED_PIN_R, 1);
                gpio_put(LED_PIN_G, 1);

                add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);

            }
        }

        // Set a pause of 10 ms to reduce CPU usage.
        // This avoids a fast execution of the loop and unnecessary resource consumption.
        sleep_ms(10);
    }
}
