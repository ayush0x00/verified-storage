#include "utils/nibbles.hpp"

#include "utils/hex.hpp"                                                                                                                                       

std::vector<uint> BufferToNibble(const std::string& input) {
    std::vector<uint64_t> buffer_ = StringToBytes(StringToHex(input));
    std::vector<uint> nibbles_;
    nibbles_.resize(input.size() * 2);

    for(std::string::size_type i = 0; i < buffer_.size(); i++) {
        int loc_ = i * 2;
        nibbles_[loc_] = buffer_[i] >> 4;
        ++loc_;
        nibbles_[loc_] = buffer_[i] % 16;
    }

    return nibbles_;
}

std::vector<uint64_t> NibbleToBuffer(const std::vector<uint>& input) {
    std::vector<uint64_t> buffer_;
    buffer_.resize(input.size() / 2);

    for(std::string::size_type i = 0; i < buffer_.size(); i++) {
        int loc_ = i * 2;
        buffer_[i] = (input[loc_] << 4) + input[++loc_];
    }

    return buffer_;
}

int MatchingNibbleLength(std::vector<uint>& input_1, std::vector<uint>& input_2) {
    std::string::size_type i = 0;
    while((input_1[i] == input_2[i]) && input_1.size() > i) {
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
        bytes_[0] += 2;
    }

    return bytes_;
}

std::vector<uint> RemoveHexPrefix(const std::vector<uint>& input) {
    std::vector<uint> bytes_;

    bytes_ = (input[0] % 2) ? slice(input, 1) : slice(input, 2);

    return bytes_;
}

bool IsTerminator(const std::vector<uint>& input) {
    return input[0] > 1;
}



int main() {
    std::string test = "test";

    std::vector<uint> nibble_ = BufferToNibble(test);
    std::cout << "Nibble: " << GetBytes(nibble_) << std::endl;

    std::vector<uint64_t> buffer_ = NibbleToBuffer(nibble_);
    std::cout << "Buffer: " << GetBytes(buffer_) << std::endl;

    std::vector<uint> nibble_1_ = BufferToNibble("testa");
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