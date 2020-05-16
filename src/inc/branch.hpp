#ifndef PMT_BRANCH_NODE_H
#define PMT_BRANCH_NODE_H

#include <array>

#include "node.hpp"

class Branch : public Node {
    private:
        std::vector<std::vector<uint64_t>> branches_;

    public:
        Branch();
        ~Branch();

        static Node FromBuffer(std::vector<std::vector<uint64_t>>& input);
        void SetBranch(const int loc, std::vector<uint64_t> input);
        std::vector<uint64_t> GetBranch(const int input);
        std::vector<std::vector<uint64_t>> GetBranches();
        std::map<int, std::vector<uint64_t>> GetChildren();

        std::vector<std::vector<uint64_t>> Branch::Raw();
};

#endif