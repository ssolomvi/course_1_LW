#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "io.h"

int main(int argc, char *argv[])
{
    FILE *in = fopen(argv[1], "r");

    if (argc != 2) {
        perror("Error");
        exit(1);
    }
    if (!in) {
        perror("Error");
        exit(2);
    }

    Computer computer;

    while (computer_read_bin(&computer, in)) {
        computer_print(&computer);
    }

    fclose(in);
    return 0;
}