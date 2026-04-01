#include <stdio.h>
#include "../detector.h"

int is_stack(uint64_t addr) {
    return (addr >= 0x7ffffffff000); // simplified
}

int is_heap(uint64_t addr) {
    return (addr >= 0x555555000000 && addr <= 0x555556000000);
}

int nx_check(cpu_state_t *state) {
    if (is_stack(state->pc) || is_heap(state->pc)) {
        return 1;
    }
    return 0;
}

detector_module_t nx_module = {
    .name = "NX Violation",
    .init = NULL,
    .check = nx_check,
    .cleanup = NULL
};
