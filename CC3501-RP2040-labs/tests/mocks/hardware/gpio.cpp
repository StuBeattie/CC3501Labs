#include <iostream>

void gpio_init(unsigned int gpio)
{
    std::cout << "Debug: initialised GPIO pin " << gpio << std::endl;
}

void gpio_set_dir(unsigned int gpio, bool out)
{
    // TODO: Could use the test harness here to check correct use of the API, e.g. that `gpio_init()` was previously called.
    std::cout << "Debug: GPIO pin " << gpio << " set to " << (out ? "output" : "input") << std::endl;
}

void gpio_put(unsigned int gpio, bool val)
{
    std::cout << "Debug: GPIO pin " << gpio << " set to " << val << std::endl;
}
