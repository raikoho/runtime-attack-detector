#include "modules.h"
#include "../detector.h"

// extern modules
extern detector_module_t nx_module;
extern detector_module_t return_module;

void register_all_modules() {
    register_module(nx_module);
    register_module(return_module);
}
