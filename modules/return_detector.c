#include <stddef.h>
#include "../detector.h"

int is_valid_code(uint64_t addr) {
    return (addr >= 0x400000 && addr <= 0x500000); // simplified
}

int return_check(cpu_state_t *state) {
    if (!is_valid_code(state->pc)) {
        return 1;
    }
    return 0;
}

detector_module_t return_module = {
    .name = "Invalid Return Address",
    .init = NULL,
    .check = return_check,
    .cleanup = NULL
};
