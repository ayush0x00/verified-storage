#include "extension.hpp"

#include "nodetype.hpp"
#include "utils/nibbles.hpp"

Extension::Extension(nibble_t nibble, buffer_t value) {
    nibble_ = nibble;
    value_ = value;
    node_type_ = EXTENSION_NODE;
}

nibble_t Extension::EncodeKey(const nibble_t& input) {
    return AddHexPrefix(input, false);
}

nibble_t DecodeKey(const nibble_t& input) {
    return RemoveHexPrefix(input);
}

nibble_t Extension::GetKey() {
    return nibble_;
}

void Extension::SetKey(nibble_t input) {
    nibble_ = input;
}

nibble_t Extension::EncodedKey() {
    return Extension::EncodeKey(nibble_);
}

bufferarray_t Extension::Raw() {
    bufferarray_t raw_;
    raw_.push_back(NibbleToBuffer(EncodedKey()));
    raw_.push_back(value_);
}
