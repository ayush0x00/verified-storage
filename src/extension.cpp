#include "inc/extension.hpp"

#include "utils/nibbles.hpp"

Extension::Extension(std::vector<uint> nibble, std::vector<uint64_t> value) {
    nibble_ = nibble;
    value_ = value;
    node_type_ = EXTENSION_NODE;
}

std::vector<uint> Extension::EncodeKey(const std::vector<uint>& input) {
    return AddHexPrefix(input, false);
}

std::vector<uint> DecodeKey(const std::vector<uint>& input) {
    return RemoveHexPrefix(input);
}

std::vector<uint> Extension::GetKey() {
    return nibble_;
}

void Extension::SetKey(std::vector<uint> input) {
    nibble_ = input;
}

std::vector<uint> Extension::EncodedKey() {
    return Extension::EncodeKey(nibble_);
}

std::vector<std::vector<uint64_t>> Extension::Raw() {
    std::vector<std::vector<uint64_t>> raw_;
    raw_.push_back(NibbleToBuffer(EncodedKey()));
    raw_.push_back(value_);
}


