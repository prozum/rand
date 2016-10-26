#include "io.h"

#include <assert.h>

#define PIN 0

int main()
{
        assert(digital_read((dpin_t)PIN) == LOW);
}