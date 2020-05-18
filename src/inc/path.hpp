#ifndef PMT_PATH_H
#define PMT_PATH_H

#include <stack>
#include <string>

#include "node.hpp"

class Path {
    private:
        Node node_;
        std::vector<uint> remaining_;
        std::stack<Node> stack_;

    public:
        Path(const Node &node, const std::vector<uint> &remaining, const std::stack<Node> &stack);

        Node GetNode();
        void SetNode(const Node &node);
        std::vector<uint> GetRemaining();
        void SetRemaining(const std::vector<uint> &remaining);
        std::stack<Node> GetStack();
        void SetStack(const std::stack<Node> &stack);
};

#endif