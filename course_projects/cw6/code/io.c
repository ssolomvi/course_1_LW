#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "structure.h"
#include "io.h"

uint32_t computer_read_txt(Computer *computer, FILE *in)
{
    fscanf(in, "%s", computer->owner);
    fscanf(in, "%s", computer->name_OS);
    fscanf(in, "%u", &computer->num_cpu);
    fscanf(in, "%s", computer->cpu.name);
    fscanf(in, "%u", &computer->cpu.freq);
    fscanf(in, "%s", computer->gpu.name);
    fscanf(in, "%u", &computer->gpu.memory);
    fscanf(in, "%u", &computer->num_hdd);

    computer->hdds = (HDD *) malloc(computer->num_hdd * sizeof(HDD));
    for (int i = 0; i < computer->num_hdd; ++i) {
        fscanf(in, "%s", computer->hdds[i].type);
        fscanf(in, "%u", &computer->hdds[i].size);
    }

    fscanf(in, "%u", &computer->ram);
    fscanf(in, "%u", &computer->num_of_exterior_dev);

    return !feof(in);
}

uint32_t computer_read_bin(Computer *computer, FILE *in)
{
    fread(computer->owner, sizeof(char), STR_SIZE, in);
    fread(computer->name_OS, sizeof(char), STR_SIZE, in);
    fread(&computer->num_cpu, sizeof(int), 1, in);
    fread(computer->cpu.name, sizeof(char), STR_SIZE, in);
    fread(&computer->cpu.freq, sizeof(int), 1, in);
    fread(computer->gpu.name, sizeof(char), STR_SIZE, in);
    fread(&computer->gpu.memory, sizeof(int), 1, in);
    fread(&computer->num_hdd, sizeof(int), 1, in);

    computer->hdds = (HDD *) malloc(computer->num_hdd * sizeof(HDD));
    for (uint32_t i = 0; i < computer->num_hdd; ++i) {
        fread(computer->hdds[i].type, sizeof(char), STR_SIZE, in);
        fread(&computer->hdds[i].size, sizeof(int), 1, in);
    }

    fread(&computer->ram, sizeof(int), 1, in);
    fread(&computer->num_of_exterior_dev, sizeof(int), 1, in);

    return !feof(in);
}

void computer_write_bin(Computer *computer, FILE *out)
{
    fwrite(computer->owner, sizeof(char), STR_SIZE, out);
    fwrite(computer->name_OS,  sizeof(char), STR_SIZE, out);
    fwrite(&computer->num_cpu, sizeof(int), 1, out);
    fwrite(computer->cpu.name, sizeof(char), STR_SIZE, out);
    fwrite(&computer->cpu.freq, sizeof(int), 1, out);
    fwrite(computer->gpu.name, sizeof(char), STR_SIZE, out);
    fwrite(&computer->gpu.memory, sizeof(int), 1, out);
    fwrite(&computer->num_hdd, sizeof(int), 1, out);

    for (int i = 0; i < computer->num_hdd; ++i) {
        fwrite(computer->hdds[i].type, sizeof(char), STR_SIZE, out);
        fwrite(&computer->hdds[i].size, sizeof(int), 1, out);
    }

    fwrite(&computer->ram, sizeof(int), 1, out);
    fwrite(&computer->num_of_exterior_dev, sizeof(int), 1, out);
}

void computer_print(Computer *computer)
{
    char c;
    printf("Owner: %s\n", computer->owner);
    printf("OS: %s\n", computer->name_OS);
    printf("CPU number / type / frequency: %d / %s / %d\n", computer->num_cpu, computer->cpu.name, computer->cpu.freq);
    printf("GPU type / memory: %s / %d\n", computer->gpu.name, computer->gpu.memory);
    printf("HDD number: %d\n", computer->num_hdd);

    for (int i = 0; i < computer->num_hdd; ++i) {
        c = (char)('a' + i);
        printf("\t%c) HDD type / memory: %s / %d\n", c, computer->hdds[i].type, computer->hdds[i].size);
    }

    printf("RAM: %d\n", computer->ram);
    printf("Number of exterior devices: %d\n", computer->num_of_exterior_dev);

    printf("\n");
}


uint32_t reference_read_txt(Reference *reference, FILE *in)
{
    char spec[STR_SIZE];
    for(int i = 0; i < 6; ++i) {
        fscanf(in, "%s", spec);
        if(!strcmp(spec, "num_cpu:")) {
            fscanf(in, "%d", &reference->num_cpu);
        } else if(!strcmp(spec, "cpu_freq:")) {
            fscanf(in, "%d", &reference->cpu_freq);
        } else if(!strcmp(spec, "gpu_memory:")) {
            fscanf(in, "%d", &reference->gpu_memory);
        } else if(!strcmp(spec, "hdd_size:")) {
            fscanf(in, "%d", &reference->hdd_size);
        } else if(!strcmp(spec, "ram:")) {
            fscanf(in, "%d", &reference->ram);
        } else if(!strcmp(spec, "num_of_exterior_dev:"))
            fscanf(in, "%d", &reference->num_of_exterior_dev);
    }
    return !feof(in);
}