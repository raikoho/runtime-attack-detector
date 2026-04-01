#include <sys/ptrace.h>
#include <sys/uio.h>
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"

// AArch64 register structure (define it ourselves for portability)
struct user_pt_regs {
    unsigned long regs[31];
    unsigned long sp;
    unsigned long pc;
    unsigned long pstate;
};

cpu_state_t get_cpu_state(pid_t pid) {
    struct iovec iov;
    struct user_pt_regs regs;

    cpu_state_t state = {0};

    memset(&regs, 0, sizeof(regs));

    iov.iov_base = &regs;
    iov.iov_len = sizeof(regs);

    if (ptrace(PTRACE_GETREGSET, pid, (void*)NT_PRSTATUS, &iov) == -1) {
        perror("ptrace GETREGSET failed");
        exit(1);
    }

    state.pc = regs.pc;
    state.sp = regs.sp;
    state.lr = regs.regs[30]; // x30 = LR

    return state;
}
