#ifndef PMT_UTILS_GENERALISED_H
#define PMT_UTILS_GENERALISED_H

#include <sstream>
#include <iomanip>

template <typename T>
std::string GetBytes(T input) {
    std::stringstream stream_;
    stream_ << "<Bytes";
    for(std::size_t i = 0; i < input.size(); i++ ) {
        stream_ << " " << input[i];
    }

    stream_ << ">";

    return stream_.str();
}

template<typename T>
std::vector<T> Slice(const std::vector<T>& vect, int start, int end) {
   if(end = -1) {
       end = vect.size() - 1;
   }

   auto first_ = vect.begin() + start;
   auto last_ = vect.begin() + end + 1;
   std::vector<T> sliced_vector(first_, last_);

   return sliced_vector;
}

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return std::is_base_of<Base, T>::value;
}

#endif
