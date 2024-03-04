
#include <unistd.h>

#include <string>
#include <sstream>

#include "node.h"
#include "topology.h"

bool ExecCommand(Topology &topo, const std::string &input,
                 const std::string &serverName) {
    std::stringstream ss(input);
    std::string command;
    ss >> command;
    if (command == "create") {
        int id, parentId;
        ss >> id >> parentId;
        if (topo.contains(id)) {
            std::cerr << "Error: Already exists\n";
            std::cout << "> ";
            std::cout.flush();
            return false;
        }
        pid_t pid = fork();
        if (pid == -1) {
            std::perror("fork");
            std::exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execl(serverName.c_str(), serverName.c_str(),
                  std::to_string(id).c_str(), std::to_string(parentId).c_str(),
                  nullptr);

        } else {
            NodeId newNode(id, pid);
            topo.insert(newNode);
            std::cout << "Ok: " + std::to_string(pid) + '\n';
        }
    } else if (command == "ping") {
        int id;
        ss >> id;
        if (!topo.contains(id)) {
            std::cerr << "Error: Not found\n";
            std::cout.flush();
            return false;
        }
        if (!ControlNode::get().send(id, "ping")) {
            std::cout << "Ok: 0\n";
            std::cout.flush();
            return false;
        }
        auto response = ControlNode::get().receive();
        if (response == "pong") {
            std::cerr << "Ok: 1\n";
        } else {
            std::cerr << "Ok: 0\n";
        }
    } else if (command == "exec") {
        int id;

        std::string hay, needle;
        ss >> id >> hay >> needle;
        if (!topo.contains(id)) {
            std::cerr << "Error: " + std::to_string(id) + " Not found\n";
            std::cout.flush();
            return false;
        }
        if (!ControlNode::get().send(id, "exec " + hay + ' ' + needle)) {
            std::cerr << "Error: Node is unavailable";
            std::cout.flush();
            return false;
        }
        auto response = ControlNode::get().receive();
        if (response) {
            std::cout << *response << '\n';
        }
    } else {
        std::cout << "Unknown command\n";
        return false;
    }
    return true;
}