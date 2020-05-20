#ifndef PMT_PATH_H
#define PMT_PATH_H

#include <stack>
#include <string>

#include "node.hpp"

class Path {
    private:
        Node node_;
        nibble_t remaining_;
        std::stack<Node> stack_;

    public:
        Path(const Node &node, const nibble_t &remaining, const std::stack<Node> &stack);

        Node GetNode();
        void SetNode(const Node &node);
        nibble_t GetRemaining();
        void SetRemaining(const nibble_t &remaining);
        std::stack<Node> GetStack();
        void SetStack(const std::stack<Node> &stack);
};

#endif