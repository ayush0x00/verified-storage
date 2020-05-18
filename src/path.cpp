#include "inc/path.hpp"

Path::Path(const Node &node, const std::vector<uint> &remaining, const std::stack<Node> &stack) {
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

std::vector<uint> Path::GetRemaining() {
    return remaining_;
}

void Path::SetRemaining(const std::vector<uint> &remaining) {
    remaining_ = remaining_;
}

std::stack<Node> Path::GetStack() {
    return stack_;
}

void Path::SetStack(const std::stack<Node> &stack) {
    stack_ = stack;
}
