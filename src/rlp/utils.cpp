#include "inc/utils.hpp"

#include <sstream>
#include <iomanip>
#include <algorithm>

#include "inc/constants.inc"

std::string BytesToString(std::vector<uint64_t> input) {
    std::string byte_str_ {""};
    for(std::string::size_type i = 0; i < input.size(); i++ ) {
        auto byte_ = input[i];
        byte_str_ += byte_;
    }
    return byte_str_;
}

std::vector<uint64_t> EmptyByte() {
    std::vector<uint64_t> bytes_ = StringToBytes(std::to_string(EMPTY_STRING));
    return bytes_;
}

bool IsNumeric(const std::string& input) {
    return std::all_of(input.begin(), input.end(), ::isdigit);
}

std::uint64_t SafeParseInt(const std::string& input, unsigned int base) {
    if (input.substr(0, 2) == "00") {
        // Todo: Throw exception
        return 0;
    }

    return std::stoul(input, 0, base);
}

std::vector<uint64_t> StringToBytes(const std::string& input) {
    std::vector<uint64_t> bytes_;
    std::string hex_str_ {""};
    uint64_t hex_char_ {0};
    std::string original_string_ = StripHexPrefix(input);

    for(std::string::size_type i = 0; i < original_string_.length(); i = i + 2) {
        hex_str_ = original_string_.substr(i, 2);
        hex_char_ = std::stoul(hex_str_, nullptr, 16);
        bytes_.push_back(hex_char_);
    }

    return bytes_;
}

std::vector<uint64_t> IntegerToBytes(const uint64_t input) {
    std::vector<uint64_t> bytes_;

    std::ostringstream output_;
    // Only positive integers are allowed
    output_ << abs(input);

    std::string converter_str_ = IntegerToHex(std::stoi(output_.str()));
    bytes_.push_back(SafeParseInt(converter_str_, 16));
    return bytes_;
}

uint64_t BytesToInteger(const std::vector<char>& input) {
    uint64_t result_ {0};
    for(auto item_ : input) {
        result_ = result_ * 10 + item_;
    }
    return result_;
}

bool IsHexPrefixed(const std::string& input) {
    return input.substr(0, 2) == "0x";
}

std::string InsertHexPrefix(const std::string& input) {
    return "0x" + input;
}

std::string StripHexPrefix(const std::string& input) {
    std::string result_ {input};
    if(IsHexPrefixed(input)) {
        result_ = input.substr(2, input.length());
    }
    return result_;
}

bool IsHexString(const std::string& input) {
    bool flag_ = true;
    std::string stripped_string_ = StripHexPrefix(input);

    for(std::string::size_type i = 0; i < stripped_string_.length(); i++) {
        if(!isxdigit(input[i])) {
            flag_ = false;
            break;
        }
    }
    return flag_;
}

std::string PadToEven(const std::string& input) {
    return (input.length() % 2) ? "0" + input : input;
}

std::string IntegerToHex(const uint64_t input) {
    if (input < 0) {
        // Todo: Throw an error
        return "";
    }

    std::ostringstream stream_;
    //stream_ << std::setfill('0') << std::setw(sizeof(input) * 2) << std::hex << input;
    stream_ << std::hex << input;

    return PadToEven(stream_.str());
}

uint64_t HexToInteger(const std::string& input) {
    std::string hex_str_ = StripHexPrefix(input);
    uint64_t number = std::stoul(hex_str_, nullptr, 16);
    return number;
}

std::string StringToHex(const std::string& input, bool upper) {
    std::ostringstream stream_;

    unsigned int converter_ {0};

    for (std::string::size_type i = 0; i < input.length(); ++i)
    {
        converter_ = (unsigned int)(unsigned char)input[i];
        stream_ << std::hex << std::setfill('0') <<
            std::setw(2) << (upper ? std::uppercase : std::nouppercase) << converter_;
    }

    return InsertHexPrefix(stream_.str());
}

std::string HexToString(const std::string& input) {
    std::string stream_ {""};
    std::string hex_str_ {""};

    std::string::size_type start = IsHexPrefixed(input) ? 2 : 0;
    for(std::string::size_type i = start; i < input.length(); i = i+2) {
        hex_str_ = input.substr(i, 2);
        stream_ += std::stoul(hex_str_, nullptr, 16);
    }
    
    return stream_;
}

std::vector<uint64_t> ToBytes(const std::string& input) {
    std::vector<uint64_t> bytes_;
    if(input.empty()) {
        // Empty string
        bytes_ = EmptyByte();
    } else if(IsNumeric(input)) {
        // It's a positive number
        auto number_ = SafeParseInt(input);
        bytes_ = IntegerToBytes(number_);
    } else {
        if(IsHexString(input)) {
            bytes_ = StringToBytes(PadToEven(StripHexPrefix(input)));
        } else {
            bytes_ = StringToBytes(StringToHex(input));
        }
    }

    return bytes_;
}

// std::vector<uint64_t> ArrayToBytes(const std::string input[]) {
//     std::vector<uint64_t> bytes_;

//     for(std::string::size_type i=0; i < sizeof(input); i++) {

//     }
// }