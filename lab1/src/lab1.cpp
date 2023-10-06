#include "lab1.h"

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

void ParentRoutine(const char* pathToChild, std::istream& streamIn, std::ostream& streamOut) {
    std::string filename;
    streamIn >> filename;

    int file = open(filename.c_str(), O_RDONLY);
    if (file == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int fds[2];
    if (pipe(fds)) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // parent
        close(file);
        close(fds[WRITE_END]);
        double res;
        while (read(fds[READ_END], &res, sizeof(double)) > 0) {
            if (std::isinf(res)) {
                streamOut << "Division by zero\n";
                exit(EXIT_FAILURE);
            }
            streamOut << res << '\n';
        }
        close(fds[READ_END]);
    } else {  // child
        close(fds[READ_END]);
        dup2(file, STDIN_FILENO);
        close(file);
        dup2(fds[WRITE_END], STDOUT_FILENO);
        close(file);
        execl(pathToChild, "child", NULL);
        perror("exec");
        exit(EXIT_FAILURE);
    }
}