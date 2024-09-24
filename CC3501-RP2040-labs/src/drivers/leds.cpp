#include "leds.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "WS2812.pio.h" // Include the generated header for the WS2812 program
#include <iostream> // for using cout for debugging

// Define the number of LEDs
#define NUM_LEDS 12 // Adjust this if you have a different number of LEDs

// Store the current state of all LEDs (12 LEDs with RGB values)
static uint32_t led_states[NUM_LEDS] = {0};

// Global variables for PIO and state machine
static PIO pio = pio0; // Use the correct PIO instance
static uint sm = 0; // State machine number

// Initialize the LEDs by setting up the PIO program
void init_leds(uint32_t pin, uint32_t freq) {
    uint offset = pio_add_program(pio, reinterpret_cast<const pio_program_t*>(&ws2812_program));
    ws2812_program_init(pio, sm, offset, pin, freq, false);
}

// Set a single LED's color (index from 0 to NUM_LEDS-1)
void set_led(uint32_t led_index, uint8_t red, uint8_t green, uint8_t blue) {
    if (led_index >= NUM_LEDS) {
        return; // Out of bounds, do nothing
    }
    // Store the color in the led_states array
    led_states[led_index] = (red << 24) | (green << 16) | (blue << 8);
}

// Send the current LED states to the LED chain
void update_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        pio_sm_put_blocking(pio, sm, led_states[i]);
    }
}

// Turn off all LEDs
void turn_off_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        led_states[i] = 0; // Set all to 0 (off)
    }
    update_leds(); // Send the off state to the LEDs
}

