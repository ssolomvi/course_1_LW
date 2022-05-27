#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <inttypes.h>

#define STR_SIZE 32

typedef struct {
    char name[STR_SIZE];
    int freq;
} CPU;

typedef struct {
    char name[STR_SIZE];
    int memory;
} GPU;

typedef struct {
    char type[STR_SIZE];
    int size;
} HDD;

typedef struct {
    char owner[STR_SIZE];
    char name_OS[STR_SIZE];
    int num_cpu;
    CPU cpu;
    GPU gpu;
    int num_hdd;
    HDD *hdds;
    int ram;
    int num_of_exterior_dev;
} Computer;

typedef struct {
    int num_cpu;
    int cpu_freq;
    int gpu_memory;
    int hdd_size;
    int ram;
    int num_of_exterior_dev;
} Reference;

#endif // STRUCTURE_H
