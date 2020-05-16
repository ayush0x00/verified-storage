#ifndef RLP_TEMPLATE_UTILS_H
#define RLP_TEMPLATE_UTILS_H

#include "constants.inc"


template<typename T>
bool IsNonValue(T input) {
    bool status = false;
    if(input == NULL) {
        status = true;
    } else if(typeid(input) == typeid(std::vector<unsigned char>)) {
        status = input.empty();
    } else if(typeid(input) == typeid(std::string)) {
        status = input.empty();
    } else if((typeid(input) == typeid(long)) || typeid(input) == typeid(uint64_t)) {
        status = (input <= 0);
    } else {
        // Todo check if it is an array / pointer
    }
    
    return status;
}

template<typename T>
std::vector<T> slice(const std::vector<T>& v, int start, int end) {
   auto first_ = v.begin() + start;
   auto last_ = v.begin() + end + 1;
   std::vector<T> sliced_vector(first_, last_);

   return sliced_vector;
}

template<typename T>
int GetLength(const T& input) {
    if (!input || input.size() == 0) {
        return EMPTY_STRING;
    }

    const std::vector<char> input_byte_ = ToBytes(input);
    const auto first_byte_ = input_byte_[0];

    int result = 0;

    if(first_byte_ <= SHORT_STRING) {
        result = input_byte_.size();
    } else if(first_byte_ <= LONG_STRING) {
        result = first_byte_ - SHORT_STRING;
    } else if(first_byte_ <= SHORT_LIST) {
        result = first_byte_ - 0xb6;
    } else if(first_byte_ <= 0xf7) {
        // a list between 0-55 bytes long
        result = first_byte_ - SHORT_LIST;
    } else {
        // a list over 55 bytes long
        const auto l_length_ = first_byte_ - LONG_LIST;

        const std::vector<char> part_byte_ = slice(input_byte_, 1, l_length_);
        // part_byte_ = std::vector<char>(input_byte_.begin() + 1, input_byte_.begin() + l_length_);

        const auto length = SafeParseInt(part_byte_.data(), 16); 

        result = l_length_ + length;
    }

    return result;
}

#endif
