#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

#include "detector.h"
#include "utils.h"
#include "modules/modules.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <program>\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // child
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    } else {
        // parent (detector)
        wait(NULL);

        register_all_modules();

        while (1) {
            ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
            wait(NULL);

            cpu_state_t state = get_cpu_state(pid);
            run_detectors(&state);
        }
    }

    return 0;
}
