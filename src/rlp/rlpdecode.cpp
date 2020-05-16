#include "inc/rlpdecode.hpp"

#include "inc/utils.hpp"
#include "inc/rlpstring.hpp"


std::vector<uint64_t> RLPDecoder::Decode(const std::vector<uint64_t>& bytes_input) {
    std::vector<uint64_t> decoded_;
    const auto first_byte_ = bytes_input[0];
    int length_ {0};

    if(first_byte_ <= SHORT_STRING) {
        // a single byte whose value is in the [0x00, 0x7f] range, that byte is its own RLP encoding.
        decoded_ = bytes_input;
    } else if(first_byte_ == NON_VALUE_STRING) {
        // Non value whose value is 0x80
        decoded_ = EmptyByte();
    } else if(first_byte_ <= LONG_STRING) {
        // string is 0-55 bytes long. 
        // A single byte with value 0x80 plus the length of the string followed by the string
        // The range of the first byte is [0x80, 0xb7]
        length_ = first_byte_ - (SHORT_STRING + 1);
        decoded_ = slice(bytes_input, 1, length_);
    } else if(first_byte_ <= 0xbf) {
        // string is more than 55 bytes long. 
        // A single byte with value 0xb7 plus the length of length of the string followed by the string.
        // The range of the first byte is [0xb8, 0xbf]
        auto l_length_ = first_byte_ - LONG_STRING;
        auto length_ = bytes_input.size() - (l_length_ + 1);

        decoded_ = slice(bytes_input, l_length_ + 1, length_ + 1); // + 1 for first byte length
    } else if(first_byte_ <= 0xf7) {
        // a list between 0-55 bytes long
        length_ = first_byte_ - 0xbf;
        auto inner_reminder = slice(bytes_input, 1, length_);
        // while(inner_reminder.size()) {
        //     auto 
        // }
    } else {
        // a list over 55 bytes long
    }

    return decoded_;
}


std::string RLPDecoder::DecodeByte(const std::vector<uint64_t>& input) {
    if(input.empty()) {
        return BytesToString(EmptyByte());
    }

    const std::vector<uint64_t> decoded_ = Decode(input);
    
    return BytesToString(decoded_);
}


std::string RLPDecoder::DecodeString(const std::string& input) {
    if(input.empty()) {
        return BytesToString(EmptyByte());
    }

    const std::vector<uint64_t> byte_input_ = ToBytes(input);
    const std::vector<uint64_t> decoded_ = Decode(byte_input_);

    return BytesToString(decoded_);
}

std::array<std::vector<uint64_t>, 17> DecodeByteList(const std::vector<uint64_t>& input) {
    // Todo complete this
    std::array<std::vector<uint64_t>, 17> bytes_array_;
    bytes_array_[0] = input;
    return bytes_array_;
}