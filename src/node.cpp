#include "inc/node.hpp"

#include "utils/hex.hpp"
#include "rlp/inc/rlpencode.hpp"
#include "keccak/keccak.h"


std::vector<uint64_t> Node::GetValue() {
    return value_;
}

void Node::SetValue(std::vector<uint64_t> input) {
    value_ = input;
}

std::vector<std::vector<uint64_t>> Node::Raw() {
    std::vector<std::vector<uint64_t>> raw_;
    raw_.resize(1, value_);

    return raw_;
}

std::vector<uint64_t> Node::Serialize() {
    return RLPEncoder::EncodeByteList(Raw());
}

std::vector<uint64_t> Node::Hash() {
    Keccak keccak256 = Keccak(Keccak::Bits::Keccak256);
    std::string byte_str_ = BytesToString(Serialize());
    byte_str_ = keccak256(byte_str_);
    return StringToBytes(byte_str_);
}
