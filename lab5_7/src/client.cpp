#include <signal.h>
#include <unistd.h>

#include <iostream>

#include "node.h"
#include "topology.h"
#include "client_util.h"



int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Not enough arguments\n";
        std::exit(EXIT_FAILURE);
    }
    std::string command;
    std::cout << "> ";

    Topology topo;
    while (std::getline(std::cin, command)) {
        ExecCommand(topo, command, argv[1]);
        std::cout << "> ";
        std::cout.flush();
    }

    for (auto node : topo) {
        kill(node.pid, SIGKILL);
    }
}