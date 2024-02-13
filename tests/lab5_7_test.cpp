#include <gtest/gtest.h>
#include <signal.h>

#include "node.h"
#include "topology.h"
#include "client_util.h"

TEST(Lab5Tests, CalculationTest) {
    ASSERT_EQ(ComputationNode::findAllOccurencies("memmem", "mem"), "0;3");
    ASSERT_EQ(ComputationNode::findAllOccurencies("1000", "00"), "1;2");
}

TEST(Lab5Tests, ExecTest) {
    auto *cstr = std::getenv("PATH_TO_SERVER");
    ASSERT_TRUE(cstr);
    pid_t pid = fork();
    if (pid == -1) {
        std::perror("fork");
        std::exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execl(cstr, cstr, std::to_string(1).c_str(), std::to_string(-1).c_str(),
              nullptr);
    }
    ControlNode::get().send(1, "exec ooloo oo");
    ASSERT_EQ(ControlNode::get().receive().value(), "Ok: 1 0;3");
    kill(pid, SIGKILL);
}

TEST(Lab5Tests, TopoTest) {
    auto *cstr = std::getenv("PATH_TO_SERVER");
    ASSERT_TRUE(cstr);
    Topology topo;
    EXPECT_EQ(ExecCommand(topo, "create 1 -1", cstr), true);
    EXPECT_EQ(ExecCommand(topo, "create 1 -1", cstr), false);
    EXPECT_EQ(ExecCommand(topo, "create 2 -1", cstr), true);
    for (auto node : topo) {
        kill(node.pid, SIGKILL);
    }
}