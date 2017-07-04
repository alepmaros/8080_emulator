#include <stdio.h>
#include <stdlib.h>

#include "emulator.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: ./main <rom>\n");
        exit(3);
    }

    State8080* state = initializeState8080();
    loadRomToMemory(argv[1], state);

    while(1)
    {
        emulate8080(state);
    }

    return 0;
}
