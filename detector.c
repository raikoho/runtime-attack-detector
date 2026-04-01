#include <stdio.h>
#include "detector.h"

#define MAX_MODULES 10

static detector_module_t modules[MAX_MODULES];
static int module_count = 0;

void register_module(detector_module_t module) {
    if (module_count < MAX_MODULES) {
        modules[module_count++] = module;
    }
}

void run_detectors(cpu_state_t *state) {
    for (int i = 0; i < module_count; i++) {
        if (modules[i].check(state)) {
            printf("[ALERT] %s triggered at PC=0x%lx\n",
                   modules[i].name, state->pc);
        }
    }
}
