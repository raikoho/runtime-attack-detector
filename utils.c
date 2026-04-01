#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>
#include "utils.h"

cpu_state_t get_cpu_state(pid_t pid) {
    struct user_pt_regs regs;
    cpu_state_t state = {0};

    if (ptrace(PTRACE_GETREGSET, pid, NT_PRSTATUS, &regs) == -1) {
        perror("ptrace GETREGSET failed");
    }

    state.pc = regs.pc;
    state.sp = regs.sp;
    state.lr = regs.regs[30]; // LR = x30

    return state;
}
