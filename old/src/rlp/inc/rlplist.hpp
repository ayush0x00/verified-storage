#ifndef RLP_RLP_LIST_H
#define RLP_RLP_LIST_H

#include <iostream>
#include <vector>

class RLPList {
    private:
        std::vector<uint64_t> bytes_;
        RLPList(std::vector<uint64_t> bytes);
    public:
        std::vector<uint64_t> GetBytes();
        std::string AsHexString();
        static RLPList Create(const std::vector<uint64_t> input);
        static RLPList Create(const std::string input[]);
};


#endif