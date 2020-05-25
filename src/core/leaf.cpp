#include "leaf.hpp"

#include "nodetype.hpp"
#include "utils/nibbles.hpp"

Leaf::Leaf(nibble_t nibbles, buffer_t value) {
    nibbles_ = nibbles;
    value_ = value;
    node_type_ = LEAF_NODE;
}

nibble_t Leaf::EncodeKey(const nibble_t& input) {
    return AddHexPrefix(input, true);
}

nibble_t Leaf::DecodeKey(const nibble_t& input) {
    return RemoveHexPrefix(input);
}

nibble_t Leaf::GetKey() {
    return nibbles_;
}

void Leaf::SetKey(nibble_t input) {
    nibbles_ = input;
}

nibble_t Leaf::EncodedKey() {
    return Leaf::EncodeKey(nibbles_);
}

bufferarray_t Leaf::Raw() {
    bufferarray_t raw_;
    raw_.push_back(NibbleToBuffer(nibbles_));
    raw_.push_back(value_);
    return raw_;
}
