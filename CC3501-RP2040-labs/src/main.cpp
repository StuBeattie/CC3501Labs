#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include <iostream>

#include "WS2812.pio.h" // This header file gets produced during compilation from the WS2812.pio file
#include "drivers/logging/logging.h"
#include "drivers/leds.h" 

#define LED_PIN 14

int main() {
    stdio_init_all(); // Initialize standard I/O
    init_leds(LED_PIN, 800000); // Initialize the LEDs

    while (true) {
        // User interaction to set LED colors
        uint32_t led_index;
        uint8_t red, green, blue;

        printf("Enter LED index (0 to %d): ", NUM_LEDS - 1);
        scanf("%u", &led_index); // Read the LED index from user input

        if (led_index >= NUM_LEDS) {
            printf("Invalid LED index. Please try again.\n");
            continue; // Skip to the next iteration if the index is invalid
        }

        printf("Enter color values (0-255) for Red, Green, Blue:\n");

        printf("Red: ");
        scanf("%hhu", &red);
        printf("You entered Red: %hhu\n", red); // Display the entered value

        printf("Green: ");
        scanf("%hhu", &green);
        printf("You entered Green: %hhu\n", green); // Display the entered value

        printf("Blue: ");
        scanf("%hhu", &blue);
        printf("You entered Blue: %hhu\n", blue); // Display the entered value

        // Set the specified LED color
        set_led(led_index, red, green, blue);
        update_leds(); // Commit changes to the LEDs

        // Optionally, to turn off all LEDs, you can include a check
        char command;
        printf("Do you want to turn off all LEDs? (y/n): ");
        scanf(" %c", &command);
        if (command == 'y' || command == 'Y') {
            turn_off_leds(); // Turn off all LEDs
            update_leds(); // Commit the changes
        }

        printf("\n"); // Add a new line for better readability
    }

    return 0;
}