#include "keccak_buffer.hpp"

#include "utils/hex.hpp"

KeccakBuffer::KeccakBuffer() {
    keccak_ = Keccak(Keccak::Bits::Keccak256);
}

KeccakBuffer::KeccakBuffer(const Keccak::Bits bits) {
    keccak_ = Keccak(bits);
}

buffer_t KeccakBuffer::operator()(const buffer_t& input) {
    std::string byte_str_ = BytesToString(input);

    auto byte_hash_ = keccak_(byte_str_);
    
    return StringToBytes(byte_hash_);
}

