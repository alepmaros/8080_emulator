#include <stdio.h>
#include <stdlib.h>

#include "disassemble.h"

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
        printf("Error: Could not open %s\n", argv[1]);
        exit(1);
    }

    // Get the file size and read it into a memory buffer
    fseek(f, 0L, SEEK_END);
    long int fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    unsigned char *buffer = malloc(fsize);

    fread(buffer, fsize, 1, f);
    fclose(f);

    int pc = 0;

    while(pc < fsize)
    {
        pc += disassemble8080(buffer, pc);
    }

    return 0;
}
