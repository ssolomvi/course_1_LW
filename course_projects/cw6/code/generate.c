#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "io.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w+");

    if (argc != 3) {
        fprintf(stdin, "Usage:\n\t./generate FILE_FROM FILE_TO\n");
        exit(1);
    }

    if (!in) {
        perror("Error");
        exit(2);
    }

    if (!out) {
        perror("Error");
        exit(2);
    }

    Computer computer;

    while (computer_read_txt(&computer, in)) {
        computer_write_bin(&computer, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}