#ifndef PMT_EXTENSION_NODE_H
#define PMT_EXTENSION_NODE_H

#include <array>

#include "node.hpp"

class Extension : public Node {
    private:
        std::vector<uint> nibble_;

    public:
        Extension(std::vector<uint> nibble, std::vector<uint64_t> value);
        ~Extension();

        static std::vector<uint> EncodeKey(const std::vector<uint>& input);
        static std::vector<uint> DecodeKey(const std::vector<uint>& input);
        
        std::vector<uint> GetKey();
        void SetKey(std::vector<uint> input);
        std::vector<uint> EncodedKey();

        std::vector<std::vector<uint64_t>> Raw();
};

#endif