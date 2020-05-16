#include "inc/rlpencode.hpp"

#include "inc/constants.inc"
#include "inc/utils.hpp"
#include "inc/rlpstring.hpp"


std::string RLPEncoder::GetBytes(const std::vector<uint64_t> input) {
    std::string byte_str_ {"<Bytes"};
    for(std::string::size_type i = 0; i < input.size(); i++ ) {
        auto byte_ = input[i];
        byte_str_ += " " + IntegerToHex(byte_);
    }

    return byte_str_ + ">";
}

std::vector<uint64_t> RLPEncoder::EncodeLength(const int len, const int offset) {
    std::vector<uint64_t> encode_length_;
    if (len <= SINGLE_BYTE_STRING) {
        encode_length_ = IntegerToBytes(len + offset);
    } else {
        const std::string hex_len_ = IntegerToHex(len);
        std::vector<uint64_t> second_part_ = StringToBytes(hex_len_);

        const auto l_length_ = second_part_.size();
        const auto number_ = offset + l_length_;
        encode_length_ = IntegerToBytes(number_);
        encode_length_.insert(encode_length_.end(), second_part_.begin(), second_part_.end());
    }

    return encode_length_;
}

std::vector<uint64_t> RLPEncoder::Encode(const std::vector<uint64_t> bytes_value) {
    std::vector<uint64_t> encode_;

    if (bytes_value.empty() || (bytes_value.size() == 1 && bytes_value[0] == EMPTY_STRING)) {
        // The input is non value
        encode_.push_back(NON_VALUE_STRING);
    } else if(bytes_value.size() == 1 && bytes_value[0] <= SHORT_STRING) {
        // It's a single byte between [0x00, 0x7f]
        encode_ = bytes_value;
    } else if(bytes_value.size() == 1 && (bytes_value[0] > SHORT_STRING && bytes_value[0] <= LAST_STRING)) {
        // It's a single byte between [0x80, 0xff]
        encode_ = EncodeLength(bytes_value.size(), SHORT_STRING + 1);
        encode_.insert(encode_.end(), bytes_value.begin(), bytes_value.end());
    } else if(bytes_value.size() <= 55) {
        // It's 2-55 byte string
        encode_ = EncodeLength(bytes_value.size(), SHORT_STRING + 1);
        encode_.insert(encode_.end(), bytes_value.begin(), bytes_value.end());
    } else if(bytes_value.size() > 55) {
        // It's a string with more than 55 bytes long.
        encode_ = EncodeLength(bytes_value.size(), LONG_STRING);
        encode_.insert(encode_.end(), bytes_value.begin(), bytes_value.end());
    }

    return encode_;
}

std::vector<uint64_t> RLPEncoder::EncodeString(RLPString input) {
    return Encode(input.GetBytes());
}

std::vector<uint64_t> RLPEncoder::EncodeString(const std::string input) {
    RLPString rlp_str_ = RLPString::Create(input);
    return EncodeString(rlp_str_);
}
