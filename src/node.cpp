#include "inc/node.hpp"

#include "utils/hex.hpp"
#include "rlp/inc/rlpencode.hpp"
#include "keccak/keccak_buffer.hpp"


buffer_t Node::GetValue() {
    return value_;
}

void Node::SetValue(buffer_t input) {
    value_ = input;
}

bufferarray_t Node::Raw() {
    bufferarray_t raw_;
    raw_.resize(1, value_);

    return raw_;
}

buffer_t Node::Serialize() {
    return RLPEncoder::EncodeByteList(Raw());
}

buffer_t Node::Hash() {
    KeccakBuffer buffer_hash_ = KeccakBuffer();
    return buffer_hash_(Serialize());
}
