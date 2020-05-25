#include "path.hpp"

Path::Path(const Node &node, const nibble_t &remaining, const std::stack<Node> &stack) {
    node_ = node;
    remaining_ = remaining;
    stack_ = stack;
}

Node Path::GetNode() {
    return node_;
}

void Path::SetNode(const Node &node) {
    node_ = node;
}

nibble_t Path::GetRemaining() {
    return remaining_;
}

void Path::SetRemaining(const nibble_t &remaining) {
    remaining_ = remaining_;
}

std::stack<Node> Path::GetStack() {
    return stack_;
}

void Path::SetStack(const std::stack<Node> &stack) {
    stack_ = stack;
}
