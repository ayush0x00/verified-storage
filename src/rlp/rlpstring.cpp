#include "inc/rlpstring.hpp" 

#include "inc/utils.hpp"

RLPString::RLPString(const std::vector<uint64_t> input) {
    bytes_ = input;
}

std::vector<uint64_t> RLPString::GetBytes() {
    return bytes_;
}

std::string RLPString::AsHexString() {
    return BytesToString(bytes_);
}

RLPString RLPString::Create(const std::vector <uint64_t> input) {
    return RLPString(input);
}

RLPString RLPString::Create(const uint64_t input) {
    if (input == 0) {
        // Only positive non-zero integers are allowed.
        return Create(EmptyByte());
    }
    std::vector<uint64_t> bytes_;
    bytes_.push_back(input);
    return RLPString(bytes_);
}

RLPString RLPString::Create(const char input) {
    if (input == 0) {
        // Only positive non-zero integers are allowed.
        return Create(EmptyByte());
    }
    std::vector<uint64_t> bytes_ = IntegerToBytes(input);
    return RLPString(bytes_);
}

RLPString RLPString::Create(const long input) {
    if (input == 0) {
        // Only positive non-zero integers are allowed.
        return Create(EmptyByte());
    }
    return Create((uint64_t)input);
}

RLPString RLPString::Create(const std::string input) {
    if (input.empty()) {
        return Create(EmptyByte());
    }
    std::vector<uint64_t> bytes_ = StringToBytes(StringToHex(input));
    return RLPString(bytes_);
}
