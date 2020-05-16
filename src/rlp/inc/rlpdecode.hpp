#ifndef RLP_RLP_DECODE_H
#define RLP_RLP_DECODE_H

#include <iostream>
#include <vector>
#include <array>

class RLPDecoder
{
private:
    static std::vector<uint64_t> Decode(const std::vector<uint64_t>& input);

public:
    static std::string DecodeByte(const std::vector<uint64_t>& input);
    static std::string DecodeString(const std::string& input);

    static std::array<std::vector<uint64_t>, 17> DecodeByteList(const std::vector<uint64_t>& input);
};

#endif