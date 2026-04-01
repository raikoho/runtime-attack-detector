#ifndef DETECTOR_H
#define DETECTOR_H

#include <stdint.h>

typedef struct {
    uint64_t pc;
    uint64_t sp;
    uint64_t lr;
} cpu_state_t;

typedef struct {
    const char *name;
    int (*init)();
    int (*check)(cpu_state_t *state);
    void (*cleanup)();
} detector_module_t;

void register_module(detector_module_t module);
void run_detectors(cpu_state_t *state);

#endif
