#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "structure.h"
#include "io.h"
#include "comp.h"

#define REFERENCE_FILE "reference.txt"

int compare(Computer *computer, Reference *reference);

int main(int argc, char *argv[])
{
    FILE* in = fopen(argv[1], "r");
    FILE* ref_txt = fopen(REFERENCE_FILE, "r");

    if (argc != 3) {
        fprintf(stderr, "Usage:\n\t./execute BINARY_FILE_FROM parameter\n");
        exit(1);
    }

    if (!in) {
        perror("Error");
        exit(2);
    }

    if (!ref_txt) {
        perror("Error");
        exit(2);
    }

    int config, bad_config = 0;
    Computer computer;
    Reference reference;
    reference_read_txt(&reference, ref_txt);
    CompList list = *list_create();

    while (computer_read_bin(&computer, in)) {
        config = compare(&computer, &reference);
        if (config) {
            list_add(&list, computer);
            bad_config++;
        }
    }
    if (bad_config <= atoi(argv[2])) {
        fprintf(stderr, "Error: too few computers are badly configured\n");
        exit(4);
    } else {
        printf("There are %d badly configured computers\n\n", bad_config);
        list_print(list);
    }

    list_destroy(&list);
    fclose(in);
    fclose(ref_txt);

    return 0;
}


int compare(Computer *computer, Reference *reference)
{
    for (int i = 0; i < computer->num_hdd; ++i) {
        if (computer->hdds[i].size < reference->hdd_size) {
            return true;
        }
    }
    return (computer->num_cpu < reference->num_cpu) ||
           (computer->cpu.freq < reference->cpu_freq) ||
           (computer->gpu.memory < reference->gpu_memory) ||
           (computer->ram < reference->ram) ||
           (computer->num_of_exterior_dev < reference->num_of_exterior_dev);
}