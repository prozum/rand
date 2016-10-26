#include "io.h"

#define PIN 0

int main()
{
    while (1)
    {
        set_pin_mode((dpin_t)PIN, 1);
    }
}