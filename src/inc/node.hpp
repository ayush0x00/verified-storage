#ifndef PMT_NODE_H
#define PMT_NODE_H

#include <vector>

class Node {
    protected:
        std::vector<uint64_t> value_;

    public:
        std::vector<uint64_t> GetValue();
        void SetValue(std::vector<uint64_t> input);
        std::vector<std::vector<uint64_t>> Raw();
        std::vector<uint64_t> Serialize();
        std::vector<uint64_t> Hash();
};

#endif