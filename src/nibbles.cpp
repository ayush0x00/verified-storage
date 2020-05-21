#include "utils/nibbles.hpp"

#include "utils/hex.hpp"                                                                                                                                       

std::vector<uint> StringToNibble(const std::string& input) {
    std::vector<uint64_t> buffer_ = StringToBytes(StringToHex(input));
    return BufferToNibble(buffer_);
}

std::vector<uint> BufferToNibble(const std::vector<uint64_t>& input) {
    std::vector<uint> nibbles_;
    nibbles_.resize(input.size() * 2);

    for(std::string::size_type i = 0; i < input.size(); i++) {
        int loc_ = i * 2;
        nibbles_.at(loc_) = input.at(i) >> 4;
        ++loc_;
        nibbles_.at(loc_) = nibbles_.at(i) % 16;
    }

    return nibbles_;
}

std::vector<uint64_t> NibbleToBuffer(const std::vector<uint>& input) {
    std::vector<uint64_t> buffer_;
    buffer_.resize(input.size() / 2);

    for(std::string::size_type i = 0; i < buffer_.size(); i++) {
        int loc_ = i * 2;
        buffer_.at(i) = (input.at(loc_) << 4) + input.at(++loc_);
    }

    return buffer_;
}

int MatchingNibbleLength(std::vector<uint>& input_1, std::vector<uint>& input_2) {
    std::string::size_type i = 0;
    while((input_1.at(i) == input_2.at(i)) && input_1.size() > i) {
        i++;
    }

    return i;
}

bool DoKeysMatch(std::vector<uint>& input_1, std::vector<uint>& input_2) {
    int length_ = MatchingNibbleLength(input_1, input_2);
    return length_ == input_1.size() && length_ == input_2.size();
}

std::vector<uint> AddHexPrefix(const std::vector<uint>& input, bool terminator) {
    std::vector<uint> bytes_;

    if(input.size() % 2) {
        bytes_.push_back(1);
    } else {
        bytes_.push_back(0);
        bytes_.push_back(0);
    }

    bytes_.insert(bytes_.end(), input.begin(), input.end());

    if(terminator) {
        bytes_.at(0) += 2;
    }

    return bytes_;
}

std::vector<uint> RemoveHexPrefix(const std::vector<uint>& input) {
    std::vector<uint> bytes_;

    bytes_ = (input.at(0) % 2) ? Slice(input, 1) : Slice(input, 2);

    return bytes_;
}

bool IsTerminator(const std::vector<uint>& input) {
    return input.at(0) > 1;
}



int main() {
    std::string test = "test";

    std::vector<uint> nibble_ = StringToNibble(test);
    std::cout << "Nibble: " << GetBytes(nibble_) << std::endl;

    std::vector<uint64_t> buffer_ = NibbleToBuffer(nibble_);
    std::cout << "Buffer: " << GetBytes(buffer_) << std::endl;

    std::vector<uint> nibble_1_ = StringToNibble("testa");
    std::cout << "Nibble: " << GetBytes(nibble_1_) << std::endl;
    std::cout << "Matching: " << MatchingNibbleLength(nibble_, nibble_1_) << std::endl;
    std::cout << "Key Matching: " << DoKeysMatch(nibble_, nibble_1_) << std::endl;

    std::vector<uint> hex_nibble_ = AddHexPrefix(nibble_1_, false);
    std::cout << "Add Hex Prefix: " << GetBytes(hex_nibble_) << std::endl;

    std::cout << "Is Terminating: " << IsTerminator(hex_nibble_) << std::endl;

    hex_nibble_ = RemoveHexPrefix(hex_nibble_);
    std::cout << "Remove Hex Prefix: " << GetBytes(hex_nibble_) << std::endl;

    return 0;
}