#pragma once

#include <iostream>
#include <set>

struct NodeId {
    NodeId(int id) : id(id), pid(-1) {}
    NodeId(int id, int pid) : id(id), pid(pid) {}
    int id;
    int pid;
    operator int();
};

inline bool operator<(const NodeId& a, const NodeId& b) {
    return a.id < b.id;
}

using Topology = std::set<NodeId>;