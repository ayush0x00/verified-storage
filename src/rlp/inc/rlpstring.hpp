#ifndef RLP_RLP_STRING_H
#define RLP_RLP_STRING_H

#include <iostream>
#include <vector>

class RLPString {
    private:
        std::vector<uint64_t> bytes_;
        RLPString(const std::vector<uint64_t> bytes);

    public:
        std::vector<uint64_t> GetBytes();
        std::string AsHexString();
        static RLPString Create(const std::vector<uint64_t> input);
        static RLPString Create(const char input);
        static RLPString Create(const uint64_t input);
        static RLPString Create(const long input);
        static RLPString Create(const std::string input);
};

#endif