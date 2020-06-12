#ifndef PMT_BRANCH_NODE_H
#define PMT_BRANCH_NODE_H

#include <map>

#include "node.hpp"

class Branch : public Node {
    private:
        bufferarray_t branches_;

    public:
        Branch();
        // ~Branch();

        static Node FromBuffer(const bufferarray_t &input);
        void SetBranch(const int loc, const buffer_t &input);
        buffer_t GetBranch(const int input);
        bufferarray_t GetBranches();
        std::map<int, buffer_t> GetChildren();

        bufferarray_t Raw();
};

#endif