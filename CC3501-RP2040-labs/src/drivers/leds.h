#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <cstdint> // For uint32_t and other types

using uint = unsigned int; // Define uint if not defined

// Define the number of LEDs in the chain
#define NUM_LEDS 12

// Function to initialize the LED driver
void init_leds(uint32_t pin, uint32_t freq);

// Function to set a single LED to a specific color
void set_led(uint32_t led_index, uint8_t red, uint8_t green, uint8_t blue);

// Function to commit all the changes to the LEDs (send to the device)
void update_leds();

// Function to turn off all LEDs
void turn_off_leds();

#endif // LEDS_H
