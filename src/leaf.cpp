#include "inc/leaf.hpp"

#include "utils/nibbles.hpp"


Leaf::Leaf(std::vector<uint> nibbles, std::vector<uint64_t> value) {
    nibbles_ = nibbles;
    value_ = value;
    node_type_ = LEAF_NODE;
}

std::vector<uint> Leaf::EncodeKey(const std::vector<uint>& input) {
    return AddHexPrefix(input, true);
}

std::vector<uint> Leaf::DecodeKey(const std::vector<uint>& input) {
    return RemoveHexPrefix(input);
}

std::vector<uint> Leaf::GetKey() {
    return nibbles_;
}

void Leaf::SetKey(std::vector<uint> input) {
    nibbles_ = input;
}

std::vector<uint> Leaf::EncodedKey() {
    return Leaf::EncodeKey(nibbles_);
}

std::vector<std::vector<uint64_t>> Leaf::Raw() {
    std::vector<std::vector<uint64_t>> raw_;
    raw_.push_back(NibbleToBuffer(nibbles_));
    raw_.push_back(value_);
    return raw_;
}
