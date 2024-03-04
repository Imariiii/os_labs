#include "lab3.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "shared_memory.h"
#include "utils.h"

int ParentRoutine(const char* pathToChild, std::istream& streamIn,
                  std::ostream& streamOut) {
    std::string filename;
    streamIn >> filename;

    int file = open(filename.c_str(), O_RDONLY);
    if (file == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    SharedMemory<Slot> shm(SHARED_MEMORY_NAME);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // parent
        close(file);
        while (shm.readLock() && !shm.getData()->isEmpty) {
            float res = shm.getData()->num;
            if (std::isinf(res)) {
                streamOut << "Division by zero\n";
                return -1;
            }
            streamOut << res << '\n';
            shm.writeUnlock();
        }
        wait(nullptr);
    } else {  // child
        dup2(file, STDIN_FILENO);
        close(file);
        execl(pathToChild, "child", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
    return 0;
}