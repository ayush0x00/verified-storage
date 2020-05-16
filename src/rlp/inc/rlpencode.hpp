#ifndef RLP_RLP_ENCODE_H
#define RLP_RLP_ENCODE_H

#include "rlpstring.hpp"

class RLPEncoder {
    private:
        static std::vector<uint64_t> EncodeLength(const int len, const int offset);
        static std::vector<uint64_t> Encode(const std::vector<uint64_t> bytes_value);

    public:
        static std::string GetBytes(const std::vector<uint64_t> input);
        static std::vector<uint64_t> EncodeString(RLPString input);
        static std::vector<uint64_t> EncodeString(const std::string input);

        static std::vector<uint64_t> EncodeByteList(const std::vector<std::vector<uint64_t>>& input);
};

#endif