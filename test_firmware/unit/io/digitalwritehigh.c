#include "io.h"

#define PIN 0

int main()
{
    while (1)
    {
        digital_write((dpin_t)PIN, 1);
    }
}