#ifndef PMT_PATH_H
#define PMT_PATH_H

#include <vector>

#include "aliasadvance.hpp"


class Path {
    private:
        node_t node_;
        nibble_t remaining_;
        std::vector<node_t> stack_;

    public:
        Path(const node_t &node, const nibble_t &remaining, const std::vector<node_t> &stack);

        node_t GetNode();
        void SetNode(const node_t &node);
        nibble_t GetRemaining();
        void SetRemaining(const nibble_t &remaining);
        std::vector<node_t> GetStack();
        void SetStack(const std::vector<node_t> &stack);
};

#endif